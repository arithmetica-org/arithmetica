#include "algexpr.hpp"
#include <FractionCPP.hpp>

namespace arithmetica {
algexpr algexpr::exponent_sum() {
  if (func != "^") {
    return *this;
  }
  if (l->is_numeric() and l->coeff.to_string() == "1") {
    algexpr ans;
    ans.coeff = "1";
    return ans;
  }
  if (!r->is_natural_number()) {
    return *this;
  }
  if (l->is_numeric()) {
    Fraction constant("1");
    for (Fraction i("0"); !(i == r->coeff); i = i + Fraction("1")) {
      constant = constant * l->coeff;
    }
    algexpr ans;
    ans.coeff = constant;
    return ans;
  }
  algexpr ans("1");
  for (Fraction i("0"); !(i == r->coeff); i = i + Fraction("1")) {
    ans = (ans * *l).multiply();
  }
  return ans;
}
} // namespace arithmetica