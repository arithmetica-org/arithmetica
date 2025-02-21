#include <arithmetica.hpp>

using namespace arithmetica;

int main() {
  // bug: --1 ==> -1
  // 3*x^3*(3*x^2)^(-1) doesnt simplify fully

  // (3*x^3+8*x^2*y+14*x^2*z+8*x*y^2+22*x*y*z+16*x*z^2+8*y^3+24*y^2*z+20*y*z^2+3*z^3)/(3*x^2+2*x*y+5*x*z+4*y^2+6*y*z+z^2)
  while (true) {
    std::cout << "Enter an expression: ";
    std::string s;
    std::getline(std::cin, s);
    // std::cout << algexpr(s).debug_string() << '\n';
    std::cout << "==> " << algexpr(s).simplify().to_string() << '\n';
  }
}