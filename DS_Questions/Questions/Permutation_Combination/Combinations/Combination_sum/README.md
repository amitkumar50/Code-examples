**Combination sum**
- [Approach-1, Backtracking](#bt)

### [39. Combination Sum](https://leetcode.com/problems/combination-sum/description/)
- Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
- The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
- The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.
```c
Example 1:
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.

Example 2:
Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]
```

<a name=bt></a>
### Approach-1, Backtracking
#### Logic. [Backtracking Template](/DS_Questions/Algorithms/Backtracking/)
- _1._ Whenever question is (combination, permutations, suduko, N queen) it's BT problem
- _2._ In BT we create candidate vector, start placing items on candidate vector, if condition is satified place in output set and remove last insert element into candidate vector
- _3._ Start with empty vector cand. And call recursive_backtrack() function.
- _4._ Base cases: if `sum of elements in vector > target || sum of elements in vector == target`
- _5._ We need to consider same element it `2 2 2 2` is valid combination hence while calling rb() pass present element again ie i is not incremented to i+1

<img src=combination_sum_bt_graph.jpg width=700/>

#### Code
```cpp
using vecVecI = vector<vector<int>>;
using vecI = vector<int>;
class Solution {
    vecVecI out;
public:
    void rb(vecI& nums, vecI& cand, int target, int index, int sum){

        /// Base Cases
        if (sum > target)
            return;
        if (sum == target) {
            out.push_back(cand);
            return;
        }

        /// Check all candidates
        for (int i=index; i<nums.size(); ++i) {
            
            /// Push element on candidate
            cand.push_back(nums[i]);

            /// Note: We donot go to next element (i+1)
            /// Count this element repetedely again
            rb (nums, cand, target, i, sum+nums[i]);

            /// Remove nums[i] from candidate
            cand.pop_back();
        }
    }
    vecVecI combinationSum(vecI& nums, int target) {
    
        /// Create Empty Candidate list
        vecI cand;
        int start_index = 0;      //Start from 1st element index=0
        int sum = 0;
        
        rb (nums, cand, target, start_index, sum);
        return out;
    }
};
```
#### Complexity
- **Time:** 
- **Space:** O(n). `vector<int> cand` can contain max n elements at any point of time
