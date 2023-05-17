#include "arithmetica.h"
#include <basic_math_operations.h>
#include <gmp.h>
#include <stdlib.h>
#include <string.h>

char *arcsin_mpf_to_char(const mpf_t number, size_t accuracy) {
    // Determine the required size for the string representation
    size_t str_size = accuracy + 20; // Initial buffer size
    char* str = (char*)malloc(str_size * sizeof(char));

    // Convert the mpf_t to a string
    mp_exp_t exponent;
    int actual_size;
    char format[256] = "";

    char ac_str[256] = "";
    snprintf(ac_str, sizeof(ac_str), "%zu", accuracy);
    strcat(format, "%.");
    strcat(format, ac_str);
    strcat(format, "Ff");

    do {
        actual_size = gmp_sprintf(str, format, number);
        if (actual_size >= str_size) {
            str_size *= 2; // Double the buffer size
            str = (char*)realloc(str, str_size * sizeof(char));
        }
    } while (actual_size >= str_size);

    return str;
}

char *
arcsin (const char *number, size_t accuracy)
{
  accuracy += 5;

  mpf_set_default_prec (accuracy * 3.32192809488736234787 + 1);

  mpf_t number_mpf;
  mpf_init (number_mpf);
  mpf_set_str (number_mpf, number, 10);
  mpf_t prev_term;
  mpf_t answer;
  mpf_init (prev_term);
  mpf_init (answer);
  mpf_set_str (answer, number, 10);
  mpf_set_str (prev_term, number, 10);

  // t_{n+1} = t_n * (2n - 1) / (2 n) * x^2 * (2n - 1) / (2n + 1)
  //         = t_n (x (2n - 1))^2 / (2n (2n + 1))

  mpf_t two_n_plus_one;
  mpf_t two_n;
  mpf_t two_n_minus_one;
  mpf_init (two_n_plus_one);
  mpf_init (two_n);
  mpf_init (two_n_minus_one);
  mpf_set_ui (two_n_plus_one, 3);
  mpf_set_ui (two_n, 2);
  mpf_set_ui (two_n_minus_one, 1);

  while (1)
    {
      mpf_t denominator;
      mpf_init (denominator);
      mpf_mul (denominator, two_n, two_n_plus_one);
      mpf_t numerator__;
      mpf_init (numerator__);
      mpf_mul (numerator__, two_n_minus_one, number_mpf);
      mpf_t numerator_;
      mpf_init (numerator_);
      mpf_mul (numerator_, numerator__, numerator__);
      mpf_t numerator;
      mpf_init (numerator);
      mpf_mul (numerator, numerator_, prev_term);

      mpf_t term;
      mpf_init (term);
      mpf_div (term, numerator, denominator);

      // answer += term
      mpf_t answer_;
      mpf_init (answer_);
      mpf_add (answer_, answer, term);

      mpf_add_ui (two_n_plus_one, two_n_plus_one, 2);
      mpf_add_ui (two_n, two_n, 2);
      mpf_add_ui (two_n_minus_one, two_n_minus_one, 2);

      mpf_clear (numerator__);
      mpf_clear (numerator_);
      mpf_clear (numerator);
      mpf_clear (denominator);

      if (mpf_cmp (answer, answer_) == 0)
        {
          mpf_clear (answer_);
          mpf_clear (term);
          break;
        }

      mpf_set (answer, answer_);
      mpf_clear (answer_);
      mpf_set (prev_term, term);
      mpf_clear (term);
    }

  mpf_clear (prev_term);
  mpf_clear (two_n_minus_one);
  mpf_clear (two_n);
  mpf_clear (two_n_plus_one);
  mpf_clear (number_mpf);

  char *answer_str = arcsin_mpf_to_char (answer, accuracy);
  mpf_clear (answer);
  size_t decimalLocation = strchr (answer_str, '.') - answer_str;
  answer_str[decimalLocation + accuracy - 4] = 0; // since we did accuracy += 5
  return answer_str;
}