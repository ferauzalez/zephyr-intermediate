# L5 Homework
## Task 1
Task:

Goal: Study reliability under pressure
Task:
1. Build a producer/consumer pipeline (from Lecture 4 homework)
2. Add a task watchdog
3. Simulate a stuck consumer (long k_sleep in consumer thread)
Observe: queue fills, watchdog fires, callback triggered
4. Add a health-check thread that monitors queue fill level and logs a warning at 75% capacity
Push tag: l5-task1

I did tasks 1 to 3 and I observe when watchdog fires and the callback function was triggered. For the task 4 I have a producer/consumer pipeline done with ZBUS_CHAN_DEFINE, which as I understand it has a depth of 1. So to simulate a full queue, I added a queue with K_MSGQ_DEFINE and then I added a warning when it exceeded 75% of its capacity.

I had a question regarding the callback. Within the callback function, I have two messages that aren't being printed. Although the restart is performed, the messages aren't being printed. I don't yet know the cause, but I'm submitting this task anyway because I believe it meets the requirements. I read a similar issue [here](https://devzone.nordicsemi.com/f/nordic-q-a/96314/task-watchdog-callback---printk-logging-and-saving-to-the-internal-flash-not-working)

Below I paste the output:
```bash

*** Booting Zephyr OS build v4.4.0 ***
[00:00:00.000,000] <inf> demo: === L5 HOMEWORK ===
[00:00:00.000,000] <inf> demo: sensor publishes every 150ms
[00:00:00.000,000] <inf> demo: logger uses message subscriber copies
[00:00:00.000,000] <inf> demo: health receives sensor read and monitor queue usage
[00:00:00.000,000] <inf> demo: =======================================================
[00:00:00.000,000] <inf> demo:
[00:00:00.000,000] <inf> demo: [SENSOR] publish seq=0 temp=20000 mC
[00:00:00.000,000] <dbg> demo: sensor_thread_fn: [PRODUCER] queued seq=0 used=1/8
[00:00:00.000,000] <inf> demo: Logger thread started.

[00:00:00.000,000] <inf> demo: [LOGGER-MSG] thread=logger seq=0 temp=20000 latency=0ms
[00:00:00.120,000] <inf> demo: [HEALTH] sensor_queue=1/8
[00:00:00.120,000] <dbg> demo: health_fn: [HEALTH] queue has 7 free slots
[00:00:00.150,000] <inf> demo: [SENSOR] publish seq=1 temp=20250 mC
[00:00:00.150,000] <dbg> demo: sensor_thread_fn: [PRODUCER] queued seq=1 used=2/8
[00:00:00.240,000] <inf> demo: [HEALTH] sensor_queue=2/8
[00:00:00.240,000] <dbg> demo: health_fn: [HEALTH] queue has 6 free slots
[00:00:00.300,000] <inf> demo: [SENSOR] publish seq=2 temp=20500 mC
[00:00:00.300,000] <dbg> demo: sensor_thread_fn: [PRODUCER] queued seq=2 used=3/8
[00:00:00.350,000] <inf> demo: [LOGGER-MSG] thread=logger seq=1 temp=20250 latency=200ms
[00:00:00.360,000] <inf> demo: [HEALTH] sensor_queue=3/8
[00:00:00.360,000] <dbg> demo: health_fn: [HEALTH] queue has 5 free slots
[00:00:00.450,000] <inf> demo: [SENSOR] publish seq=3 temp=20750 mC
[00:00:00.450,000] <dbg> demo: sensor_thread_fn: [PRODUCER] queued seq=3 used=4/8
[00:00:00.480,000] <inf> demo: [HEALTH] sensor_queue=4/8
[00:00:00.480,000] <dbg> demo: health_fn: [HEALTH] queue has 4 free slots
[00:00:00.600,000] <inf> demo: [SENSOR] publish seq=4 temp=21000 mC
[00:00:00.600,000] <dbg> demo: sensor_thread_fn: [PRODUCER] queued seq=4 used=5/8
[00:00:00.600,000] <inf> demo: [HEALTH] sensor_queue=5/8
[00:00:00.600,000] <dbg> demo: health_fn: [HEALTH] queue has 3 free slots
[00:00:00.700,000] <inf> demo: [LOGGER-MSG] thread=logger seq=2 temp=20500 latency=400ms
[00:00:00.720,000] <inf> demo: [HEALTH] sensor_queue=5/8
[00:00:00.720,000] <dbg> demo: health_fn: [HEALTH] queue has 3 free slots
[00:00:00.750,000] <inf> demo: [SENSOR] publish seq=5 temp=21250 mC
[00:00:00.750,000] <dbg> demo: sensor_thread_fn: [PRODUCER] queued seq=5 used=6/8
[00:00:00.840,000] <inf> demo: [HEALTH] sensor_queue=6/8
[00:00:00.840,000] <dbg> demo: health_fn: [HEALTH] queue has 2 free slots
[00:00:00.900,000] <inf> demo: [SENSOR] publish seq=6 temp=21500 mC
[00:00:00.900,000] <dbg> demo: sensor_thread_fn: [PRODUCER] queued seq=6 used=7/8
[00:00:00.961,000] <inf> demo: [HEALTH] sensor_queue=7/8
[00:00:00.961,000] <wrn> demo: [HEALTH] Queue at 7/8, is more than 75 percent of its capacity.
[00:00:00.961,000] <dbg> demo: health_fn: [HEALTH] queue has 1 free slots
[00:00:01.050,000] <inf> demo: [LOGGER-MSG] thread=logger seq=3 temp=20750 latency=600ms
[00:00:01.050,000] <inf> demo: [SENSOR] publish seq=7 temp=21750 mC
[00:00:01.050,000] <dbg> demo: sensor_thread_fn: [PRODUCER] queued seq=7 used=8/8
[00:00:01.081,000] <inf> demo: [HEALTH] sensor_queue=8/8
[00:00:01.081,000] <wrn> demo: [HEALTH] Queue at 8/8, is more than 75 percent of its capacity.
[00:00:01.081,000] <dbg> demo: health_fn: [HEALTH] queue has 0 free slots
[00:00:01.201,000] <inf> demo: [SENSOR] publish seq=8 temp=22000 mC
[00:00:01.201,000] <inf> demo: [HEALTH] sensor_queue=8/8
[00:00:01.201,000] <wrn> demo: [HEALTH] Queue at 8/8, is more than 75 percent of its capacity.
[00:00:01.201,000] <dbg> demo: health_fn: [HEALTH] queue has 0 free slots
[00:00:01.301,000] <wrn> demo: [PRODUCER] queue full, dropped seq=8
[00:00:01.321,000] <inf> demo: [HEALTH] sensor_queue=8/8
[00:00:01.321,000] <wrn> demo: [HEALTH] Queue at 8/8, is more than 75 percent of its capacity.
[00:00:01.321,000] <dbg> demo: health_fn: [HEALTH] queue has 0 free slots
[00:00:01.400,000] <inf> demo: [LOGGER-MSG] thread=logger seq=4 temp=21000 latency=800ms
[00:00:01.441,000] <inf> demo: [HEALTH] sensor_queue=8/8
[00:00:01.441,000] <wrn> demo: [HEALTH] Queue at 8/8, is more than 75 percent of its capacity.
[00:00:01.441,000] <dbg> demo: health_fn: [HEALTH] queue has 0 free slots
[00:00:01.451,000] <inf> demo: [SENSOR] publish seq=9 temp=22250 mC
[00:00:01.551,000] <wrn> demo: [PRODUCER] queue full, dropped seq=9
[00:00:01.561,000] <inf> demo: [HEALTH] sensor_queue=8/8
[00:00:01.561,000] <wrn> demo: [HEALTH] Queue at 8/8, is more than 75 percent of its capacity.
[00:00:01.561,000] <dbg> demo: health_fn: [HEALTH] queue has 0 free slots
[00:00:01.681,000] <inf> demo: [HEALTH] sensor_queue=8/8
[00:00:01.681,000] <wrn> demo: [HEALTH] Queue at 8/8, is more than 75 percent of its capacity.
[00:00:01.681,000] <dbg> demo: health_fn: [HEALTH] queue has 0 free slots
[00:00:01.701,000] <inf> demo: [SENSOR] publish seq=10 temp=22500 mC
[00:00:01.750,000] <wrn> demo: Logger thread getting stuck...

[00:00:01.801,000] <wrn> demo: [PRODUCER] queue full, dropped seq=10
[00:00:01.801,000] <inf> demo: [HEALTH] sensor_queue=8/8
[00:00:01.801,000] <wrn> demo: [HEALTH] Queue at 8/8, is more than 75 percent of its capacity.
[00:00:01.801,000] <dbg> demo: health_fn: [HEALTH] queue has 0 free slots
[00:00:01.921,000] <inf> demo: [HEALTH] sensor_queue=8/8
[00:00:01.921,000] <wrn> demo: [HEALTH] Queue at 8/8, is more than 75 percent of its capacity.
[00:00:01.921,000] <dbg> demo: health_fn: [HEALTH] queue has 0 free slots
[00:00:01.951,000] <inf> demo: [SENSOR] publish seq=11 temp=22750 mC
[00:00:02.041,000] <inf> demo: [HEALTH] sensor_queue=8/8
[00:00:02.041,000] <wrn> demo: [HEALTH] Queue at 8/8, is more than 75 percent of its capacity.
[00:00:02.041,000] <dbg> demo: health_fn: [HEALTH] queue has 0 free slots
[00:00:02.051,000] <wrn> demo: [PRODUCER] queue full, dropped seq=11
[00:00:02.162,000] <inf> demo: [HEALTH] sensor_queue=8/8
[00:00:02.162,000] <wrn> demo: [HEALTH] Queue at 8/8, is more than 75 percent of its capacity.
[00:00:02.162,000] <dbg> demo: health_fn: [HEALTH] queue has 0 free slots
[00:00:02.162,000] <inf> demo: [HEALTH] done
[00:00:02.201,000] <inf> demo: [SENSOR] publish seq=12 temp=23000 mC
*** Booting Zephyr OS build v4.4.0 ***
```