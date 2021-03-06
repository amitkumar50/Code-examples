## Timed mutex Try lock for
- **What is TIMED MUTEX?** Unlike try_lock(){Which returns immediately} this waits for specific timeout duration and returns if lock is not acquired during that time.
- **TRY_LOCK_FOR()?** Waits until specified timeout duration has elapsed or lock is acquired.
- **Return:**
  - true: if lock is acquired within timeout duration
  - false: if lock cannot be acquired

### Code
- Thread-1 acquires the lock, Sleeps for 4 seconds  
- Thread-2 wait for 3 seconds, But lock was not released in 3 seconds, so thread-2 returns false
  
```c++
#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>

std::timed_mutex tm;

void fun(int t){
  if(tm.try_lock_for(std::chrono::milliseconds(3*1000))){
    std::cout<<"Thread "<<t<<" in Critical Section\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(4*1000));
    tm.unlock();
  }else{
    std::cout<<"Thread "<<t<<" cannot get the lock\n";
  }
}

int main(){
  std::thread t1(fun,1);
  std::thread t2(fun,2);
  t1.join();
  t2.join();
}

# g++ timed_mutex.cpp -pthread
# ./a.out 
Thread 1 in Critical Section
Thread 2 cannot get the lock
```
