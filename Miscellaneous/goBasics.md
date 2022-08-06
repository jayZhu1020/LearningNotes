# Go Programming

## Packages, Variables and functions

### Variables and Typing
Go supports both predefined typing and inferred typing
Go inferrs with the following rule:
1. If only digits and no decimal point is given, then infer the type to be `int`
2. If a decimal point is present and no letter `i` is presents, then infer the type to be `float64`
3. If `i` is present, then infer the type to be `complex128`
```go
// Declare lists of variables with certain type
var (
    name, location string
    age int
)

// Declare lists of variable with initial values
var (
    name = "John"
    age = 32
    id, location = 100, "New York"
)

// Declare variables one by one
var name string
var age int
var location string

// Declare variables inferred from initializer
name := "Elon Musk"
age := 32
```
Go supports the following types:
```go
bool

string

int  int8  int16  int32  int64
uint uint8 uint16 uint32 uint64 uintptr

byte // alias for uint8

rune // alias for int32
     // represents a Unicode code point

float32 float64

complex64 complex128
```
If no initializer is assigned to a variable, go will initialize the variablee with zero values:
1. `0` for numeric types,
2. `false` for the boolean type, and
3. `""` (the empty string) for strings.

### Constants
Go declares constant with `const` keywords. constants cannot be declared with `:=`
```go
// Declare constants
const Pi = 3.14
const ID = 100

// Declare lists of Constants
const (
    op1 = 0
    op2 = 1
    op3 = 2
)
```

### Printing
To print message to the console, use `fmt` library. Common format symbols are:
1. `%s`: placeholder for string
2. `%d`: placeholder for int
3. `%t`: placeholder for boolean
4. `%f`: placeholder for float
5. `%w.pf`: placeholder for float with with width `w` and precision `p`

```go
package main

import "fmt"

func main() {
    msg := "Hello World"
    name := "User"
    // print variables with new line
    fmt.Println(msg)
    // print variables without new line
    fmt.Print(msg)
    // print formatted message
    fmt.Printf("%s %s!", msg, name)

    var age int
    var salary float
    // read input from stdin with format
    n, err := fmt.Scanf("%d %f", &age, &salary)

    // format a string
    s := fmt.Sprintf("%s %s", msg, name)

    // read from a formatted string
    ins := "18 200.6"
    fmt.Sscanf(ins, "%d %f", &age, &salary)
}
```

### Packages and Imports
1. All Go code **MUST** belong to a package. So the first line of a Go codee **MUST** start with `package [pkgname]`. This tells Go compiler that the current code belongs to `pkgname`. Functions within the same package can be directly called.
2. In Go, all functions and variables in a package can only be accessed by the same package unless the the name is **Capitalized**.
3. We can import other packages by `import "[module_name/package_name]"`. If the package is a built-in package, we can directly call `import "[package_name]"` otherwise we need to specify the `module_name`. 

### Functions
```go
// general syntax for defining a function
func funName(var1 type1, ... , varN typeN) (return1 type1, ..., returnM typeM) {
    // function body
}
/*
 1. It's optional to specify the return variables' name. If not specified, must explicitly indicate which values to return
 2. when two or more consecutive input and output variables have the same type, can write the name together then declare the type
*/


// example:
func add(x int, y int) int {
    return x + y
}

func add(x int, y int) (s int) {
    s = x + y
    return
}

func add_and_max(x, y int) (s, m int) {
    return x + y, math.Max(x,y)
}

// viriadic function parameters
func sum(values ...int) int {
    result := 0
    for _, v := range values {
        result += v
    }
    return result
}
```

The return value can be a stack variable. Compiler will; make sure the value returned is stored on heap
```go
func sum(values ...int) *int {
    result := 0
    for _, v := range values {
        result += v
    }
    return &result // go will make sure result is stored on heap
}
```

