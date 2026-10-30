#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/zbus/zbus.h>
#include <zephyr/task_wdt/task_wdt.h>
#include <zephyr/drivers/watchdog.h>
#include <zephyr/sys/reboot.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

#define STACK_SIZE       2048
#define SENSOR_COUNT       18
#define SENSOR_PERIOD_MS  150

#define THREAD_STUCK

#define SAMPLE_COUNT         12
#define SENSOR_QUEUE_DEPTH    8
#define PRODUCER_STACK_SIZE 1024
#define HEALTH_STACK_SIZE   1024

/* ================================================================== */
/*  Shared channel message                                            */
/* ================================================================== */

struct sensor_data {
    int32_t temperature_mc;
    uint32_t timestamp_ms;
    uint8_t seq;
};


static void task_wdt_callback(int channel_id, void *user_data)
{
	LOG_WRN("Task watchdog channel %d callback, thread: %s\n",
		channel_id, k_thread_name_get((k_tid_t)user_data));

    LOG_WRN("[WATCHDOG] Resetting device...\n");
	sys_reboot(SYS_REBOOT_COLD);
}

/* ================================================================== */
/*  Observers                                                         */
/* ================================================================== */
/*
 * Logger is a message subscriber.
 * It receives message copies, not only channel notifications.
 */
ZBUS_MSG_SUBSCRIBER_DEFINE(logger_sub);

/* ================================================================== */
/*  Channel                                                           */
/* ================================================================== */

ZBUS_CHAN_DEFINE(sensor_chan, struct sensor_data,
                 NULL, NULL,
                 ZBUS_OBSERVERS(logger_sub),
                 ZBUS_MSG_INIT(.temperature_mc = 0,
                               .timestamp_ms = 0,
                               .seq = 0));

/* ================================================================== */
/*  Listener - synchronous observer                                   */
/* ================================================================== */

K_MSGQ_DEFINE(sensor_queue, sizeof(struct sensor_data), SENSOR_QUEUE_DEPTH, 4);

/* ================================================================== */
/*  Publisher                                                         */
/* ================================================================== */
static void sensor_thread_fn(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1); ARG_UNUSED(p2); ARG_UNUSED(p3);

    k_thread_name_set(k_current_get(), "sensor");

    for (int seq = 0; seq < SENSOR_COUNT; seq++) {
        struct sensor_data data = {
            .temperature_mc = 20000 + (seq * 250),
            .timestamp_ms = k_uptime_get_32(),
            .seq = (uint8_t)seq,
        };

        LOG_INF("[SENSOR] publish seq=%u temp=%d mC",
                data.seq,
                data.temperature_mc);

        int ret = zbus_chan_pub(&sensor_chan, &data, K_MSEC(100));
        if (ret != 0) {
            LOG_WRN("[SENSOR] publish failed ret=%d", ret);
        }
        
        // here I try to acomplish the following: "Add a health-check thread that monitors queue fill level and logs a warning at 75% capacity"
        int ret2 = k_msgq_put(&sensor_queue, &data, K_MSEC(100));

        if (ret2 != 0) {
            LOG_WRN("[PRODUCER] queue full, dropped seq=%u", seq);
        } else {
            LOG_DBG("[PRODUCER] queued seq=%u used=%u/%u", 
                seq, k_msgq_num_used_get(&sensor_queue), SENSOR_QUEUE_DEPTH);
        }

        k_msleep(SENSOR_PERIOD_MS);
    }

    LOG_INF("[SENSOR] done");
}

/* ================================================================== */
/*  Message subscriber - logger                                       */
/* ================================================================== */

static void logger_thread_fn(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1); ARG_UNUSED(p2); ARG_UNUSED(p3);

    k_thread_name_set(k_current_get(), "logger");

    const struct zbus_channel *chan;
    int received = 0;

    

	LOG_INF("Logger thread started.\n");
    int task_wdt_id2;
    task_wdt_id2 = task_wdt_add(1000U, task_wdt_callback,
		(void *)k_current_get());

    while (received < SENSOR_COUNT) {
        struct sensor_data msg;

        /*
         * Message subscribers receive a copy of the published message.
         * The slow logger will not reread the latest channel value.
         */
        int ret = zbus_sub_wait_msg(&logger_sub, &chan, &msg, K_MSEC(1500));
        #ifdef THREAD_STUCK 
            if (received == 5) {
                LOG_WRN("Logger thread getting stuck...\n");
                k_sleep(K_FOREVER);
            }
        #endif
        
        if (ret != 0) {
            LOG_WRN("[LOGGER-MSG] timeout ret=%d", ret);
            break;
        }

        received++;
        task_wdt_feed(task_wdt_id2);

        LOG_INF("[LOGGER-MSG] thread=%s seq=%u temp=%d latency=%ums",
                k_thread_name_get(k_current_get()),
                msg.seq,
                msg.temperature_mc,
                k_uptime_get_32() - msg.timestamp_ms);

        /*
         * Slow logger.
         * Message copies let it process old samples safely.
         */
        k_msleep(350);
    }

    LOG_INF("[LOGGER-MSG] done received=%d", received);
}


static void health_fn(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1); ARG_UNUSED(p2); ARG_UNUSED(p3);

    for (int i = 0; i < SENSOR_COUNT; i++) {
        k_msleep(120);

        uint32_t used = k_msgq_num_used_get(&sensor_queue);

        LOG_INF("[HEALTH] sensor_queue=%u/%u",
            used, SENSOR_QUEUE_DEPTH);

        if (used > (SENSOR_QUEUE_DEPTH * 3 / 4)) {
            LOG_WRN("[HEALTH] Queue at %d/%d, is more than 75 percent of its capacity.", used, SENSOR_QUEUE_DEPTH);
        }

        LOG_DBG("[HEALTH] queue has %u free slots", SENSOR_QUEUE_DEPTH - used);
    }

    LOG_INF("[HEALTH] done");
}

/* ================================================================== */
/*  Threads                                                           */
/* ================================================================== */

K_THREAD_DEFINE(sensor_thread, STACK_SIZE, sensor_thread_fn,
                NULL, NULL, NULL, 5, 0, 0);

K_THREAD_DEFINE(logger_thread, STACK_SIZE, logger_thread_fn,
                NULL, NULL, NULL, 6, 0, 0);

K_THREAD_DEFINE(health_thread, HEALTH_STACK_SIZE, health_fn,
                NULL, NULL, NULL, 6, 0, 0);

/* ================================================================== */
/*  Main                                                              */
/* ================================================================== */

int main(void)
{
    task_wdt_init(NULL);

    LOG_INF("=== L5 HOMEWORK ===");
    LOG_INF("sensor publishes every %dms", SENSOR_PERIOD_MS);
    LOG_INF("logger uses message subscriber copies");
    LOG_INF("health receives sensor read and monitor queue usage");
    LOG_INF("=======================================================");
    LOG_INF("");// new line

    return 0;
}