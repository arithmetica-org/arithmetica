#ifndef _power_integer_h_
#define _power_integer_h_

#include <basic_math_operations.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *power_integer(const char *x_in, long n, size_t accuracy) {
  // Evaluates x^n, where n is an integer.
  char unity[] = "1";
  char two[] = "2";
  char *x = (char *)calloc(strlen(x_in) + accuracy + 4, 1);

  if (n < 0) {
    divide(unity, x_in, x, accuracy);
    n *= -1;
  } else
    strcpy(x, x_in);

  char *result = (char *)calloc(2, 1);
  result[0] = '1';
  while (n >= 1) {
    char *buf = (char *)calloc(1, 1);
    if (n & 1) {
      size_t m = strlen(result) + strlen(x) + 3;
      buf = (char *)realloc(buf, m);
      memset(buf, 0, m);
      multiply(result, x, buf);
      result = (char *)realloc(result, m);
      strcpy(result, buf);
    }
    size_t m = 2 * strlen(x) + 3;
    buf = (char *)realloc(buf, m);
    memset(buf, 0, m);
    multiply(x, x, buf);
    x = (char *)realloc(x, m);
    strcpy(x, buf);
    n /= 2;
    free(buf);
  }

  free(x);

  return result;
}

#endif