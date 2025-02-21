#include "arithmetica.h"
#include "fraction_include.h"
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

void
arithmetica_power_fraction_round_decimal (char **in, size_t n)
{
  char *dot_pos = strchr (*in, '.');
  if (dot_pos == NULL)
    {
      return;
    }
  char *end_pos = dot_pos + n + 1;
  if (*end_pos >= '5')
    {
      char *pos = end_pos - 1;
      while (*pos == '9')
        {
          *pos = '0';
          pos--;
        }
      if (*pos == '.')
        {
          pos--;
        }
      while (*pos == '9')
        {
          *pos = '0';
          pos--;
        }
      (*pos)++;
    }
  *end_pos = '\0';
  while (end_pos > dot_pos && *(end_pos - 1) == '0')
    {
      *(--end_pos) = '\0';
    }
  if (*(end_pos - 1) == '.')
    {
      *(--end_pos) = '\0';
    }
}

struct fraction
power_fraction (struct fraction base_in, struct fraction exponent_in,
                size_t accuracy)
{
  struct fraction base;
  struct fraction exponent;
  base.numerator = (char *)calloc (strlen (base_in.numerator) + 1, 1);
  base.denominator = (char *)calloc (strlen (base_in.denominator) + 1, 1);
  exponent.numerator = (char *)calloc (strlen (exponent_in.numerator) + 1, 1);
  exponent.denominator
      = (char *)calloc (strlen (exponent_in.denominator) + 1, 1);
  strcpy (base.numerator, base_in.numerator);
  strcpy (base.denominator, base_in.denominator);
  strcpy (exponent.numerator, exponent_in.numerator);
  strcpy (exponent.denominator, exponent_in.denominator);

  // If the exponent is negative, then invert the fraction and make the
  // exponent positive since x^(-n) = (1/x)^n
  if (exponent.numerator[0] == '-')
    {
      size_t n = strlen (exponent.numerator);
      memmove (exponent.numerator, exponent.numerator + 1, n - 1);
      exponent.numerator[n - 1] = 0;

      // Reciprocate the fraction.
      if (base.numerator[0] == '-')
        {
          char *tempSwap = (char *)calloc (strlen (base.numerator), 1);
          strcpy (tempSwap, base.numerator + 1);
          base.numerator = (char *)realloc (base.numerator,
                                            strlen (base.denominator) + 2);
          strcpy (base.numerator + 1, base.denominator);
          base.denominator
              = (char *)realloc (base.denominator, strlen (tempSwap) + 1);
          strcpy (base.denominator, tempSwap);
          free (tempSwap);
        }
      else
        {
          char *tempSwap = (char *)calloc (strlen (base.numerator) + 1, 1);
          strcpy (tempSwap, base.numerator);
          base.numerator = (char *)realloc (base.numerator,
                                            strlen (base.denominator) + 1);
          strcpy (base.numerator, base.denominator);
          base.denominator
              = (char *)realloc (base.denominator, strlen (tempSwap) + 1);
          strcpy (base.denominator, tempSwap);
          free (tempSwap);
        }
    }

  char *exponentDecimal
      = (char *)calloc (strlen (exponent.numerator)
                            + strlen (exponent.denominator) + accuracy + 6,
                        1);
  divide (exponent.numerator, exponent.denominator, exponentDecimal,
          accuracy + 3);

  char *powerNumerator;
  char *powerDenominator;

  if (!strcmp(exponentDecimal, "0.5")) {
    // This is a square root, so use the square root function.
    // This speeds up the calculation by a lot.
    powerNumerator = square_root (base.numerator, accuracy + 3);
    powerDenominator = square_root (base.denominator, accuracy + 3);
  } else {
    powerNumerator = power (base.numerator, exponentDecimal, accuracy + 3);
    powerDenominator = power (base.denominator, exponentDecimal, accuracy + 3);
  }

  arithmetica_power_fraction_round_decimal (&powerNumerator, accuracy);
  arithmetica_power_fraction_round_decimal (&powerDenominator, accuracy);

  char *parseFractionArgument = (char *)calloc (
      strlen (powerNumerator) + strlen (powerDenominator) + 2, 1);
  strcpy (parseFractionArgument, powerNumerator);
  parseFractionArgument[strlen (powerNumerator)] = '/';
  strcpy (parseFractionArgument + strlen (powerNumerator) + 1,
           powerDenominator);
  struct fraction answer = parse_fraction (parseFractionArgument);

  free (exponentDecimal);
  free (powerNumerator);
  free (powerDenominator);
  free (parseFractionArgument);

  delete_fraction (base);
  delete_fraction (exponent);

  return answer;
}