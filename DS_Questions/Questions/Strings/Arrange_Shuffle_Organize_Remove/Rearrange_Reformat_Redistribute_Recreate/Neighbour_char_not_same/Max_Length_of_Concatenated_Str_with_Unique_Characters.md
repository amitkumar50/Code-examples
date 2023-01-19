**Maximum Length of a Concatenated String with Unique Characters**
- [Approach-1. Using vector](#a1)

### [1239. Maximum Length of a Concatenated String with Unique Characters](https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/description/)
- You are given an array of strings arr. A string s is formed by the concatenation of a subsequence of arr that has unique characters.
- Return the maximum possible length of s.
- A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
- **Condition1:** skip all strings having repetative characters
```c
Example 1:
Input: arr = ["un","iq","ue"]
Output: 4
Explanation: All the valid concatenations are:
- ""
- "un"
- "iq"
- "ue"
- "uniq" ("un" + "iq")
- "ique" ("iq" + "ue")
Maximum length is 4.

Example 2:
Input: arr=["aa", "bc"]
Output: 2
Explanation: skip "aa" string since it has repetative characters
```

<a name=a1></a>
### Approach-1. Using vector
#### Logic
- _1._ Take a vector in which we will note all valid combinations
- _2._ Create word which need to be placed into vector by combining input word and string.
- _3._ Check does the created word have any repetative characters?
```c
  uniq  //No repetative character
  unue  //Have repetative character "u"
```
#### Complexity
- **Time:** 
- **Space:**
#### Code
```cpp
class Solution {
public:
                  //["un","iq","ue"]
    int maxLength(vector<string>& arr) {
    
        // 1. Vector in which we will note all valid combinations
        // {"uniq", "ique"]
        vector<string> output = {""};
		
        int maxLen = 0;
        for (string word : arr) {
		
            for (int i = 0; i < output.size(); i++) {
			
              // 2. Create a string by combining out vector
              // and input word
              // temp = "uniq", "unue"
                string temp = output[i] + word;
				
              // 3. Find repetative characters,
              //  a. Insert word into set "unue"=>"une"
              //  b. if input word size != us.size "unue"!="une"
              //		No need to consider, continue
                unordered_set<char> us(temp.begin(), temp.end());
                if (temp.size() != us.size())
                    continue;

                // if combined string is valid, "uniq"
                // insert into output vector and record
                // max len
                output.push_back(temp);
                maxLen = max(maxLen, (int)temp.size());
            }
        }
        return maxLen;
    }
};
```