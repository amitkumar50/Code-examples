**Threads can be implemented anywhere: user space and the kernel.**

<img src=./userspace_kernelspace_threads.PNG width=500 />

## User Space Threads
- Kernel is not aware about UST
- Kernel see it as ordinary, single-threaded process.
- **Advantages**
  - *1.* Complete thread context switch is done in user space, call need not to go into kernel space or call trap().
  - *2.* UST can be implemented on OS which does not support threads
  - *3.* Each process can have its own customized Thread scheduling algos.
  - *4.* [Threads are very fast](/Threads_Processes_IPC/README.md)
- **Problems**
  - *1.* Suppose a process has 3 threads. Thread-1 waits on [System call](https://sites.google.com/site/amitinterviewpreparation/c-1/device-driver)(blocking read()) or on [Page Fault](https://sites.google.com/site/amitinterviewpreparation/c-1/memory-management/virtual-memory) (In both cases mode is changed from user to kernel) then whole process will block/sleep. All other threads will also block(even if other threads are in runnable state).
    - *Solutions:* 
      - *1.* Making blocking calls as non-blocking.
      - *2.* [Upcall](/Threads_Processes_IPC/Threads/UserSpace_KernelSpace_Threads/Upcall_Scheduler_Activation.md)
- **How it works?** Each process will need its own **Thread Table**(to keep track of threads in process). 
### Thread Table
  - **What?** When thread is moved to sleep or blocked state(ie it finished its execution for moment), it state information is stored in thread-table so that later thread can come back to running state.For example thread1 waiting for input from thread2.
  - This is Similar to process table containing following entries:
```c
 Each thread’s program counter, stack pointer, registers, state etc
```

## Kernel space threds
- **Advantages**
  - *1.* No Thread-Table in each process.
- **Disadvantages**
  - *1.* Every thread will need some Thread-Control-block and stack space in kernel, in case of large number of threads this will become problem.
  - *2.* Every thread will make [system calls](https://sites.google.com/site/amitinterviewpreparation/c-1/device-driver) in kernel and its cost is high.
  - *3.* Slower than user level threads.
- **How it works**
  - When a thread wants to create/destroy an existing thread, it makes a kernel call, which then does the creation or destruction by updating the kernel thread table.
  - Now kernel will have thread-Table having same contents.
