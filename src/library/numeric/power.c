#include <arithmetica.h>
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

  // 0^n = 0, except when n = 0
  if (!strcmp(x, "0")) {
    char *answer = (char *)calloc (2, 1);
    if (!strcmp(n, "0")) {
      strcpy (answer, "1");
    } else {
      strcpy (answer, "0");
    }
    free(x);
    free(n);
    return answer;
  }

  if (strchr (n, '.') == NULL)
    {
      long n_z = 0;
      for (size_t i = n_in[0] == '-' ? 1 : 0; i < strlen (n_in); ++i)
        n_z = n_z * 10 + n_in[i] - '0';
      if (n_in[0] == '-')
        n_z *= -1;

      char *answer = power_integer (x, n_z, accuracy);

      free(x);
      free(n);

      return answer;
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