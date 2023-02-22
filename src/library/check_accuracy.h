#ifndef _check_accuracy_h_
#define _check_accuracy_h_

#include <basic_math_operations.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/// @brief Checks that the number of correct decimals is greater than or equal
/// to the accuracy.
/// @param a The first number.
/// @param b The second number.
/// @param accuracy The number of correct decimals.
/// @return Returns true if the number of correct decimals is greater than or
/// equal to the accuracy, otherwise returns false.
bool
check_accuracy (const char *a, const char *b, size_t accuracy)
{
  // If both strings are the same, then the accuracy is met by default.
  if (strcmp (a, b) == 0)
    return true;

  // First, make sure that the decimal place is in the same place for both.
  size_t a_decimal_place = strchr (a, '.') - a;
  size_t b_decimal_place = strchr (b, '.') - b;
  if (a_decimal_place != b_decimal_place)
    return false;

  // Next, make sure that the number of correct decimals is greater than or
  // equal to the accuracy.
  size_t a_length = strlen (a);
  size_t b_length = strlen (b);
  size_t common_decimals = 0;
  for (size_t i = a_decimal_place + 1; i < a_length && i < b_length; i++)
    {
      if (a[i] != b[i])
        break;
      common_decimals++;
    }

  return common_decimals >= accuracy;
}

#endif