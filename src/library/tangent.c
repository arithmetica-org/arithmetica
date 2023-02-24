#include "arithmetica.h"
#include <basic_math_operations.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *
tangent (const char *number, size_t accuracy)
{
  // tan(x) = sin(x) / cos(x)
  char *sine_n = sine (number, accuracy);
  char *cosine_n = cosine (number, accuracy);
  char *answer
      = (char *)calloc (strlen (sine_n) + strlen (cosine_n) + accuracy + 3, 1);
  divide (sine_n, cosine_n, answer, accuracy);

  free (sine_n);
  free (cosine_n);

  return answer;
}