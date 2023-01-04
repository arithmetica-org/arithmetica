#ifndef _simplify_arithmetic_expression_h_
#define _simplify_arithmetic_expression_h_

#include "fraction/fraction_include.h"
#include <basic_math_operations.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static void str_replace_all(char *str, char *from, char *to) {
  size_t from_len = strlen(from);
  if (from_len == 0)
    return;
  // algorithm here
}

char *simplify_arithmetic_expression(const char *expression, int outputType,
                                     size_t accuracy) {
  // code here
}

#endif