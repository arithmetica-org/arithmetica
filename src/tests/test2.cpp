#include <arithmetica.hpp>

using namespace arithmetica;

int main() {
  algexpr x("(x^2+2xy+y^2)/(x+y)");
  x = x.simplify();
  std::cout << x.to_string() << '\n';
}