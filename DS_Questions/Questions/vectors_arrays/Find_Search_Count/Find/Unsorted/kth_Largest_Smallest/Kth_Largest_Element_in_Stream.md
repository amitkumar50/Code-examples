**Kth Largest Element in a Stream**
- [Approach-1. Min Heap](#a1)
  - [Logic](#l)
  - [Complexity](#c)
  - Code
    - [CPP](#cpp)
    - [Rust](#rs)

### [703. Kth Largest Element in a Stream](https://leetcode.com/problems/kth-largest-element-in-a-stream/description/)
- Design a class to find the kth largest element in a stream. Note that it is the kth largest element in the sorted order, not the kth distinct element.
- Implement KthLargest class:
  - `KthLargest(int k, int[] nums)` Initializes the object with the integer k and the stream of integers nums.
  - `int add(int val)` Appends the integer val to the stream and returns the element representing the kth largest element in the stream.
 ```c
Example 1:
Input
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
Output
[null, 4, 5, 5, 8, 8]
Explanation
KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3);   // return 4
kthLargest.add(5);   // return 5
kthLargest.add(10);  // return 5
kthLargest.add(9);   // return 8
kthLargest.add(4);   // return 8
```

<a name=a1></a>
### Approach-1. Min Heap
<a name=l></a>
#### Logic
- Add element in minHeap, Remove all elements until sizeof minHeap != k

<a name=com></a>
#### Complexity
- O(1)

#### Code
<a name=cpp></a>
**CPP**
```cpp
class KthLargest {
    //min Heap
    priority_queue<int,vector<int>, greater<int>> pq;
    int Size;
public:
    KthLargest(int k, vector<int>& nums) {
        Size = k;
        // Insert all numbers to minHeap
        for (auto&i:nums)
            pq.push(i);
        
        // Empty minHeap until size != k
        while (pq.size() && pq.size() > k)
            pq.pop();
    }
    
    int add(int val) {
        pq.push(val);
        while (pq.size() &&  pq.size() > Size)
            pq.pop();
        return pq.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
```
<a name=rs></a>
**Rust**
```rs
use std::collections::BinaryHeap;
use std::cmp::Reverse;

struct KthLargest {
    size: usize,
    min_heap: BinaryHeap<Reverse<i32>>,
}


/** 
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl KthLargest {

    fn new(k: i32, nums: Vec<i32>) -> Self {
        let mut mh: BinaryHeap<Reverse<i32>> = BinaryHeap::new();
        for i in nums {
            mh.push(Reverse(i));
        }
        KthLargest {
            min_heap: mh,
            size: k as usize,
        }
    }
    
    fn add(&mut self, val: i32) -> i32 {
        self.min_heap.push(Reverse(val));
        while self.min_heap.len() > self.size {
            self.min_heap.pop();
        }
        self.min_heap.peek().unwrap().0
    }
}

/**
 * Your KthLargest object will be instantiated and called as such:
 * let obj = KthLargest::new(k, nums);
 * let ret_1: i32 = obj.add(val);
 */
```
