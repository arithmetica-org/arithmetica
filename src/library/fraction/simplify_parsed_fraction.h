#ifndef _simplify_parsed_fraction_
#define _simplify_parsed_fraction_

#include "../igcd.h"
#include "fraction.h"
#include <basic_math_operations.h>

struct fraction
simplify_parsed_fraction (struct fraction frac)
{
  struct fraction answer;
  if (strlen (frac.numerator) == 0 || strlen (frac.denominator) == 0)
    {
      answer = create_fraction ("0", "1");
      return answer;
    }
  if (frac.numerator[0] != '-' && frac.denominator[0] == '-')
    {
      size_t n = strlen (frac.numerator);
      frac.numerator = (char *)realloc (frac.numerator, n + 2);
      memmove (frac.numerator + 1, frac.numerator, n);
      frac.numerator[0] = '-';
      n = strlen (frac.denominator);
      memmove (frac.denominator, frac.denominator + 1, n - 1);
      frac.denominator[n - 1] = 0;
    }
  if (frac.numerator[0] == '-' && frac.denominator[0] == '-')
    {
      size_t n = strlen (frac.numerator);
      memmove (frac.numerator, frac.numerator + 1, n - 1);
      frac.numerator[n - 1] = 0;
      n = strlen (frac.denominator);
      memmove (frac.denominator, frac.denominator + 1, n - 1);
      frac.denominator[n - 1] = 0;
    }

  size_t numerator_len = strlen (frac.numerator),
         denominator_len = strlen (frac.denominator);

  char *hcf = (char *)calloc (numerator_len + denominator_len + 3, 1);
  igcd (frac.numerator, frac.denominator, hcf);
  size_t hcf_len = strlen (hcf);
  answer.numerator = (char *)calloc (numerator_len + hcf_len + 3, 1);
  answer.denominator = (char *)calloc (denominator_len + hcf_len + 3, 1);
  divide (frac.numerator, hcf, answer.numerator, 0);
  divide (frac.denominator, hcf, answer.denominator, 0);

  free (hcf);

  return answer;
}

#endif