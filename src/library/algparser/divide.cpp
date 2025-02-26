#include "algexpr.hpp"
#include <FractionCPP.hpp>
#include <map>

using namespace arithmetica;
namespace arithmetica {
// note that this WILL modify the polynomials in the case of them having
// negative powers: it will make it so they don't
std::pair<algexpr, algexpr> divide_polynomial(algexpr &e1, algexpr &e2) {
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
  auto extract_highest_powers = [&](std::vector<algexpr> &f, bool highest) {
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
            p[*i.l] = ((i.r->coeff < p[*i.l] and highest) or
                       (p[*i.l] < i.r->coeff and !highest))
                          ? p[*i.l]
                          : i.r->coeff;
          } else {
            p[*i.l] = i.r->coeff;
          }
        } else {
          if (p.count(i)) {
            p[i] = ((Fraction("1") < p[i] and highest) or
                    (Fraction("1") < p[i] and !highest))
                       ? p[i]
                       : Fraction("1");
          } else {
            p[i] = Fraction("1");
          }
        }
      }
    }
    return p;
  };
  auto p = extract_highest_powers(f, true), q = extract_highest_powers(g, true);
  if (power_contains_variable) {
    return {algexpr("0"), e1};
  }
  // ensure p >= q
  for (auto &i : q) {
    if (!p.count(i.first) or p[i.first] < i.second) {
      return {algexpr("0"), e1};
    }
  }
  // no variables in denominator
  if (q.empty()) {
    algexpr e;
    e.coeff = Fraction("1") / e2.add().coeff;
    return {(e1 * e).simplify(), algexpr("0")};
  }

  // deal with negative powers by multiplying both the numerator and denominator
  {
    algexpr factor("1");
    bool needed = false;
    for (auto &[base, pow] : extract_highest_powers(g, false)) {
      if (pow < Fraction("0")) {
        needed = true;
        arithmetica::algexpr e1;
        e1.coeff = pow * Fraction("-1");
        factor = factor * (base ^ e1);
      }
    }
    if (needed) {
      e1 = (e1 * factor).simplify();
      e2 = (e2 * factor).simplify();
      return divide_polynomial(e1, e2);
    }
  }

  // note: by this point, we have alr ensured that powers don't contain
  // variables
  auto get_pow = [&](algexpr term, algexpr base) {
    for (auto &i : term.products()) {
      if (i.func == "^") {
        if (*i.l == base) {
          return i.r->coeff;
        }
      } else if (i == base) {
        return Fraction("1");
      }
    }
    return Fraction("0");
  };

  algexpr var = q.begin()->first; // we can use any arbitrary variable
  algexpr max_f("0"), max_g("0");
  Fraction max_pow_f("-1"), max_pow_g("-1");
  for (std::size_t i = 0; i < f.size(); ++i) {
    auto p = get_pow(f[i], var);
    if (max_pow_f < p) {
      max_pow_f = p;
      max_f = f[i];
    }
  }
  for (std::size_t i = 0; i < g.size(); ++i) {
    auto p = get_pow(g[i], var);
    if (max_pow_g < p) {
      max_pow_g = p;
      max_g = g[i];
    }
  }

  auto k = (max_f * (max_g ^ algexpr("-1"))).simplify();
  auto left = (e1 - (k * e2).multiply()).add();
  auto ans = divide_polynomial(left, e2);
  if (ans.second == algexpr("0")) {
    return {(k + ans.first).add(), ans.second};
  }
  return {algexpr("0"), e1};
}

algexpr algexpr::divide() {
  if (func != "/") {
    return *this;
  }
  algexpr _l = *l, _r = *r;
  auto ans = divide_polynomial(_l, _r);
  // l/r = ans.first + ans.second/r
  if (ans.second == algexpr("0")) {
    return ans.first;
  }
  return (ans.first + (ans.second * (_r ^ algexpr("-1"))).multiply()).add();
}
} // namespace arithmetica