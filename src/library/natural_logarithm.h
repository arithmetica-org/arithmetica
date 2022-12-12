#ifndef _natural_logarithm_h_
#define _natural_logarithm_h_

#include "arithmetica.h"
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

char *natural_logarithm(const char *n, size_t accuracy) {
  size_t _accuracy = accuracy;
  accuracy = (size_t)((double)accuracy *
                      4); // 10/3 is the real constant, but 4 further ensures
                          // that the answer is accurate.
  char *sqrt = (char *)calloc(strlen(n) + 1, 1);
  strcpy(sqrt, n);
  char *two_power_n = (char *)calloc(2, 1);
  two_power_n[0] = '1';
  char unity[] = "1";
  for (size_t i = 0; i < accuracy; i++) {
    char *buf = (char *)calloc(strlen(two_power_n) + 2, 1);
    add(two_power_n, two_power_n, buf);
    two_power_n = (char *)realloc(two_power_n, strlen(buf) + 1);
    strcpy(two_power_n, buf);
    char *_buf = square_root(sqrt, accuracy);
    sqrt = (char *)realloc(sqrt, strlen(_buf) + 1);
    strcpy(sqrt, _buf);
    free(_buf);
    free(buf);
  }
  char *buf = (char *)calloc(strlen(sqrt) + 2, 1);
  subtract(sqrt, unity, buf);
  char *answer = (char *)calloc(strlen(buf) + strlen(two_power_n) + 3, 1);
  multiply(buf, two_power_n, answer);
  size_t dec_loc = 0;
  for (size_t i = 0; i < strlen(answer); i++) {
    if (answer[i] == '.') {
      dec_loc = i;
      break;
    }
  }
  if (dec_loc + _accuracy + 1 < strlen(answer))
    answer[dec_loc + _accuracy + 1] = 0;
  free(buf);
  free(sqrt);
  free(two_power_n);
  return answer;
}

#endif
