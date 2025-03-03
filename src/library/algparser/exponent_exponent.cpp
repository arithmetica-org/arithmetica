#include "algexpr.hpp"

namespace arithmetica {
// (a^b)^c = a^(bc)
algexpr algexpr::exponent_exponent() {
  if (func != "^" or l->func != "^") {
    return *this;
  }
  algexpr pow = (*l->r * *r).multiply();
  if (pow == algexpr("0")) {
    return algexpr("1");
  }
  if (pow == algexpr("1")) {
    return *l->l;
  }
  return *l->l ^ pow;
}
} // namespace arithmetica