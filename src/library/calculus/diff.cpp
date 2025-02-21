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
  if (expr.func == "sin") {
    return (cos(*expr.l) * diff(*expr.l, x)).simplify();
  }
  if (expr.func == "cos") {
    return (algexpr("-1") * sin(*expr.l) * diff(*expr.l, x)).simplify();
  }
  if (expr.func == "tan") {
    return ((sec(*expr.l) ^ algexpr("2")) * diff(*expr.l, x)).simplify();
  }
  if (expr.func == "csc") {
    return (algexpr("-1") * csc(*expr.l) * cot(*expr.l) * diff(*expr.l, x))
        .simplify();
  }
  if (expr.func == "sec") {
    return (sec(*expr.l) * tan(*expr.l) * diff(*expr.l, x)).simplify();
  }
  if (expr.func == "cot") {
    return (algexpr("-1") * (csc(*expr.l) ^ algexpr("2")) * diff(*expr.l, x))
        .simplify();
  }
  if (expr.func == "asin") {
    return (diff(*expr.l, x) / sqrt(algexpr("1") - (*expr.l * *expr.l)))
        .simplify();
  }
  if (expr.func == "acos") {
    return (algexpr("-1") * diff(*expr.l, x) /
            sqrt(algexpr("1") - (*expr.l * *expr.l)))
        .simplify();
  }
  if (expr.func == "atan") {
    return (diff(*expr.l, x) / (algexpr("1") + *expr.l * *expr.l)).simplify();
  }
  if (expr.func == "acsc") {
    return (diff(asin((algexpr("1") / *expr.l)), x)).simplify();
  }
  if (expr.func == "asec") {
    return (diff(acos(algexpr("1") / *expr.l), x)).simplify();
  }
  if (expr.func == "acot") {
    return (diff(atan(algexpr("1") / *expr.l), x)).simplify();
  }
  if (expr.func == "abs") {
    return ((*expr.l / expr) * diff(*expr.l, x)).simplify();
  }
  throw std::runtime_error("Unimplemented!");
}
} // namespace arithmetica