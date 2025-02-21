#include <arithmetica.h>
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

void
ilcm (const char *a_in, const char *b_in, char *lcm)
{
  // lcm(a, b) = ab / gcd(a, b)
  size_t a_in_len = strlen (a_in);
  size_t b_in_len = strlen (b_in);
  
  char *product = (char *)calloc (a_in_len + b_in_len + 1, 1);
  char *gcd = (char *)malloc (((a_in_len > b_in_len)? a_in_len : b_in_len) + 1);

  multiply (a_in, b_in, product);
  igcd (a_in, b_in, gcd);

  divide (product, gcd, lcm, 0);

  free (product);
  free (gcd);
}