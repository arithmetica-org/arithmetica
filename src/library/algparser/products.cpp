#include "algexpr.hpp"
#include <FractionCPP.hpp>

namespace arithmetica {
std::vector<algexpr> algexpr::products() {
  std::vector<algexpr> ans;
  if (func == "*") {
    for (auto &i : l->products()) {
      ans.push_back(i.deep_copy());
    }
    for (auto &i : r->products()) {
      ans.push_back(i.deep_copy());
    }
    return ans;
  }
  ans.push_back(deep_copy());
  return ans;
}
} // namespace arithmetica