#include <arithmetica.h>
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

void
continued_fraction_to_fraction (char **continued_fraction,
                                unsigned long long continued_fraction_length,
                                char **numerator_out, char **denominator_out)
{
  char *numerator = *numerator_out;
  char *denominator = *denominator_out;
  if (continued_fraction_length == 0)
    {
      numerator = malloc (2);
      denominator = malloc (2);
      strcpy (numerator, "0");
      strcpy (denominator, "1");
      *numerator_out = numerator;
      *denominator_out = denominator;
      return;
    }
  if (continued_fraction_length < 2)
    {
      numerator = malloc (strlen (continued_fraction[0]) + 1);
      denominator = malloc (2);
      strcpy (numerator, continued_fraction[0]);
      strcpy (denominator, "1");
      *numerator_out = numerator;
      *denominator_out = denominator;
      return;
    }

  numerator = malloc (2);
  denominator = malloc (
      strlen (continued_fraction[continued_fraction_length - 1]) + 1);
  strcpy (numerator, "1");
  strcpy (denominator, continued_fraction[continued_fraction_length - 1]);
  for (size_t i = continued_fraction_length - 2; i + 1 > 0; --i)
    {
      char *mul = calloc (
          strlen (denominator) + strlen (continued_fraction[i]) + 3, 1);
      multiply (denominator, continued_fraction[i], mul);
      char *new_denominator
          = calloc (strlen (mul) + strlen (numerator) + 3, 1);
      add (mul, numerator, new_denominator);

      free (mul);
      free (numerator);
      numerator = denominator;
      denominator = new_denominator;
    }

  char *temp = numerator;
  numerator = denominator;
  denominator = temp;
  *numerator_out = numerator;
  *denominator_out = denominator;
  return;
}