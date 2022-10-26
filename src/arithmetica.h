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

#endif