### Type conversion
The expression `T(v)` converts the value `v` to the type `T`.
```go
// declare an integer with value 42
var i int = 42
// convert to a float
var f float64 = float64(i)
// convert to a unsigned int
var u uint = unit(f)

// Alternative syntax:
i := 42
f := float64(i)
u := unit(f)
```

## Control Flow

### For
Go has **only one** looping construct, the for loop.

The basic for loop has three components separated by semicolons:

1. the **init** statement: executed before the first iteration
2. the **condition** expression: evaluated before every iteration
3. the **post** statement: executed at the end of every iteration

The init statement will often be a short variable declaration, and the variables declared there are visible **only in the scope of the `for` statement**.

```go
// loop n times
for i := 0; i < n; i++ {
   // Do something
}

// eliminating the init and post expression creates an while loop with for:
for condition {
    // Do something until the condition is not met
}

// create an infinite loop
for {
    // Do something
}

```

### If Else
The if statement can start with a short statement to execute before the condition.

Variables declared by the statement are **only in scope until the end of the `if`**.

```go
// If statement
if condition {
    // Do something
}

// if with a temporary variable
if v = expression(); conditon(v) {

} 

// if and else if and else
if condition1 {
    // Do something when condition1 is true
} else if condition2 {
    // Do something when condition2 is true
} else {
    // Otherwise do something
}
```
### Switch
Switch cases evaluate cases from top to bottom, **stopping when a case succeeds**. Note that this means that there is a break statement at the end of each case

Switch without a condition is the same as switch true. This construct can be a clean way to write long if-then-else chains.
```go
// Normal switch statement
switch variable {
    case val1:
        // Do something when variable == val1
    case val2:
        // Do something when variable == val2
    default:
        // in all other cases do something
}

// Switch with no condition
switch {
    case condition1:
        // Do something when condition 1 is true
    case condition2:
        // Do something when condition 2 is true
    case condition3:
        // Do something when condition 3 is true
    default
        // In all other cases do something
}
```

### Defer
A defer statement defers the execution of a function until the surrounding function returns.

The deferred call's arguments **are evaluated immediately**, but the function call is not executed until the surrounding function returns.
```go
package main

import "fmt"

func main() {
	defer fmt.Println("world")

	fmt.Println("hello")
}
// This code prints hello world
```
Deferred function calls are pushed onto a stack. When a function returns, its deferred calls are executed in last-in-first-out order.
```go
package main

import "fmt"

func main() {
	fmt.Println("counting")

	for i := 0; i < 10; i++ {
		defer fmt.Print(i)
	}

	fmt.Println("done")
}
// This code prints 9876543210
```

## Struct Slices and Maps

### Pointers
Go has pointers. A pointer holds the memory address of a value.

The type `*T` is a **pointer** to a `T` value. Its zero value is `nil`. 

The `&` operator generates a pointer to its operand.

The `*` operator denotes the pointer's underlying value.

Unlike C++, Go does not support pointer arithmetic. One way to utalize pointer is to specify pass variables by value or reference in a function
```go
package main

import "fmt"

// function that pass by value
func value_increment(a int) {
    a++
    return
}

// function that pass by reference
func reference_increment(a *int) {
    a++
    return
}

func main() {
    a := 1
    fmt.Println("Before:", a,"After passing by value:" value_increment(a))
    fmt.Println("Before:", a,"After passing by value:" reference_increment(&a))
    
}
```
### Structs
A struct is a collection of fields.
```go
// Define a struct
type StructName struct {
    var1 type1
    var2 type2
}

// example:
type Coord struct {
    X int
    Y int
}

func main() {
    // initialize a Coord instance
    v := Coord{1, 2}
    // modify its field
    v.X = 3
    // retrieve the pointer to v
    p := &v
    // retrievs the field value, note that *p is not needed
    p.X
    // construct just a subset of fields by using the fieldName:val syntax.
    v := Coord{X:1} // y is implicity set to 0
}
```

### Arrays
The type `[n]T` is an array of `n` values of type `T`.

