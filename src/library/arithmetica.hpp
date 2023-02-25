#pragma once

#include "arithmetica.h"
#include <cstdlib>
#include <cstring>
#include <string>

/// @brief Wrapper for C++
namespace arithmetica
{
/// @brief Computes the inverse cosine of a number less than 1.
/// @param number The number to compute the inverse cosine of.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The inverse cosine of the first argument.
std::string
arccos (std::string n, size_t accuracy)
{
  char *answer = ::arccos (n.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

/// @brief Computes the inverse sine of a number less than 1.
/// @param number The number to compute the inverse sine of.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The inverse sine of the first argument.
std::string
arcsin (std::string n, size_t accuracy)
{
  char *answer = ::arcsin (n.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

/// @brief Computes the inverse tangent of a number less than 1.
/// @param x The number to compute the inverse tangent of.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The inverse tangent of the first argument.
std::string
arctan (std::string n, size_t accuracy)
{
  char *answer = ::arctan (n.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

/// @brief Computes the cosine of the first argument.
/// @param number The angle to compute the cosine of, in radians.
/// @param accuracy The number of decimal places to calculate accuractely to.
/// @return The cosine of the first argument.
std::string
cosine (std::string n, size_t accuracy)
{
  char *answer = ::cosine (n.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

/// @brief Computes e^x, where e is Euler's number: the base to the natural
/// logarithm.
/// @param x The number to raise e to.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The value of e^x.
std::string
exponential (std::string x, size_t accuracy)
{
  char *answer = ::exponential (x.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

/// @brief Finds the factorial of the first argument.
/// @param n The number to find the factorial of.
/// @return The factorial of the first argument.
std::string
factorial (unsigned long n)
{
  char *answer
      = (char *)calloc (n * __builtin_floorf (__builtin_log10 (n) + 1) + 2, 1);
  ::factorial (n, answer);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

/// @brief Converts a non-negative rational fraction to a continued fraction.
/// @param numerator The numerator of the fraction.
/// @param denominator The denominator of the fraction.
/// @return An std::string containing the continued fraction
/// representation of the input fraction. Safe to print.
std::string
fraction_to_continued_fraction (std::string numerator, std::string denominator)
{
  char *answer = ::fraction_to_continued_fraction (numerator.c_str (),
                                                   denominator.c_str ());
  std::string _answer = answer;
  free (answer);
  return _answer;
}

/// @brief Finds the greatest common divisor of the first and second integral
/// arguments.
/// @param a The first non-negative number to find the gcd of.
/// @param b The second non-negative number to find the gcd of.
/// @return The gcd of the first two arguments.
std::string
igcd (std::string a, std::string b)
{
  char *gcd = (char *)calloc (a.length () + b.length () + 3, 1);
  ::igcd (a.c_str (), b.c_str (), gcd);
  std::string answer = gcd;
  free (gcd);
  return answer;
}

/// @brief Finds the lowest common multiple of the first and second integral
/// arguments.
/// @param a The first non-negative number to find the lcm of.
/// @param b The second non-negative number to find the lcm of.
/// @return The lcm of the first two arguments.
std::string
ilcm (std::string a, std::string b)
{
  char *lcm = (char *)calloc (2 * (a.length () + b.length () + 3) + 3, 1);
  ::ilcm (a.c_str (), b.c_str (), lcm);
  std::string answer = lcm;
  free (lcm);
  return answer;
}

/// @brief Computes the natural logarithm of a non-negative number
/// to any decimal place.
/// @param n The number to compute the natural logarithm of.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The natural logarithm of the input number.
std::string
natural_logarithm (std::string n, size_t accuracy)
{
  char *answer = ::natural_logarithm (n.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

/// @brief Computes x^n where x and n are two real numbers.
/// @param x The real number base.
/// @param n The real number exponent.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return An std::string containing x^n.
std::string
power (std::string x, std::string n, size_t accuracy)
{
  char *pow = ::power (x.c_str (), n.c_str (), accuracy);
  std::string answer = pow;
  free (pow);
  return answer;
}

/// @brief Converts a repeating decimal to a fraction
/// @param non_repeating_part The part of the fraction (including the part
/// before the decimal place) that does not repeat. For example, in
/// 0.3343434..., "0.3" would be the non-repeating part.
/// @param repeating_part The part of the fraction which repeats. For example
/// in 0.3343434..., "34" would be the repeating part.
/// @return The output fraction.
std::pair<std::string, std::string>
repeating_decimal_to_fraction (const std::string &non_repeating_part,
                               const std::string &repeating_part)
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

/// @brief Simplies an arithmetic expression involving the five basic math
/// operations: addition, subtraction, multiplication, division, and
/// exponentiation.
/// @param expression The expression to simplify, in standard computer
/// mathematical notation.
/// @param outputType This parameter controls the output type. Use zero to
/// output a decimal, one to output a fraction, and two to output a mixed
/// fraction. Output types one and two will calculate everything with maximum
/// precision.
/// @param accuracy The accuracy of the divisions and exponentiations
/// performed. You only need to worry about this if you have fractional
/// exponents in your input, or if you have divisions in output type zero.
/// @return The simplified expression.
std::string
simplify_arithmetic_expression (const std::string &expression_in,
                                int outputType, size_t accuracy)
{
  char *answer = ::simplify_arithmetic_expression (expression_in.c_str (),
                                                   outputType, accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

/// @brief Computes the sine of the first argument.
/// @param number The angle to compute the sine of, in radians.
/// @param accuracy The number of decimal places to calculate accuractely to.
/// @return The sine of the first argument.
std::string
sine (const std::string &number, size_t accuracy)
{
  char *answer = ::sine (number.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

/// @brief Computes the square root of the first argument.
/// @param number The non-negative number to compute the square root of.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The square root of the first argument.
std::string
square_root (const std::string &number_in, size_t accuracy)
{
  char *answer = ::square_root (number_in.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

/// @brief Computes the trignometric tangent of the first argument.
/// @param number The angle to compute the tangent of, in radians.
/// @param accuracy The number of decimal places to calculate accuractely to.
/// @return The tangent of the first argument.
std::string
tangent (const std::string &number, size_t accuracy)
{
  char *answer = ::tangent (number.c_str (), accuracy);
  std::string _answer = answer;
  free (answer);
  return _answer;
}

/// @brief Converts a terminating decimal to a fraction reduced to its lowest
/// terms.
/// @param decimal The decimal number to convert to a fraction.
/// @return The output fraction.
std::pair<std::string, std::string>
terminating_decimal_to_fraction (const std::string &decimal)
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
to_string (const Fraction &f)
{
  return f.numerator + "/" + f.denominator;
}
} // namespace arithmetica