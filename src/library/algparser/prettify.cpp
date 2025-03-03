#include "algexpr.hpp"

namespace arithmetica {
algexpr algexpr::prettify_term() {
  algexpr numerator("1"), denominator("1");
  for (auto i : products()) {
    if (i.func == "^") {
      i.r = new algexpr(i.r->simplify());
      if (!i.r->is_negative_number()) {
        numerator = numerator * i;
      } else {
        denominator = denominator * (*i.l ^ (*i.r * algexpr("-1")).multiply());
      }
    } else {
      numerator = numerator * i;
    }
  }
  if (denominator == algexpr("1")) {
    return numerator.simplify_term(false);
  }
  return numerator.simplify_term(false) / denominator.simplify_term(false);
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
    if (*ans.r == algexpr("1/2")) {
      algexpr _ans;
      _ans.func = "sqrt";
      _ans.l = new algexpr(*ans.l);
      return _ans;
    } else if (*ans.r == algexpr("1/3")) {
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