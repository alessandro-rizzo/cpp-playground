# Chapter 2: User-Defined Types - Study Guide

## Summary

### 2.1 Introduction
Chapter 2 introduces the concept of **user-defined types** in C++. While C++ provides rich built-in types that directly reflect hardware capabilities, they are deliberately low-level. C++ allows programmers to build higher-level abstractions through **classes** and **enumerations**.

Key points:
- User-defined types are built from fundamental types, const modifier, and declarator operators
- They provide better abstraction, easier use, less error-prone code, and often equal or better performance
- Types include: structures, classes, unions, and enumerations

### 2.2 Structures
**Structures (`struct`)** organize related data elements into a single unit.

Example:
```cpp
struct Vector {
    int sz;           // number of elements
    double* elem;     // pointer to elements
};
```

Key concepts:
- Access members using `.` (dot) for objects/references
- Access members using `->` for pointers
- Structures can have initialization functions
- Memory allocation with `new` operator (free store/heap)
- Memory deallocation with `delete` operator

### 2.3 Classes
**Classes** provide encapsulation by separating interface (public) from implementation (private).

```cpp
class Vector {
public:
    Vector(int s) : elem{new double[s]}, sz{s} { }  // constructor
    double& operator[](int i) { return elem[i]; }    // subscript operator
    int size() { return sz; }
private:
    double* elem;
    int sz;
};
```

Key concepts:
- **Constructors**: Special member functions that initialize objects (same name as class)
- **Member initializer lists**: Initialize members in constructor (`: elem{...}, sz{...}`)
- **Public members**: Define the interface accessible to all users
- **Private members**: Implementation details, only accessible within the class
- **Operator overloading**: Define custom behavior for operators (e.g., `operator[]`)
- `struct` vs `class`: Only difference is default access (public vs private)

### 2.4 Unions
**Unions** store multiple members at the same memory location, holding only one value at a time.

```cpp
union Value {
    Node* p;
    int i;
};
```

Key concepts:
- All members share the same address
- Size equals the largest member
- Programmer must track which member is active
- "Naked" unions are error-prone
- **`std::variant`**: Modern, safer alternative to unions

```cpp
variant<Node*, int> v;  // holds either Node* or int
if (holds_alternative<int>(v))
    cout << get<int>(v);
```

### 2.5 Enumerations
**Enumerations** represent small sets of named integer constants.

```cpp
enum class Color { red, blue, green };
Color col = Color::red;
```

Key concepts:
- **`enum class`** (scoped enums): Strongly typed, scoped enumerators
- Prevents accidental mixing of different enum types
- No implicit conversion to/from int
- Can define custom operators for enums
- **Plain `enum`**: Legacy style, enumerators in outer scope, implicit int conversion
- Default values start at 0 and increment by 1

### 2.6 Best Practices
1. Prefer user-defined types over built-in types for higher-level abstractions
2. Organize related data into structures
3. Use classes to separate interface from implementation
4. Define constructors to guarantee initialization
5. Avoid naked unions; use `std::variant` instead
6. Use `enum class` for named constants
7. Prefer `enum class` over plain `enum`

---

## Coding Exercises

### Exercise 1: Basic Structure
Create a `Rectangle` structure with width and height. Write functions to:
- Initialize a rectangle
- Calculate its area
- Calculate its perimeter

### Exercise 2: Class with Constructor
Convert the Rectangle from Exercise 1 into a class with:
- Private data members (width, height)
- A constructor that initializes width and height
- Public member functions for area() and perimeter()
- A member function to check if it's a square

### Exercise 3: Enhanced Vector Class
Extend the Vector class from the chapter:
- Add a constructor that takes no arguments (creates an empty vector with sz=0, elem=nullptr)
- Add a method `double get(int i)` that returns the element at index i
- Add a method `void set(int i, double value)` that sets the element at index i

### Exercise 4: Operator Overloading
Create a `Complex` class to represent complex numbers (a + bi):
- Private members: real and imaginary parts
- Constructor to initialize both parts
- Overload the `+` operator to add two complex numbers
- Overload the `*` operator to multiply two complex numbers
- Add a `print()` method to display the complex number

