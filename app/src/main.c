#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

#define STACK_SIZE 1024

#define PRIO_LOW 7
#define PRIO_MEDIUM 5
#define PRIO_HIGH 3
#define PRIO_COOP -1

uint32_t previous = 0;

void thread_low_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        uint32_t now = k_uptime_get_32();
        printk("T_LOW running. Time elapsed: %u ms\n", now - previous);
        k_msleep(300);
    }
}

void thread_med_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        uint32_t now = k_uptime_get_32();
        printk("T_MED running. Time elapsed: %u ms\n", now - previous);
        k_msleep(200);
    }
}

void thread_high_fn(void *p1, void *p2, void *p3)
{
    while (1) {
        uint32_t now = k_uptime_get_32();
        printk("T_HIGH running. Time elapsed: %u ms\n", now - previous);
        k_msleep(100);
    }
}

void thread_coop_fn(void *p1, void *p2, void *p3)
{
    int iteration = 0;

    while (iteration < 5) {
        printk("Cooperative thread running. Iteration number %d.\n", iteration);
        iteration++;
    }
    k_yield();
}

K_THREAD_DEFINE(thread_low, STACK_SIZE, thread_low_fn,
                NULL, NULL, NULL, PRIO_LOW, 0, 0);
K_THREAD_DEFINE(thread_med, STACK_SIZE, thread_med_fn,
                NULL, NULL, NULL, PRIO_MEDIUM, 0, 0);
K_THREAD_DEFINE(thread_high, STACK_SIZE, thread_high_fn,
                NULL, NULL, NULL, PRIO_HIGH, 0, 0);
K_THREAD_DEFINE(thread_coop, STACK_SIZE, thread_coop_fn,
                NULL, NULL, NULL, PRIO_COOP, 0, 0);

int main(void)
{
    previous = k_uptime_get_32();
    return 0;
}

