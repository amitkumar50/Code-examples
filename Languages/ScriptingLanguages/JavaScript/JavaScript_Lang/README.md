**Javascript**
- [Objects](#o)
- [Data Types](#d)
- [Control Flow](#c)
- [Operators](#o)

## JavaScript
- **JS has nothing to do with java.** In 1995 when JS was introduced, java was gaining success, Writer though to ride along sucess of java and nothing else.
- JS is used for web development: Display dynamic contents: interactive maps, animated 2D/3D graphics, scrolling video jukeboxes, etc.
- **1st JS Program?**
  - [Install nodejs](/Languages/ScriptingLanguages/JavaScript/JSON/Restful_JSONServer) to compile JS program
```js
test.js
var age = 39;         //Integer
console.log('Age:'+ age +'\n');

cmd> node test.js
age: 39
```

<a name=o></a>
### Objects
**1. JS uses functions as classes** JS does not have class statement.
```js
function makePerson(first, last) {                //Class 
  return {
    first: first,                               //members
    last: last,
    fullName: function() {
      return this.first + ' ' + this.last;
    },
    fullNameReversed: function() {
      return this.last + ', ' + this.first;
    }
  };
}

var s = makePerson('Simon', 'Willison');                  //Created Object
s.fullName(); // "Simon Willison"
s.fullNameReversed(); // "Willison, Simon"
```
<a name=d></a>
### Datatypes in JS
- **1. Number**: Number are 64 bit and floats not ints.
```js
console.log(3 / 2);             // 1.5, not 1
console.log(Math.floor(3 / 2)); // 1
parseInt('123', 10);            //123.          parseInt(string,number-system-base) converts string to integer
parseInt('0x10');               // 16
parseInt('hello', 10);          // NaN          NaN ("Not a Number") is returned if the string is non-numeric
isNaN(NaN); // true
 1 / 0;                         //  Infinity
-1 / 0;                         // -Infinity
```
- **2. String** These are sequences of UTF-16 code units; each code unit is represented by a 16-bit number
```js
'hello'.length;                 // 5
'hello'.charAt(0);              // "h"
'hello, world'.replace('world', 'mars'); // "hello, mars"
'hello'.toUpperCase();          // "HELLO"
```
- **3. Boolean**
- **4. Variables** Declared using one of three keywords:
  - let(declares block level or local variable)
  - const(declare variables whose values are never intended to change)
  - var(global variable)
```js
let a;
let name = 'Simon';
const Pi = 3.14; // variable Pi is set 
Pi = 1; // will throw an error because you cannot change a constant variable.
```
- **5. Objects** These are name=value pairs. Similar to Dictionaries in Python, Hash tables in C and C++, HashMaps in Java.
```js
var obj = new Object();                 //Create Empty object
var obj = {};                           //Object literal syntax preferred

var obj = {                             //Initialize object
  name: 'Carrot',
  for: 'Max', // 'for' is a reserved word, use '_for' instead.
  details: {
    color: 'orange',
    size: 12
  }
};
obj.details.color; // orange
obj['details']['size']; // 12

function Person(name, age) {              //Create a object prototype(Person) and an instance of that prototype(you)
  this.name = name;
  this.age = age;
}
// Define an object
var you = new Person('You', 24);
```
- **6. Arrays:** [Complete documentation of array methods](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array)
```js
var a = new Array();
a[0] = 'dog';
a[1] = 'cat';
a[2] = 'hen';
a.length; // 3

var a = ['dog', 'cat', 'hen'];
a.length; //3

var a = ['dog', 'cat', 'hen'];
a[100] = 'fox';
a.length;                           // 101             the length of the array is one more than the highest index

typeof a[90];                       // undefined    If you query a non-existent array index, you'll get a value of undefined in return

a.push(item);                       //Adding item to array
```
<a name=o></a>
### Operators
```js
'hello' + ' world';                 // "hello world"
'3' + 4 + 5;                         // "345"        If you add a string to a number everything is converted into a string first.
 3 + 4 + '5';                       // "75"
```
- **triple-equals operator** For comparing types of different types
```js
123 == '123';           // true. Should not be compared this is type coercion
1 == true;              // true
123 === '123'; // false
1 === true;    // false
```
- **7. Functions**
```
function add() {
  var sum = 0;
  for (var i = 0, j = arguments.length; i < j; i++) {         //Variable name 'arguments' holds all of the values passed to the function
    sum += arguments[i];
  }
  return sum;
}
add(2, 3, 4, 5);                    // 14

function avg(...args) {           //...args is Rest parameter syntax.
  var sum = 0;
  for (let value of args) {
    sum += value;
  }
  return sum / args.length;
}
avg(2, 3, 4, 5);                   // 3.5

var avg = function() {                    //Lambda, Anonymous Function
  var sum = 0;
  for (var i = 0, j = arguments.length; i < j; i++) {
    sum += arguments[i];
  }
  return sum / arguments.length;
};
```
<a name=c></a>
### Control Flow
- for, while, do while, switch, ternary operator are same. 2 additional for loops
```js
for (let value of array) {              //FOR OF loop
  // do something with value
}
for (let property in object) {            //FOR IN loop
  // do something with object property
}
```

