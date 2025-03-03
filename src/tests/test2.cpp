#include <arithmetica.hpp>

using namespace arithmetica;

int main() {
  while (true) {
    std::cout << "Enter an expression: ";
    std::string s;
    std::getline(std::cin, s);
    algexpr expr(s);
    expr = expr.simplify();
    std::cout << "expr: " << expr.prettify().to_string() << '\n';
    expr = diff(expr, algexpr("x"));
    expr = expr.prettify();
    std::cout << "derivative: " << expr.to_string() << '\n';
  }
}