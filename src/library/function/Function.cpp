#include "Function.hpp"

#include <helpers.hpp>
#include <stdexcept>

using namespace arithmetica;
using namespace arithmetica::helpers;

Function::Function (const std::string &str)
{
  std::string s = str;

  // cosec = csc
  replace_all (s, "cosec", "csc");

  // Deal with inverse trigonometric functions.
  for (auto &i : get_trigonometric_functions ())
    {
      replace_all (s, i + "^(-1)", "arc" + i);
    }

  size_t pow_index = s.find ('^');
  size_t bracket_index = s.find ('(');

  size_t after_pow = bracket_index;

  if (pow_index == std::string::npos || bracket_index < pow_index)
    {
      name = s.substr (0, bracket_index);
      power = "1";
    }
  else
    {
      name = s.substr (0, pow_index);

      if (s[pow_index + 1] == '(')
        {
          size_t closing_bracket
              = helpers::get_matching_bracket (s, pow_index + 1);
          power = s.substr (pow_index + 2, closing_bracket - pow_index - 2);
          after_pow = closing_bracket + 1;
        }
      else
        {
          power = s.substr (pow_index + 1, bracket_index - pow_index - 1);
        }
    }

  if (s[after_pow] != '(')
    {
      throw std::runtime_error ("Error: Function contents have to be enclosed "
                                "in parentheses.");
    }

  size_t closing_bracket = helpers::get_matching_bracket (s, after_pow);
  argument = s.substr (after_pow + 1, closing_bracket - after_pow - 1);
}

std::string
Function::to_string ()
{
  return name + "^(" + power + ")(" + argument + ")";
}

std::string
arithmetica::Function::get_parsed_info ()
{
  return "name=\"" + name + "\" power=\"" + power + "\" argument=\"" + argument
         + "\"";
}