## 1. Reverse/Toggle all bits
- [PrintBinary()](/Languages/Programming_Languages/C/Bitwise/Print_Binary_Representation.md)
```c
void ToggleReverseAll(int a){
  a = ~a;
  PrintBinary(a);
}
```

## 2. Toggle nth bit
> Input a = 1 = 1000000000000000000000000000000, n=3
- **Logic**
  - *1.* Create a number `b` by shifting 1 to nth place.
  - *2.* XOR `^` b and a. same bit=0, diff=1
```c
Eg:
Step-1:  b=00100000000000000000000000000000
Step-2:   a = 10000000000000000000000000000000
        ^ b = 00100000000000000000000000000000
        --------------------------------------
              1010000000000000000000000000000 //See 3rd bit toggled.
```              
- **Code**  
```c
void Toggle_nth_Bit(int a, int n){
  int b = 1;
  b <<= n-1;
  a = a ^ b;
  PrintBinary(a);
}
```

## 3. Toggle nth to mth bit(Both inclusive)
- **Logic**
  - Let's suppose input number=4 and we need to toggle 2nd to 5th bit(both inclusive)
```c
Input a = 4 = 00100000000000000000000000000000, n=2,m=5.
Output: 0 1 0 1 1 0 0 0 000000000000000000000000    //2nd to 5th bit toggled
        1 2 3 4 5 6
```
  - *1.* Create a number with all bits on from n to mth position.
```c
  b = 01111000000000000000000000000000
```
  - *2.* XOR the number with original number.
- **Code**
```c
void ToggleFrom_n_to_m(int a, int n, int m){
  int b=1, i=1, c=0;
  
  b <<= n-1;              //1
  c = b;
  while(i++<m-n){
    c <<= 1;
    b |= c;
  }
   
  a ^= b;                 //2
  PrintBinary(a);
}
```
