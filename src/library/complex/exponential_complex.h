#ifndef _exponential_complex_h_
#define _exponential_complex_h_

#include "../cosine.h"
#include "../exponential.h"
#include "../sine.h"
#include "complex_arithmetica.h"
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

struct complex_arithmetica
exponential_complex (struct complex_arithmetica n, size_t accuracy)
{
  char *e_power_a = exponential (n.real, accuracy);
  char *sin_b = sine (n.imaginary, accuracy);
  char *cos_b = cosine (n.imaginary, accuracy);
  struct complex_arithmetica answer;
  answer.real = (char *)calloc (strlen (e_power_a) + strlen (cos_b) + 3, 1);
  answer.imaginary
      = (char *)calloc (strlen (e_power_a) + strlen (sin_b) + 3, 1);
  multiply (e_power_a, cos_b, answer.real);
  multiply (e_power_a, sin_b, answer.imaginary);

  free (e_power_a);
  free (sin_b);
  free (cos_b);

  return answer;
}

#endif