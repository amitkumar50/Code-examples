## Bloom Filter
- **What?** BF is a bit array.
- **[Operations](Operations_Insert_Delete_Union):** Insert, search element, Union of 2 Bloom Filters
  - _1. Insert Element:_ Provide element to hash Function, get array index place 1.
  - _2. Search Element:_ Provide element to hash function, get index. _ELEMENT CAN BE AT INDEX._
```c
Bit array:  0 1 0 0 1 0 1 ... 1
Index:      0 1 2 3 4 5 6     n-1
  
Insert(x).   x ->|Hash Function|-> 3(array index)
BF:               1
```
- **Terms**
  - _1. [False Positive](False_Positive):_ A test result wrongly indicating particular condition is set/present.
  - _2. False Negative:_ A test result wrongly indicating particular condition is absent.
- **[Characteristics/Properties of BF](Characteristics_of_BF)**
- **[Implementations](Implementations)**
  - Google Guava library uses Murmur hash algorithm.
  - Compressed Bloom Filter
  - 
