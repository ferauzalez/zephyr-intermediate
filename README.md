# L6 Homework
## Task 1
Goal: explain and reduce a Zephyr scheduling delay
Tasks:

- [X] 1. Run the provided producer-consumer application from branch l6-homework
Below I paste the output for the subtask 1:
```bash
*** Booting Zephyr OS build v4.4.0 ***
[00:00:00.000,000] <inf> homework: === L6 Homework: Runtime Investigation ===
[00:00:00.000,000] <inf> homework: Control work must start within 10 ms
[00:00:00.000,000] <inf> homework: Inspect, measure, trace, explain, and correct the delay
[00:00:00.545,000] <inf> homework: [CONTROL] processed seq=0
[00:00:00.795,000] <inf> homework: [CONTROL] processed seq=1
[00:00:01.045,000] <inf> homework: [CONTROL] processed seq=2
[00:00:01.295,000] <inf> homework: [CONTROL] processed seq=3
[00:00:01.545,000] <inf> homework: [CONTROL] processed seq=4
[00:00:01.795,000] <inf> homework: [CONTROL] processed seq=5
[00:00:02.045,000] <inf> homework: [CONTROL] processed seq=6
[00:00:02.295,000] <inf> homework: [CONTROL] processed seq=7
[00:00:02.545,000] <inf> homework: [CONTROL] processed seq=8
[00:00:02.795,000] <inf> homework: [CONTROL] processed seq=9
[00:00:03.045,000] <inf> homework: [CONTROL] processed seq=10
[00:00:03.295,000] <inf> homework: [CONTROL] processed seq=11
[00:00:03.545,000] <inf> homework: [CONTROL] processed seq=12
[00:00:03.795,000] <inf> homework: [CONTROL] processed seq=13
[00:00:04.045,000] <inf> homework: [CONTROL] processed seq=14
[00:00:04.295,000] <inf> homework: [CONTROL] processed seq=15
[00:00:04.545,000] <inf> homework: [CONTROL] processed seq=16
[00:00:04.795,000] <inf> homework: [CONTROL] processed seq=17
[00:00:05.045,000] <inf> homework: [CONTROL] processed seq=18
[00:00:05.295,000] <inf> homework: [CONTROL] processed seq=19
```
- [x] Define and detect its response-time guarantee
- [X] Add sequence-based logs and deadline-miss counting
Below I paste the output for the subtasks 2 and 3:
``` bash
*** Booting Zephyr OS build v4.4.0 ***
[00:00:00.000,000] <inf> homework: === L6 Homework: Runtime Investigation ===
[00:00:00.000,000] <inf> homework: Control work must start within 10 ms
[00:00:00.000,000] <inf> homework: Inspect, measure, trace, explain, and correct the delay
[00:00:00.545,000] <wrn> homework: [CONTROL] processed seq=0. Response-time 45, guarantee unfulfilled. Total misses=1
[00:00:00.795,000] <wrn> homework: [CONTROL] processed seq=1. Response-time 45, guarantee unfulfilled. Total misses=2
[00:00:01.045,000] <wrn> homework: [CONTROL] processed seq=2. Response-time 45, guarantee unfulfilled. Total misses=3
[00:00:01.295,000] <wrn> homework: [CONTROL] processed seq=3. Response-time 45, guarantee unfulfilled. Total misses=4
[00:00:01.545,000] <wrn> homework: [CONTROL] processed seq=4. Response-time 45, guarantee unfulfilled. Total misses=5
[00:00:01.795,000] <wrn> homework: [CONTROL] processed seq=5. Response-time 45, guarantee unfulfilled. Total misses=6
[00:00:02.045,000] <wrn> homework: [CONTROL] processed seq=6. Response-time 45, guarantee unfulfilled. Total misses=7
[00:00:02.295,000] <wrn> homework: [CONTROL] processed seq=7. Response-time 45, guarantee unfulfilled. Total misses=8
[00:00:02.545,000] <wrn> homework: [CONTROL] processed seq=8. Response-time 45, guarantee unfulfilled. Total misses=9
[00:00:02.795,000] <wrn> homework: [CONTROL] processed seq=9. Response-time 45, guarantee unfulfilled. Total misses=10
[00:00:03.045,000] <wrn> homework: [CONTROL] processed seq=10. Response-time 45, guarantee unfulfilled. Total misses=11
[00:00:03.295,000] <wrn> homework: [CONTROL] processed seq=11. Response-time 45, guarantee unfulfilled. Total misses=12
[00:00:03.545,000] <wrn> homework: [CONTROL] processed seq=12. Response-time 45, guarantee unfulfilled. Total misses=13
[00:00:03.795,000] <wrn> homework: [CONTROL] processed seq=13. Response-time 45, guarantee unfulfilled. Total misses=14
[00:00:04.045,000] <wrn> homework: [CONTROL] processed seq=14. Response-time 45, guarantee unfulfilled. Total misses=15
[00:00:04.250,000] <inf> homework: Total events reached (15 events)
[00:00:04.250,000] <inf> homework: ===REPORT OF THE FIRST 10 EVENTS WITH RESPONSE-TIME GUARANTEE UNFULFILLED===
[00:00:04.250,000] <inf> homework: seq=0, latency=45
[00:00:04.250,000] <inf> homework: seq=1, latency=45
[00:00:04.250,000] <inf> homework: seq=2, latency=45
[00:00:04.250,000] <inf> homework: seq=3, latency=45
[00:00:04.250,000] <inf> homework: seq=4, latency=45
[00:00:04.250,000] <inf> homework: seq=5, latency=45
[00:00:04.250,000] <inf> homework: seq=6, latency=45
[00:00:04.250,000] <inf> homework: seq=7, latency=45
[00:00:04.250,000] <inf> homework: seq=8, latency=45
[00:00:04.250,000] <inf> homework: seq=9, latency=45
[00:00:04.250,000] <inf> homework: ===END OF REPORT===
```
- [X] Inspect thread priorities and states with the kernel shell.
I add `CONFIG_SHELL=y` and `CONFIG_SHELL_BACKEND_SERIAL=y` to the `prj.conf` file in order to use kernel commands. After build and flash, I saw the same report plus the Zephyr shell. I run the `kernel thread list` command and the shell report the list of kernel in use. I paste the data below:
```bash
uart:~$ kernel thread list
Scheduler: 1706 since last call
Threads:
 0x20000228 maintenance
        options: 0x0, priority: 4 timeout: 0
        state: pending, entry: 0x8000611
        stack size 2048, unused 1880, usage 168 / 2048 (8 %)

 0x200002e0 control
        options: 0x0, priority: 7 timeout: 0
        state: pending, entry: 0x8000631
        stack size 2048, unused 1696, usage 352 / 2048 (17 %)

*0x200008a0 shell_uart
        options: 0x0, priority: 14 timeout: 0
        state: queued, entry: 0x8003a95
        stack size 2048, unused 1040, usage 1008 / 2048 (49 %)

 0x200003a8 logging
        options: 0x0, priority: 14 timeout: 0
        state: pending, entry: 0x80019b9
        stack size 768, unused 568, usage 200 / 768 (26 %)

 0x20000c28 idle
        options: 0x1, priority: 15 timeout: 0
        state: , entry: 0x800b341
        stack size 320, unused 256, usage 64 / 320 (20 %)
```
From the shell data is possible to see that maintenance thread has priority level 4 whereas the control thread has priority level of 7 (low priority respect maintenance thread). Because this priority assignments, the maintenance thread execute its work before the control thread and therefore the control time guarantee is not meet.
- [X] Capture CTF and decode it with Babeltrace: After a long fight with the console, I win. So I paste the lovely output where its possible to see the details about threads 'maintenance' and 'control':
```bash
ferna@Fernando:/mnt/d/documentos_ferna/repositorios-github/zephyr-intermediate-root/zephyr-intermediate$ babeltrace ./ctf-run
[00:00:04.102992104] (+?.?????????) 0 isr_enter:
[00:00:04.103349795] (+0.000357691) 0 isr_exit:
[00:00:04.103865759] (+0.000515964) 0 idle:
[00:00:04.302949033] (+0.199083274) 0 isr_enter:
[00:00:04.303306771] (+0.000357738) 0 isr_exit:
[00:00:04.303822664] (+0.000515893) 0 idle:
[00:00:04.502906009] (+0.199083345) 0 isr_enter:
[00:00:04.503263771] (+0.000357762) 0 isr_exit:
[00:00:04.503779664] (+0.000515893) 0 idle:
[00:00:04.702863009] (+0.199083345) 0 isr_enter:
[00:00:04.703220700] (+0.000357691) 0 isr_exit:
[00:00:04.703736569] (+0.000515869) 0 idle:
[00:00:04.902819938] (+0.199083369) 0 isr_enter:
[00:00:04.903177604] (+0.000357666) 0 isr_exit:
[00:00:04.903693521] (+0.000515917) 0 idle:
[00:00:05.102776843] (+0.199083322) 0 isr_enter:
[00:00:05.103134604] (+0.000357761) 0 isr_exit:
[00:00:05.103650521] (+0.000515917) 0 idle:
[00:00:05.302733843] (+0.199083322) 0 isr_enter:
[00:00:05.303091509] (+0.000357666) 0 isr_exit:
[00:00:05.303607402] (+0.000515893) 0 idle:
[00:00:05.502690747] (+0.199083345) 0 isr_enter:
[00:00:05.503048509] (+0.000357762) 0 isr_exit:
[00:00:05.503564402] (+0.000515893) 0 idle:
[00:00:05.702647747] (+0.199083345) 0 isr_enter:
[00:00:05.703005485] (+0.000357738) 0 isr_exit:
[00:00:05.703521378] (+0.000515893) 0 idle:
[00:00:08.590022401] (+2.886501023) 0 thread_create: { thread_id = 536871400, name = "control" }
[00:00:08.592462472] (+0.002440071) 0 thread_info: { thread_id = 536871400, name = "control", stack_base = 536878912, stack_size = 2048 }
[00:00:08.595765092] (+0.003302620) 0 thread_create: { thread_id = 536871224, name = "maintenance" }
[00:00:08.598355758] (+0.002590666) 0 thread_info: { thread_id = 536871224, name = "maintenance", stack_base = 536876800, stack_size = 2048 }
[00:00:08.601649782] (+0.003294024) 0 thread_sched_lock:
[00:00:08.602172294] (+0.000522512) 0 thread_wakeup: { thread_id = 536871400, name = "control" }
[00:00:08.604772651] (+0.002600357) 0 thread_sched_ready: { thread_id = 536871400, name = "control" }
[00:00:08.607373472] (+0.002600821) 0 thread_wakeup: { thread_id = 536871224, name = "maintenance" }
[00:00:08.609969139] (+0.002595667) 0 isr_enter:
[00:00:08.610495270] (+0.000526131) 0 isr_exit:
[00:00:08.611012937] (+0.000517667) 0 thread_sched_ready: { thread_id = 536871224, name = "maintenance" }
[00:00:08.613610080] (+0.002597143) 0 thread_sched_unlock:
[00:00:08.614130103] (+0.000520023) 0 timer_start: { id = 536871032, duration = 500000, period = 250000 }
[00:00:08.615706020] (+0.001575917) 0 thread_sched_abort: { thread_id = 536871768, name = "main" }
[00:00:08.618292092] (+0.002586072) 0 thread_switched_out: { thread_id = 536871768, name = "main" }
[00:00:08.620894401] (+0.002602309) 0 thread_switched_in: { thread_id = 536871224, name = "maintenance" }
[00:00:08.623489032] (+0.002594631) 0 semaphore_take_enter: { id = 536871160, timeout = 4294967196 }
[00:00:08.624701484] (+0.001212452) 0 semaphore_take_blocking: { id = 536871160, timeout = 4294967196 }
[00:00:08.625928627] (+0.001227143) 0 thread_sched_pend: { thread_id = 536871224, name = "maintenance" }
[00:00:08.628517746] (+0.002589119) 0 thread_switched_out: { thread_id = 536871224, name = "maintenance" }
[00:00:08.631120330] (+0.002602584) 0 thread_switched_in: { thread_id = 536871400, name = "control" }
[00:00:08.633715115] (+0.002594785) 0 msgq_get_enter: { id = 536871116, timeout = 4294967196 }
[00:00:08.634927365] (+0.001212250) 0 msgq_get_blocking: { id = 536871116, timeout = 4294967196 }
[00:00:08.636149842] (+0.001222477) 0 thread_sched_pend: { thread_id = 536871400, name = "control" }
[00:00:08.638743961] (+0.002594119) 0 thread_switched_out: { thread_id = 536871400, name = "control" }
[00:00:08.641346580] (+0.002602619) 0 thread_switched_in: { thread_id = 536871592, name = "idle" }
[00:00:08.643940937] (+0.002594357) 0 idle:
[00:00:08.835746592] (+0.191805655) 0 isr_enter:
[00:00:08.836110663] (+0.000364071) 0 isr_exit:
[00:00:08.836626401] (+0.000515738) 0 idle:
[00:00:09.035709877] (+0.199083476) 0 isr_enter:
[00:00:09.036067592] (+0.000357715) 0 isr_exit:
[00:00:09.036583294] (+0.000515702) 0 idle:
[00:00:09.116036972] (+0.079453678) 0 isr_enter:
[00:00:09.116400722] (+0.000363750) 0 timer_expiry_enter: { id = 536871032 }
[00:00:09.117263532] (+0.000862810) 0 msgq_put_enter: { id = 536871116, timeout = 0 }
[00:00:09.118479365] (+0.001215833) 0 thread_sched_ready: { thread_id = 536871400, name = "control" }
[00:00:09.121078508] (+0.002599143) 0 msgq_put_exit: { id = 536871116, timeout = 0, ret = 0 }
[00:00:09.122635080] (+0.001556572) 0 semaphore_give_enter: { id = 536871160 }
[00:00:09.123504758] (+0.000869678) 0 thread_sched_ready: { thread_id = 536871224, name = "maintenance" }
[00:00:09.126108365] (+0.002603607) 0 semaphore_give_exit: { id = 536871160 }
[00:00:09.126967187] (+0.000858822) 0 timer_expiry_exit: { id = 536871032 }
[00:00:09.127837520] (+0.000870333) 0 isr_exit:
[00:00:09.128356663] (+0.000519143) 0 thread_switched_out: { thread_id = 536871592, name = "idle" }
[00:00:09.130959734] (+0.002603071) 0 thread_switched_in: { thread_id = 536871224, name = "maintenance" }
[00:00:09.133553627] (+0.002593893) 0 semaphore_take_exit: { id = 536871160, timeout = 4294967196, ret = 0 }
[00:00:09.135113532] (+0.001559905) 0 thread_busy_wait_enter: { usec_to_wait = 45000 }
[00:00:09.147337222] (+0.012223690) 0 isr_enter:
[00:00:09.147711056] (+0.000373834) 0 isr_exit:
[00:00:09.167636818] (+0.019925762) 0 isr_enter:
[00:00:09.168007663] (+0.000370845) 0 isr_exit:
[00:00:09.180981282] (+0.012973619) 0 thread_busy_wait_exit: { usec_to_wait = 45000 }
[00:00:09.181686925] (+0.000705643) 0 semaphore_take_enter: { id = 536871160, timeout = 4294967196 }
[00:00:09.182900032] (+0.001213107) 0 semaphore_take_blocking: { id = 536871160, timeout = 4294967196 }
[00:00:09.184127199] (+0.001227167) 0 thread_sched_pend: { thread_id = 536871224, name = "maintenance" }
[00:00:09.186716318] (+0.002589119) 0 thread_switched_out: { thread_id = 536871224, name = "maintenance" }
[00:00:09.189318877] (+0.002602559) 0 thread_switched_in: { thread_id = 536871400, name = "control" }
[00:00:09.191912675] (+0.002593798) 0 msgq_get_exit: { id = 536871116, timeout = 4294967196, ret = 0 }
[00:00:09.193476187] (+0.001563512) 0 msgq_get_enter: { id = 536871116, timeout = 4294967196 }
[00:00:09.194685889] (+0.001209702) 0 msgq_get_blocking: { id = 536871116, timeout = 4294967196 }
[00:00:09.195908365] (+0.001222476) 0 thread_sched_pend: { thread_id = 536871400, name = "control" }
[00:00:09.198502484] (+0.002594119) 0 thread_switched_out: { thread_id = 536871400, name = "control" }
[00:00:09.201105127] (+0.002602643) 0 thread_switched_in: { thread_id = 536871592, name = "idle" }
[00:00:09.203699044] (+0.002593917) 0 idle:
```
I cut the rest of the output because was repetitive. Its possible to see that regardless both threads are ready at times [00:00:09.118479365] and [00:00:09.123504758], maintenance thread wins and the first busy wait starts at time [00:00:09.135113532] and ends at time [00:00:09.180981282]. After that, at time [00:00:09.189318877] control thread do its job.
- [X] Apply one correction and repeat the measurement: I invert the priority levels, control thread now had priority 4 and maintenance thread had level 7. I paste the first lines of the output of babeltrace below:
```bash
$ babeltrace ./ctf-run
[00:00:01.745496717] (+?.?????????) 0 isr_enter:
[00:00:01.745854455] (+0.000357738) 0 isr_exit:
[00:00:01.746370324] (+0.000515869) 0 idle:
[00:00:01.945453693] (+0.199083369) 0 isr_enter:
[00:00:01.945811360] (+0.000357667) 0 isr_exit:
[00:00:01.946327253] (+0.000515893) 0 idle:
[00:00:02.145410598] (+0.199083345) 0 isr_enter:
[00:00:02.145768336] (+0.000357738) 0 isr_exit:
[00:00:02.146284253] (+0.000515917) 0 idle:
[00:00:04.295055105] (+2.148770852) 0 thread_create: { thread_id = 536871400, name = "control" }
[00:00:04.297495176] (+0.002440071) 0 thread_info: { thread_id = 536871400, name = "control", stack_base = 536878912, stack_size = 2048 }
[00:00:04.300797796] (+0.003302620) 0 thread_create: { thread_id = 536871224, name = "maintenance" }
[00:00:04.303388462] (+0.002590666) 0 thread_info: { thread_id = 536871224, name = "maintenance", stack_base = 536876800, stack_size = 2048 }
[00:00:04.306682486] (+0.003294024) 0 thread_sched_lock:
[00:00:04.307204998] (+0.000522512) 0 thread_wakeup: { thread_id = 536871400, name = "control" }
[00:00:04.309805355] (+0.002600357) 0 thread_sched_ready: { thread_id = 536871400, name = "control" }
[00:00:04.312406176] (+0.002600821) 0 thread_wakeup: { thread_id = 536871224, name = "maintenance" }
[00:00:04.315001843] (+0.002595667) 0 isr_enter:
[00:00:04.315527974] (+0.000526131) 0 isr_exit:
[00:00:04.316045641] (+0.000517667) 0 thread_sched_ready: { thread_id = 536871224, name = "maintenance" }
[00:00:04.318642879] (+0.002597238) 0 thread_sched_unlock:
[00:00:04.319162807] (+0.000519928) 0 timer_start: { id = 536871032, duration = 500000, period = 250000 }
[00:00:04.320738724] (+0.001575917) 0 thread_sched_abort: { thread_id = 536871768, name = "main" }
[00:00:04.323324796] (+0.002586072) 0 thread_switched_out: { thread_id = 536871768, name = "main" }
[00:00:04.325927057] (+0.002602261) 0 thread_switched_in: { thread_id = 536871400, name = "control" }
[00:00:04.328521819] (+0.002594762) 0 msgq_get_enter: { id = 536871116, timeout = 4294967196 }
[00:00:04.329734141] (+0.001212322) 0 msgq_get_blocking: { id = 536871116, timeout = 4294967196 }
[00:00:04.330961343] (+0.001227202) 0 thread_sched_pend: { thread_id = 536871400, name = "control" }
[00:00:04.333550403] (+0.002589060) 0 thread_switched_out: { thread_id = 536871400, name = "control" }
[00:00:04.336153010] (+0.002602607) 0 thread_switched_in: { thread_id = 536871224, name = "maintenance" }
[00:00:04.338747641] (+0.002594631) 0 semaphore_take_enter: { id = 536871160, timeout = 4294967196 }
[00:00:04.339960117] (+0.001212476) 0 semaphore_take_blocking: { id = 536871160, timeout = 4294967196 }
[00:00:04.341182486] (+0.001222369) 0 thread_sched_pend: { thread_id = 536871224, name = "maintenance" }
[00:00:04.343776736] (+0.002594250) 0 thread_switched_out: { thread_id = 536871224, name = "maintenance" }
[00:00:04.346379284] (+0.002602548) 0 thread_switched_in: { thread_id = 536871592, name = "idle" }
[00:00:04.348973641] (+0.002594357) 0 idle:
[00:00:04.540779188] (+0.191805547) 0 isr_enter:
[00:00:04.541143343] (+0.000364155) 0 isr_exit:
[00:00:04.541659081] (+0.000515738) 0 idle:
[00:00:04.740742557] (+0.199083476) 0 isr_enter:
[00:00:04.741100272] (+0.000357715) 0 isr_exit:
[00:00:04.741615974] (+0.000515702) 0 idle:
[00:00:04.821069676] (+0.079453702) 0 isr_enter:
[00:00:04.821433426] (+0.000363750) 0 timer_expiry_enter: { id = 536871032 }
[00:00:04.822296236] (+0.000862810) 0 msgq_put_enter: { id = 536871116, timeout = 0 }
[00:00:04.823512069] (+0.001215833) 0 thread_sched_ready: { thread_id = 536871400, name = "control" }
[00:00:04.826111212] (+0.002599143) 0 msgq_put_exit: { id = 536871116, timeout = 0, ret = 0 }
[00:00:04.827667784] (+0.001556572) 0 semaphore_give_enter: { id = 536871160 }
[00:00:04.828537462] (+0.000869678) 0 thread_sched_ready: { thread_id = 536871224, name = "maintenance" }
[00:00:04.831141176] (+0.002603714) 0 semaphore_give_exit: { id = 536871160 }
[00:00:04.831999891] (+0.000858715) 0 timer_expiry_exit: { id = 536871032 }
[00:00:04.832870224] (+0.000870333) 0 isr_exit:
[00:00:04.833389367] (+0.000519143) 0 thread_switched_out: { thread_id = 536871592, name = "idle" }
[00:00:04.835992391] (+0.002603024) 0 thread_switched_in: { thread_id = 536871400, name = "control" }
[00:00:04.838586260] (+0.002593869) 0 msgq_get_exit: { id = 536871116, timeout = 4294967196, ret = 0 }
[00:00:04.840149807] (+0.001563547) 0 msgq_get_enter: { id = 536871116, timeout = 4294967196 }
[00:00:04.841359522] (+0.001209715) 0 msgq_get_blocking: { id = 536871116, timeout = 4294967196 }
[00:00:04.842586724] (+0.001227202) 0 thread_sched_pend: { thread_id = 536871400, name = "control" }
[00:00:04.845175784] (+0.002589060) 0 thread_switched_out: { thread_id = 536871400, name = "control" }
[00:00:04.847778391] (+0.002602607) 0 thread_switched_in: { thread_id = 536871224, name = "maintenance" }
[00:00:04.850372307] (+0.002593916) 0 semaphore_take_exit: { id = 536871160, timeout = 4294967196, ret = 0 }
[00:00:04.851932188] (+0.001559881) 0 thread_busy_wait_enter: { usec_to_wait = 45000 }
[00:00:04.862569569] (+0.010637381) 0 isr_enter:
[00:00:04.862943629] (+0.000374060) 0 isr_exit:
[00:00:04.882869522] (+0.019925893) 0 isr_enter:
[00:00:04.883240236] (+0.000370714) 0 isr_exit:
[00:00:04.897800212] (+0.014559976) 0 thread_busy_wait_exit: { usec_to_wait = 45000 }
[00:00:04.898505581] (+0.000705369) 0 semaphore_take_enter: { id = 536871160, timeout = 4294967196 }
[00:00:04.899718665] (+0.001213084) 0 semaphore_take_blocking: { id = 536871160, timeout = 4294967196 }
[00:00:04.900941022] (+0.001222357) 0 thread_sched_pend: { thread_id = 536871224, name = "maintenance" }
[00:00:04.903535284] (+0.002594262) 0 thread_switched_out: { thread_id = 536871224, name = "maintenance" }
[00:00:04.906137807] (+0.002602523) 0 thread_switched_in: { thread_id = 536871592, name = "idle" }
[00:00:04.908731724] (+0.002593917) 0 idle:
[00:00:05.070669676] (+0.161937952) 0 isr_enter:
[00:00:05.071030022] (+0.000360346) 0 timer_expiry_enter: { id = 536871032 }
[00:00:05.071892903] (+0.000862881) 0 msgq_put_enter: { id = 536871116, timeout = 0 }
[00:00:05.073108712] (+0.001215809) 0 thread_sched_ready: { thread_id = 536871400, name = "control" }
[00:00:05.075707855] (+0.002599143) 0 msgq_put_exit: { id = 536871116, timeout = 0, ret = 0 }
[00:00:05.077264355] (+0.001556500) 0 semaphore_give_enter: { id = 536871160 }
[00:00:05.078134165] (+0.000869810) 0 thread_sched_ready: { thread_id = 536871224, name = "maintenance" }
[00:00:05.080737843] (+0.002603678) 0 semaphore_give_exit: { id = 536871160 }
[00:00:05.081596486] (+0.000858643) 0 timer_expiry_exit: { id = 536871032 }
[00:00:05.082466938] (+0.000870452) 0 isr_exit:
[00:00:05.082985938] (+0.000519000) 0 thread_switched_out: { thread_id = 536871592, name = "idle" }
[00:00:05.085589046] (+0.002603108) 0 thread_switched_in: { thread_id = 536871400, name = "control" }
[00:00:05.088182974] (+0.002593928) 0 msgq_get_exit: { id = 536871116, timeout = 4294967196, ret = 0 }
[00:00:05.089746474] (+0.001563500) 0 msgq_get_enter: { id = 536871116, timeout = 4294967196 }
[00:00:05.090956165] (+0.001209691) 0 msgq_get_blocking: { id = 536871116, timeout = 4294967196 }
[00:00:05.092183319] (+0.001227154) 0 thread_sched_pend: { thread_id = 536871400, name = "control" }
[00:00:05.094772379] (+0.002589060) 0 thread_switched_out: { thread_id = 536871400, name = "control" }
[00:00:05.097375057] (+0.002602678) 0 thread_switched_in: { thread_id = 536871224, name = "maintenance" }
[00:00:05.099968879] (+0.002593822) 0 semaphore_take_exit: { id = 536871160, timeout = 4294967196, ret = 0 }
[00:00:05.101528879] (+0.001560000) 0 thread_busy_wait_enter: { usec_to_wait = 45000 }
[00:00:05.112169510] (+0.010640631) 0 isr_enter:
[00:00:05.112540248] (+0.000370738) 0 isr_exit:
[00:00:05.132469688] (+0.019929440) 0 isr_enter:
[00:00:05.132836855] (+0.000367167) 0 isr_exit:
[00:00:05.147396272] (+0.014559417) 0 thread_busy_wait_exit: { usec_to_wait = 45000 }
[00:00:05.148102176] (+0.000705904) 0 semaphore_take_enter: { id = 536871160, timeout = 4294967196 }
[00:00:05.149315284] (+0.001213108) 0 semaphore_take_blocking: { id = 536871160, timeout = 4294967196 }
[00:00:05.150537688] (+0.001222404) 0 thread_sched_pend: { thread_id = 536871224, name = "maintenance" }
[00:00:05.153131950] (+0.002594262) 0 thread_switched_out: { thread_id = 536871224, name = "maintenance" }
[00:00:05.155734379] (+0.002602429) 0 thread_switched_in: { thread_id = 536871592, name = "idle" }
```
It is possible to see that regardless both threads are ready, this time control thread wins and enters at time [00:00:04.835992391].
- [X] Push tag: l6-task1