#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

char *
square_root (const char *number_in, size_t accuracy)
{
  size_t shift = 0;
  size_t number_len = strlen (number_in);
  char *number = (char *)calloc (number_len + 1, 1);
  strcpy (number, number_in);
  char *_dec_loc = strchr (number, '.');
  if (_dec_loc != NULL)
    {
      size_t dec_loc = _dec_loc - number;
      shift = (number_len - dec_loc - 1) / 2;
      if ((number_len - dec_loc - 1) & 1)
        {
          shift++;
          number_len++;
          number = (char *)realloc (number, number_len + 1);
          number[number_len - 1] = '0';
        }
      char *buf = (char *)calloc (number_len, 1);
      memmove (buf, number, dec_loc);
      memmove (buf + dec_loc, number + dec_loc + 1, shift * 2);
      strcpy (number, buf);
      free (buf);
      number_len--;
    }

  number = (char *)realloc (number, number_len + accuracy * 2 + 1);
  memset (number + number_len, '0', accuracy * 2);
  number_len += accuracy * 2;
  if (number_len & 1)
    {
      number_len++;
      number = (char *)realloc (number, number_len + 1);
      memmove (number + 1, number, number_len - 1);
      number[0] = '0';
    }
  char *left_column = (char *)calloc (2, 1);
  char *working_space = (char *)calloc (number_len + 1, 1);
  char *answer = (char *)calloc (number_len / 2 + 1, 1);
  left_column[0] = '0';
  size_t ptr = 0;
  for (size_t i = 0; i < number_len - 1; i += 2)
    {
      size_t working_space_len = strlen (working_space);
      working_space[working_space_len] = number[i];
      working_space[working_space_len + 1] = number[i + 1];
      working_space[working_space_len + 2] = 0;

      int start = 0, end = 9, ans = 0;
      char *temp = (char *)calloc (1, 1);
      char *_temp = (char *)calloc (1, 1);
      while (start <= end)
        {
          int mid = (start + end) / 2;
          char *x_ = (char *)calloc (2, 1);
          x_[0] = mid + '0';
          char *temp_ = (char *)calloc (strlen (left_column) + 2, 1);
          strcpy (temp_, left_column);
          temp_[strlen (left_column)] = x_[0];
          char *multiplication = (char *)calloc (strlen (temp_) + 2, 1);
          multiply (temp_, x_, multiplication);
          char *_temp_ = (char *)calloc (
              strlen (working_space) + strlen (multiplication) + 3, 1);
          subtract (working_space, multiplication, _temp_);
          if (_temp_[0] != '-')
            {
              start = mid + 1;
              ans = mid;
              temp = (char *)realloc (temp, strlen (temp_) + 1);
              _temp = (char *)realloc (_temp, strlen (_temp_) + 1);
              strcpy (temp, temp_);
              strcpy (_temp, _temp_);
            }
          else
            end = mid - 1;
          free (x_);
          free (temp_);
          free (multiplication);
          free (_temp_);
        }

      char *x = (char *)calloc (2, 1);
      x[0] = ans + '0';
      answer[ptr++] = x[0];

      left_column = (char *)realloc (left_column, strlen (temp) + 4);
      memset (left_column, 0, strlen (temp) + 4);
      add (temp, x, left_column);

      strcpy (working_space, _temp);

      free (temp);
      free (_temp);
      free (x);
    }

  free (number);
  free (left_column);
  free (working_space);

  char *_answer = (char *)calloc (strlen (answer) + 2, 1);
  memmove (_answer, answer, strlen (answer) - accuracy - shift);
  _answer[strlen (answer) - accuracy - shift] = '.';
  memmove (_answer + strlen (answer) - accuracy - shift + 1,
           answer + strlen (answer) - accuracy - shift, accuracy);
  free (answer);
  remove_zeroes (_answer);
  return _answer;
}