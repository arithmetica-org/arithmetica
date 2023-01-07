#pragma once

#include <arithmetica.h>
#include <chrono>
#include <string>
#include <truncate.h>
#include <vector>

std::string call_arithmetica(std::vector<std::string> args, double &timeMS) {
  if (args.empty())
    return "";

  if (args[0] == "add_fraction") {
    if (args.size() < 3)
      return "";

    struct fraction fraction1 = parse_fraction(args[1].c_str());
    struct fraction fraction2 = parse_fraction(args[2].c_str());

    auto start = std::chrono::high_resolution_clock::now();
    struct fraction _answer = add_fraction(fraction1, fraction2);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = std::string(_answer.denominator) == "1"
                             ? _answer.numerator
                             : std::string(_answer.numerator) +
                                   std::string("/") +
                                   std::string(_answer.denominator);
    delete_fraction(fraction1);
    delete_fraction(fraction2);
    delete_fraction(_answer);
    return answer;
  }
  if (args[0] == "arccos") {
    if (args.size() < 3)
      return "";

    size_t accuracy = std::stoul(args[2]);
    auto start = std::chrono::high_resolution_clock::now();
    char *_answer = arccos(args[1].c_str(), accuracy);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "arcsin") {
    if (args.size() < 3)
      return "";

    size_t accuracy = std::stoul(args[2]);
    auto start = std::chrono::high_resolution_clock::now();
    char *_answer = arcsin(args[1].c_str(), accuracy);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "arctan") {
    if (args.size() < 3)
      return "";

    size_t accuracy = std::stoul(args[2]);
    auto start = std::chrono::high_resolution_clock::now();
    char *_answer = arctan(args[1].c_str(), accuracy);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "cosine") {
    if (args.size() < 3)
      return "";

    size_t accuracy = std::stoul(args[2]);
    auto start = std::chrono::high_resolution_clock::now();
    char *_answer = cosine(args[1].c_str(), accuracy);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "exponential") {
    if (args.size() < 3)
      return "";

    size_t accuracy = std::stoul(args[2]);
    auto start = std::chrono::high_resolution_clock::now();
    char *_answer = exponential(args[1].c_str(), accuracy);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "factorial") {
    if (args.size() < 2)
      return "";

    size_t n = std::stoul(args[1]);
    char *_answer = (char *)calloc(n * n + 5, 1);
    auto start = std::chrono::high_resolution_clock::now();
    factorial(n, _answer);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "fraction_to_continued_fraction") {
    if (args.size() < 3)
      return "";

    auto start = std::chrono::high_resolution_clock::now();
    char *_answer =
        fraction_to_continued_fraction(args[1].c_str(), args[2].c_str());
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "igcd") {
    if (args.size() < 3)
      return "";

    char *_answer = (char *)calloc(args[1].length() + args[2].length() + 1, 1);
    auto start = std::chrono::high_resolution_clock::now();
    igcd(args[1].c_str(), args[2].c_str(), _answer);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "ilcm") {
    if (args.size() < 3)
      return "";

    char *_answer = (char *)calloc(args[1].length() + args[2].length() + 1, 1);
    auto start = std::chrono::high_resolution_clock::now();
    ilcm(args[1].c_str(), args[2].c_str(), _answer);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "multiply_fraction") {
    if (args.size() < 3)
      return "";

    struct fraction fraction1 = parse_fraction(args[1].c_str());
    struct fraction fraction2 = parse_fraction(args[2].c_str());

    auto start = std::chrono::high_resolution_clock::now();
    struct fraction _answer = multiply_fraction(fraction1, fraction2);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = std::string(_answer.denominator) == "1"
                             ? _answer.numerator
                             : std::string(_answer.numerator) +
                                   std::string("/") +
                                   std::string(_answer.denominator);
    delete_fraction(fraction1);
    delete_fraction(fraction2);
    delete_fraction(_answer);
    return answer;
  }
  if (args[0] == "natural_logarithm") {
    if (args.size() < 3)
      return "";

    size_t accuracy = std::stoul(args[2]);
    auto start = std::chrono::high_resolution_clock::now();
    char *_answer = natural_logarithm(args[1].c_str(), accuracy);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "power") {
    if (args.size() < 4)
      return "";

    size_t accuracy = std::stoul(args[3]);
    auto start = std::chrono::high_resolution_clock::now();
    char *_answer = power(args[1].c_str(), args[2].c_str(), accuracy);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "power_fraction") {
    if (args.size() < 4)
      return "";

    struct fraction base = parse_fraction(args[1].c_str());
    struct fraction exponent = parse_fraction(args[2].c_str());
    size_t accuracy = std::stoul(args[3]);

    auto start = std::chrono::high_resolution_clock::now();
    struct fraction _answer = power_fraction(base, exponent, accuracy);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = std::string(_answer.denominator) == "1"
                             ? _answer.numerator
                             : std::string(_answer.numerator) +
                                   std::string("/") +
                                   std::string(_answer.denominator);
    delete_fraction(base);
    delete_fraction(exponent);
    delete_fraction(_answer);
    return answer;
  }
  if (args[0] == "repeating_decimal_to_fraction") {
    if (args.size() < 3)
      return "";

    char *numerator =
        (char *)calloc(args[1].length() + args[2].length() + 10, 1);
    char *denominator =
        (char *)calloc(args[1].length() + args[2].length() + 10, 1);
    auto start = std::chrono::high_resolution_clock::now();
    repeating_decimal_to_fraction(args[1].c_str(), args[2].c_str(), numerator,
                                  denominator);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer =
        std::string(numerator) + "/" + std::string(denominator);
    free(numerator);
    free(denominator);
    return answer;
  }
  if (args[0] == "simplify_arithmetic_expression") {
    if (args.size() < 4)
      return "";

    size_t accuracy = std::stoul(args[3]);
    int outputType = std::stoi(args[2]);
    auto start = std::chrono::high_resolution_clock::now();
    char *_answer =
        simplify_arithmetic_expression(args[1].c_str(), outputType, accuracy);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "sine") {
    if (args.size() < 3)
      return "";

    size_t accuracy = std::stoul(args[2]);
    auto start = std::chrono::high_resolution_clock::now();
    char *_answer = sine(args[1].c_str(), accuracy);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "square_root") {
    if (args.size() < 3)
      return "";

    size_t accuracy = std::stoul(args[2]);
    auto start = std::chrono::high_resolution_clock::now();
    char *_answer = square_root(args[1].c_str(), accuracy);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "tangent") {
    if (args.size() < 3)
      return "";

    size_t accuracy = std::stoul(args[2]);
    auto start = std::chrono::high_resolution_clock::now();
    char *_answer = tangent(args[1].c_str(), accuracy);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "terminating_decimal_to_fraction") {
    if (args.size() < 2)
      return "";

    char *numerator = (char *)calloc(args[1].length() + 1, 1);
    char *denominator = (char *)calloc(args[1].length() + 1, 1);

    auto start = std::chrono::high_resolution_clock::now();
    terminating_decimal_to_fraction(args[1].c_str(), numerator, denominator);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                 .count();
    std::string answer =
        std::string(numerator) + "/" + std::string(denominator);
    free(numerator);
    free(denominator);
    return answer;
  }

  return "function does not exist";
}