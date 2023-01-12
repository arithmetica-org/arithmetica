#ifndef _multiply_fraction_h_
#define _multiply_fraction_h_

#include "fraction.h"
#include "simplify_parsed_fraction.h"
#include <basic_math_operations.h>

struct fraction
multiply_fraction (struct fraction frac1, struct fraction frac2)
{
  struct fraction answer;
  answer.numerator = (char *)calloc (
      strlen (frac1.numerator) + strlen (frac2.numerator) + 3, 1);
  answer.denominator = (char *)calloc (
      strlen (frac1.denominator) + strlen (frac2.denominator) + 3, 1);
  multiply (frac1.numerator, frac2.numerator, answer.numerator);
  multiply (frac1.denominator, frac2.denominator, answer.denominator);
  struct fraction _answer = simplify_parsed_fraction (answer);

  delete_fraction (answer);

  return _answer;
}

#endif