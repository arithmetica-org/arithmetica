#ifndef _power_h_
#define _power_h_

#include "exponential.h"
#include "natural_logarithm.h"
#include "power_integer.h"
#include <basic_math_operations.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *
power (const char *x_in, const char *n_in, size_t accuracy)
{
  size_t _accuracy = accuracy;
  accuracy = (size_t)((double)accuracy * 5.0 / 3);
  char *x = (char *)calloc (strlen (x_in) + 1, 1);
  char *n = (char *)calloc (strlen (n_in) + 1, 1);
  strcpy (x, x_in);
  strcpy (n, n_in);
  remove_zeroes (x);
  remove_zeroes (n);
  if (strchr (n, '.') == NULL)
    {
      long n_z = 0;
      for (size_t i = n_in[0] == '-' ? 1 : 0; i < strlen (n_in); i++)
        n_z = n_z * 10 + n_in[i] - '0';
      if (n_in[0] == '-')
        n_z *= -1;
      return power_integer (x, n_z, accuracy);
    }

  char *ln = natural_logarithm (x, accuracy);
  char *n_ln_x = (char *)calloc (strlen (n) + strlen (ln) + 3, 1);
  multiply (n, ln, n_ln_x);
  char *answer = exponential (n_ln_x, accuracy);
  free (x);
  free (n);
  free (ln);
  free (n_ln_x);

  char *_dec_loc = strchr (answer, '.');
  size_t dec_loc = _dec_loc - answer;
  if (dec_loc + _accuracy + 1 < strlen (answer))
    answer[dec_loc + _accuracy + 1] = 0;

  return answer;
}

#endif