#include "Matrix.hpp"

namespace arithmetica {
Matrix::Matrix() {}

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