# L3 Homework
## Task 1
I ran the starting code for l3 homework in order to observe the inneficient code. I got the following output confirming the unnecesary wake-ups:

```bash
*** Booting Zephyr OS build v4.4.0 ***
[00:00:00.000,000] <inf> homework: === L3 Homework: Polling to Workqueue ===
[00:00:00.000,000] <inf> homework: Starter: polling every 10ms, sensor fires eve                                                                                                             ry 100ms
[00:00:00.000,000] <inf> homework: Expected wasted wakeups: ~9 per event
[00:00:00.000,000] <inf> homework: Run this, count wakeups, then convert to work                                                                                                             queue.
[00:00:00.100,000] <inf> homework: [SENSOR] event 0  tick=100
[00:00:00.101,000] <inf> homework: [CONSUMER] processed event 1  wakeups_so_far=                                                                                                             10  tick=101
[00:00:00.200,000] <inf> homework: [SENSOR] event 1  tick=200
[00:00:00.202,000] <inf> homework: [CONSUMER] processed event 2  wakeups_so_far=                                                                                                             20  tick=202
[00:00:00.300,000] <inf> homework: [SENSOR] event 2  tick=300
[00:00:00.303,000] <inf> homework: [CONSUMER] processed event 3  wakeups_so_far=                                                                                                             30  tick=303
[00:00:00.400,000] <inf> homework: [SENSOR] event 3  tick=400
[00:00:00.404,000] <inf> homework: [CONSUMER] processed event 4  wakeups_so_far=                                                                                                             40  tick=404
[00:00:00.500,000] <inf> homework: [SENSOR] event 4  tick=500
[00:00:00.505,000] <inf> homework: [CONSUMER] processed event 5  wakeups_so_far=                                                                                                             50  tick=505
[00:00:00.600,000] <inf> homework: [SENSOR] event 5  tick=600
[00:00:00.606,000] <inf> homework: [CONSUMER] processed event 6  wakeups_so_far=                                                                                                             60  tick=606
[00:00:00.700,000] <inf> homework: [SENSOR] event 6  tick=700
[00:00:00.707,000] <inf> homework: [CONSUMER] processed event 7  wakeups_so_far=                                                                                                             70  tick=707
[00:00:00.800,000] <inf> homework: [SENSOR] event 7  tick=800
[00:00:00.808,000] <inf> homework: [CONSUMER] processed event 8  wakeups_so_far=                                                                                                             80  tick=808
[00:00:00.901,000] <inf> homework: [SENSOR] event 8  tick=901
[00:00:00.909,000] <inf> homework: [CONSUMER] processed event 9  wakeups_so_far=                                                                                                             90  tick=909
[00:00:01.001,000] <inf> homework: [SENSOR] event 9  tick=1001
[00:00:01.001,000] <inf> homework: [SENSOR] all events produced
[00:00:01.010,000] <inf> homework: [CONSUMER] processed event 10  wakeups_so_far                                                                                                             =100  tick=1010
[00:00:01.010,000] <inf> homework:

[00:00:01.010,000] <inf> homework: [SUMMARY] events=10  total_wakeups=100  waste                                                                                                             d=90
[00:00:01.010,000] <inf> homework: [SUMMARY] wasted wakeups = 90% of all wakeups

```
## Task2
I got the following output. I notice the wakeups remains in zero:

