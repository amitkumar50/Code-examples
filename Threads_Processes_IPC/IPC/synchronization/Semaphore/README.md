**[Semaphore](sem)**
- **[Types of Semaphores](#t)**
  - [1. Binary = `std::counting_semaphore<1>`](#b)
    - [Thread1 signals Thread2](#t1st2)
      - [POSIX](#pos)
      - [C++](#cpp)
  - [2. Counting = `std::counting_semaphore<n>`](#coun)
- [Datastructures: sem_t, APIs: sem_init, sem_post, sem_wait](Datastructures_API.md)

<a name=sem></a>
## Semaphore
- A integer whose [atomicity](/Threads_Processes_IPC/Terms) is maintained by kernel.
- **[Interupts](/Operating_Systems/Linux/Kernel/Interrupts) are disabled breifly for Semaphore Operations**
  - *Why?* Since interrupt can destroy atomic operation and value of semaphore can be unpredictable after processing interrupt(if interrupt is generated by process-2) which want to enter CS.
- **How Semaphore Operation is performed?**
  - _1._ OS first disables [interrupts](/Operating_Systems/Linux/Kernel/Interrupts).
  - _2._ Then reads the value of semaphore. 
    - {Semaphore Down Operation} if(semaphore == 0) puts calling process on a list of blocked processes associated with the semaphore. 
    - {Semaphore Up Operation} If it is doing an up, it must check to see if any processes are blocked on the semaphore. If one or more processes are blocked, one of them is removed from the list of blocked processes and made runnable. 
  - _3._ When all these operations have been completed, interrupts can be enabled again.
```c
  if (variable==1)            //sem_post
    //Enter in Critical section 

  if (variable==0)            //sem_wait
    //Entrace blocked. Wait
```
- Similar to mutex only 1 thread can enter Critical section, But Thread-1 will signal Thread-2 once he's done. Eg: [Binary Semaphore](#t1st2)
```c
  Thread-1()      Critical_Section()      Thread-2()
      ---execute---->                     waiting
                   Thread-1 Done
                   
  signal Thread-2 ------------------------->
  waiting
                      <--------execute--------                  
```

<a name=t></a>
## Types of Semaphores
<a name=b></a>
### 1. Binary
- Can take only 2 values (0 or 1).
- **Use case:** 1 Producer/1 Consumer Problem_
<a name=t1st2></a>
#### Thread1 signals Thread2
<a name=pos></a>
**POSIX**
```c++
#include<iostream>
#include<thread>
#include<unistd.h>
#include<semaphore.h>
sem_t sem;

void CriticalSection() {
  std::cout<<"Critical section\n\n";
  sleep(1);
}

void thread1(int a){
  for(;;) {
    std::cout<<"Thread1 inside ";
    CriticalSection();                //2. Thread1 goes into Critical Section, does processing
    sem_post (&sem);                  //3. Thread1 informs Thread2, that Thread1 is out of Critical Section
  }
}
void thread2(int a){
  for (;;) {
    sem_wait(&sem);
    std::cout<<"Thread2 inside ";
    CriticalSection();                  //4. Thread2 enters Critical Section
  }
}

int main(){
  std::thread t1(thread1, 5);            //1. Two Threads created.
  std::thread t2(thread2, 5);
  t1.join();
  t2.join();
}
# .a/out
Thread1 in Critical section
Thread2 in Critical section
Thread1 in Critical section
Thread2 in Critical section
```

<a name=cpp></a>
**C++ (Introduced in C++20)**
<a name=rel></a>
- [sem.release()](https://en.cppreference.com/w/cpp/thread/counting_semaphore/release) = sem_post()
  - Atomically increments the internal counter by the value of update. Any thread(s) waiting for the counter to be greater than 0.
<a name=acq></a>
- [sem.acquire()](https://en.cppreference.com/w/cpp/thread/counting_semaphore/acquire) = sem_wait()
  - Atomically decrements the internal counter by 1 if it is greater than 0; otherwise blocks until it is greater than 0.
```cpp
#include <iostream>
#include <semaphore>
#include <thread>
#include <vector>
using namespace std;
std::vector<int> vec = {0, 1, 0, 3};

std::binary_semaphore sem(0);                            // (1)

void Producer() {
    sleep(2);
    std::cout << "Producer Created Task..." << '\n';
    vec[2] = 1;
    for (auto i:vec)
        cout << i << ", ";
    cout << "\n";
    sem.release();                                       //sem_post
}

void Consumer() {
    std::cout << "Consumer Waiting..." << '\n';
    sem.acquire();                                        //sem_wait
    std::cout << "Consumer: Got Task" << '\n';
    vec[2] = 2;
    std::cout << "Consumer: Completed Task" << '\n';
    for (auto i:vec)
        cout << i << ", ";
    std::cout << '\n';
    
}

int main() {
    std::thread tc(Producer);
    std::thread tw(Consumer);
    tc.join();    tw.join();
}
$ ./a.out
Consumer Waiting...
Producer Created Task...
0, 1, 1, 3, 
Consumer: Got Task
Consumer: Completed Task
0, 1, 2, 3, 
```

<a name=coun></a>
### 2. Counting Semaphore
- **Usecases:** 
  - _1. n Producers/n Consumers Problem:_ Choclate,cold drink Vending machine at airport
    - n Consumers Threads: Any number of customer can take out items from machine served by consumer threads
    - n Producers Threads: Thread-1 putting choclates, Thread-2 putting cold drinks.
  - Consumer Threads need to wait if items are not in machine, Producers will notify consumers after placing items.
- Acquiring a semaphore can occur on a different thread than releasing the semaphore
```cpp
std::counting_sempahore<n> sem(m);

n = Least Max value.(should be >0). n concurrent threads allowed inside CS.
m = Initial value of semaphore
```
