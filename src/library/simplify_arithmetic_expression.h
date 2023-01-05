#ifndef _simplify_arithmetic_expression_h_
#define _simplify_arithmetic_expression_h_

#include "fraction/fraction_include.h"
#include <basic_math_operations.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static void str_replace_all(char **str_in, char *from, char *to) {
  char *str = *str_in;
  size_t from_len = strlen(from);
  if (from_len == 0)
    return;
  // algorithm here
  size_t len = strlen(str) + strlen(to) + 1;
  char *new_str = (char *)calloc(len, 1);
  size_t characters_added = 0;
  for (size_t i = 0; i < strlen(str); i++) {
    const char *loc = strstr(str + i, from);
    bool add_characters = false;
    size_t _characters_added = characters_added;
    if (loc != str + i) {
      new_str[characters_added++] = str[i];
    } else {
      add_characters = true;
      characters_added += strlen(to);
    }
    if (characters_added >= len) {
      size_t old_len = len;
      len *= 2;
      new_str = (char *)realloc(new_str, len);
      memset(new_str + _characters_added, 0, old_len);
    }
    if (add_characters) {
      memcpy(new_str + _characters_added, to, strlen(to));
    }
  }
  new_str = (char *)realloc(new_str, strlen(new_str) + 1);
  if (new_str[strlen(new_str)] != 0)
    new_str[strlen(new_str)] = 0;
  free(str);
  *str_in = new_str;
  return;
}

char *simplify_arithmetic_expression(const char *expression_in, int outputType,
                                     size_t accuracy) {
  char *expression = (char *)calloc(strlen(expression_in) + 1, 1);
  strcpy(expression, expression_in);
  str_replace_all(&expression, "[", "(");
  str_replace_all(&expression, "]", ")");
  str_replace_all(&expression, "{", "(");
  str_replace_all(&expression, "}", ")");

  // for now
  return expression;
}

#endif