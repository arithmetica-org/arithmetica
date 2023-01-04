#ifndef _fraction_h_
#define _fraction_h_

#include <stdlib.h>
#include <string.h>

struct fraction {
  char *numerator;
  char *denominator;
};

struct fraction create_fraction(const char *n, const char *d) {
  struct fraction f;
  f.numerator = (char *)calloc(strlen(n) + 1, 1);
  f.denominator = (char *)calloc(strlen(d) + 1, 1);
  strcpy(f.numerator, n);
  strcpy(f.denominator, d);
  return f;
}

void delete_fraction(struct fraction f) {
  free(f.numerator);
  free(f.denominator);
  return;
}

#endif