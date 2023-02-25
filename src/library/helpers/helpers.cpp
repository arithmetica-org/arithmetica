#include "helpers.hpp"

std::vector<std::string> trigonometric_functions = {
  "sin",  "cos",  "tan",  "csc",  "sec",  "cot",
  "sinh", "cosh", "tanh", "csch", "sech", "coth",
};

std::vector<std::string> supported_functions
    = { "sqrt",    "cbrt",    "log",    "sin",     "cos",     "tan",
        "csc",     "sec",     "cot",    "sinh",    "cosh",    "tanh",
        "csch",    "sech",    "coth",   "arcsin",  "arccos",  "arctan",
        "arccsc",  "arcsec",  "arccot", "arcsinh", "arccosh", "arctanh",
        "arccsch", "arcsech", "arccoth" };

std::vector<std::string> &
arithmetica::helpers::get_trigonometric_functions ()
{
  return trigonometric_functions;
}

std::vector<std::string> &
arithmetica::helpers::get_supported_functions ()
{
  return supported_functions;
}

void
arithmetica::helpers::replace_all (std::string &str, const std::string &from,
                                   const std::string &to)
{
  if (from.empty ())
    return;
  size_t start_pos = 0;
  while ((start_pos = str.find (from, start_pos)) != std::string::npos)
    {
      str.replace (start_pos, from.length (), to);
      start_pos += to.length ();
    }
}

size_t
arithmetica::helpers::get_matching_bracket (const std::string &str,
                                            const size_t &index)
{
  // If the index is out of bounds, return the index.
  if (index >= str.length ())
    return index;

  // First determine the type of bracket we're looking for.
  // Valid: (), [], {}
  char opening_bracket, closing_bracket;
  switch (str[index])
    {
    case '(':
    case ')':
      opening_bracket = '(';
      closing_bracket = ')';
      break;
    case '[':
    case ']':
      opening_bracket = '[';
      closing_bracket = ']';
      break;
    case '{':
    case '}':
      opening_bracket = '{';
      closing_bracket = '}';
      break;
    default:
      return std::string::npos;
    }

  // Now, determine whether we're looking for the opening or closing bracket.
  if (str[index] == opening_bracket)
    {
      // We're looking for the closing bracket.
      size_t bracket_count = 1;
      for (size_t i = index + 1; i < str.length (); ++i)
        {
          if (str[i] == opening_bracket)
            bracket_count++;
          else if (str[i] == closing_bracket)
            bracket_count--;
          if (bracket_count == 0)
            return i;
        }
      return std::string::npos;
    }

  // We're looking for the opening bracket.
  size_t bracket_count = 1;
  for (size_t i = index - 1; i + 1 > 0; --i)
    {
      if (str[i] == closing_bracket)
        bracket_count++;
      else if (str[i] == opening_bracket)
        bracket_count--;
      if (bracket_count == 0)
        return i;
    }
  return std::string::npos;
}