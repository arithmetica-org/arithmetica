#ifndef _multiply_complex_h_
#define _multiply_complex_h_

#include "complex.h"
#include <basic_math_operations.h>

struct complex
multiply_complex (struct complex a, struct complex b)
{
  struct complex answer;

  char *re_mul = (char *)calloc (strlen (a.real) + strlen (b.real) + 3, 1);
  char *im_mul
      = (char *)calloc (strlen (a.imaginary) + strlen (b.imaginary) + 3, 1);
  char *re_im_mul
      = (char *)calloc (strlen (a.real) + strlen (b.imaginary) + 3, 1);
  char *im_re_mul
      = (char *)calloc (strlen (a.imaginary) + strlen (b.real) + 3, 1);

  multiply (a.real, b.real, re_mul);
  multiply (a.imaginary, b.imaginary, im_mul);
  multiply (a.real, b.imaginary, re_im_mul);
  multiply (a.imaginary, b.real, im_re_mul);

  answer.real = (char *)calloc (strlen (re_mul) + strlen (im_mul) + 3, 1);
  answer.imaginary
      = (char *)calloc (strlen (re_im_mul) + strlen (im_re_mul) + 3, 1);

  subtract (re_mul, im_mul, answer.real);
  add (re_im_mul, im_re_mul, answer.imaginary);

  free (re_mul);
  free (im_mul);
  free (re_im_mul);
  free (im_re_mul);

  return answer;
}

#endif