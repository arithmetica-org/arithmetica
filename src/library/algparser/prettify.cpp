#include "algexpr.hpp"

namespace arithmetica {
algexpr algexpr::prettify_term() {
  algexpr numerator("1"), denominator("1");
  bool num_changed = false, den_changed = false;
  for (auto i : products()) {
    if (i.func == "^") {
      i.r = new algexpr(i.r->simplify());
      if (!i.r->is_negative_number()) {
        if (num_changed) {
          numerator = numerator * i;
        } else {
          num_changed = true;
          numerator = i;
        }
      } else {
        if (den_changed) {
          algexpr pow = (*i.r * algexpr("-1")).multiply();
          if (pow.is_numeric() and pow.coeff == Fraction("1")) {
            denominator = denominator * *i.l;
          } else {
            denominator = denominator * (*i.l ^ pow);
          }
        } else {
          den_changed = true;
          algexpr pow = (*i.r * algexpr("-1")).multiply();
          if (pow.is_numeric() and pow.coeff == Fraction("1")) {
            denominator = *i.l;
          } else {
            denominator = *i.l ^ pow;
          }
        }
      }
    } else {
      if (num_changed) {
        numerator = numerator * i;
      } else {
        num_changed = true;
        numerator = i;
      }
    }
  }
  if (denominator.is_numeric() and denominator.coeff == Fraction("1")) {
    return numerator;
  }
  return numerator / denominator;
}

algexpr algexpr::prettify() {
  algexpr ans = this->prettify_term();
  if (ans.l) {
    ans.l = new algexpr(ans.l->prettify());
  }
  if (ans.r) {
    ans.r = new algexpr(ans.r->prettify());
  }
  // x + (-1)y ==> x - y
  if (ans.func == "+") {
    if (ans.r->is_negative_number()) {
      ans.func = "-";
      ans.r->coeff = ans.r->coeff * "-1";
    }
    if (ans.r->l and ans.r->l->is_negative_number()) {
      ans.func = "-";
      ans.r->l->coeff = ans.r->l->coeff * "-1";
      ans.r = new algexpr(ans.r->simplify_term(false));
    }
    return ans;
  }
  // x^(1/2) ==> sqrt, x^(1/3) ==> cbrt
  if (ans.func == "^") {
    if (ans.r->is_numeric() and ans.r->coeff == Fraction("1/2")) {
      algexpr _ans;
      _ans.func = "sqrt";
      _ans.l = new algexpr(*ans.l);
      return _ans;
    } else if (ans.r->is_numeric() and ans.r->coeff == Fraction("1/3")) {
      algexpr _ans;
      _ans.func = "cbrt";
      _ans.l = new algexpr(*ans.l);
      return _ans;
    }
    return ans;
  }
  return ans;
}
} // namespace arithmetica