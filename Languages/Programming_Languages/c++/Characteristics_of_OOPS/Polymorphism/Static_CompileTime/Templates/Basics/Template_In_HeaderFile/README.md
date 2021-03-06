## Problem
- Template function declaration is present in Header File, Definition inside source. But **Linker Error** on compilation.
  - **Linker Error: undefined reference to `void fun<int>()'**
```c++
//test.hpp
#pragma once
template <typename T>
void fun ();

//test.cpp
#include <iostream>
#include "test.hpp"
template <typename T>
void fun () {
 std::cout <<"In fun" << std::endl;
}

//main.cpp
#include "test.hpp"
int main() {
 fun<int>();
}

# g++ main.cpp test.cpp -I.
Linker Error: undefined reference to `void fun<int>()'
```
- **Why Linker Error?**
  - The definition of the function template fun() has not been instantiated.
- **Function template instantiation?**
  - *What?* Determining template arguments at compile time so that compiler can generate actual function(which is going to be used).
  - *Why?* 
    - A function template is not a Type or Function. No code is generated from a source file that contains only template definitions.
    - In order for any code to be generated, the template arguments must be determined so that the compiler can generate an actual function.
  - *How?* Compiler must know which definition should be instantiated.
  
## Solutions
### 1. Include test.cpp in main.cpp
### 2. Inclusion Model
- **What?** Include definition of function template inside header file.
```c++
//test.hpp
#pragma once
#include <iostream>
#include "test.hpp"
template <typename T>
void fun ();

template <typename T>
void fun () {
 std::cout <<"In fun" << std::endl;
}

//main.cpp
#include "test.hpp"
int main() {
 fun<int>();
}
# g++ main.cpp -I.
```
- **Problems with inclusion model**
  - *1.* With header file system header files also gets included in main.cpp, which increases size and increses compilation time.

### 3. Explicit/Manual Instantiation
- **What?** Explicit instantiation directive consists of the keyword template followed by the fully substituted declaration of the entity we want to instantiate.
- **Disadvantage?** We must carefully keep track of which entities to instantiate. For bigger projects this becomes a burden, hence not recommended.
```c++
//test.hpp
#pragma once
template <typename T>
void fun ();

//test.cpp
#include <iostream>
#include "test.hpp"
template <typename T>
void fun () {
 std::cout <<"In fun" << std::endl;
}
template void fun<int>();                 //EXPLICIT INSTANTIATION

//main.cpp
#include "test.hpp"
int main() {
 fun<int>();
}
```

### 4. Inclusion Model + Explicit Instantiation (recommended)
- **What?** Declaration and definition in seperate files.
  - Declaration inside `test.hpp`
  - Definition inside `testdef.hpp`
  - `testdef.hpp` is included in `main.cpp`
```c++
//test.hpp                                 //Declaration inside Header
#pragma once  
template <typename T>
void fun ();

//testdef.hpp                             //Definition inside Header file
#include <iostream>
#include "test.hpp"
template <typename T>
void fun () {
 std::cout <<"In fun" << std::endl;
}

//main.cpp
#include "testdef.hpp"                    //Definition header file included in .cpp
int main() {
 fun<int>();
}
```

### 5. Making template function as inline 
- **What** Both function templates and inline functions can be defined in multiple files. ie placing definition in header file & including it in multiple `cpp` files.
- **When/Why**
  - When function template is small, it can be declared as inline.
  - The only use of the inline keyword is to stop compilers complaining about ODR violations.
- **Disadvantages**
  - *1.* By using inline the name mangling works out different which gets round the name clash at link time but at the expense of vastly bloated code.  
