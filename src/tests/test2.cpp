#include "../../deps/basic_math_operations/src/library/basic_math_operations.hpp"
#include <arithmetica.hpp>

using namespace arithmetica;

int main() {
  // while (true) {
  //   std::cout << "Enter an expression: ";
  //   std::string s;
  //   std::getline(std::cin, s);
  //   algexpr expr(s);
  //   expr = expr.simplify();
  //   std::cout << "expr: " << expr.prettify().to_string() << '\n';
  //   expr = diff(expr, algexpr("x"));
  //   expr = expr.prettify();
  //   std::cout << "derivative: " << expr.to_string() << '\n';
  // }

  algexpr f("x^2 - 2");
  algexpr f_prime = diff(f, algexpr("x"));
  basic_math_operations::BMONum g("1.414");
  basic_math_operations::DIVISION_ACCURACY = 3;
  for (int i = 0; i < 10; ++i) {
    algexpr g_new = algexpr(g.number) -
                    f.substitute(algexpr("x"), algexpr(g.number)) /
                        f_prime.substitute(algexpr("x"), algexpr(g.number));
    g_new = g_new.simplify();
    g = basic_math_operations::BMONum(g_new.coeff.numerator) /
        basic_math_operations::BMONum(g_new.coeff.denominator);
    basic_math_operations::DIVISION_ACCURACY *= 2;
    std::cout << "g_" << i + 1 << ": " << g << '\n';
  }
}