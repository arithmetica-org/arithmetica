#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

char *
sine (const char *number, size_t accuracy)
{
  unsigned char toggle = 0;
  char *x_squared = (char *)calloc (2 * strlen (number) + 1, 1);
  multiply (number, number, x_squared);
  char *x = (char *)calloc (strlen (number) + 1, 1);
  char *answer = (char *)calloc (strlen (number) + 1, 1);
  strcpy (x, number);
  strcpy (answer, number);
  char *denominator = (char *)calloc (2, 1);
  denominator[0] = '1';
  char *i = (char *)calloc (2, 1);
  i[0] = '2';
  char *maxDiff = (char *)calloc (accuracy + 3, 1);
  maxDiff[0] = '0';
  if (accuracy > 0)
    {
      maxDiff[1] = '.';
      for (size_t i = 1; i < accuracy; i++)
        maxDiff[i + 1] = '0';
      maxDiff[accuracy] = '1';
    }
  char *prev = (char *)calloc (2, 1);
  prev[0] = '0';
  size_t decimalLocation = 0;

  while (1)
    {
      size_t m = strlen (x_squared) + strlen (x) + 1;
      char *buf = (char *)calloc (m, 1);
      multiply (x, x_squared, buf);
      if (m > strlen (x))
        x = (char *)realloc (x, m);
      strcpy (x, buf);
      if (strlen (denominator) + 2 * (strlen (i) + 1) + 1 > m)
        {
          m = strlen (denominator) + 2 * (strlen (i) + 1) + 1;
          buf = (char *)realloc (buf, m);
        }
      denominator = (char *)realloc (denominator, m);
      memset (buf, 0, m);
      multiply (denominator, i, buf);
      strcpy (denominator, buf);
      memset (buf, 0, m);
      increment_whole (&i);
      multiply (denominator, i, buf);
      strcpy (denominator, buf);
      increment_whole (&i);
      toggle = !toggle;
      char *_buf = (char *)calloc (1, 1);
      if (strlen (x) + strlen (denominator) + 2 * accuracy + 3 > m)
        {
          m = strlen (x) + strlen (denominator) + 2 * accuracy + 3;
          _buf = (char *)realloc (_buf, m);
          buf = (char *)realloc (buf, m);
        }
      memset (buf, 0, m);
      memset(_buf, 0, m);
      divide (x, denominator, _buf, accuracy * 2);
      memset (buf, 0, m);
      toggle ? subtract (answer, _buf, buf) : add (answer, _buf, buf);
      answer = (char *)realloc (answer, m);
      strcpy (answer, buf);

      free (buf);
      free (_buf);

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

      char *diff = (char *)calloc (strlen (prev) + strlen (answer) + 3, 1);
      subtract (answer, prev, diff);
      if (diff[0] == '-')
        {
          for (size_t i = 0; i < strlen (diff) - 1; i++)
            diff[i] = diff[i + 1];
          diff[strlen (diff) - 1] = 0;
        }

      char *__buf = (char *)calloc (strlen (diff) + strlen (maxDiff) + 3, 1);
      subtract (diff, maxDiff, __buf);

      if (__buf[0] == '-')
        {
          free (diff);
          free (__buf);
          break;
        }

      prev = (char *)realloc (prev, strlen (answer) + 1);
      strcpy (prev, answer);
      free (diff);
      free (__buf);
    }

  free (x_squared);
  free (x);
  free (denominator);
  free (i);
  free (prev);
  free (maxDiff);

  if (number[0] == '-')
    decimalLocation++;
  answer[decimalLocation + accuracy + 2] = 0;

  return answer;
}