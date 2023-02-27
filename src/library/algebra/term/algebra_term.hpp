#pragma once

#include <Fraction.hpp>
#include <Function.hpp>
#include <map>
#include <string>
#include <vector>

namespace arithmetica
{
/// @brief A term in an algebraic expression.
class algebra_term
{
  /// @details A term is a product of factors, each of which is either a
  /// variable or a constant. Can an algebraic term be raised to a power? Yes,
  /// but only if the power is another algebraic term.

private:
  Fraction rational_constant;
  /// @brief The key is the variable name, and the value is the exponent.
  std::vector<std::pair<std::string, Fraction> > variables = {};
  /// @brief Example: sin(25), log_2(5), log(12), sqrt(2), etc.
  std::vector<Function> irrational_constants = {};
  /// @brief Example: sin(a+b), log_2(x^2), log(x+10), etc.
  std::vector<Function> function_variables = {};

public:
  algebra_term () = default;
  algebra_term (const algebra_term &) = default;
  algebra_term (const std::string &);
  algebra_term (const char *);

  algebra_term &operator= (const algebra_term &) = default;
  bool operator== (const algebra_term &);

  std::string to_string ();
  std::string get_parsed_info ();

  algebra_term operator+ (const algebra_term &);
  algebra_term operator- (const algebra_term &);
  algebra_term operator* (const algebra_term &);
  algebra_term operator/ (const algebra_term &);
  algebra_term operator^ (const algebra_term &);
};
}