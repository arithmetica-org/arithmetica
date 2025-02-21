#include <arithmetica.h>
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

void
repeating_decimal_to_fraction (const char *non_repeating_part_in,
                               const char *repeating_part, char *numerator_out,
                               char *denominator_out)
{
  char *non_repeating_part
      = (char *)malloc (strlen (non_repeating_part_in) + 1);
  strcpy (non_repeating_part, non_repeating_part_in);

  size_t decimalsRemoved = 0;
  unsigned char inDecimals = 0;
  for (size_t i = 0; i < strlen (non_repeating_part_in); i++)
    {
      if (inDecimals)
        {
          decimalsRemoved++;
          non_repeating_part[i - 1] = non_repeating_part[i];
        }
      if (non_repeating_part_in[i] == '.')
        inDecimals = 1;
    }
  if (inDecimals)
    non_repeating_part[strlen (non_repeating_part_in) - 1] = 0;

  // fraction = non_repeating_part + repeating_part /
  // strlen(repeating_part) nines

  char *nines
      = (char *)calloc (strlen (repeating_part) + decimalsRemoved + 1, 1);
  for (size_t i = 0; i < strlen (repeating_part); i++)
    nines[i] = '9';

  char *numerator = (char *)calloc (
      strlen (non_repeating_part_in) + strlen (repeating_part) + 1, 1);
  char *_numerator = (char *)calloc (
      strlen (non_repeating_part_in) + strlen (repeating_part) + 1, 1);
  multiply (nines, non_repeating_part, numerator);
  add (numerator, repeating_part, _numerator);

  for (size_t i = 0; i < decimalsRemoved; i++)
    nines[strlen (repeating_part) + i] = '0';

  size_t max = strlen (repeating_part) + decimalsRemoved;
  if (strlen (_numerator) > max)
    max = strlen (_numerator);
  char *gcd = (char *)calloc (max + 1, 1);
  igcd (_numerator, nines, gcd);
  divide (_numerator, gcd, numerator_out, 0);
  divide (nines, gcd, denominator_out, 0);

  free (non_repeating_part);
  free (nines);
  free (numerator);
  free (_numerator);
  free (gcd);
}