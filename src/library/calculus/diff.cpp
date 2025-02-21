#include "calculus.hpp"
#include <stdexcept>

namespace arithmetica {
algexpr diff(algexpr expr, algexpr x) {
  if (expr == x) {
    return algexpr("1");
  }
  if (expr.is_numeric() or (expr.l == nullptr and expr.r == nullptr)) {
    return algexpr("0");
  }
  if (expr.func == "+") {
    return (diff(*expr.l, x) + diff(*expr.r, x)).simplify();
  }
  if (expr.func == "-") {
    return (diff(*expr.l, x) - diff(*expr.r, x)).simplify();
  }
  if (expr.func == "*") {
    return (*expr.l * diff(*expr.r, x) + *expr.r * diff(*expr.l, x)).simplify();
  }
  if (expr.func == "/") {
    return ((diff(*expr.l, x) * *expr.r - *expr.l * diff(*expr.r, x)) /
            (*expr.r * *expr.r))
        .simplify();
  }
  if (expr.func == "^") {
    // (x^y)' = (y' log(x) + yx'/x) * x^y
    return ((diff(*expr.r, x) * log(*expr.l) +
             (*expr.r * diff(*expr.l, x)) / *expr.l) *
            expr)
        .simplify();
  }
  if (expr.func == "exp") {
    return (expr * diff(*expr.l, x)).simplify();
  }
  if (expr.func == "log") {
    return (diff(*expr.l, x) / *expr.l).simplify();
  }
  throw std::runtime_error("Unimplemented!");
}
} // namespace arithmetica