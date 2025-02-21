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

algexpr exp(const algexpr &a) {
  algexpr ans;
  ans.func = "exp";
  ans.l = new algexpr(a);
  return ans;
}

algexpr log(const algexpr &a) {
  algexpr ans;
  ans.func = "log";
  ans.l = new algexpr(a);
  return ans;
}

algexpr sqrt(const algexpr &a) { return *a.l ^ algexpr("1/2"); }

algexpr cbrt(const algexpr &a) { return *a.l ^ algexpr("1/3"); }
} // namespace arithmetica