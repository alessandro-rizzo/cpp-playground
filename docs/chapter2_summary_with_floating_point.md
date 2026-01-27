# Chapter 2: Representing and Manipulating Information

## Combined Summary: CSAPP 2016 + Deep Dive into IEEE Floating Point

---

## Table of Contents

1. [Overview](#overview)
2. [Information Storage](#21-information-storage)
3. [Integer Representations](#22-integer-representations)
4. [Integer Arithmetic](#23-integer-arithmetic)
5. [Floating Point](#24-floating-point)
6. [Why IEEE Floating Point is Counterintuitive](#why-ieee-floating-point-is-counterintuitive)
7. [Why Decimal Fractions Don't Work in Binary](#why-decimal-fractions-dont-work-in-binary)
8. [Summary](#summary)

---

## Overview

Chapter 2 from CSAPP 2016 covers how computers encode and manipulate information at the bit level. The chapter focuses on three fundamental representations: **unsigned integers**, **two's-complement signed integers**, and **IEEE 754 floating-point numbers**. Understanding these representations is critical for writing correct, portable programs and avoiding security vulnerabilities.

**Key Insight**: Computer representations use a limited number of bits to encode numbers, leading to overflow and unexpected behavior. For example, on most 32-bit systems:

```c
200 * 300 * 400 * 500  // yields -884,901,888 (not 12,000,000,000)
```

---

## 2.1 Information Storage

### 2.1.1 Hexadecimal Notation

- **Purpose**: Hexadecimal (base-16) provides a more manageable way to represent binary numbers
- **Digits**: 0-9 and A-F (10-15), with `0x` prefix in C notation
- **Conversion**: Each hex digit represents exactly 4 bits
  - Example: `0x173A4C` = `0001 0111 0011 1010 0100 1100`
- **Powers of 2**: For x = 2^n, if n = i + 4j where 0≤i≤3:
  - Leading hex digit is 1 (i=0), 2 (i=1), 4 (i=2), or 8 (i=3)
  - Followed by j hex zeros

### 2.1.2 Data Sizes

**Word Size**: The nominal size of pointer data, determining maximum virtual address space
- 32-bit machines: 4 GB (2^32 bytes) address space
- 64-bit machines: 16 exabytes (≈1.84 × 10^19 bytes) address space

**C Data Types** (typical sizes):

| Type | 32-bit | 64-bit | Description |
|------|--------|--------|-------------|
| `char` | 1 byte | 1 byte | Character |
| `short` | 2 bytes | 2 bytes | Short integer |
| `int` | 4 bytes | 4 bytes | Integer |
| `long` | 4 bytes | 8 bytes | Long integer |
| `float` | 4 bytes | 4 bytes | Single precision |
| `double` | 8 bytes | 8 bytes | Double precision |
| `pointer` | 4 bytes | 8 bytes | Memory address |

**Fixed-size types** (ISO C99): `int32_t`, `uint32_t`, `int64_t`, `uint64_t` provide guaranteed sizes regardless of platform

### 2.1.3 Addressing and Byte Ordering

**Multi-byte Objects**: Stored at contiguous byte addresses; object's address is the lowest address of its bytes

**Byte Ordering** (two conventions):

1. **Little-endian**: Least significant byte first (Intel x86-64)
2. **Big-endian**: Most significant byte first (IBM/Oracle SPARC)

**Example**: `0x01234567` at address `0x100`:
```
Big-endian:    01 23 45 67
Little-endian: 67 45 23 01
```

**Implications**:
- Affects network communication (must use standard conventions)
- Important when reading machine-level program representations
- Visible when programs use type casts to circumvent C's type system

### 2.1.4 Representing Strings

- Encoded as null-terminated arrays of characters
- ASCII encoding most common: digits '0'-'9' have codes `0x30`-`0x39`
- More platform-independent than binary data

### 2.1.5 Representing Code

- Machine code has different representations across processor types/operating systems
- Binary code rarely portable across different machine-OS combinations
- Type information is lost at machine level

### 2.1.6 Boolean Algebra

**Boolean Operations**:
- **NOT (~)**: Complements each bit
- **AND (&)**: Result is 1 only when both bits are 1
- **OR (|)**: Result is 1 when at least one bit is 1
- **XOR (^)**: Result is 1 when bits differ

**Properties**:
- Form a Boolean algebra for operations `|`, `&`, `~` on w-bit vectors
- Form a Boolean ring for operations `^`, `&`, `~` (where `a^a=0`)

**Applications**:
- Set representation: Bit vector encodes subsets
- Signal masks: Enable/disable interrupts

### 2.1.7 Bit-Level Operations in C

- C supports `~`, `&`, `|`, `^` on integral data types
- **Common masking**: `x & 0xFF` extracts least significant byte
- **All-ones mask**: `~0` works for any word size (portable)

**Example**: `0x69 & 0x55 = 0x41`
```
  01101001  (0x69)
& 01010101  (0x55)
-----------
  01000001  (0x41)
```

### 2.1.8 Logical Operations in C

**Operators**: `||`, `&&`, `!`

**Differences from bit-level operations**:
- Treat any nonzero as true; 0 as false
- Return either 1 (true) or 0 (false)
- **Short-circuit evaluation**: Don't evaluate second operand if result determined by first
  - `a && 5/a` never causes division by zero
  - `p && *p++` never dereferences null pointer

### 2.1.9 Shift Operations in C

**Left Shift** (`x << k`):
- Shifts bits left by k positions, filling right with k zeros
- Equivalent to multiplying by 2^k

**Right Shift** (`x >> k`):
- **Logical shift**: Fills left with k zeros (unsigned)
- **Arithmetic shift**: Fills left with k copies of sign bit (signed)
- C standard doesn't specify which for signed, but most modern compilers use arithmetic

**Properties**:
- Shift amount should be 0 to w-1 for w-bit values
- Operator precedence: shifts lower than `+`/`-`; use parentheses

---

## 2.2 Integer Representations

### 2.2.1 Integral Data Types

**C Integral Types and Ranges** (typical):

| Type | Min | Max |
|------|-----|-----|
| `[signed] char` | -128 | 127 |
| `unsigned char` | 0 | 255 |
| `short` | -32,768 | 32,767 |
| `unsigned short` | 0 | 65,535 |
| `int` | -2,147,483,648 | 2,147,483,647 |
| `unsigned int` | 0 | 4,294,967,295 |

**Key Observation**: Range is asymmetric for signed integers (one more negative value than positive)

### 2.2.2 Unsigned Encodings

**Definition** (B2U_w - Binary to Unsigned):

For bit vector **x** = [x_{w-1}, ..., x_0]:

```
B2U_w(x) = Σ(i=0 to w-1) x_i × 2^i
```

**Properties**:
- Maps each w-bit pattern to unique number in range [0, 2^w - 1]
- **UMax_w = 2^w - 1** (all bits set to 1)

**Example** (w=4):
- `B2U_4([1011])` = 8 + 2 + 1 = 11
- `B2U_4([1111])` = 15 (maximum)

### 2.2.3 Two's-Complement Encodings

**Definition** (B2T_w - Binary to Two's Complement):

For bit vector **x** = [x_{w-1}, ..., x_0]:

```
B2T_w(x) = -x_{w-1} × 2^{w-1} + Σ(i=0 to w-2) x_i × 2^i
```

The most significant bit (sign bit) has weight **-2^{w-1}** instead of **+2^{w-1}**

**Properties**:
- Sign bit = 1 → negative; sign bit = 0 → nonnegative
- **TMin_w = -2^{w-1}** (1 followed by all 0s)
- **TMax_w = 2^{w-1} - 1** (0 followed by all 1s)
- Range: [TMin_w, TMax_w] (asymmetric: |TMin| = |TMax| + 1)

**Example** (w=4):
- `B2T_4([1011])` = -8 + 2 + 1 = -5
- `B2T_4([0111])` = 7 (maximum)
- `B2T_4([1000])` = -8 (minimum, TMin)

**Key Difference from Unsigned**:
- Same bit patterns, different interpretations
- `[1111]` = 15 (unsigned) or -1 (two's complement)

### 2.2.4 Conversions Between Signed and Unsigned

**C Casting Rule**: Bit pattern does not change; only interpretation changes

**Conversion Formulas**:

1. **Two's Complement to Unsigned (T2U_w)**:
   ```
   T2U_w(x) = x + 2^w    if x < 0
            = x          if x ≥ 0
   ```

2. **Unsigned to Two's Complement (U2T_w)**:
   ```
   U2T_w(u) = u          if u ≤ TMax_w
            = u - 2^w    if u > TMax_w
   ```

### 2.2.5 Signed vs. Unsigned in C

**Implicit Conversions**:
- When mixing signed/unsigned, signed is implicitly cast to unsigned
- **Dangerous example**: `-1 < 0U` evaluates to **false** (because -1 converts to 4,294,967,295)

**Recommendation**: Avoid mixing signed and unsigned types to prevent subtle bugs

### 2.2.6 Expanding Bit Representation

**Zero Extension** (unsigned):
- Add leading zeros to expand from w to w' bits
- Preserves unsigned value

**Sign Extension** (two's complement):
- Replicate sign bit (x_{w-1}) in new high-order positions
- Preserves two's complement value

### 2.2.7 Truncating Numbers

**Unsigned Truncation**: `x' = x mod 2^k` (takes low-order k bits)

**Two's-Complement Truncation**: First compute modulo, then convert to two's complement

### 2.2.8 Advice on Signed vs. Unsigned

**Best Practices**:
- Use signed integers by default
- Unsigned useful for: bit vectors, system programming, modular arithmetic
- Avoid mixing signed/unsigned in same expression

---

## 2.3 Integer Arithmetic

### 2.3.1 Unsigned Addition

**Definition** (+_u^w):
```
x +_u^w y = (x + y) mod 2^w
```

**Overflow Detection**:
- For result `s = x +_u^w y`, overflow occurred iff `s < x` (or `s < y`)

**Modular Arithmetic**: Unsigned addition forms an abelian group
- Commutative: `x +_u^w y = y +_u^w x`
- Associative
- Identity: 0
- Inverses: For each x, there exists `-_u^w x = 2^w - x`

### 2.3.2 Two's-Complement Addition

**Three Cases**:
- **Normal**: -2^{w-1} ≤ x+y < 2^{w-1} → result = x + y
- **Positive Overflow**: x+y ≥ 2^{w-1} → result = x + y - 2^w
- **Negative Overflow**: x+y < -2^{w-1} → result = x + y + 2^w

**Overflow Detection**:
- Positive overflow: `x > 0 && y > 0 && result ≤ 0`
- Negative overflow: `x < 0 && y < 0 && result ≥ 0`

### 2.3.3 Two's-Complement Negation

**Definition**:
```
-_t^w x = TMin_w    if x = TMin_w
        = -x        if x > TMin_w
```

**Bit-level Trick**: `-x = (~x) + 1`

### 2.3.4 Unsigned Multiplication

**Definition**: `x *_u^w y = (x × y) mod 2^w`

**Key Property**: Bit-level representation identical to two's-complement multiplication

### 2.3.5 Two's-Complement Multiplication

**Definition**: `x *_t^w y = U2T_w((x × y) mod 2^w)`

Same hardware instruction can be used for signed/unsigned multiplication

### 2.3.6 Multiplying by Constants

**Optimization**: Compilers replace multiplication by constants with shifts/adds

**Multiplication by Power of 2**: `x × 2^k = x << k`

**General Constants**: Express K in binary as runs of 0s and 1s
- **Form A**: Sum of shifted values
- **Form B**: Difference of shifted values (typically fewer operations)

**Example**: `14 = [1110]_2 = (x<<3) + (x<<2) + (x<<1)` or `(x<<4) - (x<<1)`

### 2.3.7 Dividing by Powers of 2

**Unsigned Division**: `x >> k = x / 2^k` (logical right shift)

**Two's-Complement Division**:
- **Without bias**: `x >> k` (rounds toward -∞)
- **With bias**: `(x + (1<<k) - 1) >> k` (rounds toward zero, correct for negative)

### 2.3.8 Final Thoughts on Integer Arithmetic

**Key Insights**:
- Computer arithmetic is modular, not true integer arithmetic
- Overflow is silent; operations can yield surprising results
- Implicit casting between signed/unsigned can cause unexpected behavior
- These properties allow compiler optimizations

---

## 2.4 Floating Point

### 2.4.1 Fractional Binary Numbers

**Binary Point Notation**: `b_m...b_1 b_0 . b_{-1}...b_{-n}`

**Weights**: 2^m, ..., 2^0 (left of point); 2^{-1}, ..., 2^{-n} (right of point)

**Example**: `101.11_2 = 4 + 1 + 0.5 + 0.25 = 5.75`

**Limitation**: Only numbers of form `x × 2^y` can be represented exactly with finite digits

### 2.4.2 IEEE Floating-Point Representation

**IEEE Standard 754** (1985) standardized floating-point arithmetic

**Representation**: `V = (-1)^s × M × 2^E`
- **s** (sign bit): 0 = positive, 1 = negative
- **M** (significand): Fractional binary number
- **E** (exponent): Integer power of 2

**Encoding**:

| Type | Sign | Exponent | Fraction | Total |
|------|------|----------|----------|-------|
| Single (float) | 1 bit | 8 bits | 23 bits | 32 bits |
| Double (double) | 1 bit | 11 bits | 52 bits | 64 bits |

**Three Cases** (based on exponent field):

#### Case 1: Normalized Values

(exp ≠ 0 and exp ≠ 2^k - 1)

- **Exponent**: `E = e - Bias`
  - Bias = 2^{k-1} - 1 (127 for single, 1023 for double)
  - Range: -126 to +127 (single); -1022 to +1023 (double)
- **Significand**: `M = 1 + f` (implied leading 1)
  - Provides extra bit of precision
  - M ranges: 1 ≤ M < 2
- **Value**: `V = (-1)^s × (1 + f) × 2^{e - Bias}`

#### Case 2: Denormalized Values

(exp = 0)

- **Exponent**: `E = 1 - Bias`
- **Significand**: `M = f` (no implied leading 1)
- **Purposes**:
  - Represent 0 (both +0 and -0)
  - Provide gradual underflow near 0
  - Bridge from 0 to smallest normalized value

#### Case 3: Special Values

(exp = 2^k - 1)

- **Infinity** (frac = 0): +∞ or -∞
  - Represents overflow or division by zero
- **NaN** (frac ≠ 0): "Not a Number"
  - Represents results that cannot be real numbers
  - Examples: √(-1), ∞ - ∞

### 2.4.3 Example Numbers

**Single-Precision Special Values**:
- +0.0: `0x00000000`
- Smallest positive denormalized: ≈ 1.4 × 10^{-45}
- Largest denormalized: ≈ 1.2 × 10^{-38}
- Smallest positive normalized: ≈ 1.2 × 10^{-38}
- 1.0: `0x3F800000`
- Largest normalized: ≈ 3.4 × 10^{38}
- +∞: `0x7F800000`

### 2.4.4 Rounding

**Four IEEE Rounding Modes**:

1. **Round-to-Even (default)**:
   - Rounds to nearest value
   - Ties go to even (LSB = 0)
   - Avoids statistical bias

2. **Round-Toward-Zero**:
   - Rounds toward 0

3. **Round-Down**:
   - Always rounds toward -∞

4. **Round-Up**:
   - Always rounds toward +∞

### 2.4.5 Floating-Point Operations

**Addition Properties**:
- ✓ Commutative: `x +_f y = y +_f x`
- ✗ **NOT associative**: `(3.14 + 1e20) - 1e20 = 0.0`, but `3.14 + (1e20 - 1e20) = 3.14`
- ✓ Monotonic

**Multiplication Properties**:
- ✓ Commutative: `x *_f y = y *_f x`
- ✗ **NOT associative**: `(1e20 × 1e20) × 1e-20 = ∞`, but `1e20 × (1e20 × 1e-20) = 1e20`
- ✗ **NOT distributive**: `1e20 × (1e20 - 1e20) = 0`, but `1e20 × 1e20 - 1e20 × 1e20 = NaN`
- ✓ `a × a ≥ 0` (for a ≠ NaN)

### 2.4.6 Floating Point in C

**Type Conversions**:
- `int → float`: May round (not overflow)
- `int → double`: Exact
- `double → float`: May overflow to ±∞ or round
- `float/double → int`: Rounds toward zero; may overflow to TMin_w

---

## Why IEEE Floating Point is Counterintuitive

### The Core Idea (One Sentence)

**IEEE floating point numbers are approximations to real numbers, and arithmetic is done on those approximations — not on the real values you think you're manipulating.**

Once you accept that, almost all "counterintuitive" results become predictable.

### Floating Point ≠ Real Numbers

**In Mathematics**:
- ℝ is continuous
- You can represent numbers like 0.1 exactly

**In IEEE Floating Point**:
- Numbers are discrete
- Only numbers of the form `±(1.f)_2 × 2^e` can be represented
- Most decimal fractions are irrational in binary

**Example**:
```
0.1₁₀ = 0.00011001100110011…₂  (repeating forever)
```

So 0.1 is stored as the **nearest representable binary fraction**. That approximation error is small — but crucial.

### Finite Precision Forces Rounding

IEEE floats have:
- Fixed number of bits for the significand (e.g., 53 bits for double)
- Every operation produces an exact real result...
- ...which is then **rounded back into the representable set**

This rounding happens **after every operation**, not at the end of a calculation.

Think: `(real math) → exact result → rounding → float` over and over.

### Algebraic Laws Quietly Break

Because of rounding, floating point arithmetic is **not a field** and **not even a ring**.

#### Associativity Fails

```
(a + b) + c ≠ a + (b + c)
```

**Example**:
```c
a = 1e20
b = -1e20
c = 3

(a + b) + c = 0 + 3 = 3
a + (b + c) = 1e20 + (-1e20 + 3) ≈ 1e20 + (-1e20) = 0
```

The `+3` disappears due to rounding.

#### Distributivity Fails

```
a * (b + c) ≠ a*b + a*c
```

Same reason: intermediate rounding.

#### Equality Becomes Unreliable

```c
0.1 + 0.2 == 0.3  // False
```

Because:
```
float(0.1 + 0.2) = 0.30000000000000004
```

### Why Cancellation is Especially Dangerous

**Catastrophic Cancellation**

Subtracting nearly equal numbers destroys precision.

**Example**:
```c
x = 1.0000001
y = 1.0000000
x - y = 0.0000001  // only a few meaningful bits survive
```

All the leading bits cancel, leaving rounding noise dominating the result.

This is why **numerically stable algorithms** exist.

### Order of Operations Matters (More Than You Think)

**Summation Example**:
```c
sum([1e20, 1, -1e20])
```

Depending on order:
- `(1e20 + 1) - 1e20 = 0`
- `1e20 + (1 - 1e20) = 0`
- `(1e20 - 1e20) + 1 = 1`

**Same numbers. Different result.**

### Special Values Add More Surprises

IEEE floats include:
- +∞, -∞
- NaN
- +0, -0
- Subnormals

#### NaN Breaks Logic Intuition

```c
NaN != NaN      // true
NaN < x         // false
NaN > x         // false
```

NaN means "this computation is undefined", not a number.

#### Signed Zero Exists

```c
+0.0 ≠ -0.0   (bitwise)
1 / +0.0 = +∞
1 / -0.0 = -∞
```

Useful for limits, but very unintuitive.

### Denormals (Subnormals) Change Performance & Behavior

When numbers get very close to zero:
- IEEE gradually loses precision instead of jumping to zero
- This preserves continuity
- But can be **slower on some hardware**

This is a deliberate design tradeoff.

### Why IEEE Chose This Anyway

IEEE floating point optimizes for:
- **Speed**
- **Predictability**
- **Hardware efficiency**
- **Reproducibility across machines**

Not for:
- Exact arithmetic
- Algebraic elegance

It is an **engineering approximation of ℝ**, not ℝ itself.

### The Right Mental Model

**Floating point arithmetic is exact arithmetic on a different number system, followed by rounding.**

Or even better:

**Floats behave like real numbers only locally and approximately.**

### Practical Rules of Thumb

- Never compare floats for exact equality
- Be suspicious of subtraction of close values
- Reorder sums (small → large)
- Use numerically stable algorithms
- When correctness matters:
  - Use intervals
  - Use rationals
  - Use decimals
  - Use symbolic math

### One-Line Takeaway

**IEEE floating point is counterintuitive only if you expect real-number algebra to survive finite precision.**

---

## Why Decimal Fractions Don't Work in Binary

### What It Means for a Fraction to be "Exact" in a Base

**Theorem**: A fraction has a finite representation in base b **if and only if** its reduced denominator has no prime factors other than those of b.

This is a theorem from number theory.

### Prime Factors of the Bases

**Base 10**:
```
10 = 2 × 5
```

**Base 2**:
```
2 = 2
```

So:
- Decimal fractions can terminate if denominators contain **only 2s and 5s**
- Binary fractions can terminate **only if denominators contain only 2s**

### What This Means in Practice

#### Works in Binary

```
1/2 = 0.1₂
1/4 = 0.01₂
3/8 = 0.011₂
```

All denominators are powers of 2.

#### Fails in Binary

```
1/10 = 1/(2 × 5)
```

That factor of 5 has no way to be expressed as 2^k, so the expansion never terminates.

**Result**:
```
0.1₁₀ = 0.00011001100110011…₂  (repeating forever)
```

### "Irrational" vs "Non-Terminating" (Important Distinction)

Strictly speaking:
- 0.1 is **rational**
- Its binary expansion is **infinite repeating**
- It is not irrational in the mathematical sense

When people say "irrational in binary" they usually mean:

**"has no finite binary representation"**

So the precise statement is:

**Most decimal fractions have infinite repeating binary expansions.**

### Why "Most" Decimal Fractions Fail

Take common decimal fractions:
- 0.1 = 1/10 = 1/(2×5) ❌
- 0.2 = 1/5 ❌
- 0.3 = 3/10 ❌
- 0.01 = 1/100 = 1/(2²×5²) ❌

All contain factor 5 → infinite in binary.

**Rare ones that do work**:
- 0.5 = 1/2 ✓
- 0.25 = 1/4 ✓
- 0.75 = 3/4 ✓

These are the exceptions, not the rule.

### Symmetry Insight (This Goes Both Ways)

Binary fractions look "nice" in base 2:
```
0.001₂ = 1/8
```

But in base 10:
```
1/8 = 0.125₁₀   (terminates)
1/3 = 0.333…₁₀  (repeats)
```

**Every base has its "nice" fractions and its "ugly" ones.**

### The Geometric Intuition

Binary digits represent:
```
1/2, 1/4, 1/8, 1/16, ...
```

You can only build numbers that are **sums of powers of 1/2**.

You'll never hit a fraction that fundamentally requires dividing by 5 exactly.

### Why This Matters for Floating Point

IEEE floats are binary-based, so:
- Fractions like 0.1 must be approximated
- That approximation error propagates through arithmetic
- Hence:

```c
0.1 + 0.2 != 0.3
```

This isn't a bug — it's **arithmetic reality**.

### One-Sentence Takeaway

**A fraction terminates in base b only if its denominator's prime factors divide b; since base 2 has only factor 2, most decimal fractions can't terminate in binary.**

### Concrete Comparison

| Decimal | Fraction | Binary |
|---------|----------|--------|
| 0.5 | 1/2 | 0.1₂ |
| 0.25 | 1/4 | 0.01₂ |
| 0.75 | 3/4 | 0.11₂ |
| 0.1 | 1/10 | 0.000110011…₂ (repeating) |
| 0.2 | 1/5 | 0.00110011…₂ (repeating) |
| 0.3 | 3/10 | 0.01001100…₂ (repeating) |

### What "Most" Means Here

"Most" means **almost all**, in a precise mathematical sense:

Among fractions of the form `p/10^n`, only a tiny subset cancel all the factors of 5:
- 0.5
- 0.25
- 0.75
- 0.125
- 0.375

As you allow more decimal digits, the proportion of numbers whose denominator reduces to a pure power of 2 **goes to zero**.

So: **Almost every finite decimal you write down will have an infinite repeating binary expansion.**

---

## Summary

### Key Takeaways

#### 1. Number Representations

- **Unsigned**: `B2U_w(x) = Σ x_i × 2^i`
- **Two's-complement**: Most significant bit has weight `-2^{w-1}`
- **IEEE Floating-point**: `V = (-1)^s × M × 2^E` with three special cases

#### 2. Arithmetic Properties

- Unsigned/signed integer arithmetic are modular and match bit-level behavior
- Overflow occurs silently; must detect explicitly
- Floating-point not associative/distributive; limited precision

#### 3. Practical Implications

- Implicit casting between signed/unsigned causes subtle bugs
- Compiler optimizations exploit algebraic properties of integer arithmetic
- Understanding bit-level representations is critical for system programming
- Many security vulnerabilities arise from arithmetic overflow and type conversion misunderstandings

#### 4. Optimizations

- Multiplication by constants: Use shifts and adds
- Division by powers of 2: Use shifts with appropriate bias for negative numbers
- Bit-level operations enable efficient implementations of masking, flag manipulation

#### 5. Floating Point Reality

- Floating point is an **approximation** to real arithmetic
- Rounding happens after **every operation**
- Algebraic laws (associativity, distributivity) break
- Most decimal fractions cannot be represented exactly in binary
- Order of operations matters more than in integer arithmetic
- Special values (NaN, ±∞, ±0) require careful handling

### Final Insight

This comprehensive understanding of data representations and arithmetic operations is fundamental to writing **correct**, **efficient**, and **secure** systems software. The seemingly "weird" behavior of computer arithmetic isn't random — it's the inevitable consequence of finite precision + rounding + the mathematical properties of binary representation.
