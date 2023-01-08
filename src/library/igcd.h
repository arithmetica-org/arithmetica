#ifndef _igcd_h_
#define _igcd_h_

#include "clear_string.h"
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

void igcd(const char *a_in, const char *b_in, char *gcd) {
#define max(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a > _b ? _a : _b;                                                         \
  })

  if (strlen(a_in) == 0 || strlen(b_in) == 0)
    return;

  char *a = (char *)calloc(strlen(a_in) + strlen(b_in) + 3, 1);
  char *b = (char *)calloc(strlen(a_in) + strlen(b_in) + 3, 1);

  // allocate memory for some temporary variables
  char *quotient = (char *)calloc(strlen(a_in) + strlen(b_in) + 3, 1);
  char *temp = (char *)calloc(strlen(a_in) + strlen(b_in) + 3, 1);

  // copy over the input numbers, ignoring sign
  (*a_in == '-') ? strcpy(a, a_in + 1) : strcpy(a, a_in);
  (*b_in == '-') ? strcpy(b, b_in + 1) : strcpy(b, b_in);

  // euclidean algorithm
  while (strcmp(b, "0")) {
    strcpy(temp, b);
    clear_string(quotient);
    clear_string(b);
    divide_whole_with_remainder(a, temp, quotient, b);
    remove_zeroes(quotient);
    remove_zeroes(b);
    strcpy(a, temp);
  }

  remove_zeroes(a);
  strcpy(gcd, a);

  free(a);
  free(b);
  free(quotient);
  free(temp);
  return;
}

#endif