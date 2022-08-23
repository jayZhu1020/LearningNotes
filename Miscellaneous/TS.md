# Typescript
## Intro to Typescript
Typescript are transpiled into javscript to provide better typing support.

When declaring variables in Typescript, Typescript makes sure that the variable with the same name has to have the same type no matter it is declared with `var`, `let` or `const`. Always use `let` or `const` instead of `var`.


## Ambient declaration
Ambient declaration starts with `declare` that tells the transpiler that a variable will exist some where
```typescript
declare let variableDefinedSomewhereElse: number; 

declare let $: JQuery;

declare function ambientFunction(i: number):void;
```

## Define a typed variable:
```typescript
let initializedVarName : type = value;

let uninitializedVarName : type;
```
typescript can also automatically infer the variable types if no typing is specified
```typescript
let inferredVar = 5; // TS infers the value to be a number
```
However, types aren't inferred with variables declared with `const` sicne they are not expected to be changed in the future code. 

We can access the type of a variable using `typeof`
```typescript
let int : number = 1;
console.log(typeof(int))
```
In TS, `NaN` value is also of number type.

Another type is `boolean` that strictly takes only two values: `true` or `false`
```typescript
let b : boolean = true;
```
Any other assignment to such value will results in an error, for example:
```typescript
let b : boolean = 0; // ERROR!
let b : boolean = "OK"; // ERROR!
```
we can convert values to boolean with `Boolean`
```typescript
let b = Boolean("");
let c = Boolean(5);
```
Note that we should not use `new` to perform conversion, since otherwise we will have a Boolean class instead

## `any`
Typescript supports type `any`. However, it should be avoided as much as possible. 

When an object is defined as type `any`, we can access any non-existing property of it, and JS will return `undefined`. But when we specify its type, we accessing its non-existing property will result in an error.
```typescript
let x : any = 123;
console.log(x.length) // -> undefined
let y : number = 123;
console.log(x.length) // -> ERROR!
```

## `void`
Typescript supports type `void`. It can't hold any data, it can only be `undefined` or `null`.
```typescript
let whatCanIHold: void;
whatCanIHold = undefined; // OK
whatCanIHold = null; // OK
whatCanIHold = "something"; // ERROR!
```

`void` is most useful as the return type of funtions
```typescript
function logMessage(message: string): void {
  console.log(message);
}
```

## array type and `readonly`
If want to declare an type for an array, there are two syntaxes we can use:
```typescript
// syntax 1
let a : type[] = [...];

// syntax 2
let a : Array<type> = [...];

// declare a number array
let arr : number[] = [1,2,3];
let arr : Arrray<number> = [1,2,3];
```
If we want an array to be free from modification such as `push` `shift` `unshift` or `arr[i]=v`, use `readonly` keyword or declare as a `ReadonlyArray`
```javascript
let arr : readonly number[] = [1,2];
let arr : ReadonlyArray<number> = [1,2];
```

