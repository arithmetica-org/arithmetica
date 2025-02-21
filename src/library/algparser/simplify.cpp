#include "algexpr.hpp"
#include <FractionCPP.hpp>

namespace arithmetica {
void algexpr::simplify_in_place() {
  if (l != nullptr) {
    auto t = l;
    l = new algexpr(l->simplify());
    delete t;
  }
  if (r != nullptr) {
    auto t = r;
    r = new algexpr(r->simplify());
    delete t;
  }
  if (func == "^") {
    *this = exponent_sum();
    *this = exponent_product();
    *this = exponent_exponent();
  } else if (func == "*") {
    *this = multiply();
  } else if (func == "/") {
    *this = divide();
  } else if (func == "sqrt") {
    *this = sqrt(*l);
  } else if (func == "cbrt") {
    *this = cbrt(*l);
  } else {
    *this = add();
  }
}

algexpr algexpr::simplify() {
  algexpr ans = *this;
  ans.simplify_in_place();
  return ans;
}
} // namespace arithmetica