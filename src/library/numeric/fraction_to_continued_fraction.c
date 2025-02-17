#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

char **
fraction_to_continued_fraction (const char *numerator_in,
                                const char *denominator_in, unsigned long long *n_terms_out)
{
  char **answer = (char **)malloc(sizeof(char *));
  *n_terms_out = 0;
  size_t n = strlen (numerator_in) + strlen (denominator_in) + 3;
  char *remainder = (char *)calloc (n, 1);
  char *numerator = (char *)calloc (
      strlen (numerator_in) + strlen (denominator_in) + 1, 1);
  char *denominator = (char *)calloc (
      strlen (numerator_in) + strlen (denominator_in) + 1, 1);
  strcpy (numerator, numerator_in);
  strcpy (denominator, denominator_in);
  while (strcmp (denominator, "1"))
    {
      char *quotient = (char *)calloc (n, 1);
      divide_whole_with_remainder (numerator, denominator, quotient,
                                   remainder);
      answer = (char **)realloc (answer, (*n_terms_out + 1)*sizeof(char *));
      answer[*n_terms_out] = quotient;
      ++*n_terms_out;
      if (!strcmp (remainder, "0"))
        break;
      strcpy (numerator, denominator);
      strcpy (denominator, remainder);
      memset (remainder, 0, n);
    }
  if (strcmp (remainder, "0"))
    {
      ++*n_terms_out;
      answer
          = (char **)realloc (answer, *n_terms_out*sizeof(char *));
      answer[*n_terms_out - 1] = (char *)calloc (n, 1);
      strcpy (answer[*n_terms_out - 1], numerator);
    }

  free (numerator);
  free (denominator);
  free (remainder);

  return answer;
}