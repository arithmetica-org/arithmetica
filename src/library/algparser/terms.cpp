#include "algexpr.hpp"

namespace arithmetica {
std::vector<algexpr> algexpr::terms() {
  std::vector<algexpr> ans;
  if (func == "+") {
    for (auto &i : l->terms()) {
      ans.push_back(i);
    }
    for (auto &i : r->terms()) {
      ans.push_back(i);
    }
    return ans;
  }
  if (func == "-") {
    for (auto &i : l->terms()) {
      ans.push_back(i);
    }
    for (auto &i : r->terms()) {
      algexpr e;
      e.func = '*';
      e.l = new algexpr("-1");
      e.r = new algexpr(i);
      ans.push_back(e);
    }
    return ans;
  }
  ans.push_back(*this);
  return ans;
}

} // namespace arithmetica