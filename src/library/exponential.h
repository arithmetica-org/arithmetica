#ifndef _exponential_h_
#define _exponential_h_

#include "clear_string.h"
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

char *exponential(const char *x_in, unsigned long accuracy) {
  // e^x = \displaystyle\sum_{n=0}^{\infty} \frac{x^n}{n!}
  //     = 1 + x + x^2 / (1 * 2) + x^3 / (1 * 2 * 3) + x^4 / (1 * 2 * 3 * 4) +
  //     ...

#define max(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a > _b ? _a : _b;                                                         \
  })

  char one[] = "1";

  char *answer = (char *)calloc(strlen(x_in) + 2, 1);
  add(x_in, one, answer);

  char *x = (char *)calloc(strlen(x_in) + 1, 1);
  strcpy(x, x_in);
  char *denominator = (char *)calloc(2, 1);
  denominator[0] = '1';
  char *i = (char *)calloc(2, 1);
  i[0] = '2';
  char *prevAfterDecimal = (char *)calloc(accuracy + 1, 1);
  unsigned char accuracyAchieved = 1;
  size_t decimalLocation = 0;

  while (1) {
    size_t sz_1 = strlen(x) + strlen(x_in) + 1;
    size_t sz_4 = strlen(i) + 2;
    size_t m = sz_1;
    char *buf = (char *)calloc(sz_1, 1);
    multiply(x, x_in, buf);
    x = (char *)realloc(x, sz_1);
    strcpy(x, buf);
    size_t sz_2 = strlen(denominator) + strlen(i) + 1;
    if (sz_2 > sz_1) {
      buf = (char *)realloc(buf, sz_2);
      m = sz_2;
    }
    clear_string_s(buf, m);
    multiply(denominator, i, buf);
    denominator = (char *)realloc(denominator, sz_2);
    strcpy(denominator, buf);
    size_t sz_3 = strlen(x) + strlen(denominator) + 2 * accuracy + 3;
    char *_buf = (char *)calloc(sz_3, 1);
    divide(x, denominator, _buf, 2 * accuracy);
    if (strlen(answer) + sz_3 + 1 > m) {
      m = strlen(answer) + sz_3 + 1;
      buf = (char *)realloc(buf, m);
    }
    clear_string_s(buf, m);
    add(answer, _buf, buf);
    answer = (char *)realloc(answer, m);
    strcpy(answer, buf);
    if (sz_4 > m) {
      m = sz_4;
      buf = (char *)realloc(buf, sz_4);
    }
    clear_string_s(buf, m);
    add(i, one, buf);
    i = (char *)realloc(i, m);
    strcpy(i, buf);

    free(buf);
    free(_buf);

    unsigned char found = 0;
    size_t location = 0;
    for (size_t i = 0; i < strlen(answer); i++) {
      if (answer[i] == '.') {
        location = i;
        found = 1;
        break;
      }
    }
    if (found) {
      decimalLocation = location;
      char *afterDecimal = (char *)calloc(accuracy + 1, 1);
      for (size_t i = 0; i < accuracy; i++) {
        if (i + location + 1 > strlen(answer)) {
          break;
          accuracyAchieved = 0;
        }
        afterDecimal[i] = answer[i + location + 1];
      }
      if (!strcmp(afterDecimal, prevAfterDecimal)) {
        free(afterDecimal);
        break;
      }
      strcpy(prevAfterDecimal, afterDecimal);
      free(afterDecimal);
    }
  }

  free(x);
  free(denominator);
  free(i);
  free(prevAfterDecimal);

  if (accuracyAchieved)
    answer[decimalLocation + accuracy + 1] = 0;

  return answer;
}

#endif