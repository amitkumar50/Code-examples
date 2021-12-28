Forget the mistake remember the lesson. **Lesson:**
- _1. Understand Question Completely._ 
  - Read. Repeat(and ask questions). Doctest(small, medium, big inputs). Visualize
- _2._ You do lot of Yes after interviewer comments something, try follow on. Lesson: Take your stand. 
- _2. Concentrate, Meditate_

## Round-1 (Video call)
- MTU vs MSS, spinlock vs other synchronization mechanisms, project related

## Round-2 (Tasterday / Onsite Interview)
### 1. Logical Question
- **Q1a. 3 Bulbs & 3 switches?** There are 3 bulbs and room-1 and 3 switches on other room-2. From 1 room you cannot see anything in other room. Identify which switch is for which bulb?
- _Ans:_ 
  - Turn on switch1 for 1 hour, then switch it off. Turn on switch2 and run immediately to room-2. Most hot bulb=switch1, Turned on bulb=switch2, off cold bulb=switch3.
### 2. C/C++ Output related question
- static, global variable questions.
- **Q2b. Will it compile,run in C/C++? Point 3 mistakes**
```c
$ cat test.c
int main() {
  int a = 42;
  printf("%d\n",a);
}

//In C it compiles with warning. Because libc(C Standard library) has defined it already.
$ gcc test.c
test.c:3:5: warning: implicit declaration of function ‘printf’ [-Wimplicit-function-declaration]
     printf("%d\n",a);
     ^~~~~~
test.c:3:5: warning: incompatible implicit declaration of built-in function ‘printf’
test.c:3:5: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’

//In C++ did not compile. C++ always need header include
$ g++ test.c
test.c: In function ‘int main()’:
test.c:3:5: error: ‘printf’ was not declared in this scope
     printf("%d\n",a);

3 Mistakes in question:
a. return statement missing from main. Return value is stored in rax which presently stores 3 (return value from printf) which is wrong.
b. Header file include is missing
c. main() should be main(int argc, char** argv) 
```
### 3. [Code: Doubly Linked List](/DS_Questions/Data_Structures/Linked_Lists/Doubly_LinkedList/Using_Double_Pointer/AddDelete_AfterPosition.md)
```c
typedef struct node {
  int val;
  node* next;
  node* prev;
}Node;

Implement 3 functions:
1. void InitializeToNull(Node** ptr);                        //Initialize a head pointing to null
2. void AddAfter (Node** head, int position, Node node);    //Add a node inside DLL after position p.
3. void RemoveNode (Node** head, int val)                   //Remove element from Doubly Linked List
```
### 4. OOD: Asynchronous Logger class
- Create logging class in C++ which supports logging to different targets(Eg: file, console, remote server). It should have 1 method `void log (const std::string& message);`
- Features of logging class:
  - _1._ Thread safe
  - _2._ Changing logging target at runtime
  - _3._ Extend logging class in future with new logging targets without touching existing code.
- **What's needed to be done?**
  - _a._ UML diagrams
  - _b._ Write Code of logging class
    - log to console, file, remote UDP server(use netcat to test server side implementation). Write a test program to test the code
    - Add timestamps to log messages(resolution nanoseconds).
  - _c._ `log()` method should queue the messages and process asynchronously in another thread.
  - _d._ Free to use C++11, STL, boost
