### [Find Kth Bit in Nth Binary String](https://leetcode.com/contest/weekly-contest-201/problems/find-kth-bit-in-nth-binary-string/)
- Read problem on LC. Given two positive integers n and k, the binary string  Sn is formed as follows:
  - S1 = "0"
  - i = Si-1 + "1" + reverse(invert(Si-1)) for i > 1
- Where + denotes the concatenation operation, reverse(x) returns the reversed string x, and invert(x) inverts all the bits in x (0 changes to 1 and 1 changes to 0).

For example, the first 4 strings in the above sequence are:
```
S1 = "0"
S2 = "011"
S3 = "0111001"
S4 = "011100110110001"
```

### Logic
- We need to create a string based on value of n. Let n=4
- Take string s
- Push 0,1 at end of string s="01"
  - Steps(Loop from n=1 to 3)
    - Take substring from j=0 to j=i-1
    - Inverse bits of this substring
    - Reverse substring
    - Insert 1 at end, if i < n-1
```c++
  char findKthBit(int n, int k) {
    //Create n positioned string
    string s;

    s.push_back('0');
    s.push_back('1');

    for(int i=1;i<n;i++){
      string s1 = s.substr(0,s.size()-1);
      //cout<<"i="<<i<<", s1="<<s1<<endl;
      //cout<<"s1.size()="<<s1.size()<<endl;
      //inverse, reverse
      for(int j=0;j<s1.size();j++){
        //cout<<"Loop s1["<<j<<"]="<<s1[j]<<endl;
        if(s1[j] == '0'){
          //cout<<"Change to 1"<<endl;
          s1[j]='1';
        }else{
          //cout<<"Change to 0"<<endl;
          s1[j]='0';
        }
      }
      //cout<<"Inversed s1="<<s1<<endl;
      reverse(s1.begin(),s1.end());
      //cout<<"Reversed s1="<<s1<<endl;

      s.append(s1);
      if(i!=n-1)
        s.push_back('1');

      //cout<<"s="<<s<<endl;
    }
    //cout<<"string="<<s<<endl;
    return(s[k-1]);
  }
int main(){
  Solution s;
  //cout<<s.findKthBit(4,11);
  //cout<<s.findKthBit(1,1);
  //cout<<s.findKthBit(2,3);
  cout<<s.findKthBit(3,1);
}
```        
