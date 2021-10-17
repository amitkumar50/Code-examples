/*	no_of_steps_to_reduce_no_to_1.cpp

https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one

Goal: make the string s=="1".

Perform operation on last bit.
if last-bit=0. Indicates no is multiple of 2. Divide by 2 removes last 0
if last-bit=1. Indicates no is odd. Add 1.
	{1+1 = 0(at position),1(carry)}. Assign 0 to last bit and search for 0 before last bit. 
	If 0 is found, change that to 1 and all the characters after that 1 change to 0.
	If 0 is not found, insert 1 at beginning of the string and all other elements will be changed to 0.

****************Logic********************
Number	Last Bit	Operation	Logic
Even	0		Divide by 2	remove last bit
Odd 	1		Add 1		1+1= 0(at position),1(carry)

Example:
Even: Divide by 2=remove last 0	   a. 1000/2 = 8/2 = 4(100)  b.1110/2 = 14/2 = 7(111)
Odd: Add 1.	a. 111 + 1 = 7+1 = (8)1000	b. 1101 + 1 = 13+1 = (14)1110

/////////////////Code Logic////////////////////////
Even Number: remove last 0
Odd Number:
Start from End
Step-1 Make last bit as 0
Step-2:Search 0 from before last bit
Step-3:if 0 found in Step-2.
	- Change 0 to 1.
	- Change all bits after this to 0
Step-4:if 0 not found in Step-2
	4a. add 1 at beginning of number
	4b. Change all bits after this to 0
//////////////////////////////////////////////////
		
Example: number=1110
Step	 Last-bit 	resulting-no
1	    0		 111
2	    1		 11(1+1 = 1 0)
			 1(1+1)0
			 (1+1)00
			 1000
3	    0		 100
4	    0		 10
5	    0		 1
*****************************************
*/

#include<iostream>
#include<string>
#include<cmath>
#include<chrono>
using namespace std::chrono;
using namespace std;

class Solution {
public:
	int numSteps(string s) {
        	int steps = 0, i;

	        while (s != "1"){

            		if(s == "0")
		                return ++steps;
           

            		if(s[s.size() - 1] == '0'){			//Last bit is 0, Even No
                		s.erase(s.size() - 1, 1);
		                steps++;
            		}else{					//Last bit is 1, Odd No

				//Step-1
                		s[s.size() - 1] = '0';

				//Step-2
                		for(i = s.size() - 2; i >= 0; i--)
		                    if(s[i] == '0')
                		        break;


				if(i > 0){				//Step-3
                    			s[i] = '1';			//3a
                    			for(i = i+1;i < s.size(); i++){	//3b
                        			s[i] = '0';
					}
                    			steps++;
				}else{					//Step-4
                  			s.insert(0, "1");		//4a
		                    	for(int i = 1; i < s.size(); i++){
			                        s[i] = '0';		//4b
					}
			                steps++;
                		}
            		}
        	}
        	return steps;        
    	}
};
int main(){
	Solution obj;
//	string str = "1101";
//	string str = "1000101011101101001100011010111111011111010110100001101110110100000011100100010010101110101010010110000111001011000011000000011010101011100111001001110010000011101";
//	string str = "10";
	string str = "1";
	auto startTime = high_resolution_clock::now();
	cout<<obj.numSteps(str)<<endl;
	auto stopTime = high_resolution_clock::now();
	auto diff = duration_cast<microseconds>(stopTime - startTime);
	cout<<"Time taken = "<<diff.count()<<" millisec"<<endl;
}
