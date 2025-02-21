#include <arithmetica.h>
#include "truncate.h"
#include <basic_math_operations.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *
cosine (const char *number, size_t accuracy)
{
  // cos(x) = 1 - x^2/2 + x^4/4 - x^6/720 + x^8/40320 - ...
  //        = 1 - prev_term * x^2 * (1 * 2) + prev_term * x^2 / (3 * 4) -
  //        prev_term * x^2 / (5 * 6) + ...

  char *x_squared = (char *)calloc (2 * strlen (number) + 3, 1);
  char *prev_term = (char *)calloc (2, 1);
  char *answer = (char *)calloc (2, 1);
  multiply (number, number, x_squared);
  prev_term[0] = '1';
  answer[0] = '1';

  char *n_1 = (char *)calloc (2, 1);
  char *n_2 = (char *)calloc (2, 1);
  n_1[0] = '1';
  n_2[0] = '2';

  while (1)
    {
      // buf_1 = -1 * prev_term
      char *buf_1
          = (char *)calloc (strlen (prev_term) + strlen (x_squared) + 4, 1);
      strcpy (buf_1, prev_term);
      if (*buf_1 == '-')
        {
          memmove (buf_1, buf_1 + 1, strlen (buf_1) - 1);
          buf_1[strlen (buf_1) - 1] = 0;
        }
      else
        {
          buf_1 = (char *)realloc (buf_1, strlen (buf_1) + 2);
          memmove (buf_1 + 1, buf_1, strlen (buf_1) + 1);
          buf_1[0] = '-';
        }

      // buf_2 = buf_1 * x^2
      char *buf_2
          = (char *)calloc (strlen (x_squared) + strlen (buf_1) + 3, 1);
      multiply (buf_1, x_squared, buf_2);

      // buf_3 = n_1 * n_2
      char *buf_3 = (char *)calloc (strlen (n_1) + strlen (n_2) + 3, 1);
      multiply (n_1, n_2, buf_3);

      char *current_term
          = (char *)calloc (strlen (buf_2) + strlen (buf_3) + accuracy + 3, 1);
      divide (buf_2, buf_3, current_term, accuracy);

      char *answer_buf
          = (char *)calloc (strlen (current_term) + strlen (answer) + 3, 1);
      add (answer, current_term, answer_buf);

      bool accuracy_met = check_accuracy(answer, answer_buf, accuracy);

      answer = (char *)realloc (answer, strlen (answer_buf) + 1);
      strcpy (answer, answer_buf);

      prev_term = (char *)realloc (prev_term, strlen (current_term) + 1);
      strcpy (prev_term, current_term);

      increment_whole (&n_1);
      increment_whole (&n_1);
      increment_whole (&n_2);
      increment_whole (&n_2);

      free (buf_1);
      free (buf_2);
      free (buf_3);
      free (current_term);
      free (answer_buf);

      if (accuracy_met)
        break;
    }

  free (x_squared);
  free (prev_term);
  free (n_1);
  free (n_2);

  truncate (answer, accuracy);

  return answer;
}