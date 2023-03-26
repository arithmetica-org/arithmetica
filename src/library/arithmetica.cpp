#include "arithmetica.hpp"

std::string
arithmetica::arccos (std::string n, size_t accuracy)
{
  char *answer = ::arccos (n.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

std::string
arithmetica::arcsin (std::string n, size_t accuracy)
{
  char *answer = ::arcsin (n.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

std::string
arithmetica::arctan (std::string n, size_t accuracy)
{
  char *answer = ::arctan (n.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

std::string
arithmetica::cosine (std::string n, size_t accuracy)
{
  char *answer = ::cosine (n.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

std::string
arithmetica::exponential (std::string x, size_t accuracy)
{
  char *answer = ::exponential (x.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

std::string
arithmetica::factorial (unsigned long n)
{
  char *answer
      = (char *)calloc (n * __builtin_floorf (__builtin_log10 (n) + 1) + 2, 1);
  ::factorial (n, answer);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

std::vector<std::string>
arithmetica::fraction_to_continued_fraction (std::string numerator,
                                             std::string denominator)
{
  unsigned long long length;
  char **answer = ::fraction_to_continued_fraction (
      numerator.c_str (), denominator.c_str (), &length);
  std::vector<std::string> _answer;
  for (unsigned long long i = 0; i < length; i++)
    {
      _answer.push_back (answer[i]);
      free (answer[i]);
    }
  free (answer);
  return _answer;
}

std::string
arithmetica::igcd (std::string a, std::string b)
{
  char *gcd = (char *)calloc (a.length () + b.length () + 3, 1);
  ::igcd (a.c_str (), b.c_str (), gcd);
  std::string answer = gcd;
  free (gcd);
  return answer;
}

std::string
arithmetica::ilcm (std::string a, std::string b)
{
  char *lcm = (char *)calloc (2 * (a.length () + b.length () + 3) + 3, 1);
  ::ilcm (a.c_str (), b.c_str (), lcm);
  std::string answer = lcm;
  free (lcm);
  return answer;
}

std::string
arithmetica::natural_logarithm (std::string n, size_t accuracy)
{
  char *answer = ::natural_logarithm (n.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

std::string
arithmetica::power (std::string x, std::string n, size_t accuracy)
{
  char *pow = ::power (x.c_str (), n.c_str (), accuracy);
  std::string answer = pow;
  free (pow);
  return answer;
}

std::pair<std::string, std::string>
arithmetica::repeating_decimal_to_fraction (
    const std::string &non_repeating_part, const std::string &repeating_part)
{
  char *numerator = (char *)calloc (
      non_repeating_part.length () + repeating_part.length () + 1, 1);
  char *denominator = (char *)calloc (
      non_repeating_part.length () + repeating_part.length () + 1, 1);
  ::repeating_decimal_to_fraction (non_repeating_part.c_str (),
                                   repeating_part.c_str (), numerator,
                                   denominator);
  std::pair<std::string, std::string> answer = { numerator, denominator };
  free (numerator);
  free (denominator);
  return answer;
}

std::string
arithmetica::simplify_arithmetic_expression (const std::string &expression_in,
                                             int outputType, size_t accuracy)
{
  char *answer = ::simplify_arithmetic_expression (expression_in.c_str (),
                                                   outputType, accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

std::string
arithmetica::sine (const std::string &number, size_t accuracy)
{
  char *answer = ::sine (number.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

std::string
arithmetica::square_root (const std::string &number_in, size_t accuracy)
{
  char *answer = ::square_root (number_in.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

std::string
arithmetica::tangent (const std::string &number, size_t accuracy)
{
  char *answer = ::tangent (number.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

std::pair<std::string, std::string>
arithmetica::terminating_decimal_to_fraction (const std::string &decimal)
{
  char *numerator = (char *)calloc (2 * decimal.length () + 1, 1);
  char *denominator = (char *)calloc (2 * decimal.length () + 1, 1);
  ::terminating_decimal_to_fraction (decimal.c_str (), numerator, denominator);
  std::pair<std::string, std::string> answer = { numerator, denominator };
  free (numerator);
  free (denominator);
  return answer;
}

class Fraction
{
public:
  std::string numerator, denominator;

  Fraction ();
  Fraction (const std::string &numerator, const std::string &denominator);
  Fraction (const std::string &frac);
  Fraction (const char *frac);
  Fraction (const struct fraction &frac);

  /// @brief Adds two fractions.
  /// @param n The right argument to be added to the left argument.
  /// @return Where the addition will be stored.
  Fraction operator+ (const Fraction &n);
  /// @brief Subtracts two fractions.
  /// @param n The right argument to be subtracted from the left argument.
  /// @return Where the subtraction will be stored.
  Fraction operator- (const Fraction &n);
  /// @brief Multiplies two fractions.
  /// @param n The right argument to be multiplied by the left argument.
  /// @return Where the multiplication will be stored.
  Fraction operator* (const Fraction &n);
  /// @brief Divides two fractions.
  /// @param n The denominator of the division.
  /// @return Where the division will be stored.
  Fraction operator/ (const Fraction &n);
  bool operator== (const Fraction &n);
  friend bool operator== (const Fraction &LHS, const Fraction &RHS);
  friend bool operator<(const Fraction &LHS, const Fraction &RHS);
};

class Complex
{
public:
  std::string real, imaginary;

  Complex ();
  Complex (std::string real, std::string imaginary)
  {
    this->real = real;
    this->imaginary = imaginary;
  }

  /// @brief Adds two complex numbers. If you're using this function, you know
  /// what complex numbers are.
  /// @param n The right argument to be added to the left argument.
  /// @return Where the addition will be stored.
  Complex
  operator+ (Complex n)
  {
    struct complex_arithmetica i_1;
    struct complex_arithmetica i_2;

    i_1.real = (char *)calloc (real.length () + 1, 1);
    i_1.imaginary = (char *)calloc (imaginary.length () + 1, 1);
    i_2.real = (char *)calloc (n.real.length () + 1, 1);
    i_2.imaginary = (char *)calloc (n.imaginary.length () + 1, 1);

    strcpy (i_1.real, real.c_str ());
    strcpy (i_1.imaginary, imaginary.c_str ());
    strcpy (i_2.real, n.real.c_str ());
    strcpy (i_2.imaginary, n.imaginary.c_str ());

    struct complex_arithmetica result = add_complex (i_1, i_2);
    delete_complex_number (i_1);
    delete_complex_number (i_2);

    Complex answer (result.real, result.imaginary);
    delete_complex_number (result);

    return answer;
  }
};

std::string
arithmetica::to_string (const Fraction &f)
{
  std::string answer = f.numerator;
  if (f.denominator != "1")
    {
      answer += "/" + f.denominator;
    }
  return answer;
}
