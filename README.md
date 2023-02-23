# Arithmetica
> Infinite precision arithmetic has always been something that has fascinated me. This is an attempt to direct that fascination into something that might benefit other people too.

Arithmetica is a general-purpose infinite precision Linux and windows math library with a wide variety of mathematical functions and features. Currently supported languages are C, C++, and Python.

# Installation

## Python

### Using pip
If you're on or above Python 3.10, then pip will work for you. See below if not.
```shell
pip install arithmetica-py
```

### Using binaries
Go to the [project page](https://pypi.org/project/arithmetica-py/) on PyPi and download the built distributions. Use pip to install the .whl file as per your operating system.

## C/C++

Include the header [arithmetica.h]() and download the `.a` file from the [releases section](https://github.com/avighnac/arithmetica/releases/).
```c
#include "arithmetica.h"

// your code here
// ...
```
This library uses [basic_math_operations](https://github.com/avighnac/basic_math_operations) for infinite precision arithmetic.
To compile a program using [arithmetica](https://github.com/avighnac/arithmetica), do the following:
## Command line
[Download basic_math_operations](https://github.com/avighnac/basic_math_operations/releases/) in a similar manner. However, you do not have to include any headers for [basic_math_operations](https://github.com/avighnac/basic_math_operations). Use the following command to compile:
`gcc/g++ filename.cpp/c [your arguments] -L. -larithmetica -lbasic_math_operations`
## CMake
Clone [basic_math_operations](https://github.com/avighnac/basic_math_operations) and [arithmetica](https://github.com/avighnac/arithmetica) using `git`, or download the repositories. If your project is on GitHub, then use [submodules](https://github.blog/2016-02-01-working-with-submodules/) to prevent cluttering your language statistics. In either case, the repositories should be present in your project's base folder (or any subfolders in that base folder).

In your _base_ `CMakeLists.txt` file, include the following lines of code:
```cmake
# your previous CMake code here
# ...

# replace path_pointing_to_cloned_repo with the actual path 
add_subdirectory(path_pointing_to_cloned_repo_arithmetica)
add_subdirectory(path_pointing_to_cloned_repo_basic_math_operations)
```

Then, in your `CMakeLists.txt` responsible for compiling your executable, add these lines of code:
```cmake
target_link_libraries(your_project_name_here PRIVATE arithmetica)
target_link_libraries(your_project_name_here PRIVATE basic_math_operations)
```

# Usage

## Python
```py
import arithmetica

print(arithmetica.arcsin('0.5', 20))
```

## C

```c
#include "arithmetica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main ()
{
  char input[] = "0.5";
  char *res = arcsin (input, 20); // 20 is the precision
  printf ("%s%s%s", "arcsin(0.5) = ", res,
          "\n"); // prints the inverse sine of 0.5

  free (res);

  return 0;
}
```

# Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

After making changes, please run the program's test suite by changing the `ENABLE_TESTS` option to `ON`, deleting the `build/` folder, and recompiling. 

Please make sure to update tests as appropriate.

# Functions
Currently, arithmetica has the following decimal number functions:
## Decimal number functions
- `arccos()` complex the [inverse cosine](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions) of any number within the function's domain to any decimal place.
- `arcsin()` computes the [inverse sine](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions) of any number within the function's domain to any decimal place.
- `arctan()` computes the [inverse tangent](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions) of any number within the function's domain to any decimal place.
- `cosine()` computes the [cosine](https://en.wikipedia.org/wiki/Sine_and_cosine) of an angle in radians to any decimal place.
- `exponential()` computes e^x, where x is any real number to any decimal place.
- `factorial()` computes the [factorial](https://en.wikipedia.org/wiki/Factorial) of a non-negative integer.
- `fraction_to_continued_fraction()` converts a non-negative rational fraction to a [continued fraction](https://en.wikipedia.org/wiki/Continued_fraction).
- `igcd()` computes the [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) of two non-negative integers.
- `ilcm()` computes the [least common multiple](https://en.wikipedia.org/wiki/Least_common_multiple) of two non-negative integers.
- `natural_logarithm()` computes the [natural logarithm](https://en.wikipedia.org/wiki/Natural_logarithm) of a positive number to any decimal place.
- `power()` computes x^n, where x and n are rational numbers to any decimal place.
- `repeating_decimal_to_fraction()` converts a [repeating decimal](https://en.wikipedia.org/wiki/Repeating_decimal) to a fraction.
- `simplify_arithmetic_expression()` simplifies an arithmetic expression involving the five basic math operations: addition, subtraction, multiplication, division, and exponentiation. This function can output either a decimal or fractional answer.
- `sine()` computes the [sine](https://en.wikipedia.org/wiki/Sine_and_cosine) of an angle in radians to any decimal place.
- `square_root()` computes the [square root](https://en.wikipedia.org/wiki/Square_root) of a number to any decimal place.
- `tangent()` computes the [trignometric tangent](https://en.wikipedia.org/wiki/Trigonometric_functions) of an angle in radians to any decimal place.
- `terminating_decimal_to_fraction()` converts a terminating decimal to a fraction.

Arithmetica supports basic fraction arithmetic:
## Fractional number functions:
- `add_fraction()` adds two fractions.
- `multiply_fraction()` multiplies two fractions.
- `parse_fraction()` extracts a fraction from a string and/or converts a decimal to a fraction.
- `power_fraction()` computes x^n, where x and n are fractions.
- `subtract_fraction()` subtracts two fractions.

Arithmetica also has some [complex number](https://en.wikipedia.org/wiki/Complex_number) functions:
## Complex number functions:
- `add_complex()` adds two complex numbers.
- `divide_complex()` divides two complex numbers to any decimal place.
- `exponential_complex()` computes e^(a + bi), where a + bi is a complex number to any decimal place.
- `multiply_complex()` multiplies two complex numbers.
- `square_root_complex()` finds the [square root](https://en.wikipedia.org/wiki/Square_root) of a complex number to any decimal place.
- `subtract_complex()` subtracts two complex numbers.
