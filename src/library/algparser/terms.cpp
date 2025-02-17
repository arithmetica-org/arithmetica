#include "algexpr.hpp"
#include <FractionCPP.hpp>

namespace arithmetica {
std::vector<algexpr> algexpr::terms() {
  std::vector<algexpr> ans;
  if (func == "+") {
    for (auto &i : l->terms()) {
      ans.push_back(i.deep_copy());
    }
    for (auto &i : r->terms()) {
      ans.push_back(i.deep_copy());
    }
    return ans;
  }
  if (func == "-") {
    for (auto &i : l->terms()) {
      ans.push_back(i.deep_copy());
    }
    for (auto &i : r->terms()) {
      algexpr e;
      e.func = '*';
      e.l = new algexpr("-1");
      e.r = new algexpr(i.deep_copy());
      ans.push_back(e);
    }
    return ans;
  }
  ans.push_back(deep_copy());
  return ans;
}

} // namespace arithmetica