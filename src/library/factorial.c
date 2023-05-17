#include <gmp.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void
factorial (unsigned long n, char *factorial)
{
  if (n == 0 || n == 1)
    {
      factorial[0] = '1';
      return;
    }

  mpz_t result;
  mpz_init (result);

  mpz_set_ui (result, 1);
  for (unsigned long i = 2; i <= n; ++i) {
    mpz_mul_ui (result, result, i);
  }

  mpz_get_str (factorial, 10, result);
  mpz_clear (result);

  return;
}