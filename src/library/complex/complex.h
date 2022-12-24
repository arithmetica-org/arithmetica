#ifndef _complex_h_
#define _complex_h_

#include <stdlib.h>
#include <string.h>

struct complex {
  char *real;
  char *imaginary;
};

struct complex create_complex_number(const char *re, const char *im) {
  struct complex n;
  n.real = (char *)calloc(strlen(re) + 1, 1);
  n.imaginary = (char *)calloc(strlen(im) + 1, 1);
  strcpy(n.real, re);
  strcpy(n.imaginary, im);
  return n;
}

void delete_complex_number(struct complex n) {
  free(n.real);
  free(n.imaginary);
  return;
}

#endif