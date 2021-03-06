## [Check If Array Pairs Are Divisible by k](https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/)
- Given int array and int k. Divide the array into exactly n / 2 pairs such that the sum of each pair is divisible by k.
- Return True If you can find a way to do that or False otherwise.
- Examples
```
Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
Output: true  //Pairs are (1,9),(2,8),(3,7),(4,6) and (5,10).

Input: arr = [1,2,3,4,5,6], k = 10
Output: false   //You can try all possible pairs to see that there is no way to divide arr into 3 pairs each with sum divisible by 10.
```

## Logic
- *1.* Create reminder frequency array.
     - Calculate the reminder of `ar[i]%k` and store the frequency at index.
```c++
arr={2,63,3,72,9,11,13,13}  k=5
  11 % 5 = 1                             freq[1]=1
  2 % 5 = 2, 72 % 5 =2                   freq[2]=2
  63%5=3, 3%5=3, 13%5=3, 13%5=3          freq[3]=4
  9%5=4                                  freq[4]=1
```
- *3.* Let's Understand Frequency Array.
     - **index=0** Even number present at Index=0 means There exists ***pair of numbers*** which are exactly divisible by k.
        - Example: 5,10,15,20 etc.
        - Number of pairs = freq[0]/2
     - **index=1, index=4**
        - If sum of numbers at index=1,4 is even, then pairs exist.
          - ((freq[1]+freq[4])%2 == 0) it Means exact pairs are present, no extra element. Ex: (1,4) they will give reminder as 1,4
          - pairs = (freq[1]+freq[4])/2
     - **index=2,index=3**
        - If sum of numbers at index=2,3 is even, then pairs exist.
          - ((freq[2]+freq[3])%2 == 0) it means exact pairs are present, no extra element
          - pairs = (freq[2]+freq[3])/2  

### Code
```c++
  bool canPairs(vector<int> &a, int k) {  //td = Number to divide with
        vector<int> freq(td,0);

        for(auto i:v)
            freq[(i%td + td) % td]++;

        if(freq[0] % 2 !=0)
            return 0;

        for(int i=1; i<td; i++){
            if(freq[i] != freq[td-i])
                return 0;
        }
        return 1;
}
int main() {
  int k =5;
  vector<int> v = {2,63,3,72,9,11,13,13};   //ok
  cout<<canPairs(v, k)<<endl;
}  
```
