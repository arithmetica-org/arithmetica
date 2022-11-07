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

  std::vector<std::pair<std::string, std::string>> input_r = {
      {"0.", "3"},
      {"0.0",
       "008103727714748784440842787682333873581847649918962722852512155591"
       "5721231766612641815235"}};

  std::vector<std::pair<std::string, std::string>> expected_r = {{"1", "3"},
                                                                 {"1", "1234"}};

  print_test(testName, input_r.size());

  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < input_r.size(); i++) {
    char *numerator = (char *)calloc(
        input_r[i].first.length() + input_r[i].second.length() + 1, 1);
    char *denominator = (char *)calloc(
        input_r[i].first.length() + input_r[i].second.length() + 1, 1);

    repeating_decimal_to_fraction(input_r[i].first.c_str(),
                                  input_r[i].second.c_str(), numerator,
                                  denominator);

    if (std::string(numerator) != expected_r[i].first ||
        std::string(denominator) != expected_r[i].second) {
      std::cout << "error in \"" << testName << "\": check " << functionName
                << "(\"" << input_r[i].first << "\", \"" << input_r[i].second
                << "\") == \"(" << expected_r[i].first << "\", \""
                << expected_r[i].second << "\") failed\n";
      std::cout << "actual: \"(" << numerator << "\", \"" << denominator
                << "\")\n";
      number_of_failed_cases++;
    }

    free(numerator);
    free(denominator);
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

  testName = "exp_unit_tests";
  functionName = "exponential";

  std::vector<std::pair<std::string, unsigned long>> input_e = {
      {"1", 10}, {"1.69", 20}, {"2.7182818284", 10}};
  std::vector<std::string> expected_e = {
      "2.7182818284", "5.41948070513120621755", "15.1542622405"};

  print_test(testName, input_e.size());

  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < input_e.size(); i++) {
    char *answer =
        (char *)exponential(input_e[i].first.c_str(), input_e[i].second);

    if (std::string(answer) != expected_e[i]) {
      std::cout << "error in \"" << testName << "\": check " << functionName
                << "(\"" << input_e[i].first << "\", " << input_e[i].second
                << ") == \"" << expected_e[i] << "\" failed\n";
      std::cout << "actual: \"" << answer << "\"\n";
      number_of_failed_cases++;
    }

    free(answer);
  }
  end = std::chrono::high_resolution_clock::now();

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

  testName = "sin_unit_tests";
  functionName = "sine";

  std::vector<std::pair<std::string, unsigned long>> input_sin = {
      {"0.523599", 10}, {"0.69", 69}, {"1", 1}};
  std::vector<std::string> expected_sin = {
      "0.5000001943",
      "0."
      "636537182221967940237429207008720931849252173827564301711170385158449",
      "0.8"};

  print_test(testName, input_sin.size());

  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < input_sin.size(); i++) {
    char *answer =
        (char *)sine(input_sin[i].first.c_str(), input_sin[i].second);

    if (std::string(answer) != expected_sin[i]) {
      std::cout << "error in \"" << testName << "\": check " << functionName
                << "(\"" << input_sin[i].first << "\", " << input_sin[i].second
                << ") == \"" << expected_sin[i] << "\" failed\n";
      std::cout << "actual: \"" << answer << "\"\n";
      number_of_failed_cases++;
    }

    free(answer);
  }
  end = std::chrono::high_resolution_clock::now();

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