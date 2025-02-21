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

algexpr sqrt(const algexpr &a) { return a ^ algexpr("1/2"); }

algexpr cbrt(const algexpr &a) { return a ^ algexpr("1/3"); }

#define create_func(name)                                                      \
  algexpr name(const algexpr &a) {                                             \
    algexpr ans;                                                               \
    ans.func = #name;                                                          \
    ans.l = new algexpr(a);                                                    \
    return ans;                                                                \
  }

create_func(exp);
create_func(log);
create_func(sin);
create_func(cos);
create_func(tan);
create_func(csc);
create_func(sec);
create_func(cot);
create_func(asin);
create_func(acos);
create_func(atan);
create_func(acsc);
create_func(asec);
create_func(acot);
create_func(abs);

} // namespace arithmetica