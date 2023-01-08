#ifndef _simplify_arithmetic_expression_h_
#define _simplify_arithmetic_expression_h_

#include "fraction/fraction_include.h"
#include "power.h"
#include <basic_math_operations.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static void str_replace_all(char **str_in, char *from, char *to) {
  char *str = *str_in;
  size_t from_len = strlen(from);
  if (from_len == 0)
    return;
  // algorithm here
  size_t len = strlen(str) + strlen(to) + 1;
  char *new_str = (char *)calloc(len, 1);
  size_t characters_added = 0;
  for (size_t i = 0; i < strlen(str); i++) {
    const char *loc = strstr(str + i, from);
    bool found = loc == str + i;
    size_t _characters_added = characters_added;
    if (!found) {
      characters_added++;
    } else {
      characters_added += strlen(to);
    }
    if (characters_added >= len) {
      size_t old_len = len;
      len *= 2;
      new_str = (char *)realloc(new_str, len);
      memset(new_str + _characters_added, 0, old_len);
    }
    if (found) {
      memcpy(new_str + _characters_added, to, strlen(to));
      i += strlen(from) - 1;
    } else {
      new_str[_characters_added++] = str[i];
    }
  }
  new_str = (char *)realloc(new_str, strlen(new_str) + 1);
  if (new_str[strlen(new_str)] != 0)
    new_str[strlen(new_str)] = 0;
  free(str);
  *str_in = new_str;
  return;
}

static void remove_misplaced_and_redundant_signs(char **expression_in) {
  char *expression = *expression_in;
  if (expression[0] == '+') {
    size_t n = strlen(expression);
    memmove(expression, expression + 1, strlen(expression) - 1);
    expression[n - 1] = 0;
  }
  while (strstr(expression, "--") != NULL)
    str_replace_all(&expression, "--", "+");
  while (strstr(expression, "++") != NULL)
    str_replace_all(&expression, "++", "+");
  while (strstr(expression, "-+") != NULL)
    str_replace_all(&expression, "-+", "-");
  while (strstr(expression, "+-") != NULL)
    str_replace_all(&expression, "+-", "-");
  str_replace_all(&expression, "*+", "*");
  str_replace_all(&expression, "/+", "/");
  str_replace_all(&expression, "^+", "^");
  *expression_in = expression;
  return;
}

static size_t get_corresponding_closing_bracket(const char *str, size_t index) {
  char openBracket = '(', closeBracket = ')';
  if (str[index] == '[') {
    openBracket = '[';
    closeBracket = ']';
  } else if (str[index] == '{') {
    openBracket = '{';
    closeBracket = '}';
  } else if (str[index] != '(')
    return -1;
  int count = 0;
  for (size_t i = index; i < strlen(str); i++) {
    if (str[i] == openBracket)
      count++;
    if (str[i] == closeBracket)
      count--;
    if (!count)
      return i;
  }
  return -1;
}

static void replace_substring_from_position(size_t startPosition,
                                            size_t endPosition,
                                            char **string_in,
                                            const char *replacement) {
  char *string = *string_in;

  size_t replacement_len = strlen(replacement);

  char *answer = (char *)calloc(
      strlen(string) - (endPosition - startPosition + 1) + replacement_len + 1,
      1);

  for (size_t i = 0; i < startPosition; i++)
    answer[i] = string[i];
  strcpy(answer + startPosition, replacement);
  for (size_t i = endPosition + 1; i < strlen(string); i++)
    answer[startPosition + replacement_len + i - endPosition - 1] = string[i];

  free(string);
  *string_in = answer;
  return;
}

static long find_operational_sign(const char *expression, char sign) {
  bool numberFound = false;
  bool noExponent = sign != '^';
  size_t find = noExponent ? 0 : strlen(expression) - 1;
  while (noExponent ? find < strlen(expression) : find + 1 > 0) {
    if (isdigit(expression[find]))
      numberFound = true;
    if (expression[find] == sign && numberFound)
      return (long)find;
    noExponent ? find++ : find--;
  }
  // Not found
  return -1;
}

static size_t get_back_corresponding_square_bracket(const char *str,
                                                    size_t index) {
  if (str[index] != ']')
    return -1;
  int count = 0;
  for (size_t i = index; i + 1 > 0; i--) {
    if (str[i] == '[')
      count--;
    if (str[i] == ']')
      count++;
    if (!count)
      return i;
  }
  return -1;
}

