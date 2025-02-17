#include <arithmetica.hpp>

namespace arithmetica {
algexpr algexpr::deep_copy() const {
  algexpr copy;
  copy.func = func;
  copy.coeff = coeff;
  copy.variable = variable;
  copy.l = l ? new algexpr(l->deep_copy()) : nullptr;
  copy.r = r ? new algexpr(r->deep_copy()) : nullptr;
  return copy;
}
} // namespace arithmetica