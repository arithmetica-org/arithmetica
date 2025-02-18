#include "Matrix.hpp"

namespace arithmetica {
Matrix::Matrix() : called_invert(false), is_invertible(true) {}

Matrix::Matrix(const std::vector<std::vector<arithmetica::Fraction>> &m)
    : called_invert(false), is_invertible(true), m(m) {
  for (const auto &row : m) {
    if (row.size() != m[0].size()) {
      throw std::invalid_argument("Error: Inconsistent row sizes in matrix!");
    }
  }
}

std::vector<arithmetica::Fraction> &Matrix::operator[](std::size_t r) {
  if (r >= rows()) {
    throw std::out_of_range("Error: matrix row index out of range!");
  }
  return m[r];
}

std::size_t Matrix::rows() const { return m.size(); }
std::size_t Matrix::cols() const {
  if (m.empty()) {
    return 0;
  }
  return m[0].size();
}
} // namespace arithmetica