# Chapter 1: The Basics - Study Guide

## Cheatsheet

### 1. Program Structure

```cpp
#include <iostream>    // Include standard I/O library

int main() {           // Entry point - exactly one per program
    std::cout << "Hello, World!\n";
    return 0;          // Optional: 0 = success, non-zero = failure
}
```

### 2. Fundamental Types

| Type | Description | Example |
|------|-------------|---------|
| `bool` | Boolean | `true`, `false` |
| `char` | Character (typically 8-bit) | `'a'`, `'9'`, `'\n'` |
| `int` | Integer | `-273`, `42`, `1066` |
| `double` | Double-precision float | `3.14`, `6.626e-34` |
| `unsigned` | Non-negative integer | `0`, `1`, `999` |

```cpp
bool flag = true;
char letter = 'x';
int count = 42;
double pi = 3.14159;
unsigned bits = 0xFF;
```

### 3. Integer Literals

```cpp
int decimal = 42;          // Base 10
int binary = 0b101010;     // Base 2 (prefix 0b)
int octal = 052;           // Base 8 (prefix 0)
int hex = 0x2A;            // Base 16 (prefix 0x)

// Digit separators for readability
long big = 1'000'000'000;
double precise = 3.14159'26535'89793;
```

### 4. Initialization Styles

```cpp
// Traditional (C-style) - allows narrowing
double d1 = 2.3;
int i1 = 7.8;              // Silently becomes 7 (narrowing!)

// Brace initialization (preferred) - prevents narrowing
double d2 {2.3};
int i2 {7.8};              // ERROR: narrowing conversion

// Auto type deduction
auto b = true;             // bool
auto i = 123;              // int
auto d = 1.2;              // double
auto result = sqrt(2.0);   // type of sqrt's return
```

### 5. Operators

**Arithmetic:**
```cpp
x + y    // Addition
x - y    // Subtraction
x * y    // Multiplication
x / y    // Division
x % y    // Modulus (integers only)
+x       // Unary plus
-x       // Unary minus
```

**Comparison:**
```cpp
x == y   // Equal
x != y   // Not equal
x < y    // Less than
x > y    // Greater than
x <= y   // Less or equal
x >= y   // Greater or equal
```

**Logical:**
```cpp
x && y   // Logical AND
x || y   // Logical OR
!x       // Logical NOT
```

**Bitwise:**
```cpp
x & y    // Bitwise AND
x | y    // Bitwise OR
x ^ y    // Bitwise XOR
~x       // Bitwise complement
```

**Compound Assignment:**
```cpp
x += y   // x = x + y
x -= y   // x = x - y
x *= y   // x = x * y
x /= y   // x = x / y
x %= y   // x = x % y
++x      // Pre-increment
x++      // Post-increment
--x      // Pre-decrement
x--      // Post-decrement
```

### 6. Functions

```cpp
// Declaration (prototype)
double sqrt(double);
void print(int);
int* find(int[], int);

// Definition
double square(double x) {
    return x * x;
}

// void = no return value
void greet() {
    std::cout << "Hello\n";
}

// Function overloading (same name, different parameters)
void print(int i)    { std::cout << i; }
void print(double d) { std::cout << d; }
void print(string s) { std::cout << s; }
```

### 7. Constants

```cpp
// const: promise not to modify (can be runtime value)
const double sqv = sqrt(var);  // Computed at runtime
const int size = 100;

// constexpr: must be computed at compile time
constexpr int dmv = 17;
constexpr double pi = 3.14159;

// constexpr function
constexpr double square(double x) { return x * x; }
constexpr double area = square(5.0);  // Computed at compile time
```

### 8. Pointers

```cpp
int x = 10;
int* p = &x;      // p holds address of x
int y = *p;       // y = 10 (dereference p)

*p = 20;          // x is now 20
p = nullptr;      // Null pointer (no object)

// Arrays and pointers
char v[6];        // Array of 6 chars
char* ptr = &v[0]; // Points to first element
ptr = v;          // Same as above (array decays to pointer)
```

