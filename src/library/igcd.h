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

  char *a = (char *)malloc(strlen(a_in) + 1);
  char *b = (char *)malloc(strlen(b_in) + 1);

  // allocate memory for some temporary variables
  char *quotient = (char *)calloc(max(strlen(a_in), strlen(b_in)) + 1, 1);
  char *temp = (char *)malloc(strlen(b_in) + 1);

  // copy over the input numbers
  strcpy(a, a_in);
  strcpy(b, b_in);

  // euclidean algorithm
  while (strcmp(b, "0")) {
    strcpy(temp, b);
    clear_string(quotient);
    clear_string(b);
    divide_whole_with_remainder(a, temp, quotient, b);
    strcpy(a, temp);
  }

  strcpy(gcd, a);

  free(a);
  free(b);
  free(quotient);
  free(temp);
}

#endif