### Exercise 5: Using Enumerations
Create a simple card game representation:
- Define an `enum class Suit` with values: Hearts, Diamonds, Clubs, Spades
- Define an `enum class Rank` with values: Ace, Two, Three, ..., King
- Create a `Card` class with Suit and Rank members
- Write a function to print a card (e.g., "Ace of Hearts")
- Overload the `<` operator to compare cards by rank

### Exercise 6: Student Record System
Create a student record system:
- Define a `Student` class with: name (string), id (int), grades (array of doubles)
- Constructor to initialize student with name and id
- Method to add a grade
- Method to calculate average grade
- Method to print student information

### Exercise 7: Variant Usage
Create a `Result` type using `std::variant`:
- Can hold either an `int` (success value) or a `string` (error message)
- Write a function that returns a Result after attempting division
- Write a function to handle the Result and print appropriate message

### Exercise 8: Traffic Light State Machine
Implement a traffic light controller:
- Use the `Traffic_light` enum from the chapter
- Create a class `TrafficController` that stores current light state
- Implement methods: `next()` to advance to next state, `current()` to get current state
- Implement a method `can_cross()` that returns true only for green light
- Add timing: store how many seconds until next state change

---

## Theory Questions

### Basic Concepts
1. What is the difference between built-in types and user-defined types in C++?

2. What are the two main categories of user-defined types in C++?

3. Explain the difference between accessing struct members with `.` vs `->`.

4. What is the free store (heap) and how is it different from stack allocation?

5. What is the difference between a `struct` and a `class` in C++?

### Classes and Encapsulation
6. What is a constructor and why is it important?

7. What is a member initializer list? Show the syntax.

8. Explain the purpose of `public` and `private` access specifiers.

9. What does it mean to say that a class provides "encapsulation"?

10. In the Vector class example, what does `operator[]` do and why does it return a `double&`?

### Memory Management
11. What does the `new` operator do?

12. What is the purpose of the `delete` operator?

13. Why is the Vector object always the same size even though it can store different numbers of elements?

14. Explain the "handle" concept mentioned in the Vector example.

### Unions
15. What is a union and how does it differ from a struct?

16. Why are "naked" unions considered error-prone?

17. What is `std::variant` and what advantage does it have over traditional unions?

18. In the Entry example with union, why is a type field necessary?

### Enumerations
19. What is the difference between `enum class` and plain `enum`?

20. Why can't you write `Color x = red;` with an enum class?

21. Can you implicitly convert an `enum class` value to an integer? Why or why not?

22. How do you explicitly initialize an enum class with an integer value?

23. What operations are defined by default for enum class types?

24. What is the default underlying type for an enum and what are the default values?

### Design Principles
25. Why is it recommended to prefer user-defined types over built-in types?

26. According to the advice section, should you use naked unions? What should you use instead?

27. Why is `enum class` preferred over plain `enum`?

28. What is the main benefit of defining constructors for your classes?

### Advanced Understanding
29. Explain why returning `double&` from `operator[]` allows both reading and writing.

30. How would you extend an enum class with custom operations? Give an example from the chapter.

---

# ANSWERS SECTION
## (Don't look until you've attempted the exercises!)

---
---
---
---
---

## Coding Exercise Answers

### Exercise 1: Basic Structure
```cpp
#include <iostream>
using namespace std;

struct Rectangle {
    double width;
    double height;
};

void rectangle_init(Rectangle& r, double w, double h) {
    r.width = w;
    r.height = h;
}

double area(const Rectangle& r) {
    return r.width * r.height;
}

double perimeter(const Rectangle& r) {
    return 2 * (r.width + r.height);
}

int main() {
    Rectangle rect;
    rectangle_init(rect, 5.0, 3.0);
    cout << "Area: " << area(rect) << endl;
    cout << "Perimeter: " << perimeter(rect) << endl;
    return 0;
}
```

### Exercise 2: Class with Constructor
```cpp
#include <iostream>
using namespace std;

class Rectangle {
public:
    Rectangle(double w, double h) : width{w}, height{h} { }

    double area() const {
        return width * height;
    }

    double perimeter() const {
        return 2 * (width + height);
    }

    bool is_square() const {
        return width == height;
    }

private:
    double width;
    double height;
};

int main() {
    Rectangle rect(5.0, 3.0);
    cout << "Area: " << rect.area() << endl;
    cout << "Perimeter: " << rect.perimeter() << endl;
    cout << "Is square: " << (rect.is_square() ? "yes" : "no") << endl;
    return 0;
}
```