### 9. References

```cpp
int x = 10;
int& r = x;       // r refers to x (must be initialized)
r = 20;           // x is now 20

// Common use: function parameters
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// const reference: read-only access, no copy
void print(const std::vector<int>& v);
```

### 10. Control Flow

**If Statement:**
```cpp
if (condition) {
    // ...
} else if (other_condition) {
    // ...
} else {
    // ...
}

// Variable declaration in condition
if (auto n = v.size(); n > 0) {
    // n is in scope here
}

// Implicit test against 0/nullptr
if (auto n = v.size()) {  // true if n != 0
    // ...
}
```

**Switch Statement:**
```cpp
switch (value) {
    case 1:
        // ...
        break;
    case 2:
    case 3:       // Fall-through
        // ...
        break;
    default:
        // ...
}
```

**Loops:**
```cpp
// Traditional for
for (int i = 0; i < 10; ++i) {
    std::cout << i;
}

// Range-based for
int arr[] = {1, 2, 3, 4, 5};
for (auto x : arr) {           // Copy each element
    std::cout << x;
}
for (auto& x : arr) {          // Reference (can modify)
    x *= 2;
}
for (const auto& x : arr) {    // Const reference (read-only, no copy)
    std::cout << x;
}

// While
while (condition) {
    // ...
}
```

### 11. Scope Summary

| Scope | Description |
|-------|-------------|
| Local | Inside function/block, ends at `}` |
| Class | Inside class, outside functions |
| Namespace | Inside namespace |
| Global | Outside all constructs |

---

## Hands-On Exercises

### Exercise 1: Hello World Variations
Create a program that:
1. Prints your name
2. Prints a number
3. Prints a calculated result (e.g., the sum of two numbers)

### Exercise 2: Type Sizes
Write a program that prints the size (in bytes) of each fundamental type (`bool`, `char`, `int`, `double`, `unsigned`, `long`, `long long`) using `sizeof`.

### Exercise 3: Temperature Converter
Write a function `celsius_to_fahrenheit(double c)` that converts Celsius to Fahrenheit.
Formula: F = C * 9/5 + 32

Test it with 0°C and 100°C.

### Exercise 4: Swap Function
Implement a `swap` function using references that exchanges two integers. Test it by printing the values before and after swapping.

### Exercise 5: Array Sum
Write two functions that compute the sum of an integer array:
1. `sum_array(int arr[], int size)` - using index-based loop
2. `sum_array_ptr(int* arr, int size)` - using pointer arithmetic

Test both with the array `{1, 2, 3, 4, 5}`.

### Exercise 6: Count Character
Write a function `count_char(const char* str, char c)` that counts occurrences of character `c` in a null-terminated C-string.

Test cases:
- `count_char("hello world", 'l')` should return 3
- `count_char("hello world", 'o')` should return 2
- `count_char("hello world", 'z')` should return 0

### Exercise 7: constexpr Factorial
Write a `constexpr` function that computes factorial. Verify it works at compile time by using it to initialize a `constexpr` variable.

### Exercise 8: Function Overloading
Create three overloaded `max` functions that return the maximum of two values:
- One for `int`
- One for `double`
- One for `char`

Test each version.

### Exercise 9: Range-Based Modification
Write a program that:
1. Creates an array of 5 integers `{1, 2, 3, 4, 5}`
2. Uses a range-for loop with references to double each element
3. Prints the modified array using another range-for loop

### Exercise 10: Mini Calculator
Write a calculator that:
1. Reads two numbers and an operator (+, -, *, /) from standard input
2. Uses a switch statement to perform the operation
3. Prints the result
4. Handles division by zero and invalid operators

---

## Theory Questions

### Basic Understanding

1. What is the difference between a **declaration** and a **definition** in C++?

2. Explain why C++ requires exactly one `main()` function in a program.

3. What is the difference between `=` and `==` in C++?

4. Why does C++ distinguish between **signed** and **unsigned** integers? When should you use `unsigned`?

