#include "arithmetica.h"
#include "fraction_include.h"
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

struct fraction
simplify_parsed_fraction (struct fraction _frac)
{
  struct fraction answer;
  if (strlen (_frac.numerator) == 0 || strlen (_frac.denominator) == 0)
    {
      answer = create_fraction ("0", "1");
      return answer;
    }
  struct fraction frac;
  frac.numerator = (char *)malloc(strlen(_frac.numerator) + 1);
  frac.denominator = (char *)malloc(strlen(_frac.denominator) + 1);
  strcpy(frac.numerator, _frac.numerator);
  strcpy(frac.denominator, _frac.denominator);
  if (frac.numerator[0] != '-' && frac.denominator[0] == '-')
    {
      size_t n = strlen (frac.numerator);
      frac.numerator = (char *)realloc (frac.numerator, n + 2);
      memmove (frac.numerator + 1, frac.numerator, n);
      frac.numerator[0] = '-';
      frac.numerator[n + 1] = 0;
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
  delete_fraction(frac);

  return answer;
}