An array's length is part of its type, so arrays cannot be resized. 
```go
package main

import "fmt"

func main () {
    // declares an array of 10 ints, initialized to 0
    var arr [10]int
    // declares an array of initialized elemenbts
    arr := [6]int{2,3,5,7,11,13}
    // modify the n-th element
    arr[n] = 5
    // access the n-th element
    fmt.Println(arr[n])
}
```

### Slices
An array has a fixed size. A slice, on the other hand, is a **dynamically-sized**, flexible view into the elements of an array. In practice, slices are much more common than arrays.

The type `[]T` is a slice with elements of type `T`.

A slice can be formed by slicing an array specifying two indices, a low and high bound, separated by a colon:
`a[low:high]`
This selects a half-open range which includes the first element, but excludes the last one from an array.

A slice does not store any data, it just describes a section of an underlying array.

Changing the elements of a slice modifies the corresponding elements of its underlying array.

Other slices that share the same underlying array will see those changes.
```go
/* slice creation and modification*/
// declare empty slice, it will be evaluated to nil
var slice []int

// declare a slice with initialized values, by default the length and capacity equals the length of the initializer
slice := []int{1,2,3,4,5}

// construct a slice from part of an array, note that they share the same underlying memory
arrayslice := arr[0:4]

// accessing elements
slice[i]

// retrieve the length of the slice
len(slice)

// retrieve the capacity of the slice
cap(slice)

// creating a slice of l elements
s1 := make([]int, l)

// creating a slice of length l and capacity c
s2 := make([]int, l, c)

// creating a nested slice
ss := [][]int{
    []int{1,2,3},
    []int{4,5,6},
    []int{7,8,9}
}

// append to a slice
append(slice, 0)

// append multiple elements to slice
append(slice, 1, 2, 3, 4, 5)

/* iterate through the slice */
// iterate with index and value 
for i, v := range slice {
    // Do Something
}

// iterate only with index
for i := range slice {
    // Do Something
}
```

### Maps
A map is a datastructure that maps keys to values
The zero value of map is `nil`, where no key exists and no keys can be added. We can use `make()` function to modify the maps.
```go
// create an empty int, string map, this will be evaluated to nil
var m map[int]string

// initialize the map with make
m = make(map[int]string)

// initialize the map with initializer
m := map[int]string{
    1 : "one",
    2 : "two",
    3 : "three",
}

// iniialize the map with structs as values
type Coord struct {
    X int
    Y int
}

m := map[int]Coord {
    1 : Coord{1,2},
    2 : Coord{3,4},
}

m := map[int]Coord { // can omit Coord type name
    1 : {1,2},
    2 : {3,4},
}

// insert or update
m[key] = new_value

// retrieve an element
var value = m[key]

// delete an element
delete(m, key)

// test if a key is present,
// if key in map, ok is true and value is the coorresponding value
// otherwise ok is false and value is the zero value of the value type 
value, ok = m[key]
```

### Function as values
Functions are values too. They can be passed around just like other values.

Function values may be used as function arguments and return values.

```go
package main

import (
	"fmt"
	"math"
)

func compute(fn func(float64, float64) float64) float64 {
	return fn(3, 4)
}

func main() {
	hypot := func(x, y float64) float64 {
		return math.Sqrt(x*x + y*y)
	}
	fmt.Println(hypot(5, 12))

	fmt.Println(compute(hypot))
	fmt.Println(compute(math.Pow))
}
```

### Function closures
Go functions may be **closures**. A closure is a function value that references variables from outside its body. The function may access and assign to the referenced variables; in this sense the function is "bound" to the variables. We can think of function closure as a function that returns a function
```go
package main

import "fmt"

func adder() func(int) int {
	sum := 0
	return func(x int) int {
		sum += x
		return sum
	}
}

// define two adders that achieve same functionality but different parameters
func main() {
	pos, neg := adder(), adder()
	for i := 0; i < 10; i++ {
		fmt.Println(
			pos(i),
			neg(-2*i),
		)
	}
}
```

