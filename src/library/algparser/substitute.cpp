#include "algexpr.hpp"

namespace arithmetica {
algexpr algexpr::substitute(algexpr x, algexpr y) {
  if (x.func.empty()) {
    if (func.empty() and *this == x) {
      return y;
    }
  } else if (*this == x) {
    return y;
  }
  algexpr ans = *this;
  if (ans.l) {
    ans.l = new algexpr(ans.l->substitute(x, y));
  }
  if (ans.r) {
    ans.r = new algexpr(ans.r->substitute(x, y));
  }
  return ans;
}
} // namespace arithmetica