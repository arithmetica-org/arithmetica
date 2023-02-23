#ifndef _divide_complex_h
#define _divide_complex_h

#include "complex_arithmetica.h"
#include "multiply_complex.h"
#include <basic_math_operations.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct complex_arithmetica
divide_complex (struct complex_arithmetica numerator,
                struct complex_arithmetica denominator, size_t accuracy)
{
  // (a + bi) / (c + di) = [ (a + bi) (c - di) ] / [ c^2 + d^2 ]

  char *c_squ = (char *)calloc (2 * strlen (denominator.real) + 3, 1);
  char *d_squ = (char *)calloc (2 * strlen (denominator.imaginary) + 3, 1);

  multiply (denominator.real, denominator.real, c_squ);
  multiply (denominator.imaginary, denominator.imaginary, d_squ);

  char *divisor = (char *)calloc (strlen (c_squ) + strlen (d_squ) + 3, 1);

  add (c_squ, d_squ, divisor);

  // negate denominator.imaginary
  if (denominator.imaginary[0] == '-')
    {
      memmove (denominator.imaginary, denominator.imaginary + 1,
               strlen (denominator.imaginary) - 1);
    }
  else
    {
      size_t n = strlen (denominator.imaginary);
      denominator.imaginary = (char *)realloc (denominator.imaginary, n + 2);
      memmove (denominator.imaginary + 1, denominator.imaginary, n);
      *denominator.imaginary = '-';
    }

  struct complex_arithmetica answer
      = multiply_complex (numerator, denominator);
  char *buf1 = (char *)calloc (
      strlen (answer.real) + strlen (divisor) + accuracy + 3, 1);
  char *buf2 = (char *)calloc (
      strlen (answer.imaginary) + strlen (divisor) + accuracy + 3, 1);
  divide (answer.real, divisor, buf1, accuracy);
  divide (answer.imaginary, divisor, buf2, accuracy);
  answer.real = (char *)realloc (answer.real, strlen (buf1) + 1);
  answer.imaginary = (char *)realloc (answer.imaginary, strlen (buf2) + 1);
  strcpy (answer.real, buf1);
  strcpy (answer.imaginary, buf2);

  free (c_squ);
  free (d_squ);
  free (divisor);
  free (buf1);
  free (buf2);

  return answer;
}

#endif