#include "fraction_include.h"
#include <basic_math_operations.h>
#include <stdbool.h>

bool
equal_fraction (struct fraction _a, struct fraction _b)
{
  if ((strcmp (_a.numerator, "0") == 0 && strcmp (_b.numerator, "-0") == 0)
      || (strcmp (_a.numerator, "-0") == 0 && strcmp (_b.numerator, "0") == 0))
    {
      return true;
    }
  return strcmp (_a.numerator, _b.numerator) == 0
         && strcmp (_a.denominator, _b.denominator) == 0;
}