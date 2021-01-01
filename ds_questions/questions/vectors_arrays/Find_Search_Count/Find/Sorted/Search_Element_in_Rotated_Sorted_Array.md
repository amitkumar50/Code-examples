### [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
- Array is rotated at some point [0,1,2,4,5,6,7] becomes [4,5,6,7,0,1,2]
- If target is found in the array return its index, otherwise, return -1.
- Examples
```c++
Input: nums = [4,5,6,7,0,1,2], target = 1
Output: 5   //Index of element 5

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
```

### Approach-1 //2 times Binary Search
- *1.* Find point of rotation ie `arr[mid+1]<arr[mid]` using Binary Search. This divides the array into 2 halves.
- *2.* Search target element in two sub-arrays(Again using Binary Search)
- **Complexity**
  - **Time:** 2O(logn)
  - **Space:** O(1)
### Code-Approach-1
```c++
class Solution {
public:
    using vec = vector<int>;
    
  int BinarySearch (vec& v, int start, int end, int ele){
    int mid = (start+end)/2;

    if (start > end)
      return -1;

    if (v[mid] == ele)
      return mid;

    if (mid == v.size()-1)
      return -1;

    if(ele < v[mid])
      mid = BinarySearch(v,start,mid-1,ele);
    else
      mid = BinarySearch(v,mid+1,end,ele);

    return mid;
  }
  
//Rotation Point
  int FindPivot(vec& v, int start, int end){
    if (start > end)
      return -1;
    
    if (start == end)
      return start;

    int mid = (start+end)/2;

  /*Case-1: We found pivot element
  9  10  1
     mid
  */
    if (mid < end and v[mid+1] < v[mid])
      return mid;

  /*Case-2: We found Pivot element
  9  10  1
        mid
  */        
    if (mid > start and v[mid-1] > v[mid])
      return mid - 1;

  /*9  10  1  2  3
             mid
  Search in left half
  */
    if (v[start] >= v[mid])
      return FindPivot(v, start, mid - 1);

    //Search in right half
    return FindPivot(v, mid+1, end);
  }
    
  int search(vector<int>& v, int target) {
    int end = v.size() - 1;
    int start = 0, mid = -1;
    
    int pivot = FindPivot(v, start, end);

    if (pivot == -1) 
        return BinarySearch(v, start, end, target); 
  
    // If we found a pivot, then first compare with pivot 
    // and then search in two subarrays around pivot 
    if (v[pivot] == target) 
        return pivot; 
  
    if (v[0] <= target) 
        return BinarySearch(v, start, pivot - 1, target); 
  
    return BinarySearch(v, pivot + 1, end, target);    
    }
};
```
  
### Approach-2  //1 pass Binary Search
- *1.* Left subarray is sorted. `v[mid] >= v[start]`
  - *1a.* Element lies in left subarray
```c  
if (v[mid] >= ele and ele >= v[start])
  - Search in left subarray
else
  - Search in right array
```  
  - *1b.* Element lies in right sub array 
```c  
if (ele >= v[mid] and ele <= v[end])
  - Search in right subarray
else
  - Search in left array
```  
- **Complexity**
  - **Time:** O(nlogn)
  - **Space:** O(1)

### Code-2
```c++
#include<iostream>
#include<vector>
using vec = std::vector<int>;

int BinarySearch (vec& v, int start, int end, int ele){
  int mid = (start+end)/2;

  if (start > end)
    return -1;

  if (v[mid] == ele)
    return mid;

  if(v[mid] >= v[start]){                     //1

    if (ele >= v[start] and ele <= v[mid])    //1a
       mid = BinarySearch(v,start,mid-1,ele);

    return BinarySearch(v,mid+1,end,ele);
  }

  if (ele >= v[mid] and ele <= v[end])          //1b
    return BinarySearch(v, mid+1, end, ele);

  return BinarySearch(v, start, end-1, ele);
}

int search(vec& v, int target){
  int end = v.size() - 1;
  int start = 0, mid = -1;

  return BinarySearch(v, start, end, target);
}
```