5. What happens when you assign a `double` to an `int`? Why is this called a "narrowing conversion"?

### Initialization

6. What are the three ways to initialize a variable in C++? Which one prevents narrowing conversions?

7. Why should you prefer `{}` initialization over `=` initialization?

8. When is it appropriate to use `auto` for type deduction? When should you avoid it?

9. Why should you "not introduce a name until you have a suitable value for it"?

### Constants

10. What is the difference between `const` and `constexpr`?

11. Can a `constexpr` function be called with runtime values? What happens?

12. Why would you want a value computed at compile time rather than runtime?

### Pointers and References

13. What is the difference between a **pointer** and a **reference**?

14. Why can't a reference be "reseated" (made to refer to a different object)?

15. What is `nullptr` and why should you use it instead of `0` or `NULL`?

16. Given `int x = 5; int* p = &x;`, what is the value of `*p`? What does `*p = 10;` do?

17. Why do we pass large objects by `const&` instead of by value?

### Functions

18. What is **function overloading**? How does the compiler decide which function to call?

19. When does an overloaded function call become **ambiguous**?

20. What does a `void` return type mean?

### Control Flow

21. What happens if no `case` matches in a `switch` statement and there is no `default`?

22. What is the purpose of `break` in a switch statement? What happens without it?

23. In the loop `for (auto& x : arr)`, why use `&`? What's the difference from `for (auto x : arr)`?

### Memory and Hardware

24. Explain the difference between **assignment** and **initialization** in terms of memory operations.

25. Why does "a reference cannot be null" while a pointer can be `nullptr`?

26. After `int x = 2; int y = 3; int& r = x; r = y;`, what are the values of `x`, `y`, and what does `r` refer to?

### Best Practices

27. Why does the chapter advise keeping functions short and focused on a single task?

28. What does "minimize the scope of a variable" mean and why is it important?

29. Why should you avoid "magic constants" and use named constants instead?

30. The advice says to prefer immutable data. Why is immutability a valuable design concern?

---
---
---

# SOLUTIONS AND ANSWERS

*Stop here if you haven't attempted the exercises and questions yet!*

---

## Exercise Solutions

### Exercise 1 Solution
```cpp
#include <iostream>

int main() {
    std::cout << "Alessandro\n";
    std::cout << 42 << "\n";
    std::cout << "Sum: " << 10 + 32 << "\n";
}
```

### Exercise 2 Solution
```cpp
#include <iostream>

int main() {
    std::cout << "Size of bool: " << sizeof(bool) << " bytes\n";
    std::cout << "Size of char: " << sizeof(char) << " bytes\n";
    std::cout << "Size of int: " << sizeof(int) << " bytes\n";
    std::cout << "Size of double: " << sizeof(double) << " bytes\n";
    std::cout << "Size of unsigned: " << sizeof(unsigned) << " bytes\n";
    std::cout << "Size of long: " << sizeof(long) << " bytes\n";
    std::cout << "Size of long long: " << sizeof(long long) << " bytes\n";
}
```

### Exercise 3 Solution
```cpp
#include <iostream>

double celsius_to_fahrenheit(double c) {
    return c * 9.0 / 5.0 + 32.0;
}

int main() {
    std::cout << "0C = " << celsius_to_fahrenheit(0) << "F\n";      // 32
    std::cout << "100C = " << celsius_to_fahrenheit(100) << "F\n";  // 212
}
```

### Exercise 4 Solution
```cpp
#include <iostream>

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int x = 5, y = 10;
    std::cout << "Before: x=" << x << ", y=" << y << "\n";
    swap(x, y);
    std::cout << "After: x=" << x << ", y=" << y << "\n";
}
```

### Exercise 5 Solution
```cpp
#include <iostream>

int sum_array(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum;
}

int sum_array_ptr(int* arr, int size) {
    int sum = 0;
    for (int* p = arr; p < arr + size; ++p) {
        sum += *p;
    }
    return sum;
}

int main() {
    int nums[] = {1, 2, 3, 4, 5};
    std::cout << "Sum: " << sum_array(nums, 5) << "\n";         // 15
    std::cout << "Sum (ptr): " << sum_array_ptr(nums, 5) << "\n"; // 15
}
```

