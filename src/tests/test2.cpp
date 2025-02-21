#include <arithmetica.hpp>

using namespace arithmetica;

int main() {
  // bug: --1 ==> -1
  while (true) {
    std::cout << "Enter an expression: ";
    std::string s;
    std::getline(std::cin, s);
    // std::cout << algexpr(s).debug_string() << '\n';
    std::cout << "==> " << algexpr(s).simplify().to_string() << '\n';
  }

  // algexpr e("(a^b)^c");
  // std::cout << e.simplify().to_string() << '\n';
}