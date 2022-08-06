# Intermediate Javascript

## Scope
Any variable declare in the file outside of any function will be global scope
```javascript
var x = 1;
```

Any variable declare inside a function cannot be accessed by outside scope
```javascript
var x = 5;

function fn() {
    var insideFnScope = 10;
    console.log(insideFnScope);
    console.log(x);
};

fn();
// -> 10
// -> 5

console.log(insideFnScope);
// -> Uncaught ReferenceError: insideInnerScope is not defined
```

A function can access variables defined in its outside sceope. However, if a variable with the same name is redefined in the function with `var`, the inside definition masks the outside definition. Outside the function, the variable is unmasked and returns to its original value in the outside scope.
```javascript
var x = 5;
var y = 10;

function fn() {
    var y = 20;
    console.log(x);
    console.log(y);
}

fn();
// -> 5
// -> 20

console.log(x); // -> 5
console.log(y); // -> 10
```

A function can change the value of a variable in the outside scope with `=` operator
```javascript
var x = 5;

function fn() {
    x = 10;
    y = 20;
};

fn();
console.log(x); // -> 10
console.log(y); // -> 20
```

Best practice: avoid defining variable in global scope

## Variable Hoisting
JS interpreter hoist the variable declaration to the top of their avaliable scope. I.e. the following code
```javascript
// OPERATION BEFORE
var x = 1;
// OPERATION AFTER 
```
will be interepreted as 
```javascript
var x;
// OPERATION BEFORE
x = 1;
// OPERATION AFTER
```
Therefore, if `OPERATION BEFORE` tries to read `x`, it will return underfined.

## Function Hoisting
If we declare a function using *function expression*
```javascript
// OPERATION BEFORE
var fn = function() {
    // DO SOMETHING
};
// OPERATION AFTER
```
will be interepted as
```javascript
var fn;
// OPERATION BEFORE
fn = functon() {
    // DO SOMETHING
}
// OPERATION AFTER
```

If we declare a function using *function declaration*
```javascript
// OPERATION BEFORE
function fn() {
    // DO SOMETHING
}
// OPERATION AFTER
```
the JS interpreter will move the entire function declaration to the top of the scope
```javascript
function fn() {
    // DO SOMETHING
}
// OPERATION BEFORE
// OPERATION AFTER
```

## `let` 
`let` declares variables that are 
1. not hoisted
2. block-scoped.

This means only function below the declaration can access it
```javascript
console.log(x); // -> Uncaught ReferenceError: x is not defined
let x = 10;
console.log(x);
```

Also any attempt to access it outside the scope will fail
```javascript
{
  var x = 10;
  let y = 20;
  
  console.log(x); // -> 10
  console.log(y); // -> 20
}

console.log(x); // -> 10
console.log(y); // -> Uncaught ReferenceError: y is not defined
```

Also redeclaration in the same block scope is not allow, reassigning value is allowed.
```javascript
var x = 4;
var x = 5;

let y = 6;  
y = 7; // OK
let y = 8; // -> Uncaught SyntaxError: Identifier 'y' has already been declared
```

Also when using it for loop vriable, we can only assess it within the loop
```javascript
for (var i = 0; i < 10; i++) {
}

for (let j = 0; j < 10; j++) {
}

console.log(i); // -> 10
console.log(j); // -> Uncaught ReferenceError: j is not defined
```

## `const`
`const` declares varibles that 
1. is not hoisted
2. has block scope
3. cannot be reassigned
4. must have a initial value
5. if it holds an object, we can modify the object fields

Similar to let, we can't access the element from above
```javascript
console.log(x); // -> Uncaught ReferenceError: x is not defined
const x = 10;
console.log(x);
```

cannot reassign its value with `=`
```javascript
var x = 3;
let y = 4;
const z = 5;

x = 30;
y = 40;
z = 50; // -> Uncaught TypeError: Assignment to constant variable.
```

must be initialize with a initial value with `=`
```javascript
var a;
let b;
const c; // -> Uncaught SyntaxError: Missing initializer in const declaration
```

Rule of Thumb:
Use `const` whenever possible, then use `let` if reassignment must be performed. Try to avoid `var`

