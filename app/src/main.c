#include <zephyr/kernel.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/app_memory/app_memdomain.h>
#include "credentials.h"
#include "parser.h"

#define PARSER_STACK_SIZE 2048
#define PRIORITY 5
#define PART_ALIGN 32U
#define PART_SIZE  PART_ALIGN

K_THREAD_STACK_DEFINE(parser_stack, PARSER_STACK_SIZE);
static struct k_thread parser_thread;

K_APP_BMEM(app_part) static uint8_t app_storage[PART_SIZE]
__aligned(PART_ALIGN);

/*
 * Parser thread: receives three packets and parses them.
 * The first is a normal command, the other two are an attacker's commands,
 * each reading 16 bytes of the key.
 */
static void parser_entry(void *attack_index, void *p2, void *p3)
{
	/* On this thread's stack, so the parser can always access them. */
	char packets[3][32];

	strcpy(packets[0], "get=0");
	snprintf(packets[1], sizeof(packets[1]), "get=%ld", (long)attack_index);
	snprintf(packets[2], sizeof(packets[2]), "get=%ld", (long)attack_index + 1);

	for (int i = 0; i < ARRAY_SIZE(packets); i++) {
		printk("parser: received '%s'\n", packets[i]);
		parse_command(packets[i]);
	}
}

/* Starts the parser thread. */
int main(void)
{
	/* Memory domains declarations */
	struct k_mem_domain domain_parser;

	/* The attacker would compute this index from the firmware's ELF file. */
	long attack_index = ((const char *)credentials_key_addr() -
			     (const char *)parser_settings_addr()) / SETTING_SIZE;
	
	K_MEM_PARTITION_DEFINE(app_part, app_storage, 
							sizeof(app_storage),
							K_MEM_PARTITION_P_RW_U_RW);	

	extern struct k_mem_partition z_libc_partition;
    struct k_mem_partition *parts[] = { 
										&app_part,
										&z_libc_partition
									};

    k_mem_domain_init(&domain_parser, ARRAY_SIZE(parts), parts);
	

    k_tid_t tid = k_thread_create(&parser_thread, 
								  parser_stack,
                                  PARSER_STACK_SIZE,
                                  parser_entry,.
                                  (void *)attack_index, NULL, NULL,
                                  PRIORITY, K_USER, K_NO_WAIT);

    k_mem_domain_add_thread(&domain_parser, tid);
    k_thread_start(tid);
	
	return 0;
}
