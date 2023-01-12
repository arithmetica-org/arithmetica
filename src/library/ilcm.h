#ifndef _ilcm_h_
#define _ilcm_h_

#include "igcd.h"
#include <basic_math_operations.h>
#include <string.h>

void
ilcm (const char *a_in, const char *b_in, char *lcm)
{
#define max(a, b)                                                             \
  ({                                                                          \
    __typeof__ (a) _a = (a);                                                  \
    __typeof__ (b) _b = (b);                                                  \
    _a > _b ? _a : _b;                                                        \
  })

  // lcm(a, b) = ab / gcd(a, b)
  char *product = (char *)calloc (strlen (a_in) + strlen (b_in) + 1, 1);
  char *gcd = (char *)malloc (max (strlen (a_in), strlen (b_in)) + 1);

  multiply (a_in, b_in, product);
  igcd (a_in, b_in, gcd);

  divide (product, gcd, lcm, 0);

  free (product);
  free (gcd);
}

#endif