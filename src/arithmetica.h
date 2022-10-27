#ifndef _arithmetica_
#define _arithmetica_

#if defined(__cplusplus)
#define arithmetica_function_start extern "C"
#else
#define arithmetica_function_start
#endif

/// @brief Finds the greatest common divisor of the first and second integral
/// arguments.
/// @param a_in The first non-negative number to find the gcd of.
/// @param b_in The second non-negative number to find the gcd of.
/// @param gcd The gcd of the first two arguments.
arithmetica_function_start void igcd(const char *a_in, const char *b_in,
                                     char *gcd);

/// @brief Finds the lowest common multiple of the first and second integral
/// arguments.
/// @param a_in The first non-negative number to find the lcm of.
/// @param b_in The second non-negative number to find the lcm of.
/// @param lcm The lcm of the first two arguments.
arithmetica_function_start void ilcm(const char *a_in, const char *b_in,
                                     char *lcm);

/// @brief Converts a terminating decimal to a fraction reduced to its lowest
/// terms.
/// @param decimal_in The decimal number to convert to a fraction.
/// @param numerator_out The output numerator of the fraction.
/// @param denominator_out The output denominator of the fraction.
arithmetica_function_start void
terminating_decimal_to_fraction(const char *decimal_in, char *numerator_out,
                                char *denominator_out);
#endif