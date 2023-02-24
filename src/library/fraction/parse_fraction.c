#include "fraction_include.h"
#include <stddef.h>

static long
return_decimals_and_remove_decimal_point (char **n_in)
{
  char *n = *n_in;
  long decimals = 0;
  const char *_loc = strchr (n, '.');
  if (_loc != NULL)
    {
      size_t n_len = strlen (n);
      size_t loc = _loc - n;
      decimals = n_len - loc - 1;
      char *buf = (char *)calloc (n_len, 1);
      strncpy (buf, n, loc);
      strncpy (buf + loc, _loc + 1, n_len - loc);
      strcpy (n, buf);
      free (buf);
    }
  *n_in = n;
  return decimals;
}

struct fraction
parse_fraction (const char *frac)
{
  struct fraction answer;
  const char *_loc = strchr (frac, '/');
  size_t frac_len = strlen (frac);
  if (_loc == NULL)
    {
      answer.numerator = (char *)calloc (frac_len + 1, 1);
      answer.denominator = (char *)calloc (2, 1);
      strcpy (answer.numerator, frac);
      *answer.denominator = '1';
    }
  else
    {
      size_t loc = _loc - frac;
      answer.numerator = (char *)calloc (loc + 1, 1);
      answer.denominator = (char *)calloc (frac_len - loc, 1);

      strncpy (answer.numerator, frac, loc);
      strncpy (answer.denominator, _loc + 1, frac_len - loc);

      // If the denominator is negative and the numerator isn't, then swap.
      if (answer.denominator[0] == '-' && answer.numerator[0] != '-')
        {
          memmove (answer.denominator, answer.denominator + 1,
                   strlen (answer.denominator) - 1);
          answer.denominator[strlen (answer.denominator) - 1] = 0;
          size_t n = strlen (answer.numerator);
          answer.numerator = (char *)realloc (answer.numerator, n + 2);
          memmove (answer.numerator + 1, answer.numerator, n + 1);
          answer.numerator[0] = '-';
        }
    }
  long d1 = return_decimals_and_remove_decimal_point (&answer.numerator),
       d2 = return_decimals_and_remove_decimal_point (&answer.denominator);
  long diff = d1 - d2;
  if (diff > 0)
    {
      size_t len = strlen (answer.denominator);
      answer.denominator
          = (char *)realloc (answer.denominator, len + diff + 1);
      for (size_t i = len; i < len + diff; i++)
        answer.denominator[i] = '0';
      answer.denominator[len + diff] = 0;
    }
  else if (diff < 0)
    {
      diff *= -1;
      size_t len = strlen (answer.numerator);
      answer.numerator = (char *)realloc (answer.numerator, len + diff + 1);
      for (size_t i = len; i < len + diff; i++)
        answer.numerator[i] = '0';
      answer.numerator[len + diff] = 0;
    }
  struct fraction _answer = simplify_parsed_fraction (answer);
  delete_fraction (answer);
  return _answer;
}