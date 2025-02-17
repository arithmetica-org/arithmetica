#include "algexpr.hpp"
#include <FractionCPP.hpp>

namespace arithmetica {
algexpr algexpr::divide() {
  if (func != "/") {
    return *this;
  }
  auto ans = divide_polynomial(*l, *r);
  if (ans.second == algexpr("0")) {
    return ans.first;
  }
  return (ans.first + (*l * (ans.second ^ algexpr("-1"))).multiply()).add();
}
} // namespace arithmetica