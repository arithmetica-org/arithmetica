#pragma once

#include "arithmetica.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/// @brief Wrapper for C++
namespace arithmetica {
/// @brief Computes the inverse cosine of a number less than 1.
/// @param number The number to compute the inverse cosine of.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The inverse cosine of the first argument.
std::string arccos(std::string n, size_t accuracy);

/// @brief Computes the inverse sine of a number less than 1.
/// @param number The number to compute the inverse sine of.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The inverse sine of the first argument.
std::string arcsin(std::string n, size_t accuracy);

/// @brief Computes the inverse tangent of a number less than 1.
/// @param x The number to compute the inverse tangent of.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The inverse tangent of the first argument.
std::string arctan(std::string n, size_t accuracy);

/// @brief Computes the cosine of the first argument.
/// @param number The angle to compute the cosine of, in radians.
/// @param accuracy The number of decimal places to calculate accuractely to.
/// @return The cosine of the first argument.
std::string cosine(std::string n, size_t accuracy);

/// @brief Computes e^x, where e is Euler's number: the base to the natural
/// logarithm.
/// @param x The number to raise e to.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The value of e^x.
std::string exponential(std::string x, size_t accuracy);

/// @brief Finds the factorial of the first argument.
/// @param n The number to find the factorial of.
/// @return The factorial of the first argument.
std::string factorial(unsigned long n);

/// @brief Converts a non-negative rational fraction to a continued fraction.
/// @param numerator The numerator of the fraction.
/// @param denominator The denominator of the fraction.
/// @return An std::string containing the continued fraction
/// representation of the input fraction. Safe to print.
std::vector<std::string>
fraction_to_continued_fraction(std::string numerator, std::string denominator);

/// @brief Finds the greatest common divisor of the first and second integral
/// arguments.
/// @param a The first non-negative number to find the gcd of.
/// @param b The second non-negative number to find the gcd of.
/// @return The gcd of the first two arguments.
std::string igcd(std::string a, std::string b);

/// @brief Finds the lowest common multiple of the first and second integral
/// arguments.
/// @param a The first non-negative number to find the lcm of.
/// @param b The second non-negative number to find the lcm of.
/// @return The lcm of the first two arguments.
std::string ilcm(std::string a, std::string b);

/// @brief Computes the natural logarithm of a non-negative number
/// to any decimal place.
/// @param n The number to compute the natural logarithm of.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The natural logarithm of the input number.
std::string natural_logarithm(std::string n, size_t accuracy);

/// @brief Computes x^n where x and n are two real numbers.
/// @param x The real number base.
/// @param n The real number exponent.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return An std::string containing x^n.
std::string power(std::string x, std::string n, size_t accuracy);

/// @brief Converts a repeating decimal to a fraction
/// @param non_repeating_part The part of the fraction (including the part
/// before the decimal place) that does not repeat. For example, in
/// 0.3343434..., "0.3" would be the non-repeating part.
/// @param repeating_part The part of the fraction which repeats. For example
/// in 0.3343434..., "34" would be the repeating part.
/// @return The output fraction.
std::pair<std::string, std::string>
repeating_decimal_to_fraction(const std::string &non_repeating_part,
                              const std::string &repeating_part);

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
std::string simplify_arithmetic_expression(const std::string &expression_in,
                                           int outputType, size_t accuracy);

/// @brief Computes the sine of the first argument.
/// @param number The angle to compute the sine of, in radians.
/// @param accuracy The number of decimal places to calculate accuractely to.
/// @return The sine of the first argument.
std::string sine(const std::string &number, size_t accuracy);

/// @brief Computes the square root of the first argument.
/// @param number The non-negative number to compute the square root of.
/// @param accuracy The number of decimal places to calculate accurately to.
/// @return The square root of the first argument.
std::string square_root(const std::string &number_in, size_t accuracy);

/// @brief Computes the trignometric tangent of the first argument.
/// @param number The angle to compute the tangent of, in radians.
/// @param accuracy The number of decimal places to calculate accuractely to.
/// @return The tangent of the first argument.
std::string tangent(const std::string &number, size_t accuracy);

/// @brief Converts a terminating decimal to a fraction reduced to its lowest
/// terms.
/// @param decimal The decimal number to convert to a fraction.
/// @return The output fraction.
std::pair<std::string, std::string>
terminating_decimal_to_fraction(const std::string &decimal);

class Fraction {
public:
  std::string numerator, denominator;

  Fraction();
  Fraction(const std::string &numerator, const std::string &denominator);
  Fraction(const std::string &frac);
  Fraction(const char *frac);
  Fraction(const struct fraction &frac);

  std::string to_string() const;

