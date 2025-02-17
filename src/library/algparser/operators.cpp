#include "algexpr.hpp"
#include <FractionCPP.hpp>

namespace arithmetica {
algexpr operator+(const algexpr &a, const algexpr &b) {
  algexpr ans;
  ans.func = "+";
  ans.l = new algexpr(a.deep_copy());
  ans.r = new algexpr(b.deep_copy());
  return ans;
}

algexpr operator-(const algexpr &a, const algexpr &b) {
  algexpr ans;
  ans.func = "-";
  ans.l = new algexpr(a.deep_copy());
  ans.r = new algexpr(b.deep_copy());
  return ans;
}

algexpr operator*(const algexpr &a, const algexpr &b) {
  algexpr ans;
  ans.func = "*";
  ans.l = new algexpr(a.deep_copy());
  ans.r = new algexpr(b.deep_copy());
  return ans;
}

algexpr operator/(const algexpr &a, const algexpr &b) {
  algexpr ans;
  ans.func = "/";
  ans.l = new algexpr(a.deep_copy());
  ans.r = new algexpr(b.deep_copy());
  return ans;
}

algexpr operator^(const algexpr &a, const algexpr &b) {
  algexpr ans;
  ans.func = "^";
  ans.l = new algexpr(a.deep_copy());
  ans.r = new algexpr(b.deep_copy());
  return ans;
}

bool operator==(const algexpr &a, const algexpr &b) {
  return (a - b).simplify().to_string() == "0";
}
} // namespace arithmetica