#include "Matrix.hpp"

namespace arithmetica {
std::string Matrix::to_string() const {
  std::string ans = "{";
  for (std::size_t i = 0; i < m.size(); ++i) {
    ans += "{";
    for (std::size_t j = 0; j < m[i].size(); ++j) {
      ans += a[i][j].to_string();
      if (j != a[i].size() - 1) {
        ans += ", ";
      }
    }
    ans += "}";
    if (i != a.size() - 1) {
      ans += ", ";
    }
  }
  ans += "}";
  return ans;
}
} // namespace arithmetica