### Exercise 3: Enhanced Vector Class
```cpp
#include <iostream>
using namespace std;

class Vector {
public:
    Vector(int s) : elem{new double[s]}, sz{s} {
        for (int i = 0; i < sz; ++i)
            elem[i] = 0.0;  // Initialize to zero
    }

    Vector() : elem{nullptr}, sz{0} { }  // Default constructor

    double& operator[](int i) { return elem[i]; }
    int size() const { return sz; }

    double get(int i) const {
        return elem[i];
    }

    void set(int i, double value) {
        elem[i] = value;
    }

private:
    double* elem;
    int sz;
};

int main() {
    Vector v(5);
    v.set(0, 1.5);
    v.set(1, 2.5);
    cout << "v[0] = " << v.get(0) << endl;
    cout << "v[1] = " << v.get(1) << endl;
    return 0;
}
```

### Exercise 4: Operator Overloading
```cpp
#include <iostream>
using namespace std;

class Complex {
public:
    Complex(double r, double i) : real{r}, imag{i} { }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator*(const Complex& other) const {
        // (a+bi)(c+di) = (ac-bd) + (ad+bc)i
        double r = real * other.real - imag * other.imag;
        double i = real * other.imag + imag * other.real;
        return Complex(r, i);
    }

    void print() const {
        cout << real;
        if (imag >= 0)
            cout << " + " << imag << "i";
        else
            cout << " - " << -imag << "i";
        cout << endl;
    }

private:
    double real;
    double imag;
};

int main() {
    Complex c1(3, 4);
    Complex c2(1, 2);

    Complex sum = c1 + c2;
    Complex product = c1 * c2;

    cout << "c1: "; c1.print();
    cout << "c2: "; c2.print();
    cout << "Sum: "; sum.print();
    cout << "Product: "; product.print();

    return 0;
}
```

### Exercise 5: Using Enumerations
```cpp
#include <iostream>
#include <string>
using namespace std;

enum class Suit { Hearts, Diamonds, Clubs, Spades };
enum class Rank {
    Ace = 1, Two, Three, Four, Five, Six, Seven,
    Eight, Nine, Ten, Jack, Queen, King
};

class Card {
public:
    Card(Rank r, Suit s) : rank{r}, suit{s} { }

    string to_string() const {
        return rank_to_string() + " of " + suit_to_string();
    }

    bool operator<(const Card& other) const {
        return static_cast<int>(rank) < static_cast<int>(other.rank);
    }

private:
    Rank rank;
    Suit suit;

    string rank_to_string() const {
        switch (rank) {
            case Rank::Ace: return "Ace";
            case Rank::Two: return "Two";
            case Rank::Three: return "Three";
            case Rank::Four: return "Four";
            case Rank::Five: return "Five";
            case Rank::Six: return "Six";
            case Rank::Seven: return "Seven";
            case Rank::Eight: return "Eight";
            case Rank::Nine: return "Nine";
            case Rank::Ten: return "Ten";
            case Rank::Jack: return "Jack";
            case Rank::Queen: return "Queen";
            case Rank::King: return "King";
            default: return "Unknown";
        }
    }

    string suit_to_string() const {
        switch (suit) {
            case Suit::Hearts: return "Hearts";
            case Suit::Diamonds: return "Diamonds";
            case Suit::Clubs: return "Clubs";
            case Suit::Spades: return "Spades";
            default: return "Unknown";
        }
    }
};

int main() {
    Card ace_hearts(Rank::Ace, Suit::Hearts);
    Card king_spades(Rank::King, Suit::Spades);

    cout << ace_hearts.to_string() << endl;
    cout << king_spades.to_string() << endl;

    if (ace_hearts < king_spades)
        cout << "Ace is less than King" << endl;
    else
        cout << "Ace is not less than King" << endl;

    return 0;
}
```

