/*
************************Thread Attributes?************************
Thread Attributes? These are a way to specify behavior that is different from the default.
Usually Threads are created with Default attributes. Attributes are specified only at thread creation time; 
they cannot be altered while the thread is being used.

Name			Default-value		Possible-values		Meaning
contentionScope		PTHREAD_SCOPE_PROCESS	PTHREAD_SCOPE_PROCESS	Created thread is local to process
						PTHREAD_SCOPE_SYSTEM
detachstate		PTHREAD_CREATE_JOINABLE	PTHREAD_CREATE_JOINABLE	Exit status of thread would be 
						PTHREAD_CREATE_DETACHED	preserved after the thread terminates
stackaddr		NULL						No stack is allocated to thread yet
stacksize		0
inheritsched		PTHREAD_INHERIT_SCHED	PTHREAD_INHERIT_SCHED	Thread inherits parent thread scheduling priorities
						PTHREAD_EXPLICIT_SCHED
schedpolicy		SCHED_OTHER					Thread uses Solaris-defined fixed priority scheduling.
									threads run until preempted by a higher-priority
									thread or until they block or yield.

Example:
 ret = pthread_attr_init(&tattr);	//Initialize with default attributes
 ret = pthread_attr_*(&tattr,SOME_ATRIBUTE_VALUE_PARAMETER);    //Call function to alter default value
 ret = pthread_create(&tid, &tattr, start_routine, arg);	   //Create Thread
*****************************************************************

********************Thread Creation?*********************
- TCB is allocated
- [On Windows] CreateThread(NULL,0,fun,0,0,NULL)

*********************************************************

*/


#include<pthread.h>
#include<stdio.h>

void *fun(){
    printf("Thread Created\n");
}

void main(){
	pthread_t tid;     //typedef int pthread_t; //sysdeps/pthread/bits/pthread.h

/*pthread_create (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)
NULL Attributes*/
	pthread_create(&tid, NULL, fun, NULL);

	pthread_join(tid, NULL);
}

/*
# gcc -lpthread thread.c
*/
