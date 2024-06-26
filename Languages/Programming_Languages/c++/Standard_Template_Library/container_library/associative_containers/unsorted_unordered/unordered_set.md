**unordered_set`<key>`**
  - Create
    - [Set of pairs](#sp)
  - Find
    - [const_iterator find(key)](#find)
    - [random key with same probability in O(1)](/DS_Questions/Questions/Random/Implement_Class/RandomisedSet_Insert_Delete_GetRandom_in_O1.md)
  - Remove Delete
  - [Count](#count1)

## [HTML Function Compared C++,Rust,Python](https://amitkumar50.github.io/Languages/Programming/C++/STL/Containers/Associative_Containers/Unsorted_Unordered/unordered_set.html)

### unordered_set`<key>`
Keys are stored in HashMap, hence unordered not in ascending,descending order.
## Create
<a name=sp></a>
#### Set of Pair
We cannot create `unordered_set<pair<int,int>>` Why?
  - By default, it uses std::hash but there is no specialization of std::hash for std::pair<T1,T2> provided in the standard library.
  - Solution: Provide own hash [functor](/Languages/Programming_Languages/c++/Characteristics_of_OOPS/Polymorphism/Static_CompileTime/Operator_Overloading/Functor).
```cpp
struct SimpleHash {
    size_t operator()(const std::pair<int, int>& p) const {
        return p.first ^ p.second;
    }
};

std::unordered_set<std::pair<int, int>, SimpleHash> S;
S.insert(std::make_pair(0, 1));
```

## Find
<a name=find></a>
#### const_iterator find(key)
- Searches the container for an element with k as value and returns an iterator to it if found, else returns iterator to unordered_set::end (element past end of container).
```cpp
  unordered_set<int> us = { 1,2,4 };
  unordered_set<int>::const_iterator it = myset.find (2);
  if ( it == myset.end() )
    cout << "not found";
  else
    cout << "Found";
```




<a name=mapmap></a>
#### Map of Maps
```cpp
    using map1 = unordered_map<uint32_t, uint32_t>;
    using map2 = unordered_map <string, map1>;
    map2 um;
    map1 temp = { { 1,2 } };
    um[A] = temp;    
```