## Methods and Interfaces
### Methods
A method is a function with a special **receiver argument**.

You can declare methods with pointer receivers. This means the receiver type has the literal syntax *T for some type T.

Methods with pointer receivers can modify the value to which the receiver points (as Scale does here). Since methods often need to modify their receiver, pointer receivers are more common than value receivers.

When the method takes a pointer receiver, we can call the method on either a pointer or the object itself. I.e.
```
v.method() is equivalent to (&v).method()
```
Note that this is not true when the method takes the object as a parameter but not a receiver, i.e.
```
method(v) is NOT equivalent to method(&v)
```

Syntax:
```go
// with copy receiver
func (receiver, receiverType) funcname(input1 inputtype1, ..., inputN inputtypeN) (return1 returntype1, ..., returnM reeturntypeM) {
    // Do something 
}

// with poitner receiver
func (receiver, *receiverType) funcname(input1 inputtype1, ..., inputN inputtypeN) (return1 returntype1, ..., returnM reeturntypeM) {
    // Do something 
}
```
```go
// example:
package main

import (
	"fmt"
	"math"
)

type Vertex struct {
	X, Y float64
}

// a copy receiver function that returns the norm of the Vertex struct
func (v Vertex) Abs() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

// a pointer receiver function that modifies the field of the Vertex strct
func (v *Vertex) Scale(f float64) {
	v.X = v.X * f
	v.Y = v.Y * f
}

func main() {
	v := Vertex{3, 4}
	v.Scale(10)
    // these two lines are equivalent to the one above
    // p := &v 
    // p.Scale(10) 
	fmt.Println(v.Abs())
}
```

You can declare a method on non-struct types

You can only declare a method with a receiver whose type is defined **in the same package** as the method. 

You cannot declare a method with a receiver whose type is defined in another package or built in types.

```go
package main

import (
	"fmt"
	"math"
)

// non-struct type
type MyFloat float64

func (f MyFloat) Abs() float64 {
	if f < 0 {
		return float64(-f)
	}
	return float64(f)
}

func main() {
	f := MyFloat(-math.Sqrt2)
	fmt.Println(f.Abs())
}
```

### Interface
An **interface type** is defined as a set of method signatures.

A value of interface type can hold any value that implements those methods.

In general, all methods on a given type should have **either value or pointer receivers**, but not a mixture of both. 

Syntax:
```go
type InterfaceName interface {
    method1(arg type, ..., arg type) (ret type, ..., ret type)
    method2(arg type, ..., arg type) (ret type, ..., ret type)
}
```
If a type implements all functions specified by the interface, it will be considered as a type of that interface. The interface are implemented implicitly.

A nil interface value holds neither value nor concrete type. Calling a method on a object with nil interface value will be an runtime error.
```go
package main

import "fmt"

type I interface {
	M()
}

func (i *I) M() {
	if i == nil {
		fmt.Printf("<nil>")
		return
	}
	fmt.Printf("valid")
}

func main() {
	var i I // i is a nil interface in this case
	describe(i)
	i.M()
    i = nil // i is NOT a nil interface! It holds value nil
    i.M() // this will trigger a nullpointer dereference error
}

func describe(i I) {
	fmt.Printf("(%v, %T)\n", i, i)
}
```
The interface type that specifies zero methods is known as the empty interface `interface{}`.

An empty interface may hold values of any type. (Every type implements at least zero methods.)
```go
package main

import "fmt"

func main() {
	var i interface{}
	describe(i) // prints (<nil>,<nil>)

	i = 42
	describe(i) // prints (42,int)

	i = "hello"
	describe(i) // prirnts (hello, string)
}

func describe(i interface{}) {
	fmt.Printf("(%v, %T)\n", i, i)
}
```

