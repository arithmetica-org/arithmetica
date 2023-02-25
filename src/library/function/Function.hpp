#pragma once

#include <string>

namespace arithmetica
{
class Function
{
public:
  std::string name, argument, power;

  Function (const std::string &);

  std::string to_string ();
  /// @brief Used to get the name, argument, and power of a function.
  /// @return Returns the parsed info of the function.
  std::string get_parsed_info ();
};
}