```bash
*** Booting Zephyr OS build v4.4.0 ***
[00:00:00.000,000] <inf> homework: === L3 Homework: Polling to Workqueue ===
[00:00:00.000,000] <inf> homework: Starter: polling every 10ms, sensor fires every 100ms
[00:00:00.000,000] <inf> homework: Expected wasted wakeups: ~9 per event
[00:00:00.000,000] <inf> homework: Run this, count wakeups, then convert to workqueue.
[00:00:00.100,000] <inf> homework: [HANDLER] processed event 1  tick=100
[00:00:00.100,000] <inf> homework: [CONSUMER] processed event 1  wakeups_so_far=1  tick=100
[00:00:00.200,000] <inf> homework: [HANDLER] processed event 2  tick=200
[00:00:00.200,000] <inf> homework: [CONSUMER] processed event 2  wakeups_so_far=2  tick=200
[00:00:00.300,000] <inf> homework: [HANDLER] processed event 3  tick=300
[00:00:00.300,000] <inf> homework: [CONSUMER] processed event 3  wakeups_so_far=3  tick=300
[00:00:00.400,000] <inf> homework: [HANDLER] processed event 4  tick=400
[00:00:00.400,000] <inf> homework: [CONSUMER] processed event 4  wakeups_so_far=4  tick=400
[00:00:00.500,000] <inf> homework: [HANDLER] processed event 5  tick=500
[00:00:00.500,000] <inf> homework: [CONSUMER] processed event 5  wakeups_so_far=5  tick=500
[00:00:00.600,000] <inf> homework: [HANDLER] processed event 6  tick=600
[00:00:00.600,000] <inf> homework: [CONSUMER] processed event 6  wakeups_so_far=6  tick=600
[00:00:00.700,000] <inf> homework: [HANDLER] processed event 7  tick=700
[00:00:00.700,000] <inf> homework: [CONSUMER] processed event 7  wakeups_so_far=7  tick=700
[00:00:00.800,000] <inf> homework: [HANDLER] processed event 8  tick=800
[00:00:00.800,000] <inf> homework: [CONSUMER] processed event 8  wakeups_so_far=8  tick=800
[00:00:00.901,000] <inf> homework: [HANDLER] processed event 9  tick=901
[00:00:00.901,000] <inf> homework: [CONSUMER] processed event 9  wakeups_so_far=9  tick=901
[00:00:01.001,000] <inf> homework: [HANDLER] processed event 10  tick=1001
[00:00:01.001,000] <inf> homework: [CONSUMER] processed event 10  wakeups_so_far=10  tick=1001
[00:00:01.001,000] <inf> homework: [SENSOR] all events produced
```

## Task 3
In order to verify the desire behaviour I move the summary block to `main()`, after the `k_msleep()` wait for long enough for all events to complete. I saw the same sequence of events I've got in task 2 plus the following summary:

```bash
[00:00:01.700,000] <inf> homework: [SUMMARY] events=10  total_wakeups=10  wasted=0
[00:00:01.700,000] <inf> homework: [SUMMARY] wasted wakeups = 0% of all wakeups
```

