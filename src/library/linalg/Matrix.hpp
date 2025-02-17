#pragma once

#include <FractionCPP.hpp>
#include <algorithm>
#include <optional>
#include <stdexcept>
#include <vector>

namespace arithmetica {
class Matrix {
private:
  std::vector<std::vector<arithmetica::Fraction>> m;
  bool called_invert = false;
  bool is_invertible = true;
  std::vector<std::vector<arithmetica::Fraction>> m_inv;

public:
  Matrix();
  Matrix(const std::vector<std::vector<arithmetica::Fraction>> &m);

  std::vector<arithmetica::Fraction> &operator[](std::size_t r);

  std::size_t rows() const;
  std::size_t cols() const;

  void invert();
  bool invertible();
  Matrix inverse();
};

std::optional<Matrix> operator*(Matrix &a, Matrix &b);
} // namespace arithmetica