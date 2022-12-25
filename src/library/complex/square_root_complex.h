#ifndef _square_root_complex_
#define _square_root_complex_

#include "../square_root.h"
#include "complex.h"
#include <basic_math_operations.h>
#include <stddef.h>

struct complex square_root_complex(struct complex n, size_t accuracy) {
  remove_zeroes(n.imaginary);
  if (!strcmp(n.imaginary, "0")) {
    char *sqrt = square_root(n.real, accuracy);
    struct complex answer;
    answer.imaginary = (char *)realloc(answer.imaginary, 2);
    answer.real = (char *)realloc(answer.real, strlen(sqrt) + 1);
    strcpy(answer.imaginary, n.imaginary);
    strcpy(answer.real, sqrt);
    free(sqrt);
    return answer;
  }

  char *a_squ = (char *)calloc(2 * strlen(n.real) + 3, 1);
  char *b_squ = (char *)calloc(2 * strlen(n.imaginary) + 3, 1);
  multiply(n.real, n.real, a_squ);
  multiply(n.imaginary, n.imaginary, b_squ);
  char *a_squ_plus_b_squ = (char *)calloc(strlen(a_squ) + strlen(b_squ) + 3, 1);
  add(a_squ, b_squ, a_squ_plus_b_squ);
  free(a_squ);
  free(b_squ);
  char *sqrt_1 = square_root(a_squ_plus_b_squ, accuracy);
  free(a_squ_plus_b_squ);
  char *buf1 = (char *)calloc(strlen(sqrt_1) + strlen(n.real) + 3, 1);
  char *buf2 = (char *)calloc(strlen(sqrt_1) + strlen(n.real) + 3, 1);
  add(sqrt_1, n.real, buf1);
  subtract(sqrt_1, n.real, buf2);
  char *half_buf_1 = (char *)calloc(strlen(buf1) + accuracy + 4, 1);
  char *half_buf_2 = (char *)calloc(strlen(buf2) + accuracy + 4, 1);
  divide(buf1, "2", half_buf_1, accuracy);
  divide(buf2, "2", half_buf_2, accuracy);
  char *sqrt_2 = square_root(half_buf_1, accuracy);
  char *sqrt_3 = square_root(half_buf_2, accuracy);
  remove_zeroes(sqrt_2);
  remove_zeroes(sqrt_3);
  if (n.imaginary[0] == '-') {
    size_t m = strlen(sqrt_3);
    sqrt_3 = (char *)realloc(sqrt_3, m + 2);
    memmove(sqrt_3 + 1, sqrt_3, m);
    *sqrt_3 = '-';
  }
  struct complex answer = create_complex_number(sqrt_2, sqrt_3);
  free(buf1);
  free(buf2);
  free(half_buf_1);
  free(half_buf_2);
  free(sqrt_1);
  free(sqrt_2);
  free(sqrt_3);

  return answer;
}

#endif