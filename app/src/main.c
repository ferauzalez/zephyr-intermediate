#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/tracing/tracing.h>

LOG_MODULE_REGISTER(homework, LOG_LEVEL_INF);

#define STACK_SIZE            2048
#define CONTROL_PRIORITY         4
#define MAINTENANCE_PRIORITY     7
#define EVENT_PERIOD_MS        250
#define MAINTENANCE_LOAD_US  45000
#define RESPONSE_TIME_GUARANTEE 10
#define MISS_SIZE               10
#define TOTAL_EVENTS            15

struct control_event {
    uint32_t seq;
    uint32_t ready_ms;
    uint32_t response_time;
};

K_MSGQ_DEFINE(control_queue, sizeof(struct control_event), 4, 4);
K_SEM_DEFINE(maintenance_start, 0, 1);

uint32_t total_breaches_counter = 0;
uint32_t logged_breaches_counter = 0;

struct breaches_log {
    uint32_t seq;
    uint32_t latency;
};

struct breaches_log breach[MISS_SIZE];

static void print_report() {
    //LOG_INF("===REPORT OF THE FIRST %d EVENTS WITH RESPONSE-TIME GUARANTEE UNFULFILLED===", MISS_SIZE);
    for (int i=0; i < MISS_SIZE; i++) {
        //LOG_INF("seq=%d, latency=%d", breach[i].seq, breach[i].latency);
    }
    //LOG_INF("===END OF REPORT===");
}

/* ================================================================== */
/*  Timer expiry: creates one control event                           */
/* ================================================================== */

static void event_timer_expiry(struct k_timer *timer)
{
    ARG_UNUSED(timer);

    static uint32_t seq;

    if (seq >= TOTAL_EVENTS) {
        //LOG_INF("Total events reached (%d events)", TOTAL_EVENTS);
        print_report();
        k_timer_stop(timer);
        return;
    }

    struct control_event event = {
        .seq = seq++,
        .ready_ms = k_uptime_get_32(),
    };

    /* Timer expiry runs in interrupt context, so never wait here. */
    int ret = k_msgq_put(&control_queue, &event, K_NO_WAIT);

    if (ret != 0) {
        return;
    }

    /* Both threads become ready when the timer interrupt returns. */
    k_sem_give(&maintenance_start);

    /* TODO: Add an application trace event for this sequence. */
}

K_TIMER_DEFINE(event_timer, event_timer_expiry, NULL);

/* ================================================================== */
/*  Control thread                                                   */
/* ================================================================== */

static void control_fn(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1); ARG_UNUSED(p2); ARG_UNUSED(p3);

    while (true) {
        struct control_event event;
        int ret = k_msgq_get(&control_queue, &event, K_FOREVER);

        if (ret != 0) {
            //LOG_ERR("[CONTROL] receive failed: %d", ret);
            continue;
        }

        LOG_INF("[CONTROL] processed seq=%u", event.seq); //I move this line inside the if-else block below

        /* TODO: Define a response-time guarantee. */
        event.response_time = k_uptime_get_32() - event.ready_ms;
        if (event.response_time > RESPONSE_TIME_GUARANTEE) {
            total_breaches_counter++;
            //LOG_WRN("[CONTROL] processed seq=%u. Response-time %u, guarantee unfulfilled. Total misses=%u", event.seq, event.response_time, total_breaches_counter);
            if (logged_breaches_counter < MISS_SIZE) {
                breach[logged_breaches_counter].seq = event.seq;
                breach[logged_breaches_counter].latency = event.response_time;
                logged_breaches_counter++;
            }
        } else {
            LOG_INF("[CONTROL] processed seq=%u", event.seq);
        }

        /* TODO: Measure latency and count every deadline miss. */
        /* TODO: Rate-limit repeated warning messages. */
        /* TODO: Add an application trace event for completion. */
    }
}

/* ================================================================== */
/*  Background maintenance thread                                    */
/* ================================================================== */

static void maintenance_fn(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1); ARG_UNUSED(p2); ARG_UNUSED(p3);

    while (true) {
        k_sem_take(&maintenance_start, K_FOREVER);

        /* This work is important, but it has no short deadline. */
        k_busy_wait(MAINTENANCE_LOAD_US);
    }
}

K_THREAD_DEFINE(control, STACK_SIZE, control_fn,
                NULL, NULL, NULL, CONTROL_PRIORITY, 0, 0);

K_THREAD_DEFINE(maintenance, STACK_SIZE, maintenance_fn,
                NULL, NULL, NULL, MAINTENANCE_PRIORITY, 0, 0);

int main(void)
{
    //LOG_INF("=== L6 Homework: Runtime Investigation ===");
    //LOG_INF("Control work must start within 10 ms");
    //LOG_INF("Inspect, measure, trace, explain, and correct the delay");

    k_timer_start(&event_timer, K_MSEC(500), K_MSEC(EVENT_PERIOD_MS));

    return 0;
}