Interfaces can be composed. We can do it by simply defining a new interface
```go
type Writer interface {
    Write([]byte) (int error)
}

type Closer interface {
    Close() error
}
// a composed interface that should implement both Write and Close methods
type WriterCloser interface {
    Writer
    Closer
}
```
### Type assertion and Type switches
A type assertion provides access to an interface value's underlying concrete value.

```go
t := i.(T)
```
This statement asserts that the interface value `i` holds the concrete type `T` and assigns the underlying `T` value to the variable `t`.

If i does not hold a `T`, the statement will trigger a panic.

To test whether an interface value holds a specific type, a type assertion can return two values: the underlying value and a boolean value that reports whether the assertion succeeded.
```go
t, ok := i.(T)
```
If `i` holds a `T`, then `t` will be the underlying value and ok will be true.

If not, ok will be false and t will be the zero value of type `T`, and no panic occurs.
A type switch is a construct that permits several type assertions in series.

A type switch is like a regular switch statement, but the cases in a type switch specify types (not values), and those values are compared against the type of the value held by the given interface value.
```go
switch v := i.(type) {
case T:
    // here v has type T
case S:
    // here v has type S
default:
    // no match; here v has the same type as i
}
```
The declaration in a type switch has the same syntax as a type assertion i.(T), but the specific type T is replaced with the keyword type.

### Stringer Interface
In the `fmt` package, a `Stringer` interface is defined
```go
type Stringer interface {
    String() string
}
```
A `Stringer` is a type that can describe itself as a string. The fmt package (and many others) look for this interface to print values. Therefore, when we want to print some class or give some class a string representation, we should write a `String()` method for it so we have the desired output.
```go
package main

import "fmt"

type Person struct {
	Name string
	Age  int
}
// Define the String() method so the fmt package will display the class as a Stringer, note that it has to be a value receiver
func (p Person) String() string {
	return fmt.Sprintf("%v (%v years)", p.Name, p.Age)
}

func main() {
	a := Person{"Arthur Dent", 42}
	z := Person{"Zaphod Beeblebrox", 9001}
	fmt.Println(a, z)
}
```
### Error interface
Similar to `Stringer`, `error` is a interface that allows us to customize error
```go
type error interface {
    Error() string
}
```
Functions often return an error value, and calling code should handle errors by testing whether the error equals nil.
```go
i, err := strconv.Atoi("42")
if err != nil {
    fmt.Printf("couldn't convert number: %v\n", err)
    return
}
fmt.Println("Converted integer:", i)
A nil error denotes success; a non-nil error denotes failure.
```
Example:
```go
// Write custom error for negative input on squrt
package main

import (
	"math"
	"fmt"
)

type ErrNegativeSqrt float64 

func (e ErrNegativeSqrt) Error() string {
	return fmt.Sprintf("cannot Sqrt negative number: %v", float64(e))
}

func Sqrt(x float64) (float64, error) {
	if x < 0 {
		return 0, ErrNegativeSqrt(x)
	}
	return math.Sqrt(x), nil
}

func main() {
	fmt.Println(Sqrt(2))
	fmt.Println(Sqrt(-2))
}
```
## Generics 

### FOR FUTURE

## Concurrency

### Goroutines
A goroutine is a lightweight thread managed by the Go runtime.
```go
go f(x, y, z)
```
starts a new goroutine running
```
f(x, y, z)
```
The evaluation of `f`, `x`, `y`, and `z` happens in the current goroutine and the execution of `f` happens in the new goroutine.

### Channels
Channels are a typed conduit through which you can send and receive values with the channel operator, `<-`.
```go
ch <- v    // Send v to channel ch.
v := <-ch  // Receive from ch, and
           // assign value to v.
```
(The data flows in the direction of the arrow.)

Like maps and slices, channels must be created before use:
```go
ch := make(chan int)
```
By default, sends and receives **block until the other side is ready**. This allows goroutines to synchronize without explicit locks or condition variables.

