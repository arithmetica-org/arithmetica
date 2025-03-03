#pragma once

#include <FractionCPP.hpp>
#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace arithmetica {
typedef arithmetica::Fraction frac;
class algexpr {
private:
  std::vector<std::string> get_funcs() const;
  bool has_non_number(const std::string &s) const;
  std::string add_parentheses_if_needed(const std::string &s,
                                        const std::string &f, bool right) const;
  std::string stringify_function_call(const std::string &f,
                                      const std::string &l,
                                      const std::string &r) const;
  int find_sign(const std::string &s, const char &c, bool backward,
                bool exclude_first = true) const;
  int find_letter(const std::string &s);
  int opening_bracket(const std::string &s, int st);
  int closing_bracket(const std::string &s, int st);
  std::pair<int, int> get_first_bracket_pair(const std::string &s);
  int variable_end(const std::string &s, int st);
  std::string debug_string(int i) const;
  bool is_opening_bracket(const char &c) const;
  bool is_closing_bracket(const char &c) const;
  bool is_bracket(const char &c) const;
  bool is_function(const std::string &s);
  bool is_sign(const char &c) const;
  int bound(const std::string &s, long long i, int incr);
  algexpr prettify_term();

public:
  algexpr *l;
  algexpr *r;

  // funtion applied on children
  std::string func;

  // leaf (one variable active per leaf)
  frac coeff;
  std::string variable;

  ~algexpr();
  algexpr &operator=(const algexpr &other);

  algexpr();
  algexpr(const algexpr &other);
  algexpr(std::string s);

  std::string to_string() const;
  std::string debug_string() const;

  bool is_numeric();
  bool is_natural_number(); // [0,1,...,inf)
  bool is_negative_number();

  std::vector<algexpr> terms();
  std::vector<algexpr> products();

  algexpr add();
  algexpr multiply(); // you need func == "*"
  algexpr divide();   // func == "/"
  algexpr exponent_product();
  algexpr exponent_sum();                                  // expands (...)^n
  algexpr exponent_exponent();                             // (a^b)^c = a^(bc)
  algexpr simplify_term(bool bring_coeff_to_front = true); // single product

  void simplify_in_place(); // simplifies, using all the functions above
  algexpr simplify();
  algexpr prettify();
};

algexpr operator+(const algexpr &a, const algexpr &b);
algexpr operator-(const algexpr &a, const algexpr &b);
algexpr operator*(const algexpr &a, const algexpr &b);
algexpr operator/(const algexpr &a, const algexpr &b);
algexpr operator^(const algexpr &a, const algexpr &b);
bool operator==(const algexpr &a, const algexpr &b);
algexpr exp(const algexpr &a);
algexpr log(const algexpr &a);
algexpr sqrt(const algexpr &a);
algexpr cbrt(const algexpr &a);
algexpr sin(const algexpr &a);
algexpr cos(const algexpr &a);
algexpr tan(const algexpr &a);
algexpr csc(const algexpr &a);
algexpr sec(const algexpr &a);
algexpr cot(const algexpr &a);
algexpr asin(const algexpr &a);
algexpr acos(const algexpr &a);
algexpr atan(const algexpr &a);
algexpr acsc(const algexpr &a);
algexpr asec(const algexpr &a);
algexpr acot(const algexpr &a);
algexpr abs(const algexpr &a);

std::pair<algexpr, algexpr> divide_polynomial(algexpr &f, algexpr &g);
} // namespace arithmetica