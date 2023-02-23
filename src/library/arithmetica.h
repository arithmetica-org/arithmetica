#ifndef _arithmetica_
#define _arithmetica_

#include <stddef.h>

#if defined(__cplusplus)
#define arithmetica_function_start extern "C"
#else
#define arithmetica_function_start
#endif

/// @brief Computes the inverse cosine of a number less than 1.
/// @param number The number to compute the inverse cosine of.
/// @param accuracy The number of decimal places to calculate accurately.
/// @return The inverse cosine of the first argument. Free this pointer one
/// it's done being used.
arithmetica_function_start char *arccos (const char *number, size_t accuracy);

/// @brief Computes the inverse sine of a number less than 1.
/// @param number The number to compute the inverse sine of.
/// @param accuracy The number of decimal places to calculate accurately.
/// @return The inverse sine of the first argument. Free this pointer once its
/// done being used.
arithmetica_function_start char *arcsin (const char *number, size_t accuracy);

/// @brief Computes the inverse tangent of a number less than 1.
/// @param x The number to compute the inverse tangent of.
/// @param accuracy The number of decimal places to calculate accurately.
/// @return The inverse tangent of the first argument. Free this pointer once
/// it's done being used.
arithmetica_function_start char *arctan (const char *number, size_t accuracy);

/// @brief Computes the cosine of the first argument.
/// @param number The angle to compute the cosine of, in radians.
/// @param accuracy The number of decimal places to calculate accurately.
/// @return The cosine of the first argument. Free this pointer once it's done
/// being used.
arithmetica_function_start char *cosine (const char *number, size_t accuracy);

/// @brief Computes e^x, where e is Euler's number: the base to the natural
/// logarithm.
/// @param x The number to raise e to.
/// @param accuracy The number of decimal places to calculate accurately.
/// @return The value of e^x. Free this pointer once it's done being used.
arithmetica_function_start char *exponential (const char *x, size_t accuracy);

/// @brief Finds the factorial of the first argument and stores the result in
/// the second argument.
/// @param n The number to find the factorial of.
/// @param factorial Where the factorial of [n] will be stored.
arithmetica_function_start void factorial (unsigned long n, char *factorial);

/// @brief Converts a non-negative rational fraction to a continued fraction.
/// @param numerator_in The numerator of the fraction.
/// @param denominator_in The denominator of the fraction.
/// @return A pointer to a char * containing the continued fraction
/// representation of the input fraction. Safe to print; free once done using.
arithmetica_function_start char *
fraction_to_continued_fraction (const char *numerator_in,
                                const char *denominator_in);

/// @brief Finds the greatest common divisor of the first and second integral
/// arguments.
/// @param a The first non-negative number to find the gcd of.
/// @param b The second non-negative number to find the gcd of.
/// @param gcd The gcd of the first two arguments.
arithmetica_function_start void igcd (const char *a, const char *b, char *gcd);

/// @brief Finds the lowest common multiple of the first and second integral
/// arguments.
/// @param a The first non-negative number to find the lcm of.
/// @param b The second non-negative number to find the lcm of.
/// @param lcm The lcm of the first two arguments.
arithmetica_function_start void ilcm (const char *a, const char *b, char *lcm);

/// @brief Computes the natural logarithm of a non-negative number
/// to any decimal place.
/// @param n The number to compute the natural logarithm of.
/// @param accuracy The number of decimal places to calculate accurately.
/// @return A pointer to a char * containing the natural logarithm of the
/// input number.
arithmetica_function_start char *natural_logarithm (const char *n,
                                                    size_t accuracy);

/// @brief Computes x_in^n_in where x_in and n_in are two real numbers.
/// @param x_in The real number base.
/// @param n_in The real number exponent.
/// @param accuracy The number of decimal places to calculate accurately.
/// @return A pointer to a char * containing x_in^n_in.
arithmetica_function_start char *power (const char *x_in, const char *n_in,
                                        size_t accuracy);

/// @brief Converts a repeating decimal to a fraction
/// @param non_repeating_part The part of the fraction (including the part
/// before the decimal place) that does not repeat. For example, in
/// 0.3343434..., "0.3" would be the non-repeating part.
/// @param repeating_part The part of the fraction which repeats. For example
/// in 0.3343434..., "34" would be the repeating part.
/// @param numerator_out The output numerator of the fraction.
/// @param denominator_out The output denominator of the fraction.
arithmetica_function_start void
repeating_decimal_to_fraction (const char *non_repeating_part,
                               const char *repeating_part, char *numerator_out,
                               char *denominator_out);

/// @brief Simplifies an arithmetic expression involving the five basic math
/// operations: addition, subtraction, multiplication, division, and
/// exponentiation.
/// @param expression The expression to simplify, in standard computer
/// mathematical notation.
/// @param outputType This parameter controls the output type. Use zero to
/// output a decimal, one to output a fraction, and two to output a mixed
/// fraction. Output types one and two will calculate everything with maximum
/// precision.
/// @param accuracy The accuracy of the divisions and exponentiations
/// performed. You only need to worry about this if you have fractional
/// exponents in your input, or if you have divisions in output type zero.
/// @return The simplified expression.
arithmetica_function_start char *
simplify_arithmetic_expression (const char *expression_in, int outputType,
                                size_t accuracy);

/// @brief Computes the sine of the first argument.
/// @param number The angle to compute the sine of, in radians.
/// @param accuracy The number of decimal places to calculate accurately.
/// @return The sine of the first argument. Free this pointer once it's done
/// being used.
arithmetica_function_start char *sine (const char *number, size_t accuracy);