  /// @brief Adds two fractions.
  /// @param n The right argument to be added to the left argument.
  /// @return Where the addition will be stored.
  Fraction operator+(const Fraction &n);
  /// @brief Subtracts two fractions.
  /// @param n The right argument to be subtracted from the left argument.
  /// @return Where the subtraction will be stored.
  Fraction operator-(const Fraction &n);
  /// @brief Multiplies two fractions.
  /// @param n The right argument to be multiplied by the left argument.
  /// @return Where the multiplication will be stored.
  Fraction operator*(const Fraction &n);
  /// @brief Divides two fractions.
  /// @param n The denominator of the division.
  /// @return Where the division will be stored.
  Fraction operator/(const Fraction &n);
  bool operator==(const Fraction &n);
  friend bool operator==(const Fraction &LHS, const Fraction &RHS);
  friend bool operator<(const Fraction &LHS, const Fraction &RHS);
};

class Complex {
public:
  std::string real, imaginary;

  Complex();
  Complex(std::string real, std::string imaginary);

  /// @brief Adds two complex numbers. If you're using this function, you know
  /// what complex numbers are.
  /// @param n The right argument to be added to the left argument.
  /// @return Where the addition will be stored.
  Complex operator+(Complex n);
};

std::string to_string(const Fraction &f);

class algexpr {
public:
  algexpr *l;
  algexpr *r;

  // funtion applied on children
  std::string func;

  // leaf (one variable active per leaf)
  arithmetica::Fraction coeff;
  std::string variable;

  algexpr();
  algexpr(const algexpr &other);
  algexpr(std::string s);

  /// @brief Converts the algebraic expression to a string for printing.
  /// @return Returns the string form of the algebraic expression.
  std::string to_string() const;

  /// @brief Returns whether the current expression is a number
  /// without any variables.
  /// @return True or false depending on the above condition.
  bool is_numeric();
  /// @brief Returns whether the current expression is a natural number: here we
  /// define 0 to also be a natural number. [0, 1, 2, ..., inf).
  /// @return True or false depending on the above condition.
  bool is_natural_number();

  algexpr deep_copy() const;
  /// @brief Splits the expression at '+' and '-' signs, and returns the
  /// sub-expressions formed in an std::vector.
  /// @return Returns the 'terms' (that is, parts after splitting at '+' and
  /// '-') in the algebraic expression.
  std::vector<algexpr> terms();
  /// @brief Splits the expression at '*' signs, and returns the sub-expressions
  /// formed in an std::vector.
  /// @return Returns the individual products of the expression.
  std::vector<algexpr> products();

  /// @brief Combines like terms with integer coefficients. Note: this does not
  /// factor.
  /// @return Returns the algebraic expression obtained after performing
  /// additions.
  algexpr add();
  /// @brief If the expression represents a multiplication of two
  /// sub-expressions, this multiplies them.
  /// @return Returns the result after performing a single multiplication of two
  /// sub-expressions.
  algexpr multiply();
  /// @brief Performs polynomial division if the expression represents a
  /// division of two expressions.
  /// @return Evaluates and returns the result of the first division operation,
  /// if present.
  algexpr divide();
  /// @brief Distributes the exponent across all products in a term: for
  /// example, (uv)^n ==> u^n * v^n
  /// @return Returns the modified expression.
  algexpr exponent_product();
  /// @brief Expands (x_1 + x_2 + ... + x_k)^n: distributes the exponent across
  /// all terms.
  /// @return Returns the modified expression.
  algexpr exponent_sum();
  /// @brief Simplifies a single product by combining powers (x^a*x^b ==> x^(a +
  /// b)), and ordering variables.
  /// @param bring_coeff_to_front Decides whether to bring the coefficient to
  /// the front of the expression or not.
  /// @return Returns the simplified term.
  algexpr simplify_term(bool bring_coeff_to_front = true);

  /// @brief Simplifies the algebraic expression in place.
  void simplify_in_place();
  /// @brief Simplifies the algebraic experssion.
  /// @return Returns the simplified expression.
  algexpr simplify();
};

algexpr operator+(const algexpr &a, const algexpr &b);
algexpr operator-(const algexpr &a, const algexpr &b);
algexpr operator*(const algexpr &a, const algexpr &b);
algexpr operator/(const algexpr &a, const algexpr &b);
algexpr operator^(const algexpr &a, const algexpr &b);
bool operator==(const algexpr &a, const algexpr &b);

std::pair<algexpr, algexpr> divide_polynomial(algexpr f, algexpr g);

class Matrix {
public:
  Matrix();
  Matrix(const std::vector<std::vector<arithmetica::Fraction>> &m);

  std::vector<arithmetica::Fraction> &operator[](std::size_t r);

  std::size_t rows() const;
  std::size_t cols() const;

  void invert();
  bool invertible();
  Matrix inverse();
};

std::optional<Matrix> operator*(Matrix &a, Matrix &b);
} // namespace arithmetica
