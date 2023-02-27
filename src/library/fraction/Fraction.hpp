// C++ wrapper for fraction.h

#pragma once

#include "fraction_include.hpp"
#include <string>

class Fraction
{
public:
  std::string numerator, denominator;

  Fraction ();
  Fraction (const std::string &numerator, const std::string &denominator);
  Fraction (const std::string &frac);
  Fraction (const char *frac);
  Fraction (const struct fraction &frac);

  std::string to_string ();

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