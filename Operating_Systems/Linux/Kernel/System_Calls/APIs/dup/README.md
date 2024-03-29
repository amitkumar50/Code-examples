**dup**
- **dup() APIs**
  - [1. dup()](#dup)
  - [2. dup2()](#dup2)
    - [2.1 Output redirection using dup2](#impl)
  - [3. dup3()](#dup3)

## [dup() / Duplicate](https://man7.org/linux/man-pages/man2/dup2.2.html)
- All dup() system calls create copy of file descriptor.
- Input:0, Output:1, Error:2
- After a successful return of API, the old and new file descriptors may be used interchangeably. Both refers to same open file description and thus share file offset and file status flags

## dup() APIs
<a name=dup></a>
### 1. int dup(int oldfd)
- Creates a copy of oldfd, using the lowest-numbered unused file descriptor & returns new descriptor.

<a name=dup2></a>
### 2. int dup2(int oldfd, int newfd)
- dup2() also creates copy of oldfd, it uses the file descriptor number specified in newfd.
- If newfd **was already opened, it is silently closed and reused**. Closing and reusing the file descriptor done atomically.

<a name=impl></a>
#### 2.1 Output redirection `$ cat a>b`
printf("str") writes the string to STDOUT(fd=1).
```c

    ====Output_screen_Buffer====          =====a.txt=====
    /\                                    /\
  fd=1                                   fd_a=4
  saved_stdout

dup2(fd_a, 1)
  close (1)
                      ======a.txt=======
                      /\
                      fd=4,1      //Both fd's point to file=a.txt now

#include<unistd.h>
int main(){
  int saved_stdout = dup(1);             //Saving STDOUT for restoring after completing work
  int fd_a = creat("a.txt", 0644);       //1. Create a file and open it
  dup2 (fd_a, STDOUT_FILENO);            //2. Create newfd(STDOUT) as duplicate of "file.txt".
                                         //   Now if somewrite on STDOUT, it will be written to "file.txt"
  printf("Be excited");
  
  dup2 (1, saved_stdout);                //3. Work completed, Lets restore stdout back
  close (fd_a);
}
$ gcc test.c
$ cat a.txt
  Be excited
```

<a name=dup3></a>
### 3. int dup3(int oldfd, int newfd, int flags)
> flags = O_CLOEXEC
- same as dup2() except caller can force **close-on-exec flag** to be set for new file descriptor by specifying [O_CLOEXEC](https://man7.org/linux/man-pages/man2/open.2.html).
