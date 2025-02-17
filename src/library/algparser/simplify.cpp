#include <arithmetica.hpp>

namespace arithmetica {
void algexpr::simplify_in_place() {
  if (l != nullptr) {
    l = new algexpr(l->simplify());
  }
  if (r != nullptr) {
    r = new algexpr(r->simplify());
  }
  if (func == "^") {
    *this = std::move(exponent_sum());
    *this = std::move(exponent_product());
  } else if (func == "*") {
    *this = std::move(multiply());
  } else if (func == "/") {
    *this = std::move(divide());
  } else {
    *this = std::move(add());
  }
}

algexpr algexpr::simplify() {
  algexpr ans = std::move(this->deep_copy());
  ans.simplify_in_place();
  return ans;
}
} // namespace arithmetica