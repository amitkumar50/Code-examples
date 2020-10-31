## [GoogleTest](https://github.com/google/googletest)

### 1. Installation
#### 1A. Ubuntu
```c++
# sudo apt-get install libgtest-dev               //1. Install gtest source files
# sudo apt-get install cmake

# cd /usr/src/gtest                               //2. Go to directory where source is installed and make it
# sudo cmake CMakeLists.txt; sudo make

# sudo cp *.a /usr/lib                            //3. copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
```

### 2. Using Googletest Examples
#### Example-1 {Testing class}
- **test.cpp**
```c++
class A{
public:
  int fun(int a, int b) {
    return (a/b);
  }
};
```
- **main.cpp**
```c++
#include "test.cpp"
#include <gtest/gtest.h>

TEST(DivideTest, TestCase1) {
             //(Expected_Output, function call)
    ASSERT_EQ(5, obj.fun(10,2));
//    ASSERT_EQ(6, fun(10,2));
//    ASSERT_EQ(18.0, squareRoot(324.0));
//    ASSERT_EQ(25.4, squareRoot(645.16));
//    ASSERT_EQ(0, squareRoot(0.0));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
```
- **CMakeList.txt**
```c++
cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests main.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
```
- **Compile and Run tests**
```c++
# cmake CMakeLists.txt
# make
# ./runtests
```c++
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from DivideTest
[ RUN      ] DivideTest.TestCase1
[       OK ] DivideTest.TestCase1 (0 ms)
[----------] 1 test from DivideTest (4 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (24 ms total)
[  PASSED  ] 1 test.
```