/// @brief Computes the square root of the first argument.
/// @param number The non-negative number to compute the square root of.
/// @param accuracy The number of decimal places to calculate accurately.
/// @return The square root of the first argument. Free this pointer once it's
/// done being used.
arithmetica_function_start char *square_root (const char *number_in,
                                              size_t accuracy);

/// @brief Computes the trigonometric tangent of the first argument.
/// @param number The angle to compute the tangent of, in radians.
/// @param accuracy The number of decimal places to calculate accurately.
/// @return The tangent of the first argument. Free this pointer once it's done
/// being used.
arithmetica_function_start char *tangent (const char *number, size_t accuracy);

/// @brief Converts a terminating decimal to a fraction reduced to its lowest
/// terms.
/// @param decimal The decimal number to convert to a fraction.
/// @param numerator_out The output numerator of the fraction.
/// @param denominator_out The output denominator of the fraction.
arithmetica_function_start void
terminating_decimal_to_fraction (const char *decimal, char *numerator_out,
                                 char *denominator_out);

// Fractional number functions

struct fraction
{
  char *numerator;
  char *denominator;
};

/// @brief Adds two fractions and reduces the result to its simplest form.
/// @param frac1 The first fraction to add.
/// @param frac2 The second fraction to add.
/// @return Where frac1 + frac2 will be stored.
arithmetica_function_start struct fraction
add_fraction (struct fraction frac1, struct fraction frac2);

/// @brief Multiplies two fractions and reduces the result to its simplest
/// form.
/// @param frac1 The first fraction to multiply.
/// @param frac2 The second fraction to multiply.
/// @return Where frac1 * frac2 will be stored.
arithmetica_function_start struct fraction
multiply_fraction (struct fraction frac1, struct fraction frac2);

arithmetica_function_start struct fraction create_fraction (const char *n,
                                                            const char *d);

arithmetica_function_start void delete_fraction (struct fraction f);

/// @brief Extracts a fraction from a string and/or converts a decimal to a
/// fraction.
/// @param frac The fraction as a decimal and/or in the form a/b, where a and b
/// are decimal numbers.
/// @return The fractional representation of `frac` in its simplest form.
arithmetica_function_start struct fraction parse_fraction (const char *frac);

/// @brief Subtractss two fractions and reduces the result to its simplest
/// form.
/// @param frac1 The first fraction to subtract.
/// @param frac2 The second fraction to subtract.
/// @return Where frac1 - frac2 will be stored.
arithmetica_function_start struct fraction
subtract_fraction (struct fraction frac1, struct fraction frac2);

/// @brief Raises a fraction to a fractional power and reduces the result to
/// its simplest form.
/// @param base The base of the exponentiation.
/// @param exponent The exponent of the exponentiation.
/// @param accuracy The accuracy of the exponentiation.
/// @return Where frac1^frac2 will be stored.
arithmetica_function_start struct fraction
power_fraction (struct fraction base, struct fraction exponent,
                size_t accuracy);

// Geometry functions

/// @brief Constructs an n-sided regular polygon.
/// @param n The number of sides of the polygon.
/// @param length The length of each side.
/// @param accuracy The decimal place accuracy of the construction.
/// @return Returns an array of points, each with a malloc'd char *. Free each
/// of these once they're done being used.
arithmetica_function_start struct point *
construct_regular_polygon (int n, const char *length, size_t accuracy);

// Complex number functions

struct complex_arithmetica
{
  char *real;
  char *imaginary;
};

arithmetica_function_start struct complex_arithmetica
create_complex_number (const char *re, const char *im);
arithmetica_function_start void
delete_complex_number (struct complex_arithmetica n);

/// @brief Adds two complex numbers. If you're using this function, you know
/// what complex numbers are.
/// @param a The first complex number to add.
/// @param b The second complex number to add.
/// @return Where a + b will be stored.
arithmetica_function_start struct complex_arithmetica
add_complex (struct complex_arithmetica a, struct complex_arithmetica b);

/// @brief Subtracts two complex numbers. If you're using this function, you
/// know what complex numbers are.
/// @param a The first complex number to subtract.
/// @param b The second complex number to subtract.
/// @return Where a - b will be stored.
arithmetica_function_start struct complex_arithmetica
subtract_complex (struct complex_arithmetica a, struct complex_arithmetica b);

/// @brief Multiples two complex numbers. If you're using this function, you
/// know what complex numbers are.
/// @param a The first complex number to multiply.
/// @param b The second complex number to multiply.
/// @return Where a * b will be stored.
arithmetica_function_start struct complex_arithmetica
multiply_complex (struct complex_arithmetica a, struct complex_arithmetica b);

/// @brief Divides two complex numbers. If you're using this function, you
/// know what complex numbers are.
/// @param a The complex numerator.
/// @param b The complex number denominator.
/// @param accuracy The number of decimal places the division will be accurate
/// to.
/// @return Where a / b will be stored.
arithmetica_function_start struct complex_arithmetica
divide_complex (struct complex_arithmetica a, struct complex_arithmetica b,
                size_t accuracy);

/// @brief Computes the square root of a complex number. If you're using this
/// function, you know what complex numbers are.
/// @param n The complex number to find the square root of.
/// @param accuracy The number of decimals the square root will be accurate to.
/// @return Where sqrt(n) will be stored.
arithmetica_function_start struct complex_arithmetica
square_root_complex (struct complex_arithmetica n, size_t accuracy);

/// @brief Computes e^(a + bi), where a + bi is a complex number to any decimal
/// place.
/// @param n The complex number to exponentiate.
/// @param accuracy The number of decimals the calculation will be accurate to.
/// @return Where e^(a + bi) will be stored.
arithmetica_function_start struct complex_arithmetica
exponential_complex (struct complex_arithmetica n, size_t accuracy);
#endif