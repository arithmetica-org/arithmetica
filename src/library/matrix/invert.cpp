#include "Matrix.hpp"

namespace arithmetica {
void Matrix::invert() {
  called_invert = true;
  if (rows() != cols()) {
    is_invertible = false;
    return;
  }

  m_inv = std::vector(rows(), std::vector<arithmetica::Fraction>(rows(), "0"));
  for (std::size_t i = 0; i < rows(); ++i) {
    m_inv[i][i] = "1";
  }

  for (std::size_t s = 0; s < rows(); ++s) {
    int nonzero_idx = rows();
    for (std::size_t i = s; i < rows(); ++i) {
      if (!(m[i][s] == "0")) {
        nonzero_idx = i;
        break;
      }
    }
    if (nonzero_idx == rows()) {
      is_invertible = false;
      return;
    }
    if (nonzero_idx != s) {
      for (std::size_t i = 0; i < rows(); ++i) {
        m[s][i] = m[s][i] + m[nonzero_idx][i];
        m_inv[s][i] = m_inv[s][i] + m_inv[nonzero_idx][i];
      }
    }
    for (std::size_t i = s + 1; i < rows(); ++i) {
      auto k = m[i][s] / m[s][s];
      for (std::size_t j = 0; j < rows(); ++j) {
        m[i][j] = m[i][j] - k * m[s][j];
        m_inv[i][j] = m_inv[i][j] - k * m_inv[s][j];
      }
    }
  }

  for (int s = int(rows()) - 1; s >= 0; --s) {
    for (std::size_t i = s + 1; i < rows(); ++i) {
      auto k = m[s][i];
      for (std::size_t j = 0; j < rows(); ++j) {
        m[s][j] = m[s][j] - k * m[i][j];
        m_inv[s][j] = m_inv[s][j] - k * m_inv[i][j];
      }
    }
    std::size_t nonzero_idx = rows();
    for (std::size_t i = s; i < rows(); ++i) {
      if (!(m[i][s] == "0")) {
        nonzero_idx = i;
        break;
      }
    }
    if (nonzero_idx == rows()) {
      is_invertible = false;
      return;
    }
    if (nonzero_idx != s) {
      for (std::size_t i = 0; i < rows(); ++i) {
        m[s][i] = m[s][i] + m[nonzero_idx][i];
        m_inv[s][i] = m_inv[s][i] + m_inv[nonzero_idx][i];
      }
    }
    auto k = m[s][s];
    for (std::size_t i = 0; i < rows(); ++i) {
      m[s][i] = m[s][i] / k;
      m_inv[s][i] = m_inv[s][i] / k;
    }
  }

  is_invertible = true;
}

bool Matrix::invertible() { return called_invert and is_invertible; }

Matrix Matrix::inverse() {
  if (!called_invert) {
    throw std::runtime_error(
        "Error: you need to call invert() before invoking this function");
  }
  if (!is_invertible) {
    throw std::runtime_error("Error: the matrix is not invertible");
  }
  return Matrix(m_inv);
}
} // namespace arithmetica