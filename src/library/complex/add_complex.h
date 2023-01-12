#ifndef _add_complex_h_
#define _add_complex_h_

#include "complex.h"
#include <basic_math_operations.h>

struct complex
add_complex (struct complex a, struct complex b)
{
  struct complex answer;
  answer.real = (char *)calloc (strlen (a.real) + strlen (b.real) + 3, 1);
  answer.imaginary
      = (char *)calloc (strlen (a.imaginary) + strlen (b.imaginary) + 3, 1);
  add (a.real, b.real, answer.real);
  add (a.imaginary, b.imaginary, answer.imaginary);
  return answer;
}

#endif