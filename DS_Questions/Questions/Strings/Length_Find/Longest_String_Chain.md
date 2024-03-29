## [Longest String Chain](https://leetcode.com/problems/longest-string-chain/)
- Given a list of words consisting of English lowercase letters.
- We say word1 is a predecessor of word2 if and only if we can add exactly one letter anywhere in word1 to make it equal to word2. Example
  - word1="abc" is a predecessor of word2="abac".
- A word chain is a sequence of words `[word_1, word_2, ..., word_k]` with k >= 1, where word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and so on.
- Return the longest possible length of a word chain with words chosen from the given list of words.
- **Examples**
 ```console
Input: words = ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: One of the longest word chain is "a","ba","bda","bdca".

Example 2:
Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
Output: 5
```

### Approach-1    //[Graph DFS](/DS_Questions/Algorithms/Traversals), Recursion, Memoization(using unordered_map), 27% Faster
- **Logic**
  - Create a graph where each node differs from its neighbour by 1 character.
  - From each node, find its neighbour by removing each character and checking whether word exists or not.
```console
Input = {"a","b","ba","bca","bda","bdca", "dca"}
       bdca ---- dca 
       /   \
     bda   bca        
        \  / 
         ba
        / \    
       b   a 
//Finding next connected node to bdca.
1. Remove b. dca. Yes exist. Perform DFS on it
2. Remove d. bca. Yes exist. Perform DFS on it
3. Remove c. bda. Yes exist. Perform DFS on it
4. Remove a. bdc. Does not exist move to next word

//Length of longest chain = 4
  bdca -> bda -> ba -> b      OR
  bdca -> bda -> ba -> a      OR
  bdca -> bca -> ba -> a      OR
  bdca -> bca -> ba -> b
```
- **Complexity**
  - **Time:** O(NL<sup>2</sup>) = O(N + NL<sup>2</sup>)
    - N=number of words, L=length of longest word
    - O(N): We create a `unordered_set<string>` of words for fast searching.
    - O(N): Iterate thru each word to find neighbour
    - O(L): Find next connected word for each word
  - **Space:** O(N) ie creating unordered_set of words
- **Code**
   - *Step-1.* Create `unordered_set<string>` and insert all words into it for fast access in O(1) time.
   - *Step-2.* Perform DFS on words.
   - *Step-3.* Create a subWord from word. Example: word = "xbc". subWords: bc, xc, xb. 
     - Search subWord in unordered_set, if subWord is found, take word=subWord and perform DFS on subWord.
     - Note maxLength variable when subWord is found.
  - *Step-4.* `unordered_map<string=word, int=count>` stores longest string chain with present word as end.
   - Advantage: When we 1st find a word `ba` we will store the value 2 for key=ba. The next time we encounter ba, we will simply return the value stored against it in the map instead of going through the entire subtree again. //This is called **MEMOIZATION**
```console
  key=string   value=length_of_string_chain
   a             1
   b             1
   ba            2      ba ----- b
                         |------ a
                         
   bca           3      bca ------ ba -------- b   //Since ba,b,a are present in words
                                    |--------- a
                                    
   bda           3      bca ------ ba -------- b
                                    |--------- a
```
  - *Step-5.* DFS() returns 1 when any of subWord is not found in word, else returns number of words traversed.
  - *Step-6.* if word is found inunordered_map, Return count of this word(ie longest possible string chain length) of this word.
```c++
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
#include<unordered_map>
using namespace std;
using vec = vector<string>;
using US = unordered_set<string>;

//This map will store the length of the longest possible word sequence where the key is the last word in the sequence.
                      //word, length_of_longest_possible_word_sequence_ending_at_word
using UM = unordered_map<string, int>;

class Solution {
    UM um;
    US usWords;
private:

  int DFS(string word) {
  
    if (um.find(word) != um.end())                             //Step-6
      return um[word];      
    int maxLength = 1;  
    
    for (int i = 0; i < word.length(); ++i) {                  //Step-3
      string subWord = word.substr(0, i) + word.substr(i + 1);

      if (usWords.find(subWord) != usWords.end()) {           //subWord found in unordered_set
        int len = 1 + DFS(subWord);
        maxLength = max(maxLength, len);
      }
    }
    um[word] = maxLength;                                   //Step-4
    return maxLength;                                       //Step-5
  }
  
public :
  int longestStrChain(vec &words) {
    for (const auto &i : words)           //Step-1
      usWords.insert(i);
    int iOut = 0;
    
    for (const auto &i : words)          //Step-2
      iOut = max(iOut, DFS(i));

    return iOut;
  }
};

int main(){
  vec v = {"xbc","pcxbcf","xb","cxbc","pcxbc"};
  Solution s;
  cout<<s.longestStrChain(v);
}
```

## Approach-2   //Sort, Bottom up Dynamic Programming. 85% Faster
- **Logic**
  - *1.* Delete 1 letter from each word and create a subWord to be searched in map.
  - *2.* Find that word in map, if word is present, increase value in unordered_map by 1.
- **Code**
```console
  input = bdca bda bca ba b a
```
  - *1.* Sort in sequence in ascending order of length. `b a ba bda bca bdca`
  - *2.* Take `unordered_map<key=string, value=length of word seq with key as last word>`.
  - *3.* Iterate thru each word, find this word's predecessor by deleting 1 letter at a time.
    - value=1, if no predecessor present. Update unordered_map
    - value=(precedecessor's value+1), if predecessor is present. Update unordered_map
```console
word=b      //Finding predecessor of word=b               unordered_map
  subWord:0                                               key     value
  No predecessor                                           b        1
  
word=a
  subWord:0
  No predecessor                                           a        1  
  
word=ba
  (subWord: b)Search b in unordered_map. Found.            ba        2
  (subWord: a)Search a in unordered_map. Found.            ba        2

word=bda
  (subWord: da)Search da in unordered_map. Not Found.
  (subWord: ba)Search ba in unordered_map. Found.          bda        3
  (subWord: bd)Search ba in unordered_map. Not Found.

word=bca
  (subWord: ca)Search ca in unordered_map. Not Found.
  (subWord: ba)Search ba in unordered_map. Found.          bca        3
  (subWord: bc)Search bc in unordered_map. Not Found.

word=bdca
  (subWord: dca)Search dca in unordered_map. Not Found.
  (subWord: bca)Search bca in unordered_map. Found.        bdca       4
  (subWord: bda)Search bda in unordered_map. Not Found.
  (subWord: bdc)Search bdc in unordered_map. Not Found.

Longest String Chain length = 4
```
  - **C++ Code**
```c++
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
#include<unordered_map>
using namespace std;
using vec = vector<string>;

                        //key=word,value=length of word seq with key as last word
using UM = unordered_map<string, int>;

class Solution {
    UM umDP;
public :
  int longestStrChain(vec &words) {

    //Input:bdca bda bca ba b a        Output:b a ba bda bca bdca
    sort(words.begin(), words.end(),
          [](const string& a, const string& b){
            return a.size() < b.size();
          }
        );
    int iOut = 1;

    for (const auto &i : words) {
      int presentLength = 1;
      
      for (int j = 0; j < i.size(); j++) {
        string subWord = i.substr(0,j) + i.substr(j+1, i.length() + 1);

        if (umDP.find(subWord) != umDP.end()) {
          int previousLength = umDP[subWord];
          presentLength = max(presentLength, previousLength + 1);
        }
      }
      umDP[i] = presentLength;
      iOut = max(iOut, presentLength);
    }
    return iOut;
  }
};

int main(){
  vec v = {"bdca","bda","bca","ba","b","a"};
}  
```
