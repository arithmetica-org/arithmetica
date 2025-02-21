#include "algexpr.hpp"
#include <map>

namespace arithmetica {
// run after running simplify_term ==> each term becomes *(coeff, variable)
algexpr algexpr::add() {
  auto comp = [](const algexpr &a, const algexpr &b) {
    return a.to_string() < b.to_string();
  };
  std::map<algexpr, algexpr, decltype(comp)> mp(comp); // term, coeff
  Fraction constant("0");
  for (auto &term : terms()) {
    term = term.simplify_term();
    if (term.is_numeric()) {
      constant = constant + term.coeff;
      continue;
    }
    if (term.func.empty()) {
      if (mp.count(term)) {
        mp[term] = mp[term] + algexpr("1");
      } else {
        mp[term] = algexpr("1");
      }
      continue;
    }
    if (mp.count(*term.r)) {
      mp[*term.r] = mp[*term.r] + *term.l;
    } else {
      mp[*term.r] = *term.l;
    }
  }
  for (auto &i : mp) {
    i.second = i.second.add();
  }
  algexpr ans;
  ans.l = nullptr, ans.r = nullptr, ans.coeff = constant;
  bool modified_ans = constant.to_string() != "0";
  for (auto [i, j] : mp) {
    if (j.is_natural_number() and j.coeff.to_string() == "0") {
      continue;
    }
    if (!modified_ans) {
      modified_ans = true;
      ans = j.is_natural_number() and j.coeff.to_string() == "1" ? i : j * i;
    } else {
      ans = ans +
            (j.is_natural_number() and j.coeff.to_string() == "1" ? i : j * i);
    }
  }
  return ans;
}
} // namespace arithmetica