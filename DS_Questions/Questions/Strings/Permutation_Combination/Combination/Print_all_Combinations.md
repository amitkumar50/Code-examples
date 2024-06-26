## Question
- Find all combinations of given string.
- Formula: 
  - <sup>n</sup>C<sub>r</sub> = n!/r!(n-r)!     //Combination of n things, taken r at a time.
  - <sup>4</sup>C<sub>1</sub> = 4!/1!(3)!  = 4  //Combination of 4 things, taken 1 at a time.
  - <sup>4</sup>C<sub>2</sub> = 4!/2!(2)!  = 6  //Combination of 4 things, taken 2 at a time.
  - <sup>4</sup>C<sub>3</sub> = 4!/3!(1)!  = 4  //Combination of 4 things, taken 3 at a time.
  - <sup>4</sup>C<sub>4</sub> = 4!/4!(0)!  = 1  //Combination of 4 things, taken 4 at a time.
```c
Input = abcd  //Total = 15
Output:
a     //Taken 1 at time
b
c
d

//Taken 2 at a time.
ab    //Fixing a
ac
ad
bc    //Fixing b
bd
cd    //Fixing c

//Taken 3 at a time
abc   //Fixing ab
abd
bcd   //Fix bc
acd   //Fix cd

abcd  //Taken 4 a time
```

## Logic
- _1._ Keep characters from last in output string and dump the output.

## Code
```c
string strInput = "abcd";

void combine(string& outstr, int index) {
	for (int i = index; i < strInput.length(); i++) {
		outstr += strInput[i];
		cout << outstr<<"\n";
		combine(outstr, i + 1);
		outstr.erase(outstr.length() - 1,1);		//erase(length, position)
	}
}
int main() {
	string out;
	combine(out, 0);
	return 0;
}
$ ./a.out
a
ab
abc
abcd
abd
ac
acd
ad
b
bc
bcd
bd
c
cd
d
```