### Exercise 6: Student Record System
```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    Student(const string& n, int student_id)
        : name{n}, id{student_id}, grade_count{0} { }

    void add_grade(double grade) {
        if (grade_count < max_grades) {
            grades[grade_count++] = grade;
        }
    }

    double average_grade() const {
        if (grade_count == 0) return 0.0;

        double sum = 0;
        for (int i = 0; i < grade_count; ++i) {
            sum += grades[i];
        }
        return sum / grade_count;
    }

    void print() const {
        cout << "Student: " << name << " (ID: " << id << ")" << endl;
        cout << "Grades: ";
        for (int i = 0; i < grade_count; ++i) {
            cout << grades[i] << " ";
        }
        cout << endl;
        cout << "Average: " << average_grade() << endl;
    }

private:
    static const int max_grades = 10;
    string name;
    int id;
    double grades[max_grades];
    int grade_count;
};

int main() {
    Student alice("Alice Smith", 12345);
    alice.add_grade(85.5);
    alice.add_grade(92.0);
    alice.add_grade(78.5);
    alice.add_grade(88.0);

    alice.print();

    return 0;
}
```

### Exercise 7: Variant Usage
```cpp
#include <iostream>
#include <variant>
#include <string>
using namespace std;

using Result = variant<int, string>;

Result divide(int a, int b) {
    if (b == 0) {
        return string("Error: Division by zero");
    }
    return a / b;
}

void handle_result(const Result& result) {
    if (holds_alternative<int>(result)) {
        cout << "Success: " << get<int>(result) << endl;
    } else {
        cout << get<string>(result) << endl;
    }
}

int main() {
    Result r1 = divide(10, 2);
    Result r2 = divide(10, 0);

    handle_result(r1);
    handle_result(r2);

    return 0;
}
```

### Exercise 8: Traffic Light State Machine
```cpp
#include <iostream>
using namespace std;

enum class Traffic_light { green, yellow, red };

class TrafficController {
public:
    TrafficController() : current_light{Traffic_light::red}, seconds_remaining{30} { }

    void next() {
        switch (current_light) {
            case Traffic_light::green:
                current_light = Traffic_light::yellow;
                seconds_remaining = 5;
                break;
            case Traffic_light::yellow:
                current_light = Traffic_light::red;
                seconds_remaining = 30;
                break;
            case Traffic_light::red:
                current_light = Traffic_light::green;
                seconds_remaining = 30;
                break;
        }
    }

    Traffic_light current() const {
        return current_light;
    }

    bool can_cross() const {
        return current_light == Traffic_light::green;
    }

    void tick() {
        if (seconds_remaining > 0) {
            --seconds_remaining;
        }
        if (seconds_remaining == 0) {
            next();
        }
    }

    int time_remaining() const {
        return seconds_remaining;
    }

    string current_as_string() const {
        switch (current_light) {
            case Traffic_light::green: return "GREEN";
            case Traffic_light::yellow: return "YELLOW";
            case Traffic_light::red: return "RED";
            default: return "UNKNOWN";
        }
    }

private:
    Traffic_light current_light;
    int seconds_remaining;
};

int main() {
    TrafficController controller;

    cout << "Initial state: " << controller.current_as_string() << endl;
    cout << "Can cross: " << (controller.can_cross() ? "Yes" : "No") << endl;

    controller.next();
    cout << "\nAfter next(): " << controller.current_as_string() << endl;
    cout << "Can cross: " << (controller.can_cross() ? "Yes" : "No") << endl;

    controller.next();
    cout << "\nAfter next(): " << controller.current_as_string() << endl;
    cout << "Can cross: " << (controller.can_cross() ? "Yes" : "No") << endl;

    return 0;
}
```

---

## Theory Question Answers

### Basic Concepts

**1. What is the difference between built-in types and user-defined types in C++?**

Built-in types (int, double, char, pointers, etc.) are fundamental types provided by the language that directly reflect hardware capabilities. They are deliberately low-level. User-defined types are custom types built by programmers using C++'s abstraction mechanisms (classes and enumerations). They provide higher-level facilities, are easier to use, less error-prone, and often as efficient or more efficient than direct use of built-in types.

**2. What are the two main categories of user-defined types in C++?**

Classes and enumerations.

**3. Explain the difference between accessing struct members with `.` vs `->`.**

- `.` (dot) is used to access members through an object name or reference
- `->` (arrow) is used to access members through a pointer

Example:
```cpp
Vector v;
Vector& rv = v;
Vector* pv = &v;

int i1 = v.sz;    // through name
int i2 = rv.sz;   // through reference
int i3 = pv->sz;  // through pointer
```

**4. What is the free store (heap) and how is it different from stack allocation?**

