#include "Matrix.hpp"

namespace arithmetica {
std::optional<Matrix> operator*(Matrix &a, Matrix &b) {
  if (a.cols() != b.rows()) {
    return std::nullopt;
  }
  Matrix ans(
      std::vector(a.rows(), std::vector<arithmetica::Fraction>(b.cols(), "0")));
  for (int i = 0; i < a.rows(); ++i) {
    for (int j = 0; j < b.cols(); ++j) {
      for (int k = 0; k < a.cols(); ++k) {
        ans.m[i][j] = ans.m[i][j] + a.m[i][k] * b.m[k][j];
      }
    }
  }
  return ans;
}
} // namespace arithmetica