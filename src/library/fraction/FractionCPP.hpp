// C++ wrapper for fraction.h

#pragma once

#include "fraction_includeCPP.hpp"
#include <algorithm>
#include <string>

namespace arithmetica {
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
  Fraction operator+(const Fraction &n) const;
  /// @brief Subtracts two fractions.
  /// @param n The right argument to be subtracted from the left argument.
  /// @return Where the subtraction will be stored.
  Fraction operator-(const Fraction &n) const;
  /// @brief Multiplies two fractions.
  /// @param n The right argument to be multiplied by the left argument.
  /// @return Where the multiplication will be stored.
  Fraction operator*(const Fraction &n) const;
  /// @brief Divides two fractions.
  /// @param n The denominator of the division.
  /// @return Where the division will be stored.
  Fraction operator/(const Fraction &n) const;
  bool operator==(const Fraction &n) const;
  bool operator<(const Fraction &n) const;
  bool operator>(const Fraction &n) const;
};
} // namespace arithmetica