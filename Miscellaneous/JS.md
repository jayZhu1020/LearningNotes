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

## New Object Functionality
We can directly use variables as object fields
```javascript
// OLD 
var name = 'Sophia';
var age = 25;

var person = {
    name: name,
    age: age
};

// NEW
const name = 'Sophia';
const age = 25;

const person = {
    name,
    age
};
```
And we don't need the `function` keyword to define a field as function
```javascript
const name = 'Christina';
const age = 23;

const obj1 = {
    name,
    age,
    growOlder: function() {
        this.age++;
    }
}

const obj2 = {
    name,
    age,
    growOlder() {
        this.age++;
    }
}
```
A getter is a method on an object created by placing the keyword get before the function. To invoke the method and get its return value, the method is called without the (), as if it were a standard static property.
```javascript
const firstName = 'Brooke';
const lastName = 'Smith';

const person = {
    firstName,
    lastName,
    get fullName() {
        return this.firstName + ' ' + this.lastName;
    }
}

console.log(person.fullName); // -> Brooke Smith
```
Setters are special methods that take in a single argument. They are created by writing a method on an object using the keyword set. They are invoked through a normal = assignment.
```javascript
const firstName = 'Brooke';
const lastName = 'Smith';

const person = {
    firstName,
    lastName,
  
    get fullName() {
        return this.firstName + ' ' + this.lastName;
    },
  
    set fullName(name) {
        const spaceIndex = name.indexOf(' ');
        this.firstName = name.slice(0, spaceIndex);
        this.lastName = name.slice(spaceIndex + 1);
    }
}

console.log(person.fullName); // -> Brooke Smith
person.fullName = 'Alex Johnson';
console.log(person.firstName); // -> Alex
console.log(person.lastName); // -> Johnson
console.log(person.fullName); // -> Alex Johnson
```

## Array and object destructuring
We can destructure arrays and objects by grouping the variable names on the left of `=`, and array or object on the right of `=`
```javascript
const arr = [1, 2, 3];
const [one, two, three] = arr;
console.log(one, two, three); // -> 1 2 3

// ---------------------------------------

const obj = {
    key1: 'val1',
    key2: 'val2'
};
const { key1, key2 } = obj;
console.log(key1, key2); // -> val1 val2
```

we can alsos specify default value when destructuring
```javascript
const arr = [1, 2];
const [one = 'one', two = 'two', three = 'three'] = arr;
console.log(one, two, three); // -> 1 2 'three'

const obj = { key1: 'val1' };
const {
    key1 = 'val1Default',
    key2 = 'val2Default'
} = obj;
console.log(key1, key2); // -> val1 val2Default
```

This is especially helpful when we try to pass in object as function parameter
```javascript
function fn({ firstName, lastName, age, occupation }) {
    // We already have all the variables we need!
}

const firstName = 'Sophia';
const lastName = 'Lundgren';
const age = 25;
const occupation = 'Software Engineer';

fn({ firstName, lastName, age, occupation });
```

## `this` and `new`
In JavaScript, `this` inside a function is meant to reference the object that the function is a property of.

When a function is called in the global scope, it is part of the object `window`
```javascript
function fn() {
    console.log(this);
}

fn(); // -> Window {frames: Window, postMessage: ƒ, …}
```
When we use `new`, we’re always being returned a fresh, newly constructed object with a brand new reference.
```javascript
function fn() {
}
    
console.log(fn()); // -> undefined
console.log(new fn()); // -> fn {}
```
If we call `console.log()` an object that was created using new, the console logs out the name of the function that created the object and then the object.