static bool equal_to_any_from(const char *options, char n, size_t size) {
  for (size_t i = 0; i < size; i++)
    if (options[i] == n)
      return true;
  return false;
}

static char *get_numerical_arguments(const char *expression, bool fromLeft,
                                     long *signIndexIn, int outputType) {
  long signIndex = *signIndexIn;
  char *operators = (char *)calloc(10, 1);
  size_t numberOfOperators = 3;
  strcpy(operators, "^*+");
  if (outputType == 0) {
    strcpy(operators + 3, "/");
    numberOfOperators++;
  }

  bool encounteredNumber = false;
  size_t start = 0, length = 0; // for the final answer
  if (fromLeft) {
    if (expression[signIndex] == '^') {
      strcpy(operators + numberOfOperators, "-");
      numberOfOperators++;
    }
    bool encounteredMinusSign = false;
    signIndex--;

    // Check for brackets
    if (signIndex >= 0 && expression[signIndex] == ']') {
      size_t back_corresponding_square_bracket =
          get_back_corresponding_square_bracket(expression, signIndex);
      start = back_corresponding_square_bracket + 1;
      length = signIndex - back_corresponding_square_bracket - 1;
      signIndex = back_corresponding_square_bracket;
    } else {
      // No brackets
      while (signIndex >= 0 &&
             !equal_to_any_from(operators, expression[signIndex],
                                numberOfOperators) &&
             !encounteredMinusSign) {
        if (expression[signIndex] == '-')
          encounteredMinusSign = true;
        length++;
        signIndex--;
      }
      signIndex++;
      start = signIndex;
    }
  } else {
    if (expression[signIndex] == '^') {
      strcpy(operators + numberOfOperators, "/");
      numberOfOperators++;
    }
    signIndex++;
    if (signIndex < strlen(expression) && expression[signIndex] == '[') {
      size_t corresponding_closing_bracket =
          get_corresponding_closing_bracket(expression, signIndex);
      start = signIndex + 1;
      length = corresponding_closing_bracket - signIndex - 1;
      signIndex = corresponding_closing_bracket;
    } else {
      start = signIndex;
      while (signIndex < strlen(expression) &&
             !equal_to_any_from(operators, expression[signIndex],
                                numberOfOperators) &&
             !(expression[signIndex] == '-' && encounteredNumber)) {
        if (!encounteredNumber)
          encounteredNumber = isdigit(expression[signIndex]);
        length++;
        signIndex++;
      }
      signIndex--;
    }
  }

  char *answer = (char *)calloc(length + 1, 1);
  strncpy(answer, expression + start, length);
  free(operators);
  *signIndexIn = signIndex;
  return answer;
}

static void get_chain_division_location(char *expression, long *sign1In,
                                        long *sign2In) {
  long sign1 = *sign1In;
  long sign2 = *sign2In;

  long divisionSignLocation = find_operational_sign(expression, '/');
  while (divisionSignLocation >= 0) {
    long rightArgumentEnd = divisionSignLocation;
    expression[divisionSignLocation] =
        '^'; // This is just temporary, it's so we don't pull division signs in
             // the right argument.
    char *rightArgument =
        get_numerical_arguments(expression, false, &rightArgumentEnd, 1);
    expression[divisionSignLocation] = '/';
    if (rightArgumentEnd + 1 < strlen(expression) &&
        expression[rightArgumentEnd + 1] == '/') {
      free(rightArgument);
      *sign1In = divisionSignLocation;
      *sign2In = rightArgumentEnd + 1;
      return;
    }

    // Find next division sign.
    long n = find_operational_sign(expression + divisionSignLocation + 1, '/');
    if (n != -1)
      divisionSignLocation += n + 1;
    else
      divisionSignLocation = -1;
    free(rightArgument);
  }

  *sign1In = -1;
  *sign2In = -1;
  return;
}