### Exercise 6 Solution
```cpp
#include <iostream>

int count_char(const char* str, char c) {
    if (str == nullptr) return 0;

    int count = 0;
    while (*str) {
        if (*str == c) ++count;
        ++str;
    }
    return count;
}

int main() {
    std::cout << count_char("hello world", 'l') << "\n";  // 3
    std::cout << count_char("hello world", 'o') << "\n";  // 2
    std::cout << count_char("hello world", 'z') << "\n";  // 0
}
```

### Exercise 7 Solution
```cpp
#include <iostream>

constexpr int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    constexpr int f5 = factorial(5);  // Computed at compile time
    std::cout << "5! = " << f5 << "\n";  // 120

    int x = 6;
    int f6 = factorial(x);  // Computed at runtime
    std::cout << "6! = " << f6 << "\n";  // 720
}
```

### Exercise 8 Solution
```cpp
#include <iostream>

int max(int a, int b) {
    return (a > b) ? a : b;
}

double max(double a, double b) {
    return (a > b) ? a : b;
}

char max(char a, char b) {
    return (a > b) ? a : b;
}

int main() {
    std::cout << max(3, 7) << "\n";        // 7
    std::cout << max(3.14, 2.71) << "\n";  // 3.14
    std::cout << max('a', 'z') << "\n";    // z
}
```

### Exercise 9 Solution
```cpp
#include <iostream>

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    // Double each element
    for (auto& x : arr) {
        x *= 2;
    }

    // Print the result
    for (auto x : arr) {
        std::cout << x << " ";
    }
    std::cout << "\n";  // Output: 2 4 6 8 10
}
```

### Exercise 10 Solution
```cpp
#include <iostream>

int main() {
    double a, b;
    char op;

    std::cout << "Enter: number operator number\n";
    std::cin >> a >> op >> b;

    switch (op) {
        case '+':
            std::cout << a + b << "\n";
            break;
        case '-':
            std::cout << a - b << "\n";
            break;
        case '*':
            std::cout << a * b << "\n";
            break;
        case '/':
            if (b == 0) {
                std::cout << "Error: division by zero\n";
            } else {
                std::cout << a / b << "\n";
            }
            break;
        default:
            std::cout << "Error: unknown operator\n";
    }
}
```

---

## Theory Answers

### Basic Understanding

**1.** A **declaration** introduces a name and its type to the compiler (e.g., `int foo();`). A **definition** provides the complete implementation or allocates storage (e.g., `int foo() { return 42; }`). Every definition is a declaration, but not every declaration is a definition.

**2.** `main()` is the program's entry point - where execution begins. The operating system calls this function to start the program. Having exactly one ensures there's an unambiguous starting point.

**3.** `=` is the **assignment operator** - it assigns a value to a variable. `==` is the **equality comparison operator** - it tests if two values are equal and returns a boolean.

**4.** Signed integers can represent negative numbers; unsigned cannot but can represent larger positive values. Use `unsigned` primarily for **bit manipulation** operations, not for "non-negative" values, as mixing signed/unsigned can cause subtle bugs.

**5.** The fractional part is truncated (e.g., `7.8` becomes `7`). It's called "narrowing" because information (the decimal portion) is lost - the destination type cannot represent the full source value.

### Initialization

**6.** Three ways: `int x = 5;` (copy), `int x(5);` (direct), `int x{5};` (brace/uniform). **Brace initialization** `{}` prevents narrowing conversions.

**7.** Brace initialization prevents accidental narrowing conversions (compiler error instead of silent truncation), works uniformly for all types, and prevents the "most vexing parse" problem.

**8.** Use `auto` when: the type is obvious from the initializer, type names are long/complex, or in generic code. Avoid when: you want to be explicit about precision (e.g., `double` vs `float`), or in large scopes where type clarity aids readability.

