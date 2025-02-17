#include <truncate.h>
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

char *
exponential (const char *x_in, size_t accuracy)
{
  // e^x = \displaystyle\sum_{n=0}^{\infty} \frac{x^n}{n!}
  //     = 1 + x + x^2 / (1 * 2) + x^3 / (1 * 2 * 3) + x^4 / (1 * 2 * 3 * 4) +
  //     ...

  char *x = (char *)calloc (strlen (x_in) + 1, 1);
  strcpy (x, x_in);
  remove_zeroes (x);
  if (!strcmp (x, "0"))
    {
      x = (char *)realloc (x, 2);
      x[0] = '1';
      x[1] = 0;
      return x;
    }

  char one[] = "1";
  size_t x_in_len = strlen (x_in);

  char *answer = (char *)calloc (x_in_len + 2, 1);
  add (x_in, one, answer);

  char *prevTerm = (char *)calloc (x_in_len + 1, 1);
  strcpy (prevTerm, x_in);
  char *i = (char *)calloc (2, 1);
  i[0] = '2';
  char *prevAfterDecimal = (char *)calloc (accuracy + 1, 1);
  unsigned char accuracyAchieved = 1;
  size_t decimalLocation = 0;

  while (1)
    {
      size_t sz = x_in_len + strlen (i) + accuracy * 2 + 3;
      char *buf = (char *)calloc (sz, 1);
      divide (x_in, i, buf, accuracy * 2);
      char *currentTerm
          = (char *)calloc (strlen (buf) + strlen (prevTerm) + 3, 1);
      multiply (buf, prevTerm, currentTerm);
      sz = strlen (answer) + strlen (currentTerm) + 3;
      buf = (char *)realloc (buf, sz);
      memset (buf, 0, sz);
      add (answer, currentTerm, buf);
      answer = (char *)realloc (answer, sz);
      strcpy (answer, buf);
      sz = strlen (i) + 2;
      buf = (char *)realloc (buf, sz);
      memset (buf, 0, sz);
      add (i, one, buf);
      i = (char *)realloc (i, sz);
      strcpy (i, buf);
      prevTerm = (char *)realloc (prevTerm, strlen (currentTerm) + 1);
      strcpy (prevTerm, currentTerm);
      free (buf);
      free (currentTerm);
      truncate (prevTerm, accuracy * 2);

      unsigned char found = 0;
      size_t location = 0;
      for (size_t i = 0; i < strlen (answer); i++)
        {
          if (answer[i] == '.')
            {
              location = i;
              found = 1;
              break;
            }
        }
      if (found)
        {
          decimalLocation = location;
          char *afterDecimal = (char *)calloc (accuracy + 1, 1);
          for (size_t i = 0; i < accuracy; i++)
            {
              if (i + location + 1 > strlen (answer))
                {
                  break;
                  accuracyAchieved = 0;
                }
              afterDecimal[i] = answer[i + location + 1];
            }
          if (!strcmp (afterDecimal, prevAfterDecimal))
            {
              free (afterDecimal);
              break;
            }
          strcpy (prevAfterDecimal, afterDecimal);
          free (afterDecimal);
        }
    }

  free (prevTerm);
  free (i);
  free (prevAfterDecimal);
  free(x);

  if (accuracyAchieved)
    answer[decimalLocation + accuracy + 1] = 0;

  return answer;
}