char *simplify_arithmetic_expression(const char *expression_in, int outputType,
                                     size_t accuracy) {
  char *expression = (char *)calloc(strlen(expression_in) + 1, 1);
  strcpy(expression, expression_in);
  str_replace_all(&expression, "[", "(");
  str_replace_all(&expression, "]", ")");
  str_replace_all(&expression, "{", "(");
  str_replace_all(&expression, "}", ")");
  str_replace_all(&expression, " ", "");

  size_t n = strlen(expression);
  expression = (char *)realloc(expression, n + 3);
  strcpy(expression + n, "+0");
  expression[n + 2] = 0;

  bool outputMixedFraction = false;
  if (outputType == 2) {
    outputType = 1;
    outputMixedFraction = true;
  }

  remove_misplaced_and_redundant_signs(&expression);

  const char *_loc = strchr(expression, '(');
  while (_loc != NULL) {
    size_t start = _loc - expression;
    size_t end = get_corresponding_closing_bracket(expression, start);
    char *innerExpression = (char *)calloc(end - start, 1);
    strncpy(innerExpression, expression + start + 1, end - start - 1);
    char *simplifiedInnerExpression =
        simplify_arithmetic_expression(innerExpression, outputType, accuracy);

    // Reciprocate the fraction if not in output type zero and the previous
    // character is a division sign.
    if (start >= 1 && expression[start - 1] == '/' && outputType != 0) {
      struct fraction innerExpressionFraction =
          parse_fraction(simplifiedInnerExpression);
      // Reciprocate the fraction.
      if (innerExpressionFraction.numerator[0] == '-') {
        char *tempSwap =
            (char *)calloc(strlen(innerExpressionFraction.numerator), 1);
        strcpy(tempSwap, innerExpressionFraction.numerator + 1);
        innerExpressionFraction.numerator =
            (char *)realloc(innerExpressionFraction.numerator,
                            strlen(innerExpressionFraction.denominator) + 2);
        strcpy(innerExpressionFraction.numerator + 1,
               innerExpressionFraction.denominator);
        innerExpressionFraction.denominator = (char *)realloc(
            innerExpressionFraction.denominator, strlen(tempSwap) + 1);
        strcpy(innerExpressionFraction.denominator, tempSwap);
        free(tempSwap);
      } else {
        char *tempSwap =
            (char *)calloc(strlen(innerExpressionFraction.numerator) + 1, 1);
        strcpy(tempSwap, innerExpressionFraction.numerator);
        innerExpressionFraction.numerator =
            (char *)realloc(innerExpressionFraction.numerator,
                            strlen(innerExpressionFraction.denominator) + 1);
        strcpy(innerExpressionFraction.numerator,
               innerExpressionFraction.denominator);
        innerExpressionFraction.denominator = (char *)realloc(
            innerExpressionFraction.denominator, strlen(tempSwap) + 1);
        strcpy(innerExpressionFraction.denominator, tempSwap);
        free(tempSwap);
      }
      size_t n = strlen(innerExpressionFraction.numerator);
      simplifiedInnerExpression =
          (char *)realloc(simplifiedInnerExpression,
                          n + strlen(innerExpressionFraction.denominator) + 2);
      strcpy(simplifiedInnerExpression, innerExpressionFraction.numerator);
      strcpy(simplifiedInnerExpression + n, "/");
      strcpy(simplifiedInnerExpression + n + 1,
             innerExpressionFraction.denominator);
      // Change division to multiplication.
      expression[start - 1] = '*';
    }
    bool haveToChangeBrackets =
        (end + 1 < strlen(expression) && expression[end + 1] == '^') ||
        (start >= 1 && expression[start - 1] == '^');
    if (haveToChangeBrackets) {
      // Replace the brackets with '[]' (necessary for things like (-1)^n)
      expression[start] = '[';
      expression[end] = ']';
    }
    haveToChangeBrackets
        ? replace_substring_from_position(start + 1, end - 1, &expression,
                                          simplifiedInnerExpression)
        : replace_substring_from_position(start, end, &expression,
                                          simplifiedInnerExpression);
    _loc = strchr(expression, '(');
  }

  remove_misplaced_and_redundant_signs(&expression);

  // Exponents
  // Non operational signs are things like the '-' in '-2*4'
  // There is no number behind '-', so it does not act
  // as an operator.
  // Also, in the case of exponents, we need to start looking for signs from the
  // back in order to correctly deal with cases like 3^3^3.
  long signLocation = find_operational_sign(expression, '^');
  while (signLocation >= 0) {
    long start = signLocation, end = signLocation;
    char *simplifiedExponentiation;
    char *leftArgument =
        get_numerical_arguments(expression, true, &start, outputType);
    char *rightArgument =
        get_numerical_arguments(expression, false, &end, outputType);
    if (outputType == 0)
      simplifiedExponentiation = power(leftArgument, rightArgument, accuracy);
    if (outputType == 1) {
      struct fraction fraction1 = parse_fraction(leftArgument);
      struct fraction fraction2 = parse_fraction(rightArgument);
      struct fraction answer = power_fraction(fraction1, fraction2, accuracy);
      simplifiedExponentiation = (char *)calloc(
          strlen(answer.numerator) + strlen(answer.denominator) + 4, 1);
      bool squareBrackets = start - 1 >= 0 && expression[start - 1] == '^';
      if (squareBrackets)
        simplifiedExponentiation[0] = '[';
      strncpy(simplifiedExponentiation + squareBrackets, answer.numerator,
              strlen(answer.numerator));
      simplifiedExponentiation[strlen(answer.numerator) + squareBrackets] = '/';
      strncpy(simplifiedExponentiation + strlen(answer.numerator) + 1 +
                  squareBrackets,
              answer.denominator, strlen(answer.denominator));
      if (squareBrackets)
        simplifiedExponentiation[strlen(simplifiedExponentiation)] = ']';
      delete_fraction(fraction1);
      delete_fraction(fraction2);
      delete_fraction(answer);
    }
    free(leftArgument);
    free(rightArgument);
    replace_substring_from_position(start, end, &expression,
                                    simplifiedExponentiation);
    free(simplifiedExponentiation);
    signLocation = find_operational_sign(expression, '^');
  }

  // This next part deals with decimal division.
  if (outputType == 0) {
    long signLocation = find_operational_sign(expression, '/');
    while (signLocation >= 0) {
      long start = signLocation, end = signLocation;
      char *numerator =
          get_numerical_arguments(expression, true, &start, outputType);
      char *denominator =
          get_numerical_arguments(expression, false, &end, outputType);
      char *quotient = (char *)calloc(
          strlen(numerator) + strlen(denominator) + accuracy + 3, 1);
      divide(numerator, denominator, quotient, accuracy);
      replace_substring_from_position(start, end, &expression, quotient);
      signLocation = find_operational_sign(expression, '/');
      free(numerator);
      free(denominator);
      free(quotient);
    }
  } else if (outputType == 1) {
    // Check for and deal with chain divisions.
    // Chain division are divisions in the form of a/b/c/d/...
    // a/b/c/d = a/(bc)/d = a/(bcd)
    long sign1 = 0, sign2 = 0;
    get_chain_division_location(expression, &sign1, &sign2);
    while (sign1 >= 0 && sign2 >= 0) {
      long numeratorStart = sign1;
      long div1End = sign1;
      long div2End = sign2;
      char *numerator = get_numerical_arguments(expression, true,
                                                &numeratorStart, outputType);
      // Again, this is just temporary (to avoid pulling division signs)
      expression[sign1] = '^';
      char *div1 =
          get_numerical_arguments(expression, false, &div1End, outputType);
      expression[sign1] = '/';
      expression[sign2] = '^'; // Avoid pulling division signs
      char *div2 =
          get_numerical_arguments(expression, false, &div2End, outputType);
      expression[sign2] = '/';
      char *denominator = (char *)calloc(strlen(div1) + strlen(div2) + 3, 1);
      multiply(div1, div2, denominator);
      char *simplifiedChainDivision =
          (char *)calloc(strlen(numerator) + strlen(denominator) + 2, 1);
      strncpy(simplifiedChainDivision, numerator, strlen(numerator));
      simplifiedChainDivision[strlen(numerator)] = '/';
      strncpy(simplifiedChainDivision + strlen(numerator) + 1, denominator,
              strlen(denominator));
      replace_substring_from_position(numeratorStart, div2End, &expression,
                                      simplifiedChainDivision);
      get_chain_division_location(expression, &sign1, &sign2);
      free(numerator);
      free(div1);
      free(div2);
      free(denominator);
      free(simplifiedChainDivision);
    }
  }

  remove_misplaced_and_redundant_signs(&expression);

  char operators[] = "*+-"; // This order is important!
  size_t numberOfOperators = 3;
  // Generic procedure following order of operations
  for (size_t i = 0; i < numberOfOperators; i++) {
    char sign = operators[i];

    long signLocation = find_operational_sign(expression, sign);
    while (signLocation >= 0) {
      long start = signLocation, end = signLocation;
      char *leftArgument =
          get_numerical_arguments(expression, true, &start, outputType);
      char *rightArgument =
          get_numerical_arguments(expression, false, &end, outputType);
      char *operationResult;
      if (outputType == 0) {
        operationResult =
            (char *)calloc(strlen(leftArgument) + strlen(rightArgument) + 3, 1);
        switch (sign) {
        case '*':
          multiply(leftArgument, rightArgument, operationResult);
          break;
        case '+':
          add(leftArgument, rightArgument, operationResult);
          break;
        case '-':
          subtract(leftArgument, rightArgument, operationResult);
          break;
        default:
          break;
        }
      }
      if (outputType == 1) {
        struct fraction fraction1 = parse_fraction(leftArgument);
        struct fraction fraction2 = parse_fraction(rightArgument);
        struct fraction answer;
        switch (sign) {
        case '*':
          answer = multiply_fraction(fraction1, fraction2);
          break;
        case '+':
          answer = add_fraction(fraction1, fraction2);
          break;
        case '-':
          answer = subtract_fraction(fraction1, fraction2);
          break;
        default:
          break;
        }

        operationResult = (char *)calloc(
            strlen(answer.numerator) + strlen(answer.denominator) + 2, 1);
        strncpy(operationResult, answer.numerator, strlen(answer.numerator));
        operationResult[strlen(answer.numerator)] = '/';
        strncpy(operationResult + strlen(answer.numerator) + 1,
                answer.denominator, strlen(answer.denominator));

        delete_fraction(fraction1);
        delete_fraction(fraction2);
        delete_fraction(answer);
      }

      // If the left argument is negative and the result is not then the
      // negative sign is lost. This is obviously unacceptable: 1/4-1/3+1/2 -->
      // -1/3+1/2 = 1/6 so this becomes 1/41/6?? Instead, apped a '+' if this is
      // the case.
      if (leftArgument[0] == '-' && operationResult[0] != '-') {
        size_t n = strlen(operationResult);
        operationResult = (char *)realloc(operationResult, n + 2);
        memmove(operationResult + 1, operationResult, n + 1);
        operationResult[0] = '+';
      }

      replace_substring_from_position(start, end, &expression, operationResult);
      signLocation = find_operational_sign(expression, sign);

      free(leftArgument);
      free(rightArgument);
      free(operationResult);
    }

    remove_misplaced_and_redundant_signs(&expression);
  }

  // If the denominator is 1 then remove it.
  struct fraction frac = parse_fraction(expression);
  if (!strcmp(frac.denominator, "1")) {
    const char *_loc = strchr(expression, '/');
    if (_loc != NULL)
      expression[_loc - expression] = 0;
  }

  if (!outputMixedFraction)
    return expression;

  char sign = frac.numerator[0] == '-' ? '-' : '+';
  // Ignore sign.
  if (sign == '-') {
    size_t length = strlen(frac.numerator);
    memmove(frac.numerator, frac.numerator + 1, length - 1);
    frac.numerator[length - 1] = 0;
  }

  char *denominatorBiggerCheck =
      (char *)calloc(strlen(frac.numerator) + strlen(frac.denominator) + 3, 1);
  subtract(frac.numerator, frac.denominator, denominatorBiggerCheck);
  if (denominatorBiggerCheck[0] == '-') {
    free(denominatorBiggerCheck);
    return expression;
  }

  char *quotient =
      (char *)calloc(strlen(frac.numerator) + strlen(frac.denominator) + 3, 1);
  char *remainder =
      (char *)calloc(strlen(frac.numerator) + strlen(frac.denominator) + 3, 1);
  divide_whole_with_remainder(frac.numerator, frac.denominator, quotient,
                              remainder);
  remove_zeroes(quotient);
  remove_zeroes(remainder);

  expression =
      (char *)realloc(expression, strlen(quotient) + strlen(remainder) +
                                      strlen(frac.denominator) + 6);
  memset(expression, 0,
         strlen(quotient) + strlen(remainder) + strlen(frac.denominator) + 6);
  size_t charactersWritten = 0;
  if (sign == '-')
    expression[charactersWritten++] = '-';
  strncpy(expression + charactersWritten, quotient, strlen(quotient));
  charactersWritten += strlen(quotient);
  if (strcmp(remainder, "0")) {
    // If the remainder is non-zero.
    expression[charactersWritten++] = ' ';
    expression[charactersWritten++] = sign;
    expression[charactersWritten++] = ' ';
    strncpy(expression + charactersWritten, remainder, strlen(remainder));
    charactersWritten += strlen(remainder);
    expression[charactersWritten++] = '/';
    strncpy(expression + charactersWritten, frac.denominator,
            strlen(frac.denominator));
  }

  free(quotient);
  free(remainder);
  free(denominatorBiggerCheck);

  return expression;
}

#endif