**9.** Uninitialized variables contain garbage values, leading to undefined behavior. Delaying declaration until initialization ensures the variable always has a valid state and reduces the scope where it might be misused.

### Constants

**10.** `const` means "I promise not to modify this" - the value can be computed at runtime. `constexpr` means "evaluate at compile time" - the value must be computable by the compiler. `constexpr` enables compile-time computation and can be used in contexts requiring constant expressions.

**11.** Yes, a `constexpr` function can be called with runtime values. When called with runtime values, it executes at runtime like a normal function. Only when all arguments are constant expressions can the result be used as a constant expression.

**12.** Benefits: no runtime cost, enables use in array sizes/template arguments/case labels, allows placement in read-only memory (protection from corruption), and catches errors earlier (at compile time).

### Pointers and References

**13.** A **pointer** holds a memory address, can be reassigned, can be null, requires `*` to dereference, and can be uninitialized. A **reference** is an alias for an existing object, must be initialized at declaration, cannot be null, cannot be reseated, and implicitly dereferences.

**14.** References are designed to be aliases - once bound, they ARE the object they refer to. This semantic simplicity (no need to check for null, no rebinding) makes code clearer and safer. Assignment to a reference assigns to the referent, not the reference itself.

**15.** `nullptr` is a type-safe null pointer constant of type `std::nullptr_t`. Unlike `0` or `NULL`, it cannot be implicitly converted to integers, preventing bugs where a null pointer is accidentally used as a number.

**16.** `*p` is `5` (the value `p` points to). `*p = 10;` writes `10` to the location `p` points to, so `x` becomes `10`.

**17.** Pass by value copies the entire object (expensive for large objects). `const&` passes a reference (cheap - just an address) while preventing modification, giving both efficiency and safety.

### Functions

**18.** Function overloading allows multiple functions with the same name but different parameter types/counts. The compiler uses **overload resolution** - it examines the argument types at the call site and selects the function whose parameters best match.

**19.** When two or more overloads match equally well and the compiler cannot determine which is "better". Example: `print(int,double)` and `print(double,int)` are ambiguous when called with `print(0,0)`.

**20.** `void` indicates the function returns no value. It performs an action but doesn't produce a result to use in expressions.

### Control Flow

**21.** No action is taken - execution continues after the switch statement. This can be a bug if a case was expected to match.

**22.** `break` exits the switch statement. Without it, execution "falls through" to the next case's code, which is occasionally intentional but often a bug.

**23.** `auto& x` makes `x` a reference to each element, allowing modification. `auto x` copies each element - modifications affect only the copy, not the original array.

### Memory and Hardware

**24.** **Initialization** creates a new object and gives it its first value - the memory location transitions from uninitialized to valid. **Assignment** changes the value of an already-valid object - it requires the object to already exist and have a value.

**25.** A reference must be initialized when declared and cannot be rebound - there's no syntax to create an "empty" reference. Pointers are variables that hold addresses, and `nullptr` is a valid address value meaning "points to nothing."

**26.** `x = 3`, `y = 3`, and `r` still refers to `x`. The line `r = y` assigns `y`'s value (3) through the reference to `x`. It does NOT rebind `r` to refer to `y`.

### Best Practices

**27.** Short, focused functions are: easier to understand, easier to test, more reusable, less error-prone, easier to name meaningfully, and easier to maintain. The number of errors correlates with code length and complexity.

**28.** Keep variables in the smallest scope where they're needed. Benefits: reduces cognitive load (fewer things to track), prevents accidental misuse, makes code easier to refactor, and the compiler can optimize better.

**29.** Magic constants (like `52` or `3.14159`) are unclear - readers don't know what they represent. Named constants (like `CARDS_PER_DECK` or `PI`) document intent, enable easy updates in one place, and catch typos at compile time.

**30.** Immutable data: can be safely shared between threads without locks, makes program state easier to reason about, prevents accidental modification bugs, can be optimized by the compiler, and enables referential transparency (same input = same output).
