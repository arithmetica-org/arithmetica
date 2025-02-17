#include <arithmetica.hpp>

namespace arithmetica {
bool algexpr::is_numeric() {
  return func.empty() and variable.empty() and l == nullptr and r == nullptr;
}

bool algexpr::is_natural_number() {
  if (!is_numeric()) {
    return false;
  }
  std::string s = coeff.to_string();
  return s.find('/') == std::string::npos and !s.empty() and s[0] != '-';
}
} // namespace arithmetica