Channels can be buffered. Provide the buffer length as the second argument to make to initialize a buffered channel:
```go
ch := make(chan int, 100)
```
Sends to a buffered channel block only when the buffer is full. Receives block when the buffer is empty.

A sender can close a channel to indicate that no more values will be sent. Receivers can test whether a channel has been closed by assigning a second parameter to the receive expression: after
```go
v, ok := <-ch
```
`ok` is false if there are no more values to receive and the channel is closed.

The loop `for i := range c` receives values from the channel repeatedly until it is closed.

Note: Only the sender should close a channel, never the receiver. Sending on a closed channel will cause a panic.

Another note: Channels aren't like files; you don't usually need to close them. Closing is only necessary when the receiver must be told there are no more values coming, such as to terminate a range loop.

Example:
```go
package main

import (
	"fmt"
)

// sender keep pumping to the channel with fib sequences, after it is done, close the channel
func fibonacci(n int, c chan int) {
	x, y := 0, 1
	for i := 0; i < n; i++ {
		c <- x
		x, y = y, x+y
	}
	close(c)
}

// receiver keep receiving from the channel using for loop. The loop will terminate when close(c) is called in the fibonacci() function
func main() {
	c := make(chan int, 10)
	go fibonacci(cap(c), c)
	for i := range c {
		fmt.Println(i)
	}
}
```
### Select
The `select` statement lets a goroutine wait on multiple communication operations.

A `select` **blocks until one of its cases can run**, then it executes that case. It chooses one at random if multiple are ready.

```go
package main

import "fmt"

func fibonacci(c, quit chan int) {
	x, y := 0, 1
	for {
		select {
     // send x to the channel and iteratively compute new values
		case c <- x:
			x, y = y, x+y
     // when receive the quit signal from the channel, stop computing
		case <-quit:
			fmt.Println("quit")
			return
		}
	}
}

func main() {
	c := make(chan int)
	quit := make(chan int)
	go func() {
		for i := 0; i < 10; i++ {
			fmt.Println(<-c)
		}
		quit <- 0
	}()
	fibonacci(c, quit)
}
```

A `nil` chanel will block the select statement forever. The following code results in a deadlock

```go
package main

import (
	"fmt"
)

func main() {
	channel1 := make(chan string)
	channel1 = nil // a nil channel

	select {
	case message1 := <-channel1:
		fmt.Println(message1)
	}
}
```

One way to resolve is to add a default selection to allow it to exit
```go
package main

import (
	"fmt"
)

func main() {
	channel1 := make(chan string)
	channel1 = nil

	select {
	case message1 := <-channel1:
		fmt.Println(message1)
	default:
        fmt.Println("No channel is ready")
    }
}
```

### `sync` Package

#### `Waitgroup`
A `WaitGroup` blocks a program and waits for a set of goroutines to finish before moving to the next steps of execution.

We can use WaitGroups through the following functions:

`.Add(int)`: This function takes in an integer value which is essentially the number of goroutines which the waitgroup has to wait for. This function must be called before we execute a goroutine.
`.Done()`: This function is called within the goroutine to signal that the goroutine has successfully executed.
`.Wait()`: This function blocks the program until all the goroutines specified by `Add()` have invoked `Done()` from within.

#### `Mutex`
A `Mutex`, or a mutual exclusion prevents other processes from entering a critical section of data while a process occupies it.

We import mutex from the sync package in Go. sync.mutex has two methods:

`.Lock()` : acquires/holds the lock
`.Unlock()`: releases the lock

A `RWMutex` stands for Reader/Writer mutual exclusion and is essentially the same as Mutex, but it gives the lock to multiple reading processs or just one writing process.

#### `Pool`
TO BE LEARNT

#### `Once`
TO BE LEARNT

#### `Cond`
TO BE LEARNT

### `runtime` package
runtime package provides functions to specify how many CPUs we can use in the current machine and how man CPUs it is currently using.

TO BE LEARNT IN THE FUTURE

### 