The free store (also called dynamic memory or heap) is a memory area where objects can be allocated using the `new` operator. Objects on the free store:
- Are independent of the scope where they're created
- Live until explicitly destroyed with `delete`
- Have dynamic lifetime

Stack allocation creates objects that:
- Are tied to their scope
- Are automatically destroyed when scope ends
- Have automatic lifetime

**5. What is the difference between a `struct` and a `class` in C++?**

There is no fundamental difference. A `struct` is simply a class with members public by default, while a `class` has members private by default. Both can have constructors, member functions, and all other class features.

### Classes and Encapsulation

**6. What is a constructor and why is it important?**

A constructor is a special member function with the same name as its class, used to initialize objects of that class. It's important because:
- It's guaranteed to be called when objects are created
- It eliminates the problem of uninitialized variables
- It ensures proper object initialization
- It can enforce invariants from object creation

**7. What is a member initializer list? Show the syntax.**

A member initializer list is syntax used in constructors to initialize class members before the constructor body executes.

Syntax:
```cpp
Vector(int s) : elem{new double[s]}, sz{s} { }
//            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//            member initializer list
```

**8. Explain the purpose of `public` and `private` access specifiers.**

- `public`: Defines the class interface - members accessible to all users
- `private`: Defines the implementation - members accessible only within the class itself

This separation allows:
- Encapsulation of implementation details
- Guarantee of consistent data use
- Ability to change implementation without affecting users
- Easier maintenance and debugging

**9. What does it mean to say that a class provides "encapsulation"?**

Encapsulation means bundling data and the operations on that data together while hiding the internal implementation details from users. The interface (public members) is separated from the implementation (private members), allowing:
- Controlled access to data
- Prevention of invalid states
- Freedom to change implementation without affecting client code
- Better organization and maintenance

**10. In the Vector class example, what does `operator[]` do and why does it return a `double&`?**

`operator[]` is the subscript operator that provides element access. It returns a `double&` (reference to double) to allow both reading and writing:
- Reading: `double x = v[i];` (reference converts to value)
- Writing: `v[i] = 3.14;` (can assign through reference)

If it returned `double` (value), you couldn't write to elements.

### Memory Management

**11. What does the `new` operator do?**

The `new` operator allocates memory from the free store (heap) and returns a pointer to that memory. It:
- Allocates sufficient space for the requested type
- Initializes the object if needed
- Returns a pointer to the allocated memory
- Throws an exception if allocation fails

Example: `double* p = new double[10];` allocates array of 10 doubles.

**12. What is the purpose of the `delete` operator?**

The `delete` operator deallocates memory that was allocated with `new`, returning it to the free store. It:
- Calls destructors if needed
- Frees the memory
- Should be called for every `new` to prevent memory leaks

Use `delete` for single objects, `delete[]` for arrays.

**13. Why is the Vector object always the same size even though it can store different numbers of elements?**

The Vector object itself only contains a pointer (`elem`) and an integer (`sz`), which are fixed-size. The actual elements are stored elsewhere on the free store. This is the "handle" pattern: a fixed-size object that refers to variable-size data elsewhere.

**14. Explain the "handle" concept mentioned in the Vector example.**

A handle is a fixed-size object containing a pointer to variable-amount data elsewhere (typically on the free store). The handle provides:
- Predictable object size
- Ability to manage variable-size data
- Indirect access to actual data
- Easy copying/passing of the handle (though careful with ownership)

Example: Vector contains `sz` (int) and `elem` (pointer), always same size, but can reference different amounts of data.

### Unions

**15. What is a union and how does it differ from a struct?**

A union is like a struct except all members are allocated at the same address, so the union only occupies as much space as its largest member. A union can hold a value for only one member at a time, while a struct holds values for all members simultaneously.

**16. Why are "naked" unions considered error-prone?**

Naked unions are error-prone because:
- The language doesn't track which member currently holds a value
- Programmer must manually maintain this information
- Easy to accidentally read the wrong member
- Can lead to type confusion and undefined behavior
- No compile-time safety

**17. What is `std::variant` and what advantage does it have over traditional unions?**

`std::variant` is a standard library type that stores a value of one of a set of alternative types. Advantages over unions:
- Type-safe: knows which type it currently holds
- No need for manual type tracking
- Provides safe access functions (`holds_alternative`, `get`)
- Prevents reading wrong type
- Easier and safer to use

