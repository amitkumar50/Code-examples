**Minimum Time Difference**
- [Approach-1. O(nlogn)](#a1)
  - [Logic](#l)
  - [Complexity](#c)
  - Code
    - [CPP](#cpp)
    - [Rust](#r)

### Minimum Time Difference
- Given a list of 24-hour clock time points in "HH:MM" format, return the minimum minutes difference between any two time-points in the list.
```c
Example 1:
Input: timePoints = ["23:59","00:00"]
Output: 1

Example 2:
Input: timePoints = ["00:00","23:59","00:00"]
Output: 0
```

<a name=a1></a>
### Approach-1. Sort (nlogn)
<a name=l></a>
#### Logic
- _1._ Convert all times to seconds and store in vector and sort.
```c
time:       00:00     01:01       23:59
converted:  0       1*60+1=61     23*60+59=1439

vector<int> = 0, 61, 1439
```
- _2._ Now `1439-0 = 1`, that means when we reach end=1439 we should go back to 0. To ease calculation, push_back `min + 24*60`.
```c
vector<int> =  61, 1439, 1440=0+24*60
```
- _3._ if 2 values are same, return 0
- _4._ Calculate difference of vector elements ie (`v[i+1] - v[i]`)

<a name=c></a>
#### Complexity
- **Time:** O(nlogn)
- **Space:** O(2n) = O(n)

#### Code
<a name=cpp></a>
**CPP**
```cpp
class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        vector<int> v;
        unordered_set<int> us;

        for (auto&i : timePoints){
            // Convert to int and store in vector
            int a = convert(i);
            v.push_back(a);

            // if 2 values are same, just return 0
            auto it = us.find(a);
            if (it != us.end())
                return 0;
            us.insert(a);
        }

        auto it = v.begin();
        sort(v.begin(), v.end());
        int out = v[1] - v[0];

        // Push 1st element at end of vector
        v.push_back(*it + 24*60);

        // Calculate v[i]-v[i+1] from index=1
        for (auto i=1; i<v.size()-1; ++i) {
            int diff = abs(v[i] - v[i+1]);
            out = min(out, diff);
        }
        return out;
    }

    // Helper function to convert string to int
    int convert(string t){
        int hrs = stoi(t.substr(0,1))*10 + stoi(t.substr(1,1));
        int sec = stoi(t.substr(3,1))*10 + stoi(t.substr(4,1));
        return hrs*60 + sec;
    }
};
```

**Rust**
```rs
use std::{collections::HashSet};
impl Solution {
    pub fn find_min_difference(time_points: Vec<String>) -> i32 {
        let mut v:Vec<i32> = Vec::new();
        let mut hs:HashSet<i32> = HashSet::new();
        let mut out = std::i32::MAX;
        loop{
            // Store time into vector
            for i in time_points {
                let val = match Self::convert(i) {
                    Ok(v) => v,
                    Err(e) => {
                        println!("{}", e);
                        break;
                    }
                };
                v.push(val);

                // if any duplicate entry in HashSet return 0
                let hs_value =  hs.get(&val);
                if hs_value.is_some() {
                    return 0;
                } else {
                    hs.insert(val);
                }
            }

            // Sort the vector
            v.sort();

            out = v[1] - v[0];

            // Insert 0th element to last in vector
            v.push(v[0]+24*60);

            // Iterate through vector from 1st element and find v[i+1]-v[i]
            for i in 1..v.len()-1 {
                let diff = v[i +1] - v[i];
                out = std::cmp::min(out, diff);
            }
            break;
        }
        out
    }
    pub fn convert(i:String) -> Result<i32,String> {
        let result;
        loop {
            let hrs = Self::substr(&i, 0, 2);
            let h = match hrs.parse::<i32>(){
                Ok(h)=>h,
                Err(e) => {
                    let err = format!("Failed to parse h: {}", e);
                    result = Err(err);
                    break;
                },
            };
            let sec = Self::substr(&i, 3, 2);
            let s = match sec.parse::<i32>(){
                Ok(h)=>h,
                Err(e) => {
                    let err = format!("Failed to parse s: {}", e);
                    result = Err(err);
                    break;
                },
            };
            result = Ok(h*60+s);
            break;
        }
        result
    }
    fn substr(s: &str, start: usize, length: usize) -> &str {
        let end = start + length;
        &s[start..end]
    }
}
```
