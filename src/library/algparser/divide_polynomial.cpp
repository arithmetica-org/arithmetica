#include "algexpr.hpp"
#include <FractionCPP.hpp>
#include <map>

namespace arithmetica {
std::pair<algexpr, algexpr> divide_polynomial(algexpr e1, algexpr e2) {
  // note: i havent coded division where the powers for any of the variables
  // involve variables

  // this is because you can't really compare degrees to find the max (something
  // needed by my algorithm) when they involve variables

  auto f = e1.terms();
  auto g = e2.terms();
  auto comp = [](const algexpr &a, const algexpr &b) {
    return a.to_string() < b.to_string();
  };
  bool power_contains_variable = false;
  auto extract_highest_powers = [&](std::vector<algexpr> &f) {
    std::map<algexpr, Fraction, decltype(comp)> p(comp);
    for (auto &term : f) {
      for (auto &i : term.simplify_term().products()) {
        if (i.is_numeric()) {
          continue;
        }
        if (i.func == "^") {
          if (!i.r->is_numeric()) {
            power_contains_variable = true;
            continue;
          }
          if (p.count(*i.l)) {
            p[*i.l] = i.r->coeff < p[*i.l] ? p[*i.l] : i.r->coeff;
          } else {
            p[*i.l] = i.r->coeff;
          }
        } else {
          if (p.count(*i.l)) {
            p[*i.l] = Fraction("1") < p[*i.l] ? p[*i.l] : Fraction("1");
          } else {
            p[*i.l] = Fraction("1");
          }
        }
      }
    }
    return p;
  };
  auto p = extract_highest_powers(f), q = extract_highest_powers(g);
  if (power_contains_variable) {
    return {algexpr("0"), e1};
  }
  // ensure p >= q
  for (auto &i : q) {
    if (p[i.first] < i.second) {
      return {algexpr("0"), e1};
    }
  }
  throw std::runtime_error("Unimplemented function!");
}
} // namespace arithmetica