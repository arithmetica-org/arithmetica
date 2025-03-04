#include <arithmetica.hpp>

using namespace arithmetica;

int main() {
  arithmetica::Matrix mat({{"1", "2"}, {"2", "1"}});
  std::cout << mat.to_pretty_string() << '\n';
}