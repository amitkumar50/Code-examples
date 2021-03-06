## Problem
- 2 CSV files are provided. The first file contains statistics about various dinosaurs. The second file contains additional data.
- Write a program to read in the data from files, Print the names of only the bipedal dinosaurs from fastest to slowest. Do not print any other information.
```c
speed = ((STRIDE_LENGTH / LEG_LENGTH) - 1) * SQRT(LEG_LENGTH * g)
Where g = 9.8 m/s^2 (gravitational constant)

$ cat dataset1.csv
NAME,LEG_LENGTH,DIET
Hadrosaurus,1.4,herbivore
Struthiomimus,0.72,omnivore
Velociraptor,1.8,carnivore
Triceratops,0.47,herbivore
Euoplocephalus,2.6,herbivore
Stegosaurus,1.50,herbivore
Tyrannosaurus Rex,6.5,carnivore

$ cat dataset2.csv
NAME,STRIDE_LENGTH,STANCE
Euoplocephalus,1.97,quadrupedal
Stegosaurus,1.70,quadrupedal
Tyrannosaurus Rex,4.76,bipedal
Hadrosaurus,1.3,bipedal
Deinonychus,1.11,bipedal
Struthiomimus,1.24,bipedal
Velociraptorr,2.62,bipedal

[Output]
Struthiomimus,1.91845
Velociraptorr,1.91333
Stegosaurus,0.511208
Hadrosaurus,-0.264575
Euoplocephalus,-1.22311
Tyrannosaurus Rex,-2.13651
```
### Logic
- *1.* Read dataset2.csv and store in `unordered_map <key=Name, Value=strideLength>`, so that we can search name in O(1) time.
- *2.* Read Name,leg_length from dataset1.csv. 
  - Search strideLength for Name from unordered_map.
  - Calculate speed using above formula.
  - Store pair <key=speed, value=name> in priority_queue(maxHeap).
- *3.* Print second,first from priority_queue and keep on deleting entries.

### Complexity
- **Space = O(m)+O(n)** dataset2.csv=length=n, dataset2.csv=length=m
  - Creation of unordered_map = O(m)  //only name, strideLen
  - Creation of maxHeap = O(n)  //only Speed, Name
- **Time = O(m)+O(n)** 
  - Unordered_map creation=O(n), Retrieve key=O(1)
  - Prirotiy Queue creation=O(m), Retrieve = O(1)
  
### Code
```c++
#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<queue>
#include<unordered_map>

#define r  4
#define r2 r*r
#define g  9.8/r2

double CalculateSpeed (double dStrideLen, double dLegLen) {
  return ((dStrideLen/dLegLen - 1) * sqrt(dLegLen * g));
}

int main() {
  std::string strLine;  //1 Line from file
  std::string strWord;  //Word from parsed line
  std::string strName;  //Name from parsed line
  double dLegLength = 0.0, dStrideLen = 0.0;
  int i=0;
  std::unordered_map <std::string, double> mapDataSet2;
  std::map <double, std::string> mapOutput;
  std::priority_queue<std::pair<double, std::string>> maxHeap;

  std::ifstream ifDataset2 ("dataset2.csv");    //1. Open dataset2.csv
  std::getline (ifDataset2, strLine);   //Ignore 1st line of dataset2.csv

  //Read dataset2.csv and store in map<key=name, value=stride_length>
  while (ifDataset2.eof() == 0) {                           //Read file dataset2.csv
    std::getline (ifDataset2, strLine);
    std::stringstream oSSDataSet2(strLine);
    while (std::getline(oSSDataSet2, strWord, ',')) {
      if (i==0){
        strName = strWord;
      }
      if (i==1){
        std::istringstream(strWord) >> dStrideLen;
        mapDataSet2[strName] = dStrideLen;
      }
      ++i;
    }
    i=0;
  }
  std::cout<<"Map created\n";
  
    std::ifstream ifDataset1 ("dataset1.csv");    //1. Open dataset1.csv
  std::getline (ifDataset1, strLine);   //Ignore 1st line of dataset1.csv
  double dSpeed;

  while (ifDataset1) {                          //Read file dataset1.csv
    std::getline(ifDataset1, strLine);  //Read 2nd and subsequent lines
    std::stringstream oSSDataSet1(strLine);
    while (std::getline(oSSDataSet1, strWord, ',')) {   //Tokenize with delimiter , and only read 2 tokens
      if (i==0)
        strName = strWord;                      //Name
      if (i==1){
        std::istringstream(strWord) >> dLegLength;
        auto it = mapDataSet2.find(strName);
        if(it != mapDataSet2.end()){
          dSpeed = CalculateSpeed(it->second, dLegLength);
//          std::cout<<"Name:"<<strName<<", Speed:"<<dSpeed<<std::endl;
          mapOutput[dSpeed] = strName;
          maxHeap.push(make_pair(dSpeed, strName));
        }
      }
      ++i;
    }
    oSSDataSet1.clear(); i=0;
  }

  while(maxHeap.empty() != 1) {
    std::pair<double, std::string> p = maxHeap.top();
    std::cout<<p.second<<","<<p.first<<"\n";
    maxHeap.pop();
  }

}
```
