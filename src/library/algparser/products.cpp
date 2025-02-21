#include "algexpr.hpp"

namespace arithmetica {
std::vector<algexpr> algexpr::products() {
  std::vector<algexpr> ans;
  if (func == "*") {
    for (auto &i : l->products()) {
      ans.push_back(i);
    }
    for (auto &i : r->products()) {
      ans.push_back(i);
    }
    return ans;
  }
  ans.push_back(*this);
  return ans;
}
} // namespace arithmetica