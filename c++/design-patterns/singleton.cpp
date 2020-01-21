/*
 	singleton.cpp	//Single Object

What? Only single instance/object of class can be created. And provides Global point of access to it.

How to Acheive?
1.  Block All object creation methods
        a. Make default constructor pvt: Object should not be created from direct calls of constructor.
        class A{
                int a;
        public:
                A(int b){a=b}
        };
        main(){
                A obj1 = new A(1);
                A obj2 = new A(2);      //Two objects are created
        }

        b. Make copy constructor pvt: CCtr is used to copy an exiting object to create new object.
        class test{    
            String *s; 
            test (test const &t1){    
                this->s = t1.s;
            }
        };
        int main(){
            test t1;
            t2 obj(t);                  //Two objects created. t2 as copy of t1.
        }       
        
        c. Make Assignment operator pvt: Assignment Operator is used if object is already existent,new object is given new value from other object.
        class test{
                test & operator =(const test &t){  cout<<"=";  }
        };
        int main(){
                test t1, t2;            
                t2 = t1;                //Two objects created.
        }

2. Take a static variable and save Object address in it and initialize to NULL.

3. Use Static Method to create Objects: because we need to deal with static variables inside.

4. Create objects using static variable only from main


***************Multi-threaded, Synchronization***************
Multithreaded: Below code is not thread-safe. if 2 threads run this code it will creates two objects for singleton.
Solution:
    1. Making fun() as synchronized (In Java)
            public static synchronized test fun(){        //Adding synchronized makes every thread to wait for its turn.    
            }
    2. Using Mutexes (In Linux)
    
Drawbacks of Synchronization: This is heavy/time consuming operation.
1. Do eagerly instance creation (instead of lazily done Below)
            public class test{
                    static test obj = new test(); //Since all threads have same DS. so there will be only 1 copy of obj.
                    test(){}
                    public:
                        static test fun(){  return obj;  }
            }
2. Check the variable before locking mutex//Double-Checking Locking
        class test{
                volatile test obj;
            public:
                static test fun(String n){
                        if(obj == NULL){        //Adding extra check for Object reduces overhead significantly.
                            pthread_mutex_lock(&var);
                                if(obj=NULL)
                                        obj = new test(n);
                            pthread_mutex_unlock(&var);
                        }
                        return obj;    
                }
        }
**************************************************************
*/

#include<iostream>
using namespace std;

class test{
private:	
        test(){}    				//1
        test(const test &){}    		//2
        test operator=(const test &);    	//3
        static test *obj;    			//4
public:
                static test *fun(){      	//5
                        if(obj == NULL)
                                obj = new test;
                        return obj;
                }
};

test *test::obj = NULL;    			//4

int main(){
	test *p1 = test::fun();    //Address: 0x6000227f0		//6
	cout<<"p1="<<p1<<"\n";
	test *p2 = test::fun();    //Address: 0x6000227f0
	cout<<"p2="<<p2<<"\n";
	return 0;
}
/*
Output:
# ./a.out
p1=0x2129e70
p2=0x2129e70
 */
