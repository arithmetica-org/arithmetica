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

namespace arithmetica
{
namespace helpers
{
namespace arr_to_string
{
template <typename T> std::string to_string (std::vector<T> x);
template <typename T>
std::string to_string (std::vector<T> x, std::string split,
                       std::pair<std::string, std::string> brackets);
template <typename T>
std::string
to_string (T x, std::string split,
           std::pair<std::string, std::string> brackets)
{
  using std::to_string;
  return to_string (x);
}
std::string
to_string (std::string x)
{
  return x;
}
std::string
to_string (std::string x, std::string split,
           std::pair<std::string, std::string> brackets)
{
  return "\"" + x + "\"";
}

template <typename T>
std::string
array_to_string (std::vector<T> arr, std::string split = ", ",
                 std::pair<std::string, std::string> brackets = { "[", "]" })
{
  if (arr.empty ())
    return brackets.first + brackets.second;
  std::string result = brackets.first;
  for (auto i = 0; i < arr.size (); i++)
    result += to_string (arr[i], split, brackets) + split;
  return result.substr (0, result.size () - split.length ()) + brackets.second;
}

template <typename T>
std::string
to_string (std::vector<T> x, std::string split,
           std::pair<std::string, std::string> brackets)
{
  return array_to_string (x, split, brackets);
}

std::string
array_to_string (std::vector<std::string> arr, std::string split = ", ",
                 std::pair<std::string, std::string> brackets = { "[", "]" })
{
  if (arr.empty ())
    return brackets.first + brackets.second;
  std::string result = brackets.first;
  for (auto i = 0; i < arr.size (); i++)
    result += "\"" + arr[i] + "\"" + split;
  return result.substr (0, result.size () - split.length ()) + brackets.second;
}

std::string
array_to_string (std::vector<char> arr, std::string split = ", ",
                 std::pair<std::string, std::string> brackets = { "[", "]" })
{
  if (arr.empty ())
    return brackets.first + brackets.second;
  std::string result = brackets.first;
  for (size_t i = 0; i < arr.size (); i++)
    {
      result += "'" + std::string (1, arr[i]) + "'" + split;
    }
  return result.substr (0, result.size () - split.length ()) + brackets.second;
}

template <typename T>
std::string
subarray_to_string (std::vector<T> arr, size_t start, size_t elements,
                    std::string split = ", ",
                    std::pair<std::string, std::string> brackets
                    = { "[", "]" })
{
  if (arr.empty ())
    {
      return brackets.first + brackets.second;
    }
  std::string result = brackets.first;
  for (auto i = 0; i < arr.size (); i++)
    {
      result += std::to_string (arr[i]) + split;
    }
  return result.substr (0, result.size () - split.length ()) + brackets.second;
}
}
}
}

template <typename T>
std::string
arithmetica::helpers::array_to_string (
    std::vector<T> arr, const std::string &split,
    const std::pair<std::string, std::string> &brackets)
{
  return arithmetica::helpers::arr_to_string::array_to_string (arr, split,
                                                               brackets);
}