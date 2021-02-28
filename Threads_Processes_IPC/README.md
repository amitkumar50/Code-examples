## Thread(miniprocess) vs Process

### Comparison

||Thread|Process|
|---|---|---|
|Weight|Light(Since no duplication of process space)|Heavy(Complete process space(CS,DS,SS,HS) duplicated to child|
|Speed|Fast. When process need to execute thread-2, while executing thread-1. It does not need Context Switch,No memory cache flush, No Trap instruction. Since everything is inside process(No need to go into kernel space). Process can decide his own scheduling algo|SLOW. Context switch needed, Memory cache flushing needed, Trap needed and to achieve these control need to go into kernel space|

### Thread Usecases
- **1. Editing/Displaying/(Storing on cloud) Big word document at same time**
  - Suppose user is editing 10000 lined word document online. if he edits 9000th page and click save, word process need to search from starting text changed, pick and store the diff on cloud. If user want to scroll to some other page while word process is saving on cloud(Since this is single threaded) this will hang the Word Document(making user annooyed).
  - **Solution** 3 threads, 1 for diplay, 1 for saving on cloud, 1 for editing the file(ie picking up the changes). Benefits of 3 threads: while thread-2 is saving on cloud. Thread-1 can still display contents of user without delay.
- **2. Webserver**
  - if webserver is single threaded, then it has to wait everytime to get resource from DB/backend while incoming connections keep on getting discarded.
