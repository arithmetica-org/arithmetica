#ifndef _complex_arithmetica_h_
#define _complex_arithmetica_h_

#include <stdlib.h>
#include <string.h>

struct complex_arithmetica
{
  char *real;
  char *imaginary;
};

struct complex_arithmetica create_complex_number (const char *re,
                                                  const char *im);
void delete_complex_number (struct complex_arithmetica n);

#endif