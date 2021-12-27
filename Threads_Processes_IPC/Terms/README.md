- [Asynchronous](#as)
  - [async function](#afun)
  - [block_on() rust](#bo)
  - [await](#aw)
  - [Asynchronous vs Multithreaded](#vs1)
- [Atomic](#at)
  - [Atomic Variables](#av)
- [Bound Waiting](#bw)
- [Busy Waiting](#busyw)
- [Concurrent](#con)
- [Condition Variable](#cv)
- [Context Switch](#cos)
- [Critical Section(requires Mutual Exclusion)](#cs)
- [CPU Bound](#cb)
- [Deadlock](#dl)
- [Future, Promise](#fut)
- [IO Bound](#io)
- [Parallelism](#pa)


<a name=as></a>
### Asynchronous
- Async program are [concurrent](#con) ie work on many tasks at a time but only using 1 thread, it usually returns a [future](#fut)
```c
main () {
  future = send()          //Does not block
  //execution resumes
}
```
**C++**
- Used to create asynchronous task and execute in parallel.
  - *promise(input side)* For passing value from calling to called thread.
  - *future(output side)* For retreving values returned by called thred into main() thread. `auto returned_value = get_future()`

<a name=afun></a>
#### async Function
Function prefixed with async & which will run asynchronously in rust.
```rs
async fn fun() {
    ...
}
```

<a name=bo></a>
#### block_on() 
Block/sleep the caller until async function does not run to completion. block_on() returns [future](/Languages/Programming_Languages/Rust/Triat_Interface).
```rs
$ cat Cargo.toml
[dependencies]
futures = "0.3"

$ cat main.rs
use futures::executor::block_on;
async fn fun1() { print!("fun1"); }
async fn fun2() { print!("fun2"); }
fn main() {
    block_on(fun1());                       //main() blocks until fun1(),fun2() does not compelte
    block_on(fun2());
}
$ main.exe
fun1 fun2
```

<a name=aw></a>
### await
Inside [async function](#afun) await is used to wait for another async function.
```rs
$ cat main.rs
use futures::executor::block_on;
async fn fun1() { print!("fun1"); }
async fn fun2() { print!("fun2"); }

aync fn async_main() {                  //fun1(),fun2() can independently execute. async_main() can run other tasks independently as well.
    fun1().await;
    //other work
    fun2.await();
}

fn main() {
    block_on(async_main());
}
```
**await vs block_on()** 
```c
                                        |   await          |        block_on()    |
----------------------------------------|------------------|----------------------|
Blocks current thread                   |     no           |          yes         |
wait for future to complete             |     yes          |          yes         |
Other tasks in async function can run?  |     yes          |          no          |
```

<a name=vs1></a>
#### Asynchronous vs Multithreaded
Asynchronous can be both single and multithreaded

<a name=at></a>
### [Atomic](https://en.cppreference.com/w/cpp/atomic/atomic)
- The end result of Atomic Operation is predictable and correct.
- If one thread writes to an atomic object while another thread reads from it, the behavior is well-defined. Example:
```cpp
a = 0;
void fun () {     //2 Threads executing this function
  a += 12;
}

/////////Problem without Atomic////////
- Thread-1 enters fun() does a=12, At this point of execution, thread-1 is preempted and another thread-2 gets into same function.
- Thread-2 does a=12
- Thread-1 comes back and has previous value (12), instead of writing(24), it ends up in writing (12). But value should be 24.
  
/////Solution(Make operation a+=12 atomic):////////
a. Take a as volatile
b. Use synchronization methods.
```

<a name=av></a>
### Atomic Variables
- Atomic types provide are used for shared-memory communication between threads. Atomic variables are safe to share between threads.
- ie values at end in these variables in not vague/unpredictable after n threads finished operating.

<a name=bw></a>
### Bound Waiting
Process-2 waits outside critical section while process-1 is executing inside.

<a name=busyw></a>
### Busy Waiting
**spinlock is Busy waiting**
- Thread-1(or process-1) is in Critical section and has set atomic variable var=1, before entering into CS.
- Thread-2 keeps checking var continously in while(1) to be 0 and enter CS.

**Busy waiting when doing IO**
- Let's suppose UserSpace program wants to read IO device. It invokes [Device Driver using device file](/Device_Drivers/Linux).
- [Device driver writes to Device Controller's register](/Device_Drivers/Linux/#how) for reading memory address & device driver sits in loop, continuously polling the device to see if it is done 
- When IO is completed data(if any) is returned to driver. Device driver returns control to user space process. User space process was said to be in busy waiting.

<a name=con></a>
### Concurrent (opposite of sequential)
Alternate between two tasks, then you are working on both tasks concurrently, but not in [parallelism](#pa)

<a name=cv></a>
### Conditional Variable / Condition Variable / shared variable
- This is used for synchronization.
- This block 1 thread/or multiple threads, until another thread modifies a shared variable (the condition), and notifies the condition_variable.
- Implemented as class in C++. [Code](/Threads_Processes_IPC/IPC/synchronization/Condition_Variable)

<a name=cos></a>
### Context Switch
- Means giving CPU from 1 process to other by scheduler.
- Each process is given a time interval(called its quantum) during which it is allowed to run. If the process keeps on running after the quantum also, CPU is preempted(fetched) from process and given to another process. 
- When the scheduler switches the CPU from executing process-1 to another process-2, the state of the current running process-1 is stored in its PCB. 
#### Tasks Done before CS
- **Suppose CS needed to be done from processA to processB**
  - _a._ Save processA registers, Remove Physical to Virtual Map (in MMU), Flush TLB for processA.
  - _b._ Load processB registers, Update Physical to Virtual Map (in MMU), Update TLB for processB.
- **Context switch from ProcessB to processA:** perform operations a and b again.
  - _c._ Additionally, Flushing memory caches(L1,L2,L3), reloading memory caches
#### Is context switch good? No(its wastage of CPU time). 
- _Smaller Quantum:_ Suppose quantum is of 4millisec, Context switch(saving loading registers, caches etc) is of 1millisec. 4 1 4 1 4 1 ... After 100millisec. 20millisec wasted in context switch(that's waste of CPU time).
- _Larger Quantum:_ Suppose quantum is of 100millisec, Context switch is 1millisec. 100 1 100 1. if 50 processes are in queue. last process will get CPU after 5 seconds. That's too long.
- _Reasonable Quantum:_ 20-50millisec

 <a name=cs></a>
### Critical Section(requires Mutual Exclusion)
  - Piece of code where 2 processes/threads are not allowed to execute concurrently. 
  - Ex: shared data structures, peripheral device, or network connection. CS should be accessed using synchronization. Eg: semaphore
- **Pareto Principle** 90% of CPU cycles are spent in 10% of code. Means we have to focus & parallelly implement this 10% of code
- **Race Condition?** 2 or more threads/processes are accessing/writing same shared resource(file, global variables etc) then at end result is unpredictable or wrong.
- **Reentrant**
  - Making second call same function while a previous call has not yet finished.
  - *Example:*
    - Suppose 2 threads can excute same function `fun()`.
    - Thread-1 executing is on line-11(writing to some big memory area `*ptr=bb`) of `fun()` & CPU decides to context switch. State of memory `*ptr` will be inconsistent and control is given to thread-2.
    - Thread-2 starts executing and writes to `*ptr=bbaaaa` and again context switch is done to thread-1.
    - Thread-1 comes back, expects `*ptr=bb` and starts writing `*ptr=bbbbb` and done.
    - Thread-2 reads `*ptr` thinking output as `bbaaaa` But `*ptr` is in inconsistent state.
  - **Solution:** mutex(But it eliminates parallelism)
```c
  fun(){            
      ...
11:    writing_to_big_memory (*ptr)
      ...
  }
  
int main(){  
  thread t1(fun);
  thread t2(fun);
  t1.join();
  t2.join();
}  
```

<a name=cb></a>
### CPU Bound 
Process spends most of time with CPU executing instructions. From Source: Program doing lot of calculations Eg: finding all possible permutations of a string.
<a name=dl></a>
### Deadlock
2 or more threads waits on resources which is/are held by each other. None of thread releases the resource and in turn waits for other to release. 
```c
Example-1
  Thread-1 acquires mutex-a. 
  Thread-2 acquires mutex-b. 
  Thread-1 wants to acquire mutex-b, thread-2 mutex-a
- Example-2:    
  Thread-1 acquires mutex a, b.    
  Thread-2 acquires mutex b,a
  
//Code for creating Deadlock
#include<pthread.h>
pthread_mutex_t     a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t     b = PTHREAD_MUTEX_INITIALIZER;
main(){
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);
    pthread_join(tid1, NULL);     //Wait until thread-1 to terminate
    pthread_join(tid2, NULL);    ////Wait until thread-2 to terminate
}
void *thread-1(void *a){
    while(1){
        pthread_mutex_lock(&a); 
        pthread_mutex_lock(&b);
        pthread_mutex_unlock(&b);
        pthread_mutex_unlock(&a);
    }
}

void *thread-2(void *a){
    while(1){
        pthread_mutex_lock(&b); 
        pthread_mutex_lock(&a);
        pthread_mutex_unlock(&a);
        pthread_mutex_unlock(&b);
    }
}
```

<a name=fut></a>
### Future(Rust) = Promise(C++)
This is a value which is not yet ready. (Same as Javascript=promises). if we wait for some time it will be ready, its something compute heavy(Eg: network channel etc).
- **Rust**
```rs
//Example, non working code
fn main() {
    let fut_x  = TcpStream::connect("127.0.0.1")
                 .and_then(|c| c.write("got it");       //When connected write this

    let ex: Executor;
    let a = ex.run(fut_x);
}
```
- **Promise**
```cpp

```

<a name=io></a>
### IO Bound 
Process spends most of time in IO. From source: Program doing lot of File RW operations.
```c
Q: Find whether a process is IO Bound or CPU Bound?
 top command has %cpu column(Total CPU time used by process from when its started). CPU bound will have high %cpu.
 while (i<100){    ++i;                //Its %cpu = 100
    if(i==98)
        i=0;
 }
 ```

<a name=pa></a>
### Parallelism
2 tasks assigned to 2 threads running on different cores.
