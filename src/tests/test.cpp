#include "call_arithmetica.hpp"
#include "color.hpp"
#include "get_current_directory.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

static std::string get_input_filename(std::string function,
                                      std::string currentDir) {
  return currentDir + "src/tests/arithmetica_tests/" + function + "/input.txt";
}

static std::string get_expected_filename(std::string function,
                                         std::string currentDir) {
  return currentDir + "src/tests/arithmetica_tests/" + function +
         "/expected.txt";
}

static size_t write_callback(char *ptr, size_t size, size_t nmemb,
                             void *userdata) {
  // Do nothing with the received data
  return size * nmemb;
}

std::string get_cpu_name();

// Linux
#ifdef __linux__
#include <cpuid.h>
std::string get_cpu_name() {
  char CPUBrandString[0x40];
  unsigned int CPUInfo[4] = {0, 0, 0, 0};

  __cpuid(0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
  unsigned int nExIds = CPUInfo[0];

  memset(CPUBrandString, 0, sizeof(CPUBrandString));

  for (unsigned int i = 0x80000000; i <= nExIds; ++i) {
    __cpuid(i, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);

    if (i == 0x80000002)
      memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
    else if (i == 0x80000003)
      memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
    else if (i == 0x80000004)
      memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
  }

  return CPUBrandString;
}
// Windows
#elif _WIN32
std::string get_cpu_name() {
  return "some random windows cpu idk (probs intel) use linux";
}
#endif

static std::vector<std::string> split_string(std::string s, char ch) {
  std::vector<std::string> answer;
  std::string part;
  for (auto &i : s) {
    if (i != ch)
      part.push_back(i);
    else {
      answer.push_back(part);
      part.clear();
    }
  }
  if (!part.empty())
    answer.push_back(part);
  return answer;
}

static std::string color_digits(std::string s, std::string col) {
  std::string answer;
  for (auto &i : s) {
    if (isdigit(i))
      answer += color(std::string(1, i), col);
    else
      answer.push_back(i);
  }
  return answer;
}

int main(int argc, char **argv) {
  std::cout << "Testing arithmetica:\n\n";
  std::vector<std::string> functions = {"diff",
                                        "algexpr_simplify",
                                        "multiply_fraction",
                                        "invert_matrix",
                                        "arcsin",
                                        "arccos",
                                        "arctan",
                                        "cosine",
                                        "factorial",
                                        "exponential",
                                        "fraction_to_continued_fraction",
                                        "igcd",
                                        "ilcm",
                                        "natural_logarithm",
                                        "power",
                                        "repeating_decimal_to_fraction",
                                        "simplify_arithmetic_expression",
                                        "sine",
                                        "square_root",
                                        "tangent",
                                        "terminating_decimal_to_fraction",
                                        "add_fraction",
                                        "power_fraction",
                                        "construct_regular_polygon",
                                        "continued_fraction_to_fraction",
                                        "find_roots_of_polynomial"};

  if (argc > 1) {
    std::vector<std::string> newFunctions;
    for (auto i = 1; i < argc; i++)
      newFunctions.push_back(argv[i]);
    functions = newFunctions;
  }

  std::string currentDir = get_current_directory();
  std::replace(currentDir.begin(), currentDir.end(), '\\', '/');
  if (currentDir.find("build") != std::string::npos)
    currentDir = currentDir.substr(0, currentDir.find("build"));
  if (currentDir.back() != '/')
    currentDir.push_back('/');

  for (auto i = 0; i < functions.size(); i++) {
    std::cout << "<" << i + 1 << "> " << color(functions[i] + ":", "Magenta")
              << '\n';

    int currentTest = 0;
    std::ifstream expectedFile(get_expected_filename(functions[i], currentDir));
    std::ifstream inputFile(get_input_filename(functions[i], currentDir));

    if (!expectedFile || !inputFile) {
      std::cout << "Couldn't open test files!\n";
      std::cout << currentDir << "\n";
      continue;
    }

    std::string input;
    double totalTimeMS = 0;
    std::vector<std::vector<std::string>> arithmetica_inputs;
    while (std::getline(inputFile, input)) {
      std::string inputsStr;
      std::string spaces =
          "   " + std::string(std::to_string(i + 1).length(), ' ');
      currentTest++;
      auto _inputs = split_string(input, ' ');
      std::vector<std::string> inputs = {functions[i]};
      std::copy(_inputs.begin(), _inputs.end(), std::back_inserter(inputs));
      for (auto i = 0; i < _inputs.size(); i++) {
        inputsStr += _inputs[i];
        if (i != _inputs.size() - 1)
          inputsStr += ", ";
      }
      std::string Expected;
      std::getline(expectedFile, Expected);
      double timeMS;
      arithmetica_inputs.push_back(inputs);
      std::string res = call_arithmetica(inputs, timeMS);
      totalTimeMS += timeMS;
      if (std::string(res) != Expected) {
        std::cout << spaces << "<" << currentTest << "> "
                  << color("Error: " + functions[i] + "(", "Red") << inputsStr
                  << color(") failed.", "Red") << "\n"
                  << spaces;
        std::cout << color("Expected: ", "Red") << Expected << '\n' << spaces;
        std::cout << color("Actual  : ", "Red") << res << '\n';
        inputFile.close();
        expectedFile.close();
        throw std::runtime_error(functions[i] + " failed a test.");
      } else {
        auto cPrint =
            1 + spaces.length() + std::to_string(currentTest).length() + 3 +
            std::to_string((int)timeMS).length() + 5 + functions[i].length() +
            1 + inputsStr.length() + 4 + res.length();
        std::cout << spaces << "<" << currentTest << "> (" << timeMS << " ms) "
                  << color(functions[i], "Yellow") << "("
                  << color_digits(inputsStr, "Green")
                  << ") = " << color_digits(res, "Green") << '\n';
      }
    }

    std::cout << "<" << i + 1 << "> "
              << "(" << totalTimeMS << " ms) "
              << color(functions[i] + ":", "Green") << " (" << currentTest
              << "/" << currentTest << ")" << '\n';

    inputFile.close();
    expectedFile.close();
  }

  std::cout << color("All tests passed successfully!\n", "Green");

  return 0;
}