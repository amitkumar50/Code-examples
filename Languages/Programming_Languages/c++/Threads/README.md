**Threads**
- std::thread vs std::thread
- [Create Threads in C++](/Threads_Processes_IPC/Threads/Code)
- [std::async](#as)

### std::thread vs std::future
Promise is deferred computations, Same as [Future in Rust](/Languages/Programming_Languages/Rust)
```c
              std::thread | std::future, std::promise or std::async
-----|--------------------|-------------------------------------------
What | Seperate execution | Operate on threads, data can be transferred without locks
                            When a task wants to pass a value to another, it puts the value into a promise
                            When want to retrieve value get it in future
```

<a name=as></a>
## std::async
Used to create asynchronous task and execute in parallel.
- **promise(input side)** For passing value from calling to called thread.
- **future(output side)** For retreving values returned by called thred into main() thread. `auto returned_value = get_future()`

#### Code
- Imagine there is a huge floating number array stored on the disk, which has been partitioned over N different processing nodes.
- Design a software system in C++ to calculate the median value using N multiple processing nodes. 4 nodes are considered as Threads.
- [code](/Companies-Coding-Rounds/DisplaySweets/Code/Calculate-Median-using-N-nodes.cpp)