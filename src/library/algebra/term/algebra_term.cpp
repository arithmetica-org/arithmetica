#include "algebra_term.hpp"
#include <Fraction.hpp>
#include <helpers.hpp>
#include <iostream>
#include <stdexcept>

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

  // Remove brackets at the beginning of the string.
  while (str[0] == '(')
    {
      size_t close = get_matching_bracket (str, 0);
      if (close == std::string::npos)
        throw std::invalid_argument ("Error: in " + s
                                     + ", no matching closing bracket for "
                                       "opening bracket at position 0.");
      str[close] = '*';
      str.erase (0, 1);
    }

  // Remove all subsequent spaces.
  while (str.find ("  ") != std::string::npos)
    str.replace (str.find ("  "), 2, " ");

  // Now replace all instances of " " with "*".
  replace_all (str, " ", "*");

  // Insert a '*' between a number and a variable and between two variables.
  for (size_t i = 0; i < str.length () - 1; ++i)
    {
      if (isalpha (str[i + 1]) && (isdigit (str[i]) || isalpha (str[i])))
        {
          str.insert (i + 1, "*");
        }
    }

  // Remove all '()' that do not change the
  // meaning of the expression, i.e. that are not part of a function.
  // size_t bracket_location = 0;
  // while ((bracket_location = str.find ('(')) != std::string::npos)
  //   {

  //   }

  std::cout << "str = " << str << std::endl;
}

std::string
algebra_term::get_parsed_info ()
{
  // return rational_constant.to_string () + " "
  //        + array_to_string (irrational_constants, ", ", { "[", "]" }) + " "
  //        + array_to_string (variables, ", ", { "[", "]" }) + " "
  //        + array_to_string (function_variables, ", ", { "[", "]" });
  return "lol no.";
}