## callback
In JS functions are objects. Thus we can assign it with attributes and also pass it into another function

A callback is a function that is passed in to another function.
```javascript
function fn() {
    console.log("Hello World!");
}

function functionCaller(f) {
    f()
}

functionCaller(fn) // "Hello World"
```

## function closure
A function closure is the combination of a function and the lexical environment within which that function was declared.

Function allows encapsulation and provides a interface that hides the detail of implementation
```javascript
function counterGenerator() {
    let counter = 1;
  
    return function() {
        return counter++;
    }
}

const incrementCounter = counterGenerator();
console.log(incrementCounter()); // -> 1
console.log(incrementCounter()); // -> 2
counter = 100; // <- sets a new global variable 'counter';
               // the one inside counterGenerator is unchanged
console.log(incrementCounter()); // -> 3
```

## Value and Refernece
JavaScript has 5 data types that are copied by value: `Boolean`, `null`, `undefined`, `String`, and `Number`. We’ll call these primitive types. Primitives are vopied by values when `=` is used.
```javascript
const x = 10;
const y = 'abc';

let a = x;
let b = y;

a = 5;
b = 'def';

console.log(x, y, a, b); // -> 10, 'abc', 5, 'def'
```

JavaScript has 3 data types that are copied by having their reference copied: `Array`, `Function`, and `Object`. These are all technically Objects, so we’ll refer to them collectively as Objects. Objects are copied by reference when `=` is used.
```javascript
const reference = [1];
const refCopy = reference;

reference.push(2);
console.log(reference, refCopy);
// -> [1, 2], [1, 2]
```

However, we can reassign a reference variable to replace the old reference. The old value will be garbage collected if no variable has reference to it
```javascript
let obj = { first: 'reference' };
obj = { second: 'ref2' }
```

We can check whether two reference points to the same object using `===`. 
```javascript
const arrRef = ['Hi!'];
const arrRef2 = arrRef;

console.log(arrRef === arrRef2); // -> true

const arr1 = ['Hi!'];
const arr2 = ['Hi!'];

console.log(arr1 === arr2); // -> false
```

## Template literals
A template literal is encompassed by \` \`. We can add `${}` any where inside the literal to encompass javascript expressions. Then the string will be formed by evaluating the javascript expression in `${}`
```javascript
const firstname = "Joe"
const secondname = "Doe"
const temp = `Hi! My name is ${firstname} ${secondname}`
```

## Function parameters
Functions now can have default parameter values
```javascript
function fn(param = "Default value") {
    console.log(param);
}

fn('String passed in'); // -> String passed in
fn(); // -> Default value
```
they can also contain expression
```javascript
function fn(param = 10 * 10) {
    console.log(param);
    return param;
}

function fn2(param = fn(50)) {
    console.log(param);
}

fn('String passed in'); // -> String passed in
fn(); // -> 100

fn2(); // -> 50
       // -> 50
```
and latter parameter can use previous parameters
```javascript
function add(param1 = 10, param2 = param1) {
    console.log(param1 + param2);
}

add(2, 5); // -> 7
add(2); // -> 4
add(); // -> 20
```

## Arrow functions
We can declare arrow functions in the syntax `() => {}` to make clear interface
```javascript
const standardFnAdd = function(num1, num2) {
    console.log(num1 + num2);
    return num1 + num2;
}

const arrowFnAdd = (num1, num2) => {
    console.log(num1 + num2);
    return(num1 + num2);
};

standardFnAdd(2, 5); // -> 7
arrowFnAdd(2, 5); // -> 7
```

The right hand side can be a simple expression used as the return value
```javascript
const standardFnAdd = function(num1, num2) {
    return num1 + num2;
}

const arrowFnAdd = (num1, num2) => num1 + num2;

console.log(standardFnAdd(2, 5)); // -> 7
console.log(arrowFnAdd(2, 5)); // -> 7
```

This is particular useful for function callbacks
```javascript
const arr = [{ prop: 'abc' }, { prop: 'def' }];
const props = arr.map(obj => obj.prop);
console.log(props); // -> [ 'abc', 'def' ]
```