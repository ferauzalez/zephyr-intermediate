I ran the l2-demo in order to observe a race condition and I got the following output, detecting the race condition:

```bash
*** Booting Zephyr OS build v4.4.0 ***
[00:00:00.000,000] <inf> demo: Expected final value: 2000000
[00:00:00.163,000] <inf> demo: [worker_a] finished
[00:00:00.167,000] <inf> demo: [worker_b] finished
[00:00:00.167,000] <inf> demo: Actual final value: 1520645
[00:00:00.167,000] <err> demo: Race condition confirmed: lost 479355 updates
```
And after adding a mutex, the race condition was avoided:

```bash
*** Booting Zephyr OS build v4.4.0 ***
[00:00:00.000,000] <inf> demo: START
[00:00:00.000,000] <inf> demo: Expected final value: 2000000
[00:00:40.880,000] <inf> demo: [worker_a] finished
[00:00:40.880,000] <inf> demo: [worker_b] finished
[00:00:40.880,000] <inf> demo: Actual final value: 2000000
[00:00:40.880,000] <inf> demo: No race this run
```