**18. In the Entry example with union, why is a type field necessary?**

The type field (Type t) is necessary to track which member of the union currently holds a valid value, since the language doesn't do this automatically. Without it, there's no way to know whether to access `v.p` or `v.i`, leading to potential errors and undefined behavior.

### Enumerations

**19. What is the difference between `enum class` and plain `enum`?**

`enum class` (scoped enum):
- Enumerators are scoped within the enum
- Strongly typed (no implicit conversion to int)
- Must use qualified names (e.g., `Color::red`)
- Safer, prevents accidental mixing

Plain `enum`:
- Enumerators in same scope as enum name
- Implicitly converts to int
- Can use unqualified names
- Less safe, more error-prone
- Legacy style from C

**20. Why can't you write `Color x = red;` with an enum class?**

With `enum class`, enumerators are scoped within the enum, so you must qualify them: `Color x = Color::red;`. Writing just `red` causes a compilation error because the compiler doesn't know which `red` you mean (could be from different enum classes) and `red` isn't visible in the outer scope.

**21. Can you implicitly convert an `enum class` value to an integer? Why or why not?**

No, you cannot implicitly convert an `enum class` to an integer. This is a safety feature to prevent accidental misuse. If you need the integer value, you must explicitly cast: `int i = static_cast<int>(Color::red);`

**22. How do you explicitly initialize an enum class with an integer value?**

You can use brace initialization or explicit construction:
```cpp
Color x = Color{5};  // OK, but verbose
Color y{6};          // also OK
```

**23. What operations are defined by default for enum class types?**

By default, enum classes have:
- Assignment
- Initialization
- Comparisons (==, !=, <, >, <=, >=)

No arithmetic operations are defined by default. You can define custom operators if needed.

**24. What is the default underlying type for an enum and what are the default values?**

- Default underlying type: `int`
- Default values: Start at 0 and increase by 1 for each enumerator

Example:
```cpp
enum class Color { red, green, blue };
// red = 0, green = 1, blue = 2
```

### Design Principles

**25. Why is it recommended to prefer user-defined types over built-in types?**

User-defined types are preferred when built-in types are too low-level because they:
- Provide better abstraction
- Are easier to use
- Are less error-prone
- Better express intent
- Can enforce invariants
- Are typically as efficient or more efficient
- Make code more maintainable and readable

**26. According to the advice section, should you use naked unions? What should you use instead?**

No, avoid naked unions. Instead:
- Wrap unions in a class with a type field
- Better yet, use `std::variant` which is simpler and safer

**27. Why is `enum class` preferred over plain `enum`?**

`enum class` is preferred because it:
- Provides type safety
- Prevents accidental mixing of different enum types
- Prevents implicit conversion to int
- Scopes enumerators to prevent name conflicts
- Minimizes surprises and errors
- Makes code more explicit and clear

**28. What is the main benefit of defining constructors for your classes?**

Constructors guarantee and simplify initialization of classes. They:
- Ensure objects are properly initialized before use
- Eliminate uninitialized variable problems
- Can enforce class invariants from creation
- Make object creation simpler and safer
- Are automatically called, can't be forgotten

### Advanced Understanding

**29. Explain why returning `double&` from `operator[]` allows both reading and writing.**

A reference (`double&`) is an alias to the actual storage location. When you return a reference:

Reading: The reference automatically converts to a value when used in expressions:
```cpp
double x = v[0];  // reads value through reference
```

Writing: The reference allows assignment to the actual location:
```cpp
v[0] = 42.0;  // writes to actual element through reference
```

If it returned `double` (by value), assignments like `v[0] = 42.0` would compile but have no effect (assign to temporary).

**30. How would you extend an enum class with custom operations? Give an example from the chapter.**

Define operator functions for the enum type. Example from chapter:

```cpp
Traffic_light& operator++(Traffic_light& t) {
    switch (t) {
        case Traffic_light::green:
            return t = Traffic_light::yellow;
        case Traffic_light::yellow:
            return t = Traffic_light::red;
        case Traffic_light::red:
            return t = Traffic_light::green;
    }
}

// Usage:
Traffic_light light = Traffic_light::red;
++light;  // light is now green
```

This defines the prefix increment operator (++) for the Traffic_light enum, allowing natural state transitions.
