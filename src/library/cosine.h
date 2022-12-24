#ifndef _cosine_h_
#define _cosine_h_

#include "arcsin.h"
#include "sine.h"
#include "truncate.h"
#include <basic_math_operations.h>
#include <stddef.h>
#include <string.h>

char *cosine(const char *number, size_t accuracy) {
  // cos(x) = sin(pi / 2 - x)
  // = sin(arcsin(1) - x)

  char *half_pi = (char *)calloc(accuracy + 2, 1);
  if (accuracy > 100) {
    free(half_pi);
    half_pi = arcsin("1", accuracy);
  } else
    strcpy(half_pi, "1."
                    "5707963267948966192313216916397514420985846996875529104874"
                    "72296153908203143104499314017412671058533");
  truncate(half_pi, accuracy);
  char *sine_arg = (char *)calloc(strlen(half_pi) + strlen(number) + 3, 1);
  subtract(half_pi, number, sine_arg);
  char *answer = sine(sine_arg, accuracy);

  free(half_pi);
  free(sine_arg);

  return answer;
}

#endif