#include "algexpr.hpp"
#include <FractionCPP.hpp>

namespace arithmetica {
bool algexpr::has_non_number(const std::string &s) const {
  bool has_non_number = false;
  for (auto &i : s) {
    has_non_number = has_non_number or i < '0' or i > '9';
  }
  return has_non_number;
}

std::string algexpr::add_parentheses_if_needed(const std::string &s,
                                               const std::string &f) const {
  if (s.length() == 1) {
    return s;
  }
  if (f == "+") {
    return s;
  }
  if (f == "*") {
    if (find_sign(s, '+', false, false) == -1 and
        find_sign(s, '-', false, false) == -1) {
      return s;
    }
    return "(" + s + ")";
  }
  if (!has_non_number(s)) {
    return s;
  }
  return "(" + s + ")";
}

std::string algexpr::stringify_function_call(const std::string &f,
                                             const std::string &l,
                                             const std::string &r) const {
  if (f == "+" or f == "-" or f == "*" or f == "/" or f == "^") {
    std::string ans = add_parentheses_if_needed(l, f);
    bool include_f = f == "+" or f == "-" or f == "*" or f == "/" or f == "^";
    bool include_space = f == "+" or f == "-" or f == "*";
    if (f == "*" and has_non_number(r)) {
      include_f = include_space = false;
    }
    if (include_space) {
      ans += " ";
    }
    if (include_f) {
      ans += f;
    }
    if (include_space) {
      ans += " ";
    }
    ans += add_parentheses_if_needed(r, f);
    return ans;
  }
  // unary functions
  if (l.empty()) {
    return f + "(" + r + ")";
  }
  if (r.empty()) {
    return f + "(" + l + ")";
  }

  return f + "(" + l + ", " + r + ")";
}

std::string algexpr::to_string() const {
  if (l == nullptr and r == nullptr) {
    std::string s = coeff.to_string();
    if (s == "1" and !variable.empty()) {
      s.clear();
    }
    return s + variable;
  }
  std::string left, right;
  if (l != nullptr) {
    left = l->to_string();
  }
  if (r != nullptr) {
    right = r->to_string();
  }
  return stringify_function_call(func, left, right);
}
} // namespace arithmetica