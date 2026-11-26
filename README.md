# L7 Homework

I have been working on the assignments using Windows but for this homework I used WSL on Windows. To push to my fork repo, I modified the `main.c`, and this readme to paste the outputs. Please let me know if you need other files and I will push them too.

I read (this example)[https://github.com/Ac6Embedded/Zephyr-Examples/blob/main/user-mode/user_mode_separate/src/main.c] and (this lesson)[https://www.zephyrproject.org/user-mode-explained-in-simple-words/] to understand the subject a bit more. 

## Output of bash after setup
```bash
=== Running in QEMU for 10 seconds ===
*** Booting Zephyr OS build v3.7.2 ***
parser: received 'get=0'
parser: setting 0 = led=off
parser: received 'get=41941731'
parser: setting 41941731 = EC-PRIVATE-KEY:8
parser: received 'get=41941732'
parser: setting 41941732 = f3a91c25d7e04b6
qemu-system-arm: terminating on signal 15 from pid 1395 (timeout)
```
## Output of bash after modifying main.c

```bash
=== Running in QEMU for 10 seconds ===
*** Booting Zephyr OS build v3.7.2 ***
parser: received 'get=0'
parser: setting 0 = led=off
parser: received 'get=41941076'
[00:00:00.000,000] <err> os: ***** MPU FAULT *****
[00:00:00.000,000] <err> os:   Data Access Violation
[00:00:00.000,000] <err> os:   MMFAR Address: 0x38003260
[00:00:00.000,000] <err> os: r0/a1:  0x027ff854  r1/a2:  0x00000000  r2/a3:  0x0000000a
[00:00:00.000,000] <err> os: r3/a4:  0x38003260 r12/ip:  0x00000000 r14/lr:  0x0ccccccc
[00:00:00.000,000] <err> os:  xpsr:  0x41000000
[00:00:00.000,000] <err> os: Faulting instruction address (r15/pc): 0x100007e0
[00:00:00.000,000] <err> os: >>> ZEPHYR FATAL ERROR 19: Unknown error on CPU 0
[00:00:00.000,000] <err> os: Current thread: 0x38000060 (unknown)
[00:00:00.010,000] <err> os: Halting system
qemu-system-arm: terminating on signal 15 from pid 1522 (timeout)
```