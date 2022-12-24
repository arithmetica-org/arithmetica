#ifndef _subtract_complex_h_
#define _subtract_complex_h_

#include "complex.h"
#include <basic_math_operations.h>

struct complex subtract_complex(struct complex a, struct complex b) {
  struct complex answer;
  answer.real = (char *)calloc(strlen(a.real) + strlen(b.real) + 3, 1);
  answer.imaginary =
      (char *)calloc(strlen(a.imaginary) + strlen(b.imaginary) + 3, 1);
  subtract(a.real, b.real, answer.real);
  subtract(a.imaginary, b.imaginary, answer.imaginary);
  return answer;
}

#endif