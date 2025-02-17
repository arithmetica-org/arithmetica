#include <arithmetica.h>
#include <basic_math_operations.h>
#include <stdlib.h>
#include <string.h>

char *
arctan (const char *number, size_t accuracy)
{
  // arctan(x) = arcsin(x / sqrt(x^2 + 1))

  char *number_squ = (char *)calloc (2 * strlen (number) + 3, 1);
  multiply (number, number, number_squ);
  char *sqrtarg = (char *)calloc (strlen (number_squ) + 4, 1);
  add (number_squ, "1", sqrtarg);
  char *sqrt = square_root (sqrtarg, accuracy);
  char *asinarg
      = (char *)calloc (strlen (number) + strlen (sqrt) + accuracy + 3, 1);
  divide (number, sqrt, asinarg, accuracy);
  char *answer = arcsin (asinarg, accuracy);

  free (number_squ);
  free (sqrtarg);
  free (sqrt);
  free (asinarg);

  return answer;
}