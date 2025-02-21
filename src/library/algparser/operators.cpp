#include "algexpr.hpp"

namespace arithmetica {
algexpr operator+(const algexpr &a, const algexpr &b) {
  algexpr ans;
  ans.func = "+";
  ans.l = new algexpr(a);
  ans.r = new algexpr(b);
  return ans;
}

algexpr operator-(const algexpr &a, const algexpr &b) {
  algexpr ans;
  ans.func = "-";
  ans.l = new algexpr(a);
  ans.r = new algexpr(b);
  return ans;
}

algexpr operator*(const algexpr &a, const algexpr &b) {
  algexpr ans;
  ans.func = "*";
  ans.l = new algexpr(a);
  ans.r = new algexpr(b);
  return ans;
}

algexpr operator/(const algexpr &a, const algexpr &b) {
  algexpr ans;
  ans.func = "/";
  ans.l = new algexpr(a);
  ans.r = new algexpr(b);
  return ans;
}

algexpr operator^(const algexpr &a, const algexpr &b) {
  algexpr ans;
  ans.func = "^";
  ans.l = new algexpr(a);
  ans.r = new algexpr(b);
  return ans;
}

bool operator==(const algexpr &a, const algexpr &b) {
  return (a - b).simplify().to_string() == "0";
}
} // namespace arithmetica