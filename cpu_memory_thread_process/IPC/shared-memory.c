/*      shared_memory.c

Shared Memory: Common memory that is present between 2 or more processes.
        Process-1                               Process-2
                        |shared-memory|

Process of adding message:
a. ftok(char *pathname, int proj_id): convert a pathname and a project identifier to a unique key
b. shmget(key_t,size_tsize,intshmflg); upon successful completion, returns an identifier for the shared memory segment.
c. shmat(): Before starting to use shared memory segment, you need to attach to it using shmat().
d. shmdt(): After using the shared memory it needed to be detached
e. shmctl(): After detaching shared memory need to be destroyed.
*/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include "stdio.h"

#ifdef WRITER
int main(){
    key_t key = ftok("shmfile",65);

    int shmid = shmget(key,1024,0666|IPC_CREAT);
    char *str = (char*) shmat(shmid,(void*)0,0);

    printf("Write data:");
    scanf("%s",str);
    printf("Data written in memory: %s\n",str);
    shmdt(str);
    return 0;
}
#endif

#ifdef READER
int main()
{
    key_t key = ftok("shmfile",65);

    int shmid = shmget(key,1024,0666|IPC_CREAT);
    char *str = (char*) shmat(shmid,(void*)0,0);
    printf("Data read from memory: %s\n",str);
    shmdt(str);
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}
#endif

/*Output:
# ./writer 
Write data:amit
Data written in memory: amit
# ./reader 
Data read from memory: amit
*/
