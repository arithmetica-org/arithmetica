#pragma once

#include <arithmetica.h>
#include <arithmetica.hpp>
#include <chrono>
#include <cstring>
#include <functional>
#include <geometry/point.h>
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "continued_fraction_to_fraction") {
    if (args.size() < 2)
      return "";

    char **cont_frac = (char **)calloc(args.size() - 1, sizeof(char *));
    for (size_t i = 1; i < args.size(); i++) {
      cont_frac[i - 1] = (char *)calloc(args[i].size() + 1, sizeof(char));
      strcpy(cont_frac[i - 1], args[i].c_str());
    }
    char *numerator;
    char *denominator;
    auto start = std::chrono::high_resolution_clock::now();
    continued_fraction_to_fraction(cont_frac, args.size() - 1, &numerator,
                                   &denominator);
    auto end = std::chrono::high_resolution_clock::now();

    // Free memory
    for (size_t i = 0; i < args.size() - 1; i++) {
      free(cont_frac[i]);
    }
    free(cont_frac);

    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
    std::string answer =
        std::string(numerator) + std::string("/") + std::string(denominator);

    free(numerator);
    free(denominator);

    return answer;
  }
  if (args[0] == "cosine") {
    if (args.size() < 3)
      return "";

    size_t accuracy = std::stoul(args[2]);
    auto start = std::chrono::high_resolution_clock::now();
    char *_answer = cosine(args[1].c_str(), accuracy);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "find_roots_of_polynomial") {
    if (args.size() < 2)
      return "Not enough arguments! Check your input!";

    std::string coefficients = args[1];
    // remove '[' and ']' front and back
    coefficients.erase(0, 1);
    coefficients.erase(coefficients.size() - 1, 1);
    // tokenize on ',' making a char **
    const char **coeffs =
        (const char **)calloc(coefficients.size(), sizeof(char *));
    unsigned long long i = 0;
    char *token = strtok((char *)coefficients.c_str(), ",");
    while (token != NULL) {
      coeffs[i] = (char *)calloc(strlen(token) + 1, sizeof(char));
      strcpy(const_cast<char *>(coeffs[i]), token);
      token = strtok(NULL, ",");
      i++;
    }

    size_t exact_roots_found;

    auto start = std::chrono::high_resolution_clock::now();
    struct fraction **_answer =
        find_roots_of_polynomial(coeffs, i, &exact_roots_found);
    auto end = std::chrono::high_resolution_clock::now();

    // Free memory
    for (size_t i = 0; i < coefficients.size(); i++) {
      free(const_cast<char *>(coeffs[i]));
    }
    free(coeffs);

    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;

    std::string answer; // [a],[b],[c], ...
    for (size_t i = 0; i < exact_roots_found; i++) {
      answer += std::string(_answer[i]->numerator);
      if (std::string(_answer[i]->denominator) != "1") {
        answer += "/" + std::string(_answer[i]->denominator);
      }
      if (i != exact_roots_found - 1)
        answer += ",";
    }

    // Free memory
    for (size_t i = 0; i < exact_roots_found; i++) {
      delete_fraction(*_answer[i]);
      free(_answer[i]);
    }
    free(_answer);

    return answer;
  }
  if (args[0] == "fraction_to_continued_fraction") {
    if (args.size() < 3)
      return "";

    auto start = std::chrono::high_resolution_clock::now();
    unsigned long long cont_frac_len;
    char **_answer = fraction_to_continued_fraction(
        args[1].c_str(), args[2].c_str(), &cont_frac_len);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
    std::string answer;
    if (cont_frac_len > 1) {
      answer = "[";
      for (size_t i = 0; i < cont_frac_len; i++) {
        answer += _answer[i];
        if (i == 0)
          answer += "; ";
        else if (i != cont_frac_len - 1)
          answer += ", ";
        free(_answer[i]);
      }
      answer += "]";
    } else {
      answer = _answer[0];
      free(_answer[0]);
    }
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
    std::string answer = _answer;
    free(_answer);
    return answer;
  }
  if (args[0] == "ilcm") {
    if (args.size() < 3)
      return "";

    char *_answer = (char *)calloc(args[1].length() + args[2].length() + 3, 1);
    auto start = std::chrono::high_resolution_clock::now();
    ilcm(args[1].c_str(), args[2].c_str(), _answer);
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
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
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
    std::string answer =
        std::string(numerator) + "/" + std::string(denominator);
    free(numerator);
    free(denominator);
    return answer;
  }
  if (args[0] == "construct_regular_polygon") {
    if (args.size() < 4)
      return "";

    auto start = std::chrono::high_resolution_clock::now();
    point *polygon = construct_regular_polygon(
        std::stoi(args[1]), args[2].c_str(), std::stoull(args[3]));
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;

    std::string answer;
    for (auto i = 0; i < std::stoi(args[1]); i++) {
      answer += std::string(polygon[i].x) + " " + std::string(polygon[i].y);
      if (i < std::stoi(args[1]) - 1)
        answer += " ";

      free(polygon[i].x);
      free(polygon[i].y);
    }

    free(polygon);

    return answer;
  }
  if (args[0] == "invert_matrix") {
    if (args.size() < 2) {
      return "";
    }
    auto replace_all = [](std::string &str, const std::string &from,
                          const std::string &to) {
      if (from.empty())
        return;
      size_t start_pos = 0;
      while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
      }
    };
    auto tokenize = [&](std::string s, char ch) {
      replace_all(s, "[", "(");
      replace_all(s, "]", ")");
      replace_all(s, "{", "(");
      replace_all(s, "}", ")");

      int bracket_count = 0;

      std::vector<std::string> tokens;
      std::string token;
      for (size_t i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
          bracket_count++;
        } else if (s[i] == ')') {
          bracket_count--;
        }

        if (bracket_count != 0) {
          token += s[i];
          continue;
        }

        if (s[i] == ch) {
          tokens.push_back(token);
          token.clear();
          continue;
        }
        token += s[i];
      }
      tokens.push_back(token);
      return tokens;
    };
    auto parse_matrix = [tokenize](std::string str) {
      std::vector<std::vector<arithmetica::Fraction>> a;
      str = str.substr(1, str.length() - 2);
      std::string cur;
      for (int i = 0, bal = 0; i < str.length(); ++i) {
        bal += str[i] == '(';
        bal -= str[i] == ')';
        if (bal == 1 and str[i] == '(') {
          cur.clear();
          continue;
        }
        if (bal == 0 and str[i] == ')') {
          auto t = tokenize(cur, ',');
          std::vector<arithmetica::Fraction> v;
          for (auto &i : t) {
            v.emplace_back(i);
          }
          a.push_back(v);
          continue;
        }
        cur.push_back(str[i]);
      }
      return a;
    };
    arithmetica::Matrix m = parse_matrix(args[1]);
    std::string answer;
    auto start = std::chrono::high_resolution_clock::now();
    m.invert();
    if (!m.invertible()) {
      return "N/A";
    }
    answer = m.inverse().to_string();
    auto end = std::chrono::high_resolution_clock::now();
    timeMS = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                 .count() *
             1e-6;
    return answer;
  }

  return "function does not exist";
}