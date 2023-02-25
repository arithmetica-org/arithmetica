#include "fraction.h"

struct fraction
create_fraction (const char *n, const char *d)
{
  struct fraction f;
  f.numerator = (char *)malloc (strlen (n) + 1);
  f.denominator = (char *)malloc (strlen (d) + 1);
  strcpy (f.numerator, n);
  strcpy (f.denominator, d);
  return f;
}

void
delete_fraction (struct fraction f)
{
  free (f.numerator);
  free (f.denominator);
  return;
}