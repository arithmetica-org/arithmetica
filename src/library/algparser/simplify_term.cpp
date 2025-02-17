#include <arithmetica.hpp>

namespace arithmetica {
algexpr algexpr::simplify_term(bool bring_coeff_to_front) {
  // we have a pure product (hopefully lol)
  auto prods = exponent_product().products();
  auto comp = [](const algexpr &a, const algexpr &b) {
    return a.to_string() < b.to_string();
  };
  std::map<algexpr, algexpr, decltype(comp)> mp(comp); // base, exponent
  Fraction constants("1");
  for (auto &term : prods) {
    if (term.is_numeric()) {
      constants = constants * term.coeff;
      continue;
    }
    if (term.func != "^") {
      if (mp.count(term)) {
        mp[term] = mp[term] + algexpr("1");
      } else {
        mp[term] = algexpr("1");
      }
      continue;
    }
    if (mp.count(*term.l)) {
      mp[*term.l] = mp[*term.l] + *term.r;
    } else {
      mp[*term.l] = *term.r;
    }
  }
  for (auto &i : mp) {
    i.second = i.second.add();
  }
  algexpr ans;
  ans.coeff = "1";
  bool ans_modified = false;
  for (auto it = mp.begin(); it != mp.end(); ++it) {
    if (it->second.is_natural_number() and
        it->second.coeff.to_string() == "0") {
      continue;
    }
    if (it->second.is_natural_number() and
        it->second.coeff.to_string() == "1") {
      if (!ans_modified) {
        ans = it->first;
        ans_modified = true;
      } else {
        ans = ans * it->first;
      }
    } else {
      if (!ans_modified) {
        ans = it->first ^ it->second;
        ans_modified = true;
      } else {
        ans = ans * (it->first ^ it->second);
      }
    }
  }
  if (constants.to_string() == "1" and !bring_coeff_to_front) {
    return ans;
  }
  algexpr expr_coeff;
  expr_coeff.coeff = constants;
  if (constants.to_string() == "0") {
    return expr_coeff;
  }
  if (!ans_modified) {
    ans = expr_coeff;
  } else {
    ans = expr_coeff * ans;
  }
  return ans;
}
} // namespace arithmetica