We can use `new` and `this` to write object constructor
```javascript
function PersonConstructor(name, age) {
    this.name = name;
    this.age = age;
}

const christa = new PersonConstructor('Christa', 30);
console.log(christa); // -> { name: 'Christa', age: 30 }
```
Under the hood, when `new` is called on some function,
1. Creates a new object and binds it to the this keyword.
2. Sets the object’s internal prototype-inheritance property, __proto__, to be the prototype of the constructing function. This also makes it so the constructor of the new object is prototypically inherited.
3. Sets up logic such that if a variable of any type other than object, array, or function is returned in the function body, return this, the newly constructed object, instead of what the function says to return.
4. At the end of the function, returns this if there is no return statement in the function body.
```javascript
function PersonConstructor(name, age) {
    // this = {};
    // this.__proto__ = PersonConstructor.prototype;

    // if (there is a return statement
    // in the function body that
    // returns anything EXCEPT an
    // object, array, or function) {
    //     return 'this' (the newly
    //     constructed object)
    //     instead of that item at
    //     the return statement;
    // }

    this.name = name;
    this.age = age;

    // return this;
}
```

## `apply` `call` and `bind`
To allow a function to work on different object, we can override the `this` object so that the function can behave generically. 

given a function `fn`, we can call `fn.call(newObj, para1,...,paran)` so that the function can be act as a method on `newObj` with parameter `para1,...,paran`. This is equivalent to `fn.apply(newObj, [para1, ..., paran])`. Also we can use `const bindingFunc = fn.bind(newObj, para1,...,paran)` to bind and store the function for future use.
```javascript
function logThisAndArguments(arg1, arg2) {
    console.log(this);
    console.log(arg1);
    console.log(arg2);
}

const obj = { val: 'Hello!' };

// NORMAL FUNCTION CALL
logThisAndArguments('First arg', 'Second arg');
// -> Window {frames: Window, postMessage: ƒ, …}
// -> First arg
// -> Second arg

// USING CALL
logThisAndArguments.call(obj, 'First arg', 'Second arg');
// -> { val: 'Hello!' }
// -> First arg
// -> Second arg

// USING APPLY
logThisAndArguments.apply(obj, ['First arg', 'Second arg']);
// -> { val: 'Hello!' }
// -> First arg
// -> Second arg

// USING BIND
const fnBound = logThisAndArguments.bind(obj, 'First arg', 'Second arg');
fnBound();
// -> { val: 'Hello!' }
// -> First arg
// -> Second arg
```

## Spread using `...`
the `...` operator spreads an array or object, i.e.
1. `arr = [1,2,3,...[4,5,6]]` will spread the subarray `[4,5,6]` to `arr = [1,2,3,4,5,6]`
2. `obj = {1:1,2:2,3:3,...{4:4,5:5,6:6}}` will spread the subobject `{4:4,5:5,6:6}` to `obj = {1:1,2:2,3:3,4:4,5:5,6:6}`

We can also use `...` to copy array or object by reference
```javascript
const arr = [1, 2, 3];
const arrCopy = [...arr];

const obj = { item: 'value' };
const objCopy = { ...obj };

console.log(arrCopy); // -> [ 1, 2, 3 ]
console.log(objCopy); // -> { item: 'value' }
```

We can also spread string into arrays or objects
```javascript
const str = 'abcde';

const strArr = [...str];
console.log(strArr);
// -> [ 'a', 'b', 'c', 'd', 'e' ]

const strObj = { ...str };
console.log(strObj);
// -> { '0': 'a', '1': 'b', '2': 'c', '3': 'd', '4': 'e' }
```

We can use this property to collect any number of arguments left in a function call
```javascript
function add(num1, ...args) {
    console.log(num1);
    console.log(args);
}

add(1, 2, 3);
// -> 1
// -> [2, 3]
```

