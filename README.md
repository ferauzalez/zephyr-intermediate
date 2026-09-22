I make a test with the three taks with differents priority levels. With 1516 samples I observe the following count appearences:
* T_LOW:	312 times
* T_MED:	467 times
* T_HIGH:	936 times
  So, T_HIGH was the thread that ran more often.
  
In order to see if priority does affect interleaving, I watched again the demo of interleaving. After refreshing these concepts I can say that indeed priority affects interleaving helping the scheduler decide what thread run when two task are ready.

And finnaly I paste two outputs:
* The following is a sample of the homework with the propose message:
T_HIGH running
T_MED running
T_HIGH running
T_LOW running
T_HIGH running
T_MED running
T_HIGH running
T_HIGH running
T_LOW running
T_MED running
T_HIGH running
T_HIGH running

* The following is a sample of the homework with the fourth cooperative thread and a time elapsed message:
*** Booting Zephyr OS build v4.4.0 ***
Cooperative thread running. Iteration number 0.
Cooperative thread running. Iteration number 1.
Cooperative thread running. Iteration number 2.
Cooperative thread running. Iteration number 3.
Cooperative thread running. Iteration number 4.
T_HIGH running. Time elapsed: 0 ms
T_MED running. Time elapsed: 0 ms
T_LOW running. Time elapsed: 0 ms
T_HIGH running. Time elapsed: 100 ms
T_MED running. Time elapsed: 200 ms
T_HIGH running. Time elapsed: 200 ms
T_LOW running. Time elapsed: 300 ms
T_HIGH running. Time elapsed: 300 ms
T_MED running. Time elapsed: 400 ms
T_HIGH running. Time elapsed: 400 ms
T_HIGH running. Time elapsed: 500 ms

