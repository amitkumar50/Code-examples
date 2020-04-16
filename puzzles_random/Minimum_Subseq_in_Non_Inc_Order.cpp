/*      Minimum_subseq_in_Non_inc_order.cpp     

https://leetcode.com/contest/weekly-contest-183/problems/minimum-subsequence-in-non-increasing-order/

Question: Given array nums, obtain a subsequence of the array whose sum of elements is strictly greater than the sum of the non included elements in such subsequence. 

If there are multiple solutions, return the subsequence with minimum size and if there still exist multiple solutions, return the subsequence with the maximum total sum of all its elements. A subsequence of an array can be obtained by erasing some (possibly zero) elements from the array. 

Note that the solution with the given constraints is guaranteed to be unique. Also return the answer sorted in non-increasing order.

Example-1:
Input: nums = [4,3,10,9,8]
Output: [10,9]
Explanation: The subsequences [10,9] and [10,8] are minimal such that the sum of their elements is strictly greater than the sum of elements not included, however, the subsequence [10,9] has the maximum total sum of its elements.

Example-2:
Input: nums = [4,4,7,6,7]
Output: [7,7,6]
Explanation: The subsequence [7,7] has the sum of its elements equal to 14 which is not strictly greater than the sum of elements not included (14 = 4 + 4 + 6). Therefore, the subsequence [7,6,7] is the minimal satisfying the conditions. Note the subsequence has to returned in non-decreasing order.

Example-3:
Input: nums = [6]
Output: [6]

*************Logic*************
Step-1: sort 10,9,8,4,3
Step-2: find sum = 34           //O(n)
Step-3:
 array  10 9 8 4 3
 index  0  1 2 3 4

 i  sum-from-start(sfs)   sum-from-end(sfe)
      
 0    10                  9+8+4+3 = 34 - 10 = 24
 1    10+9=19             8+4+3   = 24 - 9  = 15
 2    10+9+8=27           4+3     = 15 - 8  = 7
 Break when sof>=soe. This will break at 19
*******************************     
*/
#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
        vector<int> minSubsequence(vector<int>& nums) {
                vector<int> v;
                int s1=0, sfs=0,sfe=0;

                sort(nums.begin(), nums.end(), greater<int>());

                for(auto i:nums){
                        s1 += i;
                }

                sfe = s1;

                for(auto i:nums){
                        if(sfe>=sfs){
                                sfs = sfs + i;
                                sfe = sfe - i;
                                v.push_back(i);
                        }
                        if(sfe<sfs)
                                break;
                }
                return v;
        }
};

int main(){
        Solution s;
        vector<int> nums = {4,3,10,9,8};      //Output: 10,9
//      vector<int> nums = {4,4,7,6,7};       //Output: 7,7,6
//      vector<int> nums = {6};               //Output: 6
        vector<int> v = s.minSubsequence(nums);
        for(auto i:v){
                cout<<i<<" ";
        }
}
