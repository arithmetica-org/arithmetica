#ifndef _natural_logarithm_h_
#define _natural_logarithm_h_

#include "arithmetica.h"
#include "power_integer.h"
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

char *natural_logarithm(const char *n, size_t accuracy) {
  size_t _accuracy = accuracy;
  char unity[] = "1";
  char two[] = "2";
  accuracy *= 4; // 10/3 is the real constant, but 4 further ensures
                 // that the answer is accurate.
  char *sqrt = (char *)calloc(strlen(n) + 1, 1);
  strcpy(sqrt, n);
  char *two_power_acc = power_integer(two, (long)accuracy, 0);
  for (size_t i = 0; i < accuracy; i++) {
    char *_buf = square_root(sqrt, accuracy);
    sqrt = (char *)realloc(sqrt, strlen(_buf) + 1);
    strcpy(sqrt, _buf);
    free(_buf);
  }
  char *buf = (char *)calloc(strlen(sqrt) + 2, 1);
  subtract(sqrt, unity, buf);
  char *answer = (char *)calloc(strlen(buf) + strlen(two_power_acc) + 3, 1);
  multiply(buf, two_power_acc, answer);
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
  free(two_power_acc);
  return answer;
}

#endif
