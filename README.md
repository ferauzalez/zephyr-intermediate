# L3 Homework
## Task 1
For this task I ran first the demo code for observe the behaviour more closely. After that I delete the alarm because was not required, I keep the loogger for get a slower logging. Finally I've got the following output:
```bash
*** Booting Zephyr OS build v4.4.0 ***
[00:00:00.000,000] <inf> demo: === L4 HOMEWORK: Zbus Pub-Sub ===
[00:00:00.000,000] <inf> demo: sensor publishes every 150ms
[00:00:00.000,000] <inf> demo: display listener runs in publisher context
[00:00:00.000,000] <inf> demo: logger uses message subscriber copies
[00:00:00.000,000] <inf> demo: [SENSOR] publish seq=0 temp=20000 mC
[00:00:00.000,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=0 temp=20000 mC
[00:00:00.000,000] <inf> demo: [LOGGER-MSG] thread=logger seq=0 temp=20000 latency=0ms
[00:00:00.150,000] <inf> demo: [SENSOR] publish seq=1 temp=20250 mC
[00:00:00.150,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=1 temp=20250 mC
[00:00:00.300,000] <inf> demo: [SENSOR] publish seq=2 temp=20500 mC
[00:00:00.300,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=2 temp=20500 mC
[00:00:00.350,000] <inf> demo: [LOGGER-MSG] thread=logger seq=1 temp=20250 latency=200ms
[00:00:00.450,000] <inf> demo: [SENSOR] publish seq=3 temp=20750 mC
[00:00:00.450,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=3 temp=20750 mC
[00:00:00.600,000] <inf> demo: [SENSOR] publish seq=4 temp=21000 mC
[00:00:00.600,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=4 temp=21000 mC
[00:00:00.700,000] <inf> demo: [LOGGER-MSG] thread=logger seq=2 temp=20500 latency=400ms
[00:00:00.751,000] <inf> demo: [SENSOR] publish seq=5 temp=21250 mC
[00:00:00.751,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=5 temp=21250 mC
[00:00:00.901,000] <inf> demo: [SENSOR] publish seq=6 temp=21500 mC
[00:00:00.901,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=6 temp=21500 mC
[00:00:01.050,000] <inf> demo: [LOGGER-MSG] thread=logger seq=3 temp=20750 latency=600ms
[00:00:01.051,000] <inf> demo: [SENSOR] publish seq=7 temp=21750 mC
[00:00:01.051,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=7 temp=21750 mC
[00:00:01.201,000] <inf> demo: [SENSOR] publish seq=8 temp=22000 mC
[00:00:01.201,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=8 temp=22000 mC
[00:00:01.351,000] <inf> demo: [SENSOR] publish seq=9 temp=22250 mC
[00:00:01.351,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=9 temp=22250 mC
[00:00:01.400,000] <inf> demo: [LOGGER-MSG] thread=logger seq=4 temp=21000 latency=800ms
[00:00:01.502,000] <inf> demo: [SENSOR] publish seq=10 temp=22500 mC
[00:00:01.502,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=10 temp=22500 mC
[00:00:01.652,000] <inf> demo: [SENSOR] publish seq=11 temp=22750 mC
[00:00:01.652,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=11 temp=22750 mC
[00:00:01.750,000] <inf> demo: [LOGGER-MSG] thread=logger seq=5 temp=21250 latency=999ms
[00:00:01.802,000] <inf> demo: [SENSOR] publish seq=12 temp=23000 mC
[00:00:01.802,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=12 temp=23000 mC
[00:00:01.952,000] <inf> demo: [SENSOR] publish seq=13 temp=23250 mC
[00:00:01.952,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=13 temp=23250 mC
[00:00:02.100,000] <inf> demo: [LOGGER-MSG] thread=logger seq=6 temp=21500 latency=1199ms
[00:00:02.102,000] <inf> demo: [SENSOR] publish seq=14 temp=23500 mC
[00:00:02.102,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=14 temp=23500 mC
[00:00:02.253,000] <inf> demo: [SENSOR] publish seq=15 temp=23750 mC
[00:00:02.253,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=15 temp=23750 mC
[00:00:02.403,000] <inf> demo: [SENSOR] publish seq=16 temp=24000 mC
[00:00:02.403,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=16 temp=24000 mC
[00:00:02.450,000] <inf> demo: [LOGGER-MSG] thread=logger seq=7 temp=21750 latency=1399ms
[00:00:02.553,000] <inf> demo: [SENSOR] publish seq=17 temp=24250 mC
[00:00:02.553,000] <inf> demo: [DISPLAY-LIS] thread=sensor seq=17 temp=24250 mC
[00:00:02.703,000] <inf> demo: [SENSOR] done
[00:00:02.801,000] <inf> demo: [LOGGER-MSG] thread=logger seq=8 temp=22000 latency=1600ms
[00:00:03.151,000] <inf> demo: [LOGGER-MSG] thread=logger seq=9 temp=22250 latency=1800ms
[00:00:03.501,000] <inf> demo: [LOGGER-MSG] thread=logger seq=10 temp=22500 latency=1999ms
[00:00:03.851,000] <inf> demo: [LOGGER-MSG] thread=logger seq=11 temp=22750 latency=2199ms
[00:00:04.201,000] <inf> demo: [LOGGER-MSG] thread=logger seq=12 temp=23000 latency=2399ms
[00:00:04.551,000] <inf> demo: [LOGGER-MSG] thread=logger seq=13 temp=23250 latency=2599ms
[00:00:04.901,000] <inf> demo: [LOGGER-MSG] thread=logger seq=14 temp=23500 latency=2799ms
[00:00:05.251,000] <inf> demo: [LOGGER-MSG] thread=logger seq=15 temp=23750 latency=2998ms
[00:00:05.601,000] <inf> demo: [LOGGER-MSG] thread=logger seq=16 temp=24000 latency=3198ms
[00:00:05.951,000] <inf> demo: [LOGGER-MSG] thread=logger seq=17 temp=24250 latency=3398ms
[00:00:06.302,000] <inf> demo: [LOGGER-MSG] done received=18
```