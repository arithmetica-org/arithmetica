#ifndef _fraction_to_continued_fraction_
#define _fraction_to_continued_fraction_

#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

char *fraction_to_continued_fraction(const char *numerator_in,
                                     const char *denominator_in) {
  char *answer = (char *)calloc(1, 1);
  size_t n = strlen(numerator_in) + strlen(denominator_in) + 3;
  char *quotient = (char *)calloc(n, 1);
  char *remainder = (char *)calloc(n, 1);
  size_t c = 0;
  char *numerator =
      (char *)calloc(strlen(numerator_in) + strlen(denominator_in) + 1, 1);
  char *denominator =
      (char *)calloc(strlen(numerator_in) + strlen(denominator_in) + 1, 1);
  strcpy(numerator, numerator_in);
  strcpy(denominator, denominator_in);
  while (strcmp(denominator, "1")) {
    divide_whole_with_remainder(numerator, denominator, quotient, remainder);
    answer = (char *)realloc(answer, strlen(answer) + strlen(quotient) + 3);
    strcat(answer, quotient);
    strcat(answer, ", ");
    c++;
    if (!strcmp(remainder, "0"))
      break;
    strcpy(numerator, denominator);
    strcpy(denominator, remainder);
    memset(quotient, 0, n);
    memset(remainder, 0, n);
  }
  if (strcmp(remainder, "0")) {
    answer = (char *)realloc(answer, strlen(answer) + strlen(numerator) + 3);
    strcat(answer, numerator);
    strcat(answer, ", ");
    c++;
  }

  answer[strlen(answer) - 2] = 0;
  if (c > 1) {
    answer[strlen(answer)] = ']';
    memcpy(answer + 1, answer, strlen(answer));
    answer[0] = '[';
    *strstr(answer, ",") = ';';
    answer[strlen(answer) - 1] = 0;
  }

  return answer;
}

#endif