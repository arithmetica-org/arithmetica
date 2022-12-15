#ifndef _factorial_h_
#define _factorial_h_

#include "clear_string.h"
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

void factorial(unsigned long n, char *factorial) {
  // The number of digits in n! will never exceed n * floor(log_10(n) + 1)
  // In practice, it's almost always less than this. Using this approximation
  // doesn't waste much space. For 5-digit numbers, only 43kb is wasted.

  char *_factorial = (char *)calloc(n * __builtin_floorf(__builtin_log10(n) + 1) + 2, 1);
  factorial[0] = '1'; // 0! = 1

  char *str_i = (char *)calloc(__builtin_floorf(__builtin_log10(n) + 1) + 2, 1);
  char *_str_i = (char *)calloc(__builtin_floorf(__builtin_log10(n) + 1) + 2, 1);
  str_i[0] = '2';
  char one[] = "1";
  for (unsigned long i = 2; i <= n; i++) {
    strcpy(_factorial, factorial);
    clear_string(factorial);
    multiply(_factorial, str_i, factorial);
    strcpy(_str_i, str_i);
    clear_string(str_i);
    add(_str_i, one, str_i);
  }

  free(_factorial);
  free(str_i);
  free(_str_i);
}

#endif