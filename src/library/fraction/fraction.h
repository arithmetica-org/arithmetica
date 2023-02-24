#ifndef _fraction_h_
#define _fraction_h_

#include <stdlib.h>
#include <string.h>

struct fraction
{
  char *numerator;
  char *denominator;
};

struct fraction create_fraction (const char *n, const char *d);
void delete_fraction (struct fraction f);

#endif