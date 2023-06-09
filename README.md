<h1 align='center'>Arithmetica</h1>

> Infinite precision arithmetic has always been something that has fascinated me. This is an attempt to direct that fascination into something that might benefit other people too.
<br>
<div align='center'>
  If thou dost find this test passing, thou art assured of a library that doth not suffer from memory leaks.
  <br>
  <a href='https://github.com/arithmetica-org/arithmetica/actions/workflows/tests.yml'>
    <img src='https://github.com/arithmetica-org/arithmetica/actions/workflows/tests.yml/badge.svg'>
  </a>
</div>
<br>
Arithmetica is a general-purpose infinite precision Linux and windows math library with a wide variety of mathematical functions and features. Currently supported languages are C, C++, and Python.

# Documentation
The documentation for arithmetica can be found [here](https://arithmetica-org.github.io/arithmetica-docs/)!

# Demonstration
Using [construct_regular_polygon.c](https://github.com/avighnac/arithmetica/blob/main/src/library/geometry/construct_regular_polygon.c), you can create and render polygons.
<div align='center'>
  <img width="400" height="400" src='https://user-images.githubusercontent.com/74564976/223171924-53bd642e-425f-4870-aa0e-2da184dd9f52.gif'>
</div>

The code for this can be found after the usage section.
<p>(<a href="#code-for-demonstration">Code</a>)</p>

## Python

### Using pip!

If you're on or above Python 3.10, then pip will work for you. See below if not.
```shell
pip install arithmetica-py
```

### Using binaries
Go to the [project page](https://pypi.org/project/arithmetica-py/) on PyPi and download the built distributions. Use pip to install the .whl file as per your operating system.

## C/C++

### Linux
Linux users are in luck! If you're on Linux, then you can automatically copy the '.a', '.so', '.h', and '.hpp' to `/usr/include` with one command! Note that you will also need to [install basic_math_operations](https://github.com/avighnac/basic_math_operations): this can be done similarly.

```shell
curl -s -H "Accept: application/vnd.github.v3.raw" https://api.github.com/repos/arithmetica-org/arithmetica/contents/install.sh | sudo bash
```

### Windows

Include the header [arithmetica.h]() and download the `.a` file from the [releases section](https://github.com/arithmetica-org/arithmetica/releases/).
```c
#include "arithmetica.h"

// your code here
// ...
```
This library uses [basic_math_operations](https://github.com/avighnac/basic_math_operations) for infinite precision arithmetic.
To compile a program using [arithmetica](https://github.com/arithmetica-org/arithmetica), do the following:
## Command line
[Download basic_math_operations](https://github.com/avighnac/basic_math_operations/releases/) in a similar manner. However, you do not have to include any headers for [basic_math_operations](https://github.com/avighnac/basic_math_operations). Use the following command to compile:
`gcc/g++ filename.cpp/c [your arguments] -L. -larithmetica -lbasic_math_operations`
## CMake
Clone [basic_math_operations](https://github.com/avighnac/basic_math_operations) and [arithmetica](https://github.com/arithmetica-org/arithmetica) using `git`, or download the repositories. If your project is on GitHub, then use [submodules](https://github.blog/2016-02-01-working-with-submodules/) to prevent cluttering your language statistics. In either case, the repositories should be present in your project's base folder (or any subfolders in that base folder).

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

# Code for demonstration
```py
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import arithmetica
from PIL import Image

sides_init = 3
sides_max = 25
delay = 16 # in milliseconds

fig, ax = plt.subplots(figsize=(6, 6))
ax.set_aspect('equal')

polygon = arithmetica.construct_regular_polygon(sides_init, "1", 20)
polygon.append(("0", "0"))

x_coords = [float(pt[0]) for pt in polygon]
y_coords = [float(pt[1]) for pt in polygon]

line, = ax.plot(x_coords, y_coords)

def update(sides):
    polygon = arithmetica.construct_regular_polygon(sides, "1", 20)
    polygon.append(("0", "0"))

    x_coords = [float(pt[0]) for pt in polygon]
    y_coords = [float(pt[1]) for pt in polygon]

    line.set_xdata(x_coords)
    line.set_ydata(y_coords)

    max_x = max(x_coords)
    max_y = max(y_coords)

    min_x = min(x_coords)
    min_y = min(y_coords)

    x_margin = 0.05 * (max_x - min_x)
    y_margin = 0.05 * (max_y - min_y)
    ax.set_xlim(min_x - x_margin, max_x + x_margin)
    ax.set_ylim(min_y - y_margin, max_y + y_margin)

    # Hide the spines and remove the ticks
    ax.spines['top'].set_color('none')
    ax.spines['right'].set_color('none')
    ax.spines['bottom'].set_color('none')
    ax.spines['left'].set_color('none')
    ax.tick_params(axis='both', length=0, which='both')
    ax.set_axis_off()


# Create a list of images for each frame of the animation
images = []
for sides in range(sides_init, sides_max+1):
    update(sides)
    fig.canvas.draw_idle()
    fig.subplots_adjust
    img = Image.frombytes('RGB', fig.canvas.get_width_height(),
                          fig.canvas.tostring_rgb())
    images.append(img)

# Save the list of images as a GIF file
images[0].save('polygon.gif', save_all=True, append_images=images[1:], optimize=False, duration=delay, loop=0)

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
- `continued_fraction_to_fraction()` converts a [continued fraction](https://en.wikipedia.org/wiki/Continued_fraction) to a non-negative rational fraction.
- `cosine()` computes the [cosine](https://en.wikipedia.org/wiki/Sine_and_cosine) of an angle in radians to any decimal place.
- `exponential()` computes e^x, where x is any real number to any decimal place.
- `factorial()` computes the [factorial](https://en.wikipedia.org/wiki/Factorial) of a non-negative integer.
- `find_roots_of_polynomial()` finds the **exact** rational roots of a polynomial function.
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
