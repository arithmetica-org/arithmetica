#include <arithmetica.h>
#include <chrono>
#include <iostream>
#include <vector>

inline void print_test(std::string testName, size_t number_tests) {
  std::cout << "Running " << number_tests << " test cases for " << testName
            << ".\n";
}

class power_test {
public:
  std::string base, exponent;
  size_t accuracy;

  power_test() {}
  power_test(std::string b, std::string e, size_t a) {
    base = b;
    exponent = e;
    accuracy = a;
  }
};

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
              << " \u00b5s)" << '\n';
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
              << " \u00b5s)" << '\n';
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
              << " \u00b5s)" << '\n';
  } else {
    std::cout << number_of_failed_cases << " error/s detected in " << testName
              << ".\n";
  }

  testName = "arctan_unit_tests";
  functionName = "arctan";

  std::vector<std::pair<std::string, unsigned long>> input_atan = {{"1", 20}};
  std::vector<std::string> expected_atan = {"0.78539816339744830961"};

  print_test(testName, input_atan.size());

  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < input_atan.size(); i++) {
    char *answer =
        (char *)arctan(input_atan[i].first.c_str(), input_atan[i].second);

    if (std::string(answer) != expected_atan[i]) {
      std::cout << "error in \"" << testName << "\": check " << functionName
                << "(\"" << input_atan[i].first << "\", "
                << input_atan[i].second << ") == \"" << expected_atan[i]
                << "\" failed\n";
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
                         .count() *
                     1e-6
              << " s)" << '\n';
  } else {
    std::cout << number_of_failed_cases << " error/s detected in " << testName
              << ".\n";
  }

  testName = "arcsin_unit_tests";
  functionName = "arcsin";

  std::vector<std::pair<std::string, unsigned long>> input_asin = {
      {"0.5", 100}, {"0.866", 10}};
  std::vector<std::string> expected_asin = {
      "0."
      "523598775598298873077107230546583814032861566562517636829157432051302734"
      "3810348331046724708903528446",
      "1.0471467458"};

  print_test(testName, input_asin.size());

  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < input_asin.size(); i++) {
    char *answer =
        (char *)arcsin(input_asin[i].first.c_str(), input_asin[i].second);

    if (std::string(answer) != expected_asin[i]) {
      std::cout << "error in \"" << testName << "\": check " << functionName
                << "(\"" << input_asin[i].first << "\", "
                << input_asin[i].second << ") == \"" << expected_asin[i]
                << "\" failed\n";
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
                         .count() *
                     1e-6
              << " s)" << '\n';
  } else {
    std::cout << number_of_failed_cases << " error/s detected in " << testName
              << ".\n";
  }

  testName = "fraction_to_continued_fraction_unit_tests";
  functionName = "fraction_to_continued_fraction";

  std::vector<std::pair<std::string, std::string>> input_frtocofr = {
      {"123", "456"},
      {"532013", "376190"},
      {"1", "69"},
      {"1", "1"},
      {"3", "3"}};
  std::vector<std::string> expected_frtocofr = {
      "[0; 3, 1, 2, 2, 2, 2]", "[1; 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3]",
      "[0; 69]", "1", "1"};

  print_test(testName, input_frtocofr.size());

  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < input_frtocofr.size(); i++) {
    char *answer = (char *)fraction_to_continued_fraction(
        input_frtocofr[i].first.c_str(), input_frtocofr[i].second.c_str());

    if (std::string(answer) != expected_frtocofr[i]) {
      std::cout << "error in \"" << testName << "\": check " << functionName
                << "(\"" << input_frtocofr[i].first << "\", \""
                << input_frtocofr[i].second << "\") == \""
                << expected_frtocofr[i] << "\" failed\n";
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
              << "\u00b5s)" << '\n';
  } else {
    std::cout << number_of_failed_cases << " error/s detected in " << testName
              << ".\n";
  }

  testName = "sqrt_unit_tests";
  functionName = "square_root";

  std::vector<std::pair<std::string, unsigned long>> input_sqrt = {
      {"1004004", 5},
      {"69", 5},
      {"10", 100},
      {"0.04", 5},
      {"1.00135471989210820588", 10}};
  std::vector<std::string> expected_sqrt = {
      "1002.00000", "8.30662",
      "3."
      "162277660168379331998893544432718533719555139325216826857504852792594438"
      "6392382213442481083793002951",
      "0.20000", "1.0006771306"};

  print_test(testName, input_sqrt.size());

  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < input_sqrt.size(); i++) {
    char *answer =
        (char *)square_root(input_sqrt[i].first.c_str(), input_sqrt[i].second);

    if (std::string(answer) != expected_sqrt[i]) {
      std::cout << "error in \"" << testName << "\": check " << functionName
                << "(\"" << input_sqrt[i].first << "\", "
                << input_sqrt[i].second << ") == \"" << expected_sqrt[i]
                << "\" failed\n";
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
              << "\u00b5s)" << '\n';
  } else {
    std::cout << number_of_failed_cases << " error/s detected in " << testName
              << ".\n";
  }

  testName = "ln_unit_tests";
  functionName = "natural_logarithm";

  std::vector<std::pair<std::string, unsigned long>> input_ln = {
      {"2", 20}, {"69", 20}, {"0.1", 5}};
  std::vector<std::string> expected_ln = {"0.69314718055994530941",
                                          "4.23410650459725938220", "-2.30258"};

  print_test(testName, input_ln.size());

  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < input_ln.size(); i++) {
    char *answer = (char *)natural_logarithm(input_ln[i].first.c_str(),
                                             input_ln[i].second);

    if (std::string(answer) != expected_ln[i]) {
      std::cout << "error in \"" << testName << "\": check " << functionName
                << "(\"" << input_ln[i].first << "\", " << input_ln[i].second
                << ") == \"" << expected_ln[i] << "\" failed\n";
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
              << "\u00b5s)" << '\n';
  } else {
    std::cout << number_of_failed_cases << " error/s detected in " << testName
              << ".\n";
  }

  testName = "power_unit_tests";
  functionName = "power";

  std::vector<power_test> input_power = {
      power_test("2", "5", 0),
      power_test("2.717", "3.141", 10),
      power_test("1.414213562373095", "1.414213562373095", 15),
      power_test("3.141592653589793238462643", "3.141592653589793238462643",
                 25),
      power_test("69", "420", 0),
      power_test("10", "-3", 25)};
  std::vector<std::string> expected_power = {
      "32",
      "23.0927446996",
      "1.632526919438152",
      "36.4621596072079117709907960",
      "207308977526536747147207234274590008892499155296009815304333653351885892"
      "067755271392296019951158360435357866295807921447730784267768342682983321"
      "872368180423802268494438848603696884064066601180187510415545430958066707"
      "843240170676904087910781254639513780304991745122110217620538991463218117"
      "543266762008483176686157460327914778101893707657968720154542087265358910"
      "653923654977806809342947658906144624332304346420198502101945749418371499"
      "045066680926235315667314639769578557380221485817710996842236642636373680"
      "048620596486279357053307251863142859610322835862779661459662809299188872"
      "669098908200243853754449231266527755891022635409781869010342123464944031"
      "408995518569965212572412851338778145229949673588222246859263776604678710"
      "22924275654082181950373765807211473562917453950351601",
      "0.001"};

  print_test(testName, input_power.size());

  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < input_power.size(); i++) {
    char *answer =
        (char *)power(input_power[i].base.c_str(),
                      input_power[i].exponent.c_str(), input_power[i].accuracy);

    if (std::string(answer) != expected_power[i]) {
      std::cout << "error in \"" << testName << "\": check " << functionName
                << "(\"" << input_power[i].base << "\", "
                << input_power[i].exponent << "\", " << input_power[i].accuracy
                << ") == \"" << expected_power[i] << "\" failed\n";
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
              << "\u00b5s)" << '\n';
  } else {
    std::cout << number_of_failed_cases << " error/s detected in " << testName
              << ".\n";
  }

  testName = "cos_unit_tests";
  functionName = "cosine";

  std::vector<std::pair<std::string, unsigned long>> input_cos = {{"0.523", 5}};
  std::vector<std::string> expected_cos = {"0.86632"};

  print_test(testName, input_cos.size());

  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < input_cos.size(); i++) {
    char *answer =
        (char *)cosine(input_cos[i].first.c_str(), input_cos[i].second);

    if (std::string(answer) != expected_cos[i]) {
      std::cout << "error in \"" << testName << "\": check " << functionName
                << "(\"" << input_cos[i].first << "\", " << input_cos[i].second
                << ") == \"" << expected_cos[i] << "\" failed\n";
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
              << "\u00b5s)" << '\n';
  } else {
    std::cout << number_of_failed_cases << " error/s detected in " << testName
              << ".\n";
  }

  if (number_of_failed_cases)
    throw std::runtime_error(std::to_string(number_of_failed_cases) +
                             " test/s failed.");
}
