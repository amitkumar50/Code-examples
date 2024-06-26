Type Annotation
- **Scalar / Primitive Data Type**
  - [int](#int)
    - [int overflow](#into)
    - [Array slice](#arrs)
  - [float](#fl)
  - [bool](#booldatatype)
  - [char](#chardatatype)
- **Compund Data Type**
  - [Array Type](#a)
  - [Tuple Type](#t)
    - [`Option<String, i32>` tuple](#opt)
  - [struct Type](#st)
  - [cons list](#cl)

### Type Annotation
- When many types are possible. Eg: String converted to a int using parse(), we must add a type annotation to tell type to complier.
```rs
  let a = 1;        //a inferred int
  let b = "get";    //b inferred string
  
  let c:u32 = "42".parse().expect("Not a number!");            //Type Annotation u32
```

# Scalar / Primitive Data Type
A scalar type represents a single value. Rust has 4 primary scalar types: int, float, bool, char

<a name="int"></a>
## int
Integers can be signed(-ve, +ve  both) and unsigned(takes +ve values). Signed Number are stored using [2's Compliment](/Languages/Programming_Languages/C/Bitwise/Representation_of_Numbers). 
  - _Signed:_ i8, i16, i32, i64, i128
  - _unsigned:_ u8, u16, u32, u64, u128
  - _isize, usize:_ Pointer sized signed, unsigned integer type. Depends on computer architecture. 
  - _How usize is different from u32/u64?_ 
    - u32/u64 are always 4/8 bytes, But usize(sizeof pointer) depends on complier ie for 32Bit(its 32), for 64Bit(its 64).
    - So it makes great sense to access array variables using address only, bcoz it can change with architecture!! Cool
- _f32, f64_
- **Writing Integer Literals**
```c
Number literals 	          Example
Decimal can be written as   98_222
Hex	                        0xff
Octal	                      0o77
Binary	                    0b1111_0000
Byte (u8 only)            	b'A'
```

<a name="into"></a>
### Integer Overflow
Assigning value outside of allowed range. Example:
```rs
  let a:u8 = 256      //This is integer overflow, because u8 0-255 values can be assigned
```  
- *Compiled in debug mode?* When program is compiled in debug mode, Rust includes checks for integer overflow & program will PANIC(exit with error) at runtime.
- *Compiled in release mode(--release flag)*
  - When program is compiled in release mode, Rust DOES NOT include checks for integer overflow. At runtime, overflow occurs Rust performs 2’s complement wrapping. 
  - *2’s complement wrapping?* Values greater than 255 gets wrapped around. 256 becomes 0. 257 becomes 1 and so on. No PANIC happens.

<a name="arrs"></a>
### Array Slice
Read [String Slice](../) to understand How slices are stored and their type. Array Slice is taking piece of array. Type of Array slice is `&i[32]`
```rs
fn main() {
    let a = [1,2,3,4,5];
    let b = &a[1..3];             //Type of b is &[i32]
    println!("{}",b[0]);
}
```

<a name="fl"></a>
## Floating-Point Types
- Floating point are of 2 sizes f32(32 bit), f64(64 bit). 
- f64 is default. Why f64 is default, because on modern CPUs f64 is roughly the same speed as f32 but is capable of more precision.
```rs
fn main() {
    let x = 2.0;          //f64
    let y: f32 = 3.0;     //f32
}
```
- *All operations are supported on float*
```rs
fn main() {
    let sum = 5.2 + 10.1;               //addition
    let difference = 95.5 - 4.3;        //subtraction
    let product = 4 * 30;               //multiplication
    let quotient = 56.7 / 32.2;         //division
    let remainder = 43 % 5;             //remainder
}
```

<a name="booldatatype"></a>
## Boolean type
Booleans are one byte in size. Can have 2 values: true, false.
```rs
fn main() {
    let a = true;
    let b: bool = false;      //with explicit type annotation
}
```

<a name="chardatatype"></a>
## Character Type
- char literals are specified with single quotes and string literals use double quotes.
- Size of char type = 4 bytes
- Letters: Chinese, Japanese, and Korean characters; emoji; and zero-width spaces are all valid char values in Rust
```rust
fn main() {
    let c = 'z';
    let z = 'ℤ';
    let heart_eyed_cat = '😻';
}
```

# Compund Data Type
Compound types can group multiple values into one type.

<a name="a"></a>
## Array Type
- Array elements are allocated contigiously on stack, unlike vectors which's allocated on heap.
- Unlike Tuple, every element of an array must have the same type.
- **Fixed length.** arrays in Rust have a fixed length
- Array are written as a comma-separated list inside square brackets
```rs
fn main() {
    let a = [1, 2, 3, 4, 5];
    let a: [i32; 5] = [1, 2, 3, 4, 5];
    let a = [3; 5];                     //[element, no-of-elements].  a = [3,3,3,3,3]
    
    //Accessing array elements
    let first = a[0];
    let second = a[1];
}
```

<a name="t"></a>
## Tuple Type
- Grouping together different data types into 1 compound type.
- Tuples are fixed length, once declared, they cannot grow or shrink in size.
  - *1. Destructring a Tuple?* Assigning tuple variable values to seperate variables to use.
```rs
fn main() {
  let tup = (500, 6.4);                              //Type annotation is not mandatory
  let (x, y) = tup;                                  //Destructing tuple
  println!("The value of y is: {}", y);              //6.4
}
```
*Accessing tuple using index values?* We can access a tuple element directly by using a period (.) followed by the index of the value we want to access. 1st index is 0.
```rs
  let a = tup.0                                         //500
  let b = tup.1                                         //6.4
}
```

<a name=opt></a>
#### `Option<String, i32>` tuple
```rs
  let tup : Option <&(String, i32)> = ("amit", 1);
  
```

<a name="st"></a>
## [Struct Type](Compound)
- associated functions

<a name=cl></a>
## cons list
CL is data structure which constructs a new pair from its two arguments, its something like a box is allocated internally to other and so on.
```rs
use crate::List::{Cons, Nil};

fn main() {
    let list = Cons(1, Cons(2, Cons(3, Nil)));           //Compile error. recursive without indirection
}
//Why Compile error? Compiler cannot determine how many i32 are nested inside.

//Solution: Now we only store pointer to cons list at compile time.
enum List { Cons(i32, Box<List>), Nil,}             //BOX

fn main() {
    let list = Cons(1, Box::new(Cons(2, Box::new(Cons(3, Box::new(Nil))))));
}
```
<img src=cons_list.JPG width=400/>
