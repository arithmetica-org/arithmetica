#include "algexpr.hpp"

namespace arithmetica {
// (a^b)^c = a^(bc)
algexpr algexpr::exponent_exponent() {
  if (func != "^" or l->func != "^") {
    return *this;
  }
  return *l->l ^ (*l->r * *r).multiply();
}
} // namespace arithmetica