## Rules of `this`
The value of `this` is determined with the following rules;
1. If the new keyword is used when calling the function, this inside the function is a brand new object created by the JavaScript engine.
```javascript
function ConstructorExample() {
    console.log(this);
    this.value = 10;
    console.log(this);
}

new ConstructorExample();

// -> ConstructorExample {}
// -> ConstructorExample { value: 10 }
```
2. If `apply`, `call`, or `bind` are used to call a function, this inside the function is the object that is passed in as the argument.
```javascript
function fn() {
    console.log(this);
}

var obj = {
    value: 5
};

var boundFn = fn.bind(obj);

boundFn(); // -> { value: 5 }
fn.call(obj); // -> { value: 5 }
fn.apply(obj); // -> { value: 5 }
```
3. If a function is called as a method — that is, if dot notation is used to invoke the function — this is the object that the function is a property of.
```javascript
const obj = {
    value: 5,
    printThis: function() {
      console.log(this);
    }
};

obj.printThis(); // -> { value: 5, printThis: ƒ }
```
4. If a function is invoked as a free function invocation, meaning it was invoked without any of the conditions present above, this is the global object. In a browser, it’s `window`
```javascript
function fn() {
    console.log(this);
}

// If called in browser:
fn(); // -> Window {stop: ƒ, open: ƒ, alert: ƒ, ...}
```
6. If the function is an ES2015 arrow function, it ignores all the rules above and receives the this value of its surrounding scope at the time it’s created.
```javascript
const obj = {
    value: 'abc',
    createArrowFn: function() {
        return () => console.log(this);
    }
};

const arrowFn = obj.createArrowFn();
arrowFn(); // -> { value: 'abc', createArrowFn: ƒ }
```

## Object Prototypes
In javascripts, `Object`, `Array` and `Function` are functions. We can check by running
```javascript
console.log(Object); // -> [Function: Object]
console.log(Array); // -> [Function: Array]
console.log(Function); // -> [Function: Function]
```
When we call `const obj = {}`, the engine under the hood calls `new Object()`

All objects has an attribute `__proto__` to an object with several properties:
```javascript
const obj = {};
console.log(obj.__proto__);
// -> {constructor: ƒ, __defineGetter__: ƒ, __defineSetter__: ƒ, hasOwnProperty: ƒ, __lookupGetter__: ƒ, …}
```
For the function object `Object`, we have that `Object.prototype` is a "base" object having `__proto__` equals to `null`. This implies that `Object` is the end of the prototype chain. It has no parent prototype. 

When we look for a property of an object, say `object.someproperty`, the JavaScript engine will first check the object itself for the existence of the property, i.e. whether `someproperty` in `object.property`. If not found, it’ll go to the object’s prototype and check that object, i.e. whether `someproperty` in `object.__proto__`. If found, it’ll use that property. If it finds `null` at some step, it returns `undefined`.

There are several functions used to manage `__proto__` and properties of a object. 
1. `hasOwnProperty`: It’ll return true or false based on whether the object itself contains the property being tested. Testing for `__proto__`, however, will ALWAYS return `false`.
   
2. `Object.getOwnPropertyNames`: Returns the properties of the current object in a list, not including `__proto__`
   
3. `Object.getPrototypeOf`: Object.getPrototypeOf is a function that returns an object’s `__proto__` property.

4. `Object.setPrototypeOf`: It allows us to change an object’s `__proto__` property.




## `vue.js`
Vue is based on the idea of virtual DOM. A DOM (Document Object Model) is used as the structure of the HTML files where components are nested within each other. To search a component in a DOM, the cost is expensive. Virtual DOM represents each DOM component as a Javascript Object, and we can dynamically modifies its property to reflect that in the actual DOM in HTML.

Vue can be added as an instance to a webpage and all of its resources reside within that object. The `Vue()` constructor takes in a JS object with some properties
```javascript
var vm = new Vue({
  // options
})
```
The key properties are 
1. `el`: When a Vue instance is created, it looks for an element in the webpage to control. That element will be defined by the developer. It can be defined by assigning that element (usually a `div`) an `id`. This `id` is then mentioned in the Vue instance as the value of the `el` key.
2. `template`: The `template` defines what the Vue instance would display. The template is an HTML style element that can be controlled by the Vue instance. This actually replaces the element in the HTML file whose `id` is mentioned in the Vue instance.
3. `data`: The `data` is the store of a Vue instance. It stores all the variables it needs.
4. `methods`: A Vue instance may also need to perform some tasks. For this, it can also have its own methods or functions that can be defined in the methods key of the Vue instance.
Example:
```javascript
new Vue({
  el: '#app',
  template:
  `<div>
    <h1>Vue.js Application</h1>
    <p> {{name}}'s age is {{age}}</p>
    <button @click="incrementAge">Increment Age</button>
  </div>
  `,
  data: {
      name: 'John',
      age: 26
  },
  methods: {
      incrementAge() {
            this.age++
      }
  }
})
```
Also vue needs ti be imported using `<script src="https://cdn.jsdelivr.net/npm/vue@2"></script>`

