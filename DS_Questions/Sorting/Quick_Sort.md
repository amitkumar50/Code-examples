**Quick Sort / Divide and conquer algo**
- [Approach](#a)
- [Logic](#l)
- [Complexity](#c)
- [Code](#cpp)


[if confused](https://www.youtube.com/watch?v=QN9hnmAgmOc)

<a name=a></a>
### Approach(Very Simple)
```c
  6   7   8   9   1   5
start                end
```
- *1.* Any random element is selected as Pivot. Eg: pivot=`a[0]=6`
- *2.* Find the final place(index=2) of pivot in the array. Final place will be the position which it will have in sorted array. `1 5 6 7 8 9`

<a name=l></a>
### Logic
```c
  Iterate Until(start < end)
    if(element_at_start <= pivot){ 
      it ok. Because on left of pivot elements should be smaller.
      start++
    }else
      stop

    if(element_at_end > pivot){
      it ok. Because on right of pivot elements should be greater.
      end--
    }else
      stop
 
    we found elements where element_at_start>pivot & element_at_end<pivot.
    if(start < end)
      Swap end and start elements
}
Now end crossed start, swap element_pointed_by_pivot with end_element.

Recursively do this for left and right sub-arrays.
```

<a name=c></a>
### Complexity
- **Time:**
  - Worst: O(n<sup>2</sup>).
    - When input array is sorted or reverse sorted. this makes picked pivot as always extreme(smallest or largest) element.
  - Avg: O(nlogn)
  - Best: O(n)
- **Space:** O(1)

<a name=cpp></a>
### Code
```cpp
int partition(vector<int>& v, int start, int end) {  
    int pivot = v[end];   //or int pivot = v[left + (right - left) / 2];
    int i = start, j = end;
    while(i <= j) {
        while(v[i] < pivot)
            i++;
        while(v[j] > pivot)
            j--;
        if(i <= j)
          swap(v[i++], v[j--]);
    }
    return i;
}

void qs(vector<int>& v, int start, int end){
  if (start < end){
    int pivotIndex = partition(v, start, end);

    qs(v, start, pivotIndex - 1);
    qs(v, pivotIndex, end);
  }
}

int main(){
  vector<int> v = {6, 7, 8, 9, 1, 5};
  qs(v, 0, v.size()-1);

    cout << "Sorted array is: \n";
    for (auto i:v)
        cout << i << " ";
}
```
