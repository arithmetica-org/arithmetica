#include "algexpr.hpp"

namespace arithmetica {
algexpr algexpr::multiply() {
  if (func != "*") {
    return *this;
  }
  auto a = l->terms();
  auto b = r->terms();
  if (a.size() == 1 and b.size() == 1) {
    return (a[0] * b[0]).simplify_term(false);
  }
  algexpr ans("0");
  bool ans_updated = false;
  for (std::size_t i = 0; i < a.size(); ++i) {
    for (std::size_t j = 0; j < b.size(); ++j) {
      if (!ans_updated) {
        ans_updated = true;
        ans = (a[i] * b[j]).multiply();
      } else {
        ans = ans + (a[i] * b[j]).multiply();
      }
    }
  }
  return ans.add();
}
} // namespace arithmetica