## Mount Vue.js
Two ways to mount vue virtual DOM to the HTML:
1. Use `el=#app`. This mounts the content right away
```javascript
<!-- This is the div that is assigned the id= 'app' -->
<div id='app'></div>

<script>
new Vue({
    el: '#app' , // This is a way to mount Vue instance!
    ...
})
</script>
```
2. Use `$mount('#app')` on the Vue instance. This allows aynchronous mounting.
```javascript
<!-- This is the div that is assigned the id= 'app' -->
<div id='app'></div>

<script>
new Vue({
    ...
}).$mount('#app') //This is another way to mount Vue instance!
</script>
```

## Data and function in vue
The data property in a Vue instance is responsible for storing the variables for that particular instance. The accepted types are:
* String - Stores strings
* Number - Stores integers, floating point, and exponential notations
* Boolean - Stores ‘true’ or ‘false’
* Null - Represents null value
* Object - Stores a dictionary
* Array - Stores a list of variables
Variables are reference in the template using `{{}}`. For example, the following template renders the name in template with `{{name}}`
```javascript
new Vue({
  el: '#app',
  template:
  `<div>
    <h1> Vue.js Application </h1>
    <p> My name is {{name}}. See how my name is referenced from the data!</p>
  </div>
  `,
  data: {
      name: 'John'
  }
})
```

We can also call the function using `{{functionname()}}` inside template string. We can also access data in the function using `this`
```javascript
new Vue({
  el: '#app',
  template:
  `<div>
    <h1> Vue.js Application </h1>
    <p> My name is {{getMyName()}}. See how my name is retrived using a function!</p>
  </div>
  `,
  data: {
      name: 'John'
  },
  methods: {
    getMyName: function(){
      return this.name;
    }
  }
})
```

## Vue lifecycle
Every vue instance has 4 phases: 
1. create
2. mount
3. update
4. destory

And there are methods called lifecycle hooks that can perform certain tasks during those stages:
1. Creation hooks
`beforeCreate`
`created`
2. Mounting hooks
`beforeMount`
`mounted`
3. Updating hooks
`beforeUpdate`
`updated`
4. Destruction hooks
`beforeDestroy`
`destroyed`

```javascript
let myVM = new Vue({
  el: '#app',
  template:
  `<div>
    <h1>Vue.js Application</h1>
    <p> Please see the console below to view when each lifecycle hook is executed!</p>
    <h3> The instance will be destroyed after three seconds! So, destruction hooks will run later. </h3>
  </div>
  `,
  beforeCreate() {
    console.log('Events and lifecycle have been initialized');
  },
  created() {
    console.log('Vue instance have been created!');
  },
  beforeMount() {
    console.log('vm.$el has not been created yet.')
  },
  mounted() {
    console.log('vm.$el has been created and el has been replaced.')
  },
  beforeUpdate() {
    console.log('Virtual DOM has not re-rendered or patched yet');
  },
  updated() {
    console.log('Virtual DOM has re-rendered and patched.');
  },
  beforeDestroy() {
    console.log('Destroyed!!! Watchers and event listeners have not been teared down yet.');
  },
  destroyed() {
    console.log('Watchers and event listeners have been torn down');
  }
});

setTimeout(function() {
	myVM.$destroy();
}, 3000);
// Events and lifecycle have been initialized
// Vue instance have been created!
// vm.$el has not been created yet.
// vm.$el has been created and el has been replaced. 
// ... 3 SECONDS LATER ...
// Destroyed!!! Watchers and event listeners have not been teared down yet.
// Watchers and event listeners have been torn down
```