
2. 进程间的协调通信(8学时)
掌握进程的概念、进程间通信的基本原理、集成间通信的主要类型和各自的特点。实验内容：在linux平台上实现1个父进程、2个子进程，利用管道和共享内存实现两个子进程之间数据快速传送。
(1) 创建一个进程，再创建一对管道、一块共享内存（大于64kB）；
(2) 通过fork（）函数生成2个子进程；
(3) 调试程序，确定父、子进程之间可以双向通信；
(4) 调试程序，确定两个子进程之间可以通过父进程中转实现双向通信；
(5) 调试程序，确定两个子进程都可访问共享内存；
(6) 实现两个子进程之间无冲突地访问共享内存。传送的数据块不小于32kB，为了能够看到演示效果，读/写每个字节后都延时0.5ms。

Process:

```
the first child process:
open auth.log ----> fgets file ----> P(sem_w) [test point 1] ----> write pipe ----> V(sem_d) [test point 2]

parent process:
P(sem_d) [test point 3] ----> read pipe / write pipe ----> V(sem_r) [test point 4]

the second child process:
P(sem_r) [test point 5] ----> read pipe ----> V(shm_w) [test point 6] ----> write shm(cycle queue) ----> V(shm_r) [test point 7] ----> V(sem_w) [test point 8]

the first child process:
P(shm_r) [test point 9] ----> read shm(cycle queue) ----> V(shm_w) [test point 10]
```

一号子进程向父进程通过管道传递数据
父进程接收到数据后，通过管道向二号子进程传递数据
二号子进程接收到数据后，写入共享内存
一号子进程读取共享内存中的数据，并输出

3 个生产者消费者模型，1 个循环队列。分别解决数据同步问题、传输的数据块过大问题。
