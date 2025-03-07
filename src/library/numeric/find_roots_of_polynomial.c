#include <arithmetica.h>
#include <basic_math_operations.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#define ull unsigned long long

char *
find_roots_of_polynomial_substitute (const char **coefficients, ull size,
                                     const char *guess)
{
  if (size < 1)
    {
      return NULL;
    }

  char *result = calloc (strlen (coefficients[size - 1]) + 1, 1);
  char *_power = malloc (strlen (guess) + 1);
  strcpy (_power, guess);
  strcpy (result, coefficients[size - 1]);
  for (ull i = size - 2; i + 1 > 0; --i)
    {
      char *mul = calloc (strlen (coefficients[i]) + strlen (_power) + 3, 1);
      multiply (coefficients[i], _power, mul);
      char *new_result = calloc (strlen (result) + strlen (mul) + 3, 1);
      add (result, mul, new_result);
      free (result);
      result = new_result;
      char *new_power = calloc (strlen (_power) + strlen (guess) + 3, 1);
      multiply (_power, guess, new_power);
      free (_power);
      _power = new_power;
      free (mul);
    }
  free (_power);
  return result;
}

struct fraction *
find_roots_of_polynomial_substitute_fraction (struct fraction **coefficients,
                                              ull size, struct fraction *guess)
{
  struct fraction *answer = malloc (sizeof (struct fraction));
  answer->numerator = malloc (2);
  answer->denominator = malloc (2);
  strcpy (answer->numerator, "0");
  strcpy (answer->denominator, "1");
  struct fraction power = parse_fraction ("1/1");
  for (size_t i = size - 1; i + 1 > 0; --i)
    {
      struct fraction mul = multiply_fraction (*coefficients[i], power);
      struct fraction new_answer = add_fraction (*answer, mul);
      free (answer->numerator);
      free (answer->denominator);
      answer->numerator = new_answer.numerator;
      answer->denominator = new_answer.denominator;
      struct fraction new_power = multiply_fraction (power, *guess);
      free (power.numerator);
      free (power.denominator);
      power.numerator = new_power.numerator;
      power.denominator = new_power.denominator;
      delete_fraction (mul);
    }
  delete_fraction (power);
  return answer;
}

char **
find_roots_of_polynomial_divide_polynomial (const char **coefficients,
                                            size_t size, const char *root)
{
  char **answer = malloc ((size - 1) * sizeof (char *));
  size_t ptr = 0;
  char *remainder = malloc (2);
  strcpy (remainder, "0");
  for (size_t i = 0; i < size - 1; ++i)
    {
      char *mul = calloc (strlen (root) + strlen (remainder) + 3, 1);
      multiply (root, remainder, mul);
      char *new_remainder
          = calloc (strlen (coefficients[i]) + strlen (mul) + 3, 1);
      add (coefficients[i], mul, new_remainder);
      free (remainder);
      remainder = new_remainder;
      answer[ptr] = calloc (strlen (remainder) + 1, 1);
      strcpy (answer[ptr], remainder);
      ++ptr;

      free (mul);
    }

  free (remainder);
  return answer;
}

