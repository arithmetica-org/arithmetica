#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void
igcd (const char *a_in, const char *b_in, char *gcd)
{
  if (a_in[0] == '\0' || b_in[0] == '\0')
    return;

  // gcd(n,1) = 1
  if (strcmp (a_in, "1") == 0 || strcmp (b_in, "1") == 0)
    {
      strcpy (gcd, "1");
      return;
    }

  size_t buffer_sizes = strlen (a_in) + strlen (b_in) + 3;

  char *a = (char *)calloc (buffer_sizes, 1);
  char *b = (char *)calloc (buffer_sizes, 1);

  // allocate memory for some temporary variables
  char *quotient = (char *)calloc (buffer_sizes, 1);
  char *temp = (char *)calloc (buffer_sizes, 1);

  // copy over the input numbers, ignoring sign
  (*a_in == '-') ? strcpy (a, a_in + 1) : strcpy (a, a_in);
  (*b_in == '-') ? strcpy (b, b_in + 1) : strcpy (b, b_in);

  // euclidean algorithm
  while (strcmp (b, "0"))
    {
      strcpy (temp, b);
      memset (quotient, 0, buffer_sizes);
      memset (b, 0, buffer_sizes);
      divide_whole_with_remainder (a, temp, quotient, b);
      strcpy (a, temp);
    }

  strcpy (gcd, a);

  free (a);
  free (b);
  free (quotient);
  free (temp);
  return;
}