## Bonus
I added a `simulate_bounce()` function in order to make a burst of bouncing events. I note the console drops some messages and I don't know why (I reset the board many times and I've got the same output). I think that it's fine because In the summary I saw the same result as Task 3. I paste the output:
```bash
*** Booting Zephyr OS build v4.4.0 ***
[00:00:00.000,000] <inf> homework: === L3 Homework: Polling to Workqueue ===
[00:00:00.000,000] <inf> homework: Starter: polling every 10ms, sensor fires every 100ms
[00:00:00.000,000] <inf> homework: Expected wasted wakeups: ~9 per event
[00:00:00.000,000] <inf> homework: Run this, count wakeups, then convert to workqueue.
[00:00:00.000,000] <inf> homework: [DEBOUNCE] simulating 5 rapid button events
[00:00:00.000,000] <inf> homework: [DEBOUNCE] event 0 tick=0
[00:00:00.004,000] <inf> homework: [DEBOUNCE] event 1 tick=4
[00:00:00.008,000] <inf> homework: [DEBOUNCE] event 2 tick=8
[00:00:00.012,000] <inf> homework: [DEBOUNCE] event 3 tick=12
[00:00:00.016,000] <inf> homework: [DEBOUNCE] event 4 tick=16
[00:00:00.020,000] <inf> homework: [DEBOUNCE] burst done
[00:00:00.020,000] <inf> homework: [HANDLER] processed event 1  tick=20
[00:00:00.020,000] <inf> homework: [CONSUMER] processed event 1  wakeups_so_far=1  tick=20
[00:00:00.020,000] <inf> homework: [DEBOUNCE] simulating 5 rapid button events
--- 1 messages dropped ---
[00:00:00.041,000] <inf> homework: [HANDLER] processed event 2  tick=41
--- 7 messages dropped ---
[00:00:00.045,000] <inf> homework: [DEBOUNCE] event 1 tick=45
--- 2 messages dropped ---
[00:00:00.061,000] <inf> homework: [DEBOUNCE] simulating 5 rapid button events
--- 7 messages dropped ---
[00:00:00.074,000] <inf> homework: [DEBOUNCE] event 3 tick=74
--- 2 messages dropped ---
[00:00:00.086,000] <inf> homework: [DEBOUNCE] event 1 tick=86
--- 6 messages dropped ---
[00:00:00.098,000] <inf> homework: [DEBOUNCE] event 4 tick=98
--- 3 messages dropped ---
[00:00:00.107,000] <inf> homework: [DEBOUNCE] event 1 tick=107
--- 4 messages dropped ---
[00:00:00.119,000] <inf> homework: [DEBOUNCE] event 4 tick=119
--- 1 messages dropped ---
[00:00:00.123,000] <inf> homework: [DEBOUNCE] burst done
--- 4 messages dropped ---
[00:00:00.127,000] <inf> homework: [DEBOUNCE] event 1 tick=127
--- 2 messages dropped ---
[00:00:00.140,000] <inf> homework: [DEBOUNCE] event 4 tick=140
--- 4 messages dropped ---
[00:00:00.144,000] <inf> homework: [DEBOUNCE] event 0 tick=144
[00:00:00.148,000] <inf> homework: [DEBOUNCE] event 1 tick=148
[00:00:00.152,000] <inf> homework: [DEBOUNCE] event 2 tick=152
[00:00:00.156,000] <inf> homework: [DEBOUNCE] event 3 tick=156
[00:00:00.160,000] <inf> homework: [DEBOUNCE] event 4 tick=160
[00:00:00.164,000] <inf> homework: [DEBOUNCE] burst done
[00:00:00.164,000] <inf> homework: [HANDLER] processed event 8  tick=164
[00:00:00.164,000] <inf> homework: [CONSUMER] processed event 8  wakeups_so_far=8  tick=164
[00:00:00.164,000] <inf> homework: [DEBOUNCE] simulating 5 rapid button events
[00:00:00.164,000] <inf> homework: [DEBOUNCE] event 0 tick=164
[00:00:00.169,000] <inf> homework: [DEBOUNCE] event 1 tick=169
[00:00:00.173,000] <inf> homework: [DEBOUNCE] event 2 tick=173
[00:00:00.177,000] <inf> homework: [DEBOUNCE] event 3 tick=177
[00:00:00.181,000] <inf> homework: [DEBOUNCE] event 4 tick=181
[00:00:00.185,000] <inf> homework: [DEBOUNCE] burst done
[00:00:00.185,000] <inf> homework: [HANDLER] processed event 9  tick=185
[00:00:00.185,000] <inf> homework: [CONSUMER] processed event 9  wakeups_so_far=9  tick=185
[00:00:00.185,000] <inf> homework: [DEBOUNCE] simulating 5 rapid button events
[00:00:00.185,000] <inf> homework: [DEBOUNCE] event 0 tick=185
[00:00:00.189,000] <inf> homework: [DEBOUNCE] event 1 tick=189
[00:00:00.193,000] <inf> homework: [DEBOUNCE] event 2 tick=193
[00:00:00.197,000] <inf> homework: [DEBOUNCE] event 3 tick=197
[00:00:00.201,000] <inf> homework: [DEBOUNCE] event 4 tick=201
[00:00:00.206,000] <inf> homework: [DEBOUNCE] burst done
[00:00:00.206,000] <inf> homework: [HANDLER] processed event 10  tick=206
[00:00:00.206,000] <inf> homework: [CONSUMER] processed event 10  wakeups_so_far=10  tick=206
[00:00:00.206,000] <inf> homework: [SENSOR] all events produced
[00:00:00.232,000] <inf> homework: [HANDLER] processed event 11  tick=232
[00:00:00.232,000] <inf> homework: [CONSUMER] processed event 11  wakeups_so_far=11  tick=232
[00:00:01.700,000] <inf> homework:

[00:00:01.700,000] <inf> homework: [SUMMARY] events=11  total_wakeups=11  wasted=0
[00:00:01.700,000] <inf> homework: [SUMMARY] wasted wakeups = 0% of all wakeups

```