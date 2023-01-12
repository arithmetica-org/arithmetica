#ifndef _arcsin_h_
#define _arcsin_h_

#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

char *
arcsin (const char *number, size_t accuracy)
{
  accuracy++;
  char one[] = "1";
  char two[] = "2";
  char *answer = (char *)calloc (strlen (number) + 1, 1);
  strcpy (answer, number);
  char *two_power_n = (char *)calloc (2, 1);
  char *two_n_factorial = (char *)calloc (2, 1);
  char *n_factorial = (char *)calloc (2, 1);
  char *i = (char *)calloc (2, 1);
  char *j = (char *)calloc (2, 1);
  two_power_n[0] = '1';
  two_n_factorial[0] = '1';
  n_factorial[0] = '1';
  i[0] = '1';
  j[0] = '1';
  char *x = (char *)calloc (strlen (number) + 1, 1);
  strcpy (x, number);
  char *x_squared = (char *)calloc (2 * strlen (number) + 1, 1);
  multiply (x, x, x_squared);
  char *prev = (char *)calloc (strlen (number) + 1, 1);
  strcpy (prev, answer);

  char *epsilon = (char *)calloc (accuracy + 4, 1);
  epsilon[0] = '0';
  if (accuracy > 0)
    {
      epsilon[1] = '.';
      for (size_t i = 0; i < accuracy; i++)
        epsilon[i + 2] = '0';
      epsilon[accuracy + 2] = '1';
    }

  while (1)
    {
      char *buf = (char *)calloc (strlen (two_power_n) + 2, 1);
      multiply (two_power_n, two, buf);
      two_power_n = (char *)realloc (two_power_n, strlen (two_power_n) + 2);
      strcpy (two_power_n, buf); // two_power_n *= 2

      char *_buf = (char *)calloc (strlen (i) + 2, 1);
      add (i, one, _buf);
      buf = (char *)realloc (buf, strlen (i) + strlen (_buf) + 1);
      memset (buf, 0, strlen (i) + strlen (_buf) + 1);
      multiply (i, _buf, buf); // buf = i * (i + 1)
      char *__buf
          = (char *)calloc (strlen (two_n_factorial) + strlen (buf) + 1, 1);
      multiply (two_n_factorial, buf,
                __buf); // __buf = two_n_factorial * i * (i + 1)
      two_n_factorial = (char *)realloc (
          two_n_factorial, strlen (two_n_factorial) + strlen (buf) + 1);
      strcpy (two_n_factorial, __buf); // two_n_factorial *= i * (i + 1);

      memset (_buf, 0, strlen (i) + 2);
      add (i, two, _buf);
      i = (char *)realloc (i, strlen (_buf) + 1);
      strcpy (i, _buf); // i += 2

      buf = (char *)realloc (buf, strlen (n_factorial) + strlen (j) + 1);
      memset (buf, 0, strlen (n_factorial) + strlen (j) + 1);
      multiply (n_factorial, j, buf);
      n_factorial = (char *)realloc (n_factorial,
                                     strlen (n_factorial) + strlen (j) + 1);
      strcpy (n_factorial, buf); // n_factorial *= j

      _buf = (char *)realloc (_buf, strlen (j) + 2);
      memset (_buf, 0, strlen (j) + 2);
      add (j, one, _buf);
      j = (char *)realloc (j, strlen (j) + 2);
      strcpy (j, _buf); // j++

      char *_den_1 = (char *)calloc (
          strlen (two_power_n) + strlen (n_factorial) + 1, 1);
      char *den_1 = (char *)calloc (
          2 * (strlen (two_power_n) + strlen (n_factorial)) + 1, 1);
      multiply (two_power_n, n_factorial, _den_1);
      multiply (_den_1, _den_1, den_1); // den_1 = (2^n * n!)^2

      buf = (char *)realloc (buf, strlen (x) + strlen (x_squared) + 1);
      memset (buf, 0, strlen (x) + strlen (x_squared) + 1);
      multiply (x, x_squared, buf);
      x = (char *)realloc (x, strlen (x) + strlen (x_squared) + 1);
      strcpy (x, buf); // x *= x^2

      size_t m = strlen (two_n_factorial) + strlen (den_1) + accuracy + 4;
      buf = (char *)realloc (buf, m);
      memset (buf, 0, m);
      divide (two_n_factorial, den_1, buf, accuracy + 1);
      m = strlen (x) + strlen (i) + accuracy + 4;
      _buf = (char *)realloc (_buf, m);
      memset (_buf, 0, m);
      divide (x, i, _buf, accuracy + 1);
      m = strlen (buf) + strlen (_buf) + 1;
      __buf = (char *)realloc (__buf, m);
      memset (__buf, 0, m);
      multiply (buf, _buf, __buf); // __buf = (2n)! / den_1 * x / i
      m = strlen (answer) + strlen (__buf) + 3;
      buf = (char *)realloc (buf, m);
      memset (buf, 0, m);
      add (answer, __buf, buf);
      answer = (char *)realloc (answer, m);
      strcpy (answer, buf); // answer += (2n)! / den_1 * x / i

      free (den_1);
      free (_den_1);
      free (__buf);

      // reuse buf and _buf instead of allocating new buffers
      char *diff = (char *)calloc (strlen (prev) + strlen (answer) + 3, 1);
      subtract (prev, answer, diff);
      if (diff[0] == '-')
        {
          for (size_t i = 0; i < strlen (diff) - 1; i++)
            diff[i] = diff[i + 1];
          diff[strlen (diff) - 1] = 0;
        } // diff = abs(diff)
      char *_diff = (char *)calloc (strlen (diff) + accuracy + 6, 1);
      subtract (diff, epsilon, _diff);
      if (_diff[0] == '-')
        {
          free (buf);
          free (_buf);
          free (diff);
          free (_diff);
          break;
        }

      prev = (char *)realloc (prev, strlen (answer) + 1);
      strcpy (prev, answer);

      free (buf);
      free (_buf);
      free (diff);
      free (_diff);
    }

  free (two_power_n);
  free (two_n_factorial);
  free (n_factorial);
  free (i);
  free (j);
  free (x);
  free (x_squared);
  free (prev);
  free (epsilon);

  size_t decimalLocation = 0;
  for (size_t i = 0; i < strlen (answer); i++)
    {
      if (answer[i] == '.')
        {
          decimalLocation = i;
          break;
        }
    }
  answer[decimalLocation + accuracy] = 0;
  return answer;
}

#endif