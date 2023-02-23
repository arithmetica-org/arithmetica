#ifndef _subtract_complex_h_
#define _subtract_complex_h_

#include "complex_arithmetica.h"
#include <basic_math_operations.h>

struct complex_arithmetica
subtract_complex (struct complex_arithmetica a, struct complex_arithmetica b)
{
  struct complex_arithmetica answer;
  answer.real = (char *)calloc (strlen (a.real) + strlen (b.real) + 3, 1);
  answer.imaginary
      = (char *)calloc (strlen (a.imaginary) + strlen (b.imaginary) + 3, 1);
  subtract (a.real, b.real, answer.real);
  subtract (a.imaginary, b.imaginary, answer.imaginary);
  return answer;
}

#endif