struct fraction **
find_roots_of_polynomial (const char **_coefficients, size_t size,
                          size_t *exact_roots_found)
{
  // This is an overestimation of the accuracy required which will never miss roots.
  size_t max = strlen (_coefficients[0]);
  if (strlen (_coefficients[size - 1]) > max)
    {
      max = strlen (_coefficients[size - 1]);
    }
  size_t accuracy = 2 * (1 + max);

  struct fraction zero = parse_fraction ("0/1");

  // Make a fraction copy of the coefficients. Ensure that the leading
  // coefficient is 1.
  struct fraction **fraction_coefficients
      = malloc (size * sizeof (struct fraction *));
  for (size_t i = 0; i < size; ++i)
    {
      fraction_coefficients[i] = malloc (sizeof (struct fraction));
      struct fraction f = parse_fraction (_coefficients[i]);
      fraction_coefficients[i]->numerator = f.numerator;
      fraction_coefficients[i]->denominator = f.denominator;
    }
  if (size != 0)
    {
      struct fraction first;
      first.numerator
          = malloc (strlen (fraction_coefficients[0]->numerator) + 1);
      first.denominator
          = malloc (strlen (fraction_coefficients[0]->denominator) + 1);
      strcpy (first.numerator, fraction_coefficients[0]->numerator);
      strcpy (first.denominator, fraction_coefficients[0]->denominator);
      // Reciprocate 'first' so we can multiply by it instead of dividing by
      // it.
      if (first.numerator[0] == '-')
        {
          // -21/24 -> 24/-21
          char *temp = first.denominator;
          first.denominator = first.numerator;
          first.numerator = temp;

          // 24/-21 -> -24/21
          first.numerator
              = realloc (first.numerator, strlen (first.numerator) + 2);
          memmove (first.numerator + 1, first.numerator,
                   strlen (first.numerator) + 1);
          first.numerator[0] = '-';
          memmove (first.denominator, first.denominator + 1,
                   strlen (first.denominator));
        }
      else
        {
          // 21/24 -> 24/21
          char *temp = first.denominator;
          first.denominator = first.numerator;
          first.numerator = temp;
        }

      for (size_t i = 0; i < size; ++i)
        {
          struct fraction n = *fraction_coefficients[i];
          struct fraction new_fraction = multiply_fraction (n, first);
          free (fraction_coefficients[i]->numerator);
          free (fraction_coefficients[i]->denominator);
          fraction_coefficients[i]->numerator = new_fraction.numerator;
          fraction_coefficients[i]->denominator = new_fraction.denominator;
        }
      delete_fraction (first);
    }

  // Make a regular copy of the coefficients by dividing the fractions.
  // Note that this regular copy will also have the leading coefficient as 1. (as it should)
  // But at the same time (for the quick elimination), obtain two copies of the first and last coefficients,
  // multiplied by the denominator of each of the other coefficients.

  char *first_for_check = malloc (strlen(fraction_coefficients[size - 1]->numerator) + 1);
  strcpy (first_for_check, fraction_coefficients[size - 1]->numerator);
  char *last_for_check = malloc (strlen(fraction_coefficients[size - 1]->denominator) + 1); 
  strcpy (last_for_check, fraction_coefficients[size - 1]->denominator);

  for (size_t i = 0; i < size; ++i)
    {
      if (strcmp(fraction_coefficients[i]->denominator, "1"))
        {
          // Multiply first_for_check and last_for_check by the denominator of this coefficient.
          char *temp = calloc (strlen (fraction_coefficients[i]->denominator) + strlen (first_for_check) + 3, sizeof (char));
          multiply (fraction_coefficients[i]->denominator, first_for_check, temp);
          free (first_for_check);
          first_for_check = temp;
          temp = calloc (strlen (fraction_coefficients[i]->denominator) + strlen (last_for_check) + 3, sizeof (char));
          multiply (fraction_coefficients[i]->denominator, last_for_check, temp);
          free (last_for_check);
          last_for_check = temp;
        }
    }

  char **coefficients = malloc (size * sizeof (char *));
  bool division_in_original_coefficients = false;
  for (size_t i = 0; i < size; ++i)
    {
      // Check if there's a division sign in the original coefficients.
      if (strchr (_coefficients[i], '/'))
        {
          division_in_original_coefficients = true;
        }
    }
  if (!division_in_original_coefficients) {
    // If there's no division sign in the original coefficients, then we can just use the original coefficients.
    for (size_t i = 0; i < size; ++i)
      {
        coefficients[i] = malloc (strlen (_coefficients[i]) + 1);
        strcpy (coefficients[i], _coefficients[i]);
      }
  } else {
    for (size_t i = 0; i < size; ++i)
      {
        coefficients[i] = calloc (strlen (fraction_coefficients[i]->numerator) + strlen (fraction_coefficients[i]->denominator) + accuracy + 3, sizeof (char));
        divide (fraction_coefficients[i]->numerator, fraction_coefficients[i]->denominator, coefficients[i], accuracy);
      }
  }

  // First we need to find the approximate roots of the polynomial.
  char **derivative_coefficients = calloc (size - 1, sizeof (char *));
  // 5x^2-3x+1 -> 10x-3
  char *power = calloc (2, sizeof (char));
  power[0] = '1';
  for (ull i = size - 2; i + 1 > 0; --i)
    {
      char *mul = calloc (strlen (coefficients[i]) + strlen (power) + 3, 1);
      multiply (coefficients[i], power, mul);
      derivative_coefficients[i] = mul;
      increment_whole (&power);
    }

  struct fraction **exact_roots
      = malloc ((size - 1) * sizeof (struct fraction *));
  *exact_roots_found = 0;

  size_t _size = size;
  for (ull i = 0; i < _size - 1; ++i)
    {
      // g_{n+1} = g_n - f(g_n)/f'(g_n)
      char *guess = calloc (2, sizeof (char));
      guess[0] = '0'; // Our initial guess is 0. This might lead to divisons by 0 sometimes: we need to choose a value that doesn't divide by 0.
      bool good_division = false;
      do {
        // Check if f'(guess) is 0: if it is, increment guess and check again, otherwise, break.
        char *check = find_roots_of_polynomial_substitute ((const char **)derivative_coefficients, size - 1, guess);
        if (!strcmp (check, "0")) {
          increment_whole (&guess);
        } else {
          good_division = true;
        }
        free (check);
      } while (!good_division);
      char *prev_guess = calloc (strlen(guess) + 4, sizeof (char));
      subtract (guess, "1", prev_guess);
      char *prev_diff = calloc (2, sizeof (char));
      prev_diff[0] = '1';
      bool diff_decreasing = false;
      for (ull j = 0; j < accuracy || diff_decreasing; ++j)
        {
          if (!strcmp (guess, prev_guess))
            {
              break;
            }

          char *diff = calloc (strlen (guess) + strlen (prev_guess) + 3, 1);
          subtract (guess, prev_guess, diff);
          bool diff_abs = diff[0] == '-';
          if (diff_abs) {
            ++diff;
          }
          // if diff - prev_diff < 0
          char *diff_of_diff = calloc (strlen (diff) + strlen (prev_diff) + 3, 1);
          subtract (diff, prev_diff, diff_of_diff);
          if (diff_of_diff[0] == '-') {
            diff_decreasing = true;
          }
          free (diff - diff_abs);
          free (diff_of_diff);

          char *f = find_roots_of_polynomial_substitute (
              (const char **)coefficients, size, guess);
          char *f_prime = find_roots_of_polynomial_substitute (
              (const char **)derivative_coefficients, size - 1, guess);
          char *div = calloc (strlen (f) + strlen (f_prime) + accuracy + 3, 1);
          divide (f, f_prime, div, accuracy);
          char *new_guess = calloc (strlen (guess) + strlen (div) + 3, 1);
          subtract (guess, div, new_guess);
          free (prev_guess);
          prev_guess = guess;
          guess = new_guess;
          free (f);
          free (f_prime);
          free (div);
        }

      free (prev_guess);
      free (prev_diff);

      unsigned int guess_negative = guess[0] == '-';
      if (guess_negative)
        {
          ++guess;
        }
      char *numerator = (char *)calloc (2 * strlen (guess) + 1, sizeof (char));
      char *denominator
          = (char *)calloc (2 * strlen (guess) + 1, sizeof (char));
      terminating_decimal_to_fraction (guess, numerator, denominator);
      unsigned long long cont_frac_len;
      char **cont_frac = fraction_to_continued_fraction (
          numerator, denominator, &cont_frac_len);

      for (size_t i = 0; i < cont_frac_len; ++i)
        {
          struct fraction *exact_guess = malloc (sizeof (struct fraction));
          continued_fraction_to_fraction (cont_frac, i + 1,
                                          &exact_guess->numerator,
                                          &exact_guess->denominator);
          if (guess_negative)
            {
              size_t len = strlen (exact_guess->numerator) + 1;
              exact_guess->numerator = realloc (
                  exact_guess->numerator, strlen (exact_guess->numerator) + 2);
              memmove (exact_guess->numerator + 1, exact_guess->numerator,
                       len);
              exact_guess->numerator[0] = '-';
            }
          // Quick elimination
          char *remainder_1
              = abs_mod (first_for_check, exact_guess->numerator);
          char *remainder_2
              = abs_mod (last_for_check, exact_guess->denominator);
          unsigned int divisible_test_1 = strcmp (remainder_1, "0");
          unsigned int divisible_test_2 = strcmp (remainder_2, "0");
          free (remainder_1);
          free (remainder_2);
          if (strlen (coefficients[size - 1])
                  < strlen (exact_guess->numerator) - guess_negative
              || strlen (coefficients[0])
                     < strlen (exact_guess->denominator) - guess_negative
              || divisible_test_1 || divisible_test_2)
            {
              delete_fraction (*exact_guess);
              free (exact_guess);
              continue;
            }

          // Skip everything ahead if it is a duplicate
          unsigned int duplicate = 0;
          for (size_t j = 0; j < *exact_roots_found; ++j)
            {
              if (equal_fraction (*exact_roots[j], *exact_guess))
                {
                  duplicate = 1;
                  break;
                }
            }

          if (duplicate)
            {
              delete_fraction (*exact_guess);
              free (exact_guess);
              continue;
            }

          // Check if it is a root
          struct fraction *check
              = find_roots_of_polynomial_substitute_fraction (
                  fraction_coefficients, _size, exact_guess);
          unsigned int root_found = equal_fraction (*check, zero);
          delete_fraction (*check);
          free (check);
          if (root_found)
            {
              exact_roots[*exact_roots_found] = exact_guess;
              ++*exact_roots_found;

              // Let's also divide the polynomial by (x - root) here
              // so that we can find the other roots.
              char *guess_decimal = calloc (
                  strlen (exact_guess->numerator)
                      + strlen (exact_guess->denominator) + accuracy + 3,
                  1);
              divide (exact_guess->numerator, exact_guess->denominator,
                      guess_decimal, accuracy);
              char **new_coefficients
                  = find_roots_of_polynomial_divide_polynomial (
                      (const char **)coefficients, size, guess_decimal);
              free (guess_decimal);
              for (ull i = 0; i < size; ++i)
                {
                  free (coefficients[i]);
                }
              free (coefficients);
              coefficients = new_coefficients;
              --size;

              // We also need to update the derivative coefficients
              // since the polynomial has changed.
              for (size_t i = 0; i < size; ++i)
                {
                  free (derivative_coefficients[i]);
                }

              memset (power, 0, strlen (power) * sizeof (char));
              power[0] = '1';
              for (ull i = size - 2; i + 1 > 0; --i)
                {
                  char *mul = calloc (
                      strlen (power) + strlen (coefficients[i]) + 3, 1);
                  multiply (power, coefficients[i], mul);
                  derivative_coefficients[i] = mul;
                  increment_whole (&power);
                }

              break;
            }
          else
            {
              delete_fraction (*exact_guess);
              free (exact_guess);
            }
        }

      for (size_t i = 0; i < cont_frac_len; ++i)
        {
          free (cont_frac[i]);
        }
      free (cont_frac);
      free (guess - guess_negative);
      free (numerator);
      free (denominator);
    }

  free (power);
  delete_fraction (zero);
  for (ull i = 0; i < _size; ++i)
    {
      delete_fraction (*fraction_coefficients[i]);
      free (fraction_coefficients[i]);
    }
  for (ull i = 0; i < size; ++i)
    {
      free (coefficients[i]);
    }
  for (ull i = 0; i < size - 1; ++i)
    {
      free (derivative_coefficients[i]);
    }
  free (fraction_coefficients);
  free (coefficients);
  free (derivative_coefficients);

  // Remove leading zeroes from the roots, if any.
  for (size_t i = 0; i < *exact_roots_found; ++i)
    {
      remove_zeroes (exact_roots[i]->numerator);
      remove_zeroes (exact_roots[i]->denominator);
    }

  free (first_for_check);
  free (last_for_check);

  return exact_roots;
}