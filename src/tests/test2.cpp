#include <arithmetica.hpp>

using namespace arithmetica;

int main() {
  algexpr x("x*x");
  x.simplify_term();
}