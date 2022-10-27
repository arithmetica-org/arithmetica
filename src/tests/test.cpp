#include <arithmetica.h>
#include <chrono>
#include <iostream>
#include <vector>

inline void print_test(std::string testName, size_t number_tests) {
  std::cout << "Running " << number_tests << " test cases for " << testName
            << ".\n";
}

int main() {
  std::string testName = "repeating_decimal_to_fraction_unit_tests";
  std::string functionName = "repeating_decimal_to_fraction";

  int number_of_failed_cases = 0;

  std::vector<std::pair<std::string, std::string>> input = {
      {"0.", "3"},
      {"0.0",
       "008103727714748784440842787682333873581847649918962722852512155591"
       "5721231766612641815235"}};

  std::vector<std::pair<std::string, std::string>> expected = {{"1", "3"},
                                                               {"1", "1234"}};

  print_test(testName, input.size());

  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < input.size(); i++) {
    char *numerator = (char *)calloc(
        input[i].first.length() + input[i].second.length() + 1, 1);
    char *denominator = (char *)calloc(
        input[i].first.length() + input[i].second.length() + 1, 1);

    repeating_decimal_to_fraction(input[i].first.c_str(),
                                  input[i].second.c_str(), numerator,
                                  denominator);

    if (std::string(numerator) != expected[i].first ||
        std::string(denominator) != expected[i].second) {
      std::cout << "error in \"" << testName << "\": check " << functionName
                << "(\"" << input[i].first << "\", \"" << input[i].second
                << "\") == \"(" << expected[i].first << "\", \""
                << expected[i].second << "\") failed\n";
      std::cout << "actual: \"(" << numerator << "\", \"" << denominator
                << "\")\n";
      number_of_failed_cases++;
    }
  }
  auto end = std::chrono::high_resolution_clock::now();

  if (!number_of_failed_cases) {
    std::cout << "no errors detected in " << testName << ". (finished in "
              << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                       start)
                     .count()
              << " microseconds)" << '\n';
  } else {
    std::cout << number_of_failed_cases << " error/s detected in " << testName
              << ".\n";
  }

  if (number_of_failed_cases)
    throw std::runtime_error(std::to_string(number_of_failed_cases) +
                             " test/s failed.");
}