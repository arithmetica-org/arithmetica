#include "algebra_term.hpp"
#include <Fraction.hpp>
#include <helpers.hpp>

using namespace arithmetica;
using namespace arithmetica::helpers;

/// @brief Constructs an algebraic term from a string. Note that algebraic
/// terms are simple objects, only consisting of a product of factors, each of
/// which is either a variable or a constant. This constructor does not parse
/// operators, but functions are allowed, and operators are allowed in the
/// arguments of functions.
/// @param s The string to construct the algebraic term from.
algebra_term::algebra_term (const std::string &s)
{
  /* Examples of valid algebraic terms:
  - 5x
  - x^2
  - 3x^2y
  - 10/3x^2y^(3/17)
   */

  std::string str = s;

  // Replace all instances of " " with "", [] and {} with ().
  replace_all (str, " ", "");
  replace_all (str, "[", "(");
  replace_all (str, "]", ")");
  replace_all (str, "{", "(");
  replace_all (str, "}", ")");

  // Remove all empty brackets (i.e. '()').
  replace_all (str, "()", "");

  // cosec and csc refer to the same function. Similarly, ln and log without an
  // explicit base refer to the same function.
  replace_all (str, "cosec", "csc");
  replace_all (str, "ln", "log");

  // A variable suffixed with '-' causes problems with the parser, so we
  // replace it with '-1'.
  for (size_t i = 0; i < str.length () - 1; ++i)
    {
      if (str[i] == '-' && isalpha (str[i + 1]))
        {
          str.replace (i, 1, "-1");
        }
    }
}