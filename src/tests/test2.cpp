#include <arithmetica.hpp>

using namespace arithmetica;

int main() {
  while (true) {
    std::cout << "Enter an expression: ";
    std::string s;
    std::getline(std::cin, s);
    algexpr expr(s);
    expr = expr.simplify();
    auto d = diff(expr, algexpr("x"));
    std::cout << "==> diff(" << expr.to_string() << ") = " << d.to_string()
              << '\n';
  }
}