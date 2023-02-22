#ifndef _arcsin_h_
#define _arcsin_h_

#include "check_accuracy.h"
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

char *
arcsin (const char *number, size_t accuracy)
{
  accuracy += 5;

  char *prev_term = (char *)calloc (strlen (number) + 1, 1);
  char *answer = (char *)calloc (strlen (number) + 1, 1);
  strcpy (prev_term, number);
  strcpy (answer, number);

  // t_{n+1} = t_n * (2n - 1) / (2 n) * x^2 * (2n - 1) / (2n + 1)
  //         = t_n (x (2n - 1))^2 / (2n (2n + 1))

  char *two_n_plus_one = (char *)calloc (2, 1);
  char *two_n = (char *)calloc (2, 1);
  char *two_n_minus_one = (char *)calloc (2, 1);
  two_n_plus_one[0] = '3';
  two_n[0] = '2';
  two_n_minus_one[0] = '1';

  while (1)
    {
      char *denominator
          = (char *)calloc (strlen (two_n) + strlen (two_n_plus_one) + 3, 1);
      multiply (two_n, two_n_plus_one, denominator);
      char *numerator__
          = (char *)calloc (strlen (two_n_minus_one) + strlen (number) + 3, 1);
      multiply (two_n_minus_one, number, numerator__);
      char *numerator_ = (char *)calloc (
          strlen (numerator__) + strlen (numerator__) + 3, 1);
      multiply (numerator__, numerator__, numerator_);
      char *numerator
          = (char *)calloc (strlen (numerator_) + strlen (prev_term) + 3, 1);
      multiply (numerator_, prev_term, numerator);

      char *term = (char *)calloc (
          strlen (numerator) + strlen (denominator) + accuracy + 3, 1);
      divide (numerator, denominator, term, accuracy);

      // answer += term
      char *answer_ = (char *)calloc (strlen (answer) + strlen (term) + 3, 1);
      add (answer, term, answer_);

      increment_whole (&two_n_plus_one);
      increment_whole (&two_n_plus_one);
      increment_whole (&two_n);
      increment_whole (&two_n);
      increment_whole (&two_n_minus_one);
      increment_whole (&two_n_minus_one);

      free (numerator__);
      free (numerator_);
      free (numerator);
      free (denominator);

      if (check_accuracy (answer, answer_, accuracy))
        {
          free (answer_);
          free (term);
          break;
        }

      answer = (char *)realloc (answer, strlen (answer_) + 1);
      strcpy (answer, answer_);
      free (answer_);
      prev_term = (char *)realloc (prev_term, strlen (term) + 1);
      strcpy (prev_term, term);
      free (term);
    }

  free (prev_term);
  free (two_n_minus_one);
  free (two_n);
  free (two_n_plus_one);

  size_t decimalLocation = strchr (answer, '.') - answer;
  answer[decimalLocation + accuracy - 4] = 0; // since we did accuracy += 5
  return answer;
}

#endif