#ifndef _arithmetica_
#define _arithmetica_

#include <stddef.h>

#if defined(__cplusplus)
#define arithmetica_function_start extern "C"
#else
#define arithmetica_function_start
#endif

/// @brief Computes the inverse sine of a number less than 1.
/// @param number The number to compute the inverse sine of.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The inverse sine of the first argument. Free this pointer one it's
/// done being used.
arithmetica_function_start char *arcsin(const char *number, size_t accuracy);

/// @brief Computes the inverse tangent of a number less than 1.
/// @param x The number to compute the inverse tangent of.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The inverse tangent of the first argument. Free this pointer once
/// it's done being used.
arithmetica_function_start char *arctan(const char *number, size_t accuracy);

/// @brief Computes the cosine of the first argument.
/// @param number The angle to compute the cosine of, in radians.
/// @param accuracy The number of decimal places to calculate accuractely to.
/// @return The cosine of the first argument. Free this pointer once it's done
/// being used.
arithmetica_function_start char *cosine(const char *number, size_t accuracy);

/// @brief Computes e^x, where e is Euler's number: the base to the natural
/// logarithm.
/// @param x The number to raise e to.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The value of e^x. Free this pointer once it's done being used.
arithmetica_function_start char *exponential(const char *x, size_t accuracy);

/// @brief Finds the factorial of the first argument and stores the result in
/// the second argument.
/// @param n The number to find the factorial of.
/// @param factorial Where the factorial of [n] will be stored.
arithmetica_function_start void factorial(unsigned long n, char *factorial);

/// @brief Converts a non-negative rational fraction to a continued fraction.
/// @param numerator_in The numerator of the fraction.
/// @param denominator_in The denominator of the fraction.
/// @return A pointer to a char * containing the continued fraction
/// representation of the input fraction. Safe to print; free once done using.
arithmetica_function_start char *
fraction_to_continued_fraction(const char *numerator_in,
                               const char *denominator_in);

/// @brief Finds the greatest common divisor of the first and second integral
/// arguments.
/// @param a The first non-negative number to find the gcd of.
/// @param b The second non-negative number to find the gcd of.
/// @param gcd The gcd of the first two arguments.
arithmetica_function_start void igcd(const char *a, const char *b, char *gcd);

/// @brief Finds the lowest common multiple of the first and second integral
/// arguments.
/// @param a The first non-negative number to find the lcm of.
/// @param b The second non-negative number to find the lcm of.
/// @param lcm The lcm of the first two arguments.
arithmetica_function_start void ilcm(const char *a, const char *b, char *lcm);

/// @brief Computes the natural logarithm of a non-negative number
/// to any decimal place.
/// @param n The number to compute the natural logarithm of.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return A pointer to a char * containing the natural logarithm of the
/// input number.
arithmetica_function_start char *natural_logarithm(const char *n,
                                                   size_t accuracy);

/// @brief Computes x_in^n_in where x_in and n_in are two real numbers.
/// @param x_in The real number base.
/// @param n_in The real number exponent.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return A pointer to a char * containing x_in^n_in.
arithmetica_function_start char *power(const char *x_in, const char *n_in,
                                       size_t accuracy);

/// @brief Converts a repeating decimal to a fraction
/// @param non_repeating_part The part of the fraction (including the part
/// before the decimal place) that does not repeat. For example, in
/// 0.3343434..., "0.3" would be the non-repeating part.
/// @param repeating_part The part of the fraction which repeats. For example in
/// 0.3343434..., "34" would be the repeating part.
/// @param numerator_out The output numerator of the fraction.
/// @param denominator_out The output denominator of the fraction.
arithmetica_function_start void
repeating_decimal_to_fraction(const char *non_repeating_part,
                              const char *repeating_part, char *numerator_out,
                              char *denominator_out);

/// @brief Computes the sine of the first argument.
/// @param number The angle to compute the sine of, in radians.
/// @param accuracy The number of decimal places to calculate accuractely to.
/// @return The sine of the first argument. Free this pointer once it's done
/// being used.
arithmetica_function_start char *sine(const char *number, size_t accuracy);

/// @brief Computes the square root of the first argument.
/// @param number The non-negative number to compute the square root of.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The square root of the first argument. Free this pointer once it's
/// done being used.
arithmetica_function_start char *square_root(const char *number_in,
                                             size_t accuracy);

/// @brief Computes the trignometric tangent of the first argument.
/// @param number The angle to compute the tangent of, in radians.
/// @param accuracy The number of decimal places to calculate accuractely to.
/// @return The tangent of the first argument. Free this pointer once it's done
/// being used.
arithmetica_function_start char *tangent(const char *number, size_t accuracy);

/// @brief Converts a terminating decimal to a fraction reduced to its lowest
/// terms.
/// @param decimal The decimal number to convert to a fraction.
/// @param numerator_out The output numerator of the fraction.
/// @param denominator_out The output denominator of the fraction.
arithmetica_function_start void
terminating_decimal_to_fraction(const char *decimal, char *numerator_out,
                                char *denominator_out);
#endif
