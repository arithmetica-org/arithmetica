#ifndef _arctan_h_
#define _arctan_h_

#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

char *arctan(const char *number, size_t accuracy) {
  // arctan(x) = \displaystyle \sum_{n=0}^{\infty} (-1)^n x^(2n+1) / (2n+1)
  //           = x - x^3 / 3 + x^5 / 5 - x^7 / 7 + ...

  accuracy += 2;

  unsigned char toggle = 0;
  char two[] = "2";
  char *i = (char *)calloc(2, 1);
  char *x = (char *)calloc(strlen(number) + 1, 1);
  char *x_squared = (char *)calloc(2 * strlen(number) + 1, 1);
  char *answer = (char *)calloc(strlen(number) + 1, 1);
  multiply(number, number, x_squared);
  strcpy(x, number);
  strcpy(answer, number);
  i[0] = '1';

  char *maxDiff = (char *)calloc(accuracy + 3, 1);
  maxDiff[0] = '0';
  if (accuracy > 0) {
    maxDiff[1] = '.';
    for (size_t i = 1; i < accuracy; i++)
      maxDiff[i + 1] = '0';
    maxDiff[accuracy] = '1';
  }
  char *prev = (char *)calloc(2, 1);
  prev[0] = '0';
  size_t decimalLocation = 0;

  while (1) {
    toggle = !toggle; // (-1)^n
    size_t m = strlen(i) + 2;
    char *buf = (char *)calloc(m, 1);
    add(i, two, buf); // i += 2 for the denominator
    i = (char *)realloc(i, m);
    strcpy(i, buf);
    m = strlen(x_squared) + strlen(x) + 1;
    buf = (char *)realloc(buf, m);
    memset(buf, 0, m);
    multiply(x, x_squared, buf); // x *= x^2
    x = (char *)realloc(x, m);
    strcpy(x, buf);
    m = strlen(x) + strlen(i) + 2 * accuracy + 3;
    buf = (char *)realloc(buf, m);
    memset(buf, 0, m);
    divide(x, i, buf, 2 * accuracy); // buf = x / i
    char *_buf = (char *)calloc(strlen(answer) + strlen(buf) + 3, 1);
    toggle ? subtract(answer, buf, _buf)
           : add(answer, buf, _buf); // add/subtract the next taylor series term
    answer = (char *)realloc(answer, strlen(_buf) + 1);
    strcpy(answer, _buf);

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

    char *diff = (char *)calloc(strlen(prev) + strlen(answer) + 3, 1);
    subtract(answer, prev, diff);
    if (diff[0] == '-') {
      for (size_t i = 0; i < strlen(diff) - 1; i++)
        diff[i] = diff[i + 1];
      diff[strlen(diff) - 1] = 0;
    }

    char *__buf = (char *)calloc(strlen(diff) + strlen(maxDiff) + 3, 1);
    subtract(diff, maxDiff, __buf);

    if (__buf[0] == '-') {
      free(diff);
      free(__buf);
      break;
    }

    prev = (char *)realloc(prev, strlen(answer) + 1);
    strcpy(prev, answer);
    free(diff);
    free(__buf);
  }

  free(i);
  free(x);
  free(x_squared);

  if (number[0] == '-')
    decimalLocation++;
  answer[decimalLocation + accuracy] = 0;

  return answer;
}

#endif