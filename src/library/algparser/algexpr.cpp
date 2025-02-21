#include "algexpr.hpp"
#include <algorithm>
#include <array>

namespace arithmetica {
std::vector<std::string> algexpr::get_funcs() const {
  std::vector<std::string> funcs = {
      "sin",   "cos",  "tan",   "log",  "abs",   "sgn",   "exp",   "asin",
      "atan",  "acos", "sec",   "csc",  "cot",   "acsc",  "asec",  "acot",
      "fact",  "ceil", "floor", "sinh", "cosh",  "tanh",  "asinh", "acosh",
      "atanh", "csch", "sech",  "coth", "acsch", "asech", "acoth"};
  std::sort(funcs.begin(), funcs.end(),
            [](const std::string &a, const std::string &b) {
              return a.length() > b.length();
            });
  return funcs;
}

bool algexpr::is_opening_bracket(const char &c) const {
  return c == '(' or c == '[' or c == '{';
}

bool algexpr::is_closing_bracket(const char &c) const {
  return c == ')' or c == ']' or c == '}';
}

bool algexpr::is_bracket(const char &c) const {
  return is_opening_bracket(c) or is_closing_bracket(c);
}

int algexpr::find_sign(const std::string &s, const char &c, bool backward,
                       bool exclude_first) const {
  int i = backward * (s.length() - 1);
  int bal = 0;
  while ((backward and i >= 0) or (!backward and i < int(s.length()))) {
    bal += is_opening_bracket(s[i]);
    bal -= is_closing_bracket(s[i]);
    // i == 0 implies something like "-1" or "+1"
    if (bal == 0 and s[i] == c and (!exclude_first or i != 0)) {
      return i;
    }
    i -= 2 * backward - 1;
  }
  return -1;
}

int algexpr::opening_bracket(const std::string &s, int st) {
  for (long long i = st, bal = 0; i >= 0; --i) {
    bal += is_opening_bracket(s[i]);
    bal -= is_closing_bracket(s[i]);
    if (bal == 0) {
      return i;
    }
  }
  return -1;
}

int algexpr::closing_bracket(const std::string &s, int st) {
  for (std::size_t i = st, bal = 0; i < s.length(); ++i) {
    bal += is_opening_bracket(s[i]);
    bal -= is_closing_bracket(s[i]);
    if (bal == 0) {
      return i;
    }
  }
  return -1;
}

std::pair<int, int> algexpr::get_first_bracket_pair(const std::string &s) {
  std::pair<int, int> ans = {-1, -1};
  for (std::size_t i = 0, bal = 0; i < s.length(); ++i) {
    bal += is_opening_bracket(s[i]);
    if (i >= 1 and s[i - 1] == '_') {
      i = closing_bracket(s, i);
      bal--;
      continue;
    }
    if (bal == 1) {
      if (ans.first == -1) {
        ans.first = i;
      }
      ans.second = i;
    }
    bal -= is_closing_bracket(s[i]);
    if (bal == 0 and ans.first != -1 and ans.second != -1) {
      break;
    }
  }
  return ans;
}

bool algexpr::is_function(const std::string &s) {
  if (s.empty()) {
    return false;
  }
  auto funcs = get_funcs();
  if (std::find(funcs.begin(), funcs.end(), s) != funcs.end()) {
    return true;
  }
  return false;
}

int algexpr::find_letter(const std::string &s) {
  for (std::size_t i = 0; i < s.length(); ++i) {
    if (std::isalpha(s[i])) {
      return i;
    }
  }
  return -1;
}

int algexpr::variable_end(const std::string &s, int st) {
  if (st == int(s.length()) - 1) {
    return st;
  }
  if (s[st + 1] != '_') {
    return st;
  }
  if (is_opening_bracket(s[st + 2])) {
    return closing_bracket(s, st + 2);
  }
  if (std::isalpha(s[st + 2])) {
    return st + 2;
  }
  for (std::size_t i = st + 2; i < s.length(); ++i) {
    if (std::isalpha(s[i])) {
      return i - 1;
    }
  }
  return s.length() - 1;
}

bool algexpr::is_sign(const char &c) const {
  return std::string("+-*/^").find(c) != std::string::npos;
}

int algexpr::bound(const std::string &s, long long i, int incr) {
  if (i == 0 or i == (long long)s.length() - 1) {
    return i;
  }
  if (incr == 1) {
    if (is_opening_bracket(s[i + 1])) {
      return closing_bracket(s, i + 1);
    }
    for (auto &func : get_funcs()) {
      if (s.find(func, i + 1) != std::string::npos) {
        return closing_bracket(s, i + func.length() + 1);
      }
    }
  }
  if (incr == -1 and is_closing_bracket(s[i - 1])) {
    std::size_t open = opening_bracket(s, i - 1);
    for (auto &func : get_funcs()) {
      auto pos = s.rfind(func, open - 1);
      if (pos != std::string::npos and pos + func.length() == open) {
        return open - func.length();
      }
    }
    return open;
  }
  if (std::isalpha(s[i + incr])) {
    return i + incr;
  }
  i += incr;
  for (; 0 <= i and i < (long long)s.length(); i += incr) {
    if (std::isalpha(s[i]) or is_sign(s[i]) or is_bracket(s[i])) {
      return i - incr;
    }
  }
  return (incr == 1) * (s.length() - 1);
}

algexpr::~algexpr() {
  delete l;
  delete r;
}

algexpr &algexpr::operator=(const algexpr &other) {
  if (this == &other) {
    return *this;
  }
  algexpr t(other);
  std::swap(func, t.func);
  std::swap(coeff, t.coeff);
  std::swap(variable, t.variable);
  std::swap(l, t.l);
  std::swap(r, t.r);
  return *this;
}

algexpr::algexpr() : l(nullptr), r(nullptr) {}

algexpr::algexpr(const algexpr &other) {
  func = other.func;
  coeff = other.coeff;
  variable = other.variable;
  l = other.l ? new algexpr(*other.l) : nullptr;
  r = other.r ? new algexpr(*other.r) : nullptr;
}

algexpr::algexpr(std::string s) : l(nullptr), r(nullptr) {
  // Some preprocessing
  // remove spaces
  s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
  {
    // remove consecutive +'s and -'s
    std::string _s;
    for (std::size_t i = 0, len = 0; i < s.length(); ++i) {
      if (i != 0 and (s[i] == '+' or s[i] == '-') and s[i] == s[i - 1]) {
        len++;
        continue;
      } else {
        if (len % 2 == 1 and len != 1) {
          _s.pop_back();
        }
        _s.push_back(s[i]);
        len = 0;
      }
    }
    s = _s;
  }
  {
    // ((1)) ==> 1
    int l = 0, r = s.length() - 1;
    while (l < r and is_opening_bracket(s[l]) and closing_bracket(s, l) == r) {
      l++, r--;
    }
    if (r - l + 1 == 0) {
      s = "";
    } else {
      s = s.substr(l, r - l + 1);
    }
  }
  // add multiplication signs before and after ^ and /
  for (auto &c : std::string("^/")) {
    std::size_t i = -1;
    while ((i = s.find(c, i + 1)) != std::string::npos) {
      auto br = bound(s, i, 1), bl = bound(s, i, -1);
      if (br != (long long)s.length() - 1 and !is_sign(s[br + 1]) and
          !is_bracket(s[br + 1])) {
        s.insert(br + 1, "*"); // add ahead
      }
      if (bl != 0 and !is_sign(s[bl - 1]) and !is_bracket(s[bl - 1])) {
        s.insert(bl, "*"); // add behind}
      }
    }
  }

  // -1 in particular
  if (s == "-1") {
    coeff = s;
    return;
  }
  // +x and -x
  while (s[0] == '+') {
    s = s.substr(1, s.length() - 1);
  }
  if (s[0] == '-') {
    s = "(-1)*" + s.substr(1, s.length() - 1);
  }

  std::array<char, 5> signs = {'+', '-', '*', '/', '^'};
  std::array<bool, 5> back = {true, true, true, true, false};
  for (int _i = 0; _i < 5; ++_i) {
    auto &c = signs[_i];
    int i;
    if (((i = find_sign(s, c, back[_i])) != -1)) {
      func = c;
      l = new algexpr(s.substr(0, i));
      r = new algexpr(s.substr(i + 1, s.length() - i - 1));
      return;
    }
  }

  // [] (...) []
  // take cases
  auto [idx_l, idx_r] = get_first_bracket_pair(s);
  // no brackets at all
  if (idx_l == -1 or idx_r == -1) {
    int a_idx = find_letter(s);
    if (a_idx == -1) {
      // just number
      coeff = s;
      return;
    }
    if (a_idx != 0) {
      func = '*';
      l = new algexpr(s.substr(0, a_idx));
      r = new algexpr(s.substr(a_idx, s.length() - a_idx));
      return;
    }
    a_idx = variable_end(s, a_idx);
    if (a_idx == int(s.length()) - 1) {
      // just variable
      variable = s;
    } else {
      func = '*';
      l = new algexpr(s.substr(0, a_idx + 1));
      r = new algexpr(s.substr(a_idx + 1, s.length() - a_idx - 1));
    }
    return;
  }

  if (idx_r == int(s.length()) - 1) {
    std::string part = s.substr(0, idx_l);
    if (is_function(part)) {
      func = part;
      l = new algexpr(s.substr(idx_l + 1, idx_r - idx_l - 1));
    } else {
      func = '*';
      l = new algexpr(part);
      r = new algexpr(s.substr(idx_l + 1, idx_r - idx_l - 1));
    }
    return;
  }

  func = '*';
  l = new algexpr(s.substr(0, idx_r + 1));
  r = new algexpr(s.substr(idx_r + 1, s.length() - idx_r - 1));
}
} // namespace arithmetica