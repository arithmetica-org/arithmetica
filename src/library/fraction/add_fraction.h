#ifndef _add_fraction_
#define _add_fraction_

#include "fraction.h"
#include "simplify_parsed_fraction.h"
#include <basic_math_operations.h>

struct fraction
add_fraction (struct fraction frac1, struct fraction frac2)
{
  size_t frac1_den_len = strlen (frac1.denominator);
  size_t frac2_den_len = strlen (frac2.denominator);
  struct fraction answer;
  char *mul_1
      = (char *)calloc (strlen (frac1.numerator) + frac2_den_len + 3, 1);
  char *mul_2
      = (char *)calloc (strlen (frac2.numerator) + frac1_den_len + 3, 1);
  answer.denominator = (char *)calloc (frac1_den_len + frac2_den_len + 3, 1);
  multiply (frac1.numerator, frac2.denominator, mul_1);
  multiply (frac1.denominator, frac2.numerator, mul_2);
  multiply (frac1.denominator, frac2.denominator, answer.denominator);
  answer.numerator = (char *)calloc (strlen (mul_1) + strlen (mul_2) + 3, 1);
  add (mul_1, mul_2, answer.numerator);
  struct fraction _answer = simplify_parsed_fraction (answer);

  delete_fraction (answer);
  free (mul_1);
  free (mul_2);

  return _answer;
}

#endif