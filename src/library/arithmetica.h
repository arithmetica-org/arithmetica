#ifndef _arithmetica_
#define _arithmetica_

#if defined(__cplusplus)
#define arithmetica_function_start extern "C"
#else
#define arithmetica_function_start
#endif

/// @brief Finds the factorial of the first argument and stores the result in
/// the second argument.
/// @param n The number to find the factorial of.
/// @param factorial Where the factorial of [n] will be stored.
arithmetica_function_start void factorial(unsigned long n, char *factorial);

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

/// @brief Converts a terminating decimal to a fraction reduced to its lowest
/// terms.
/// @param decimal The decimal number to convert to a fraction.
/// @param numerator_out The output numerator of the fraction.
/// @param denominator_out The output denominator of the fraction.
arithmetica_function_start void
terminating_decimal_to_fraction(const char *decimal, char *numerator_out,
                                char *denominator_out);
#endif