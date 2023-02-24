#include "arithmetica.h"
#include "truncate.h"
#include <basic_math_operations.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *
arccos (const char *number, size_t accuracy)
{
  // arccos(x) = pi/2 - arcsin(x)
  size_t num_accuracy = number + strlen (number) - 1 - strchr (number, '.');
  num_accuracy += accuracy; // to keep final answer accuracy high
  char _half_pi[]
      = "1."
        "5707963267948966192313216916397514420985846996875529104874"
        "722961539082031431044993140174126710585339";
  char *half_pi = (char *)calloc (num_accuracy + 3, 1);
  if (num_accuracy > 100)
    {
      free (half_pi);
      half_pi = arcsin ("1", num_accuracy);
    }
  else
    {
      truncate (_half_pi, num_accuracy);
      strcpy (half_pi, _half_pi);
    }
  char *asin = arcsin (number, accuracy);
  char *answer = (char *)calloc (strlen (half_pi) + strlen (asin) + 3, 1);
  subtract (half_pi, asin, answer);
  truncate (answer, accuracy);

  free (half_pi);
  free (asin);

  return answer;
}