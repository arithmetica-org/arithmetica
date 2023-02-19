#include "call_arithmetica.hpp"
#include "color.hpp"
#include "get_current_directory.hpp"
#include "get_terminal_size.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

static std::string
get_input_filename (std::string function, std::string currentDir)
{
  return currentDir + "src/tests/arithmetica_tests/" + function + "/input.txt";
}

static std::string
get_expected_filename (std::string function, std::string currentDir)
{
  return currentDir + "src/tests/arithmetica_tests/" + function
         + "/expected.txt";
}

static std::vector<std::string>
split_string (std::string s, char ch)
{
  std::vector<std::string> answer;
  std::string part;
  for (auto &i : s)
    {
      if (i != ch)
        part.push_back (i);
      else
        {
          answer.push_back (part);
          part.clear ();
        }
    }
  if (!part.empty ())
    answer.push_back (part);
  return answer;
}

static std::string
color_digits (std::string s, std::string col)
{
  std::string answer;
  for (auto &i : s)
    {
      if (isdigit (i))
        answer += color (std::string (1, i), col);
      else
        answer.push_back (i);
    }
  return answer;
}

int
main ()
{
  std::cout << "Testing arithmetica:\n\n";
  std::vector<std::string> functions = { "arcsin",
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
                                         "multiply_fraction",
                                         "power_fraction",
                                         "construct_regular_polygon" };
  std::sort (functions.begin (), functions.end ());

  int width = 10, height = 10;
  get_terminal_size (width, height);
  if (width < 0 || width > 1000)
    width = 15;

  std::string currentDir = get_current_directory ();
  std::replace (currentDir.begin (), currentDir.end (), '\\', '/');
  if (currentDir.find ("build") != std::string::npos)
    currentDir = currentDir.substr (0, currentDir.find ("build"));
  if (currentDir.back () != '/')
    currentDir.push_back ('/');

  for (auto i = 0; i < functions.size (); i++)
    {
      std::cout << "<" << i + 1 << "> "
                << color (functions[i] + ".h:", "Magenta") << '\n';

      int currentTest = 0;
      std::ifstream expectedFile (
          get_expected_filename (functions[i], currentDir));
      std::ifstream inputFile (get_input_filename (functions[i], currentDir));

      if (!expectedFile || !inputFile)
        {
          std::cout << "Couldn't open test files!\n";
          std::cout << currentDir << "\n";
          continue;
        }

      std::string input;
      size_t linesPrinted = 0;
      double totalTimeMS = 0;
      while (std::getline (inputFile, input))
        {
          size_t charactersPrinted = 3 + std::to_string (i + 1).length ();
          std::string inputsStr;
          std::string spaces
              = "   " + std::string (std::to_string (i + 1).length (), ' ');
          currentTest++;
          auto _inputs = split_string (input, ' ');
          std::vector<std::string> inputs = { functions[i] };
          for (auto &i : _inputs)
            inputs.push_back (i);
          for (auto i = 0; i < _inputs.size (); i++)
            {
              inputsStr += _inputs[i];
              if (i != _inputs.size () - 1)
                inputsStr += ", ";
            }
          std::string Expected;
          std::getline (expectedFile, Expected);
          double timeMS;
          std::string res = call_arithmetica (inputs, timeMS);
          totalTimeMS += timeMS;
          for (auto i = 0; i < linesPrinted; i++)
            std::cout << "\033[A\33[2K";
          if (std::string (res) != Expected)
            {
              std::cout << spaces << "<" << currentTest << "> "
                        << color ("Error: " + functions[i] + "(", "Red")
                        << inputsStr << color (") failed.", "Red") << "\n"
                        << spaces;
              std::cout << color ("Expected: ", "Red") << Expected << '\n'
                        << spaces;
              std::cout << color ("Actual  : ", "Red") << res << '\n';
              inputFile.close ();
              expectedFile.close ();
              throw std::runtime_error (functions[i] + " failed a test.");
            }
          else
            {
              auto cPrint = 1 + spaces.length ()
                            + std::to_string (currentTest).length () + 3
                            + std::to_string ((int)timeMS).length () + 5
                            + functions[i].length () + 1 + inputsStr.length ()
                            + 4 + res.length ();
              if (cPrint <= width)
                {
                  charactersPrinted += cPrint;
                  std::cout << spaces << "<" << currentTest << "> (" << timeMS
                            << " ms) " << color (functions[i], "Yellow") << "("
                            << color_digits (inputsStr, "Green")
                            << ") = " << color_digits (res, "Green") << '\n';
                }
              else
                {
                  charactersPrinted += spaces.length () + 1
                                       + std::to_string (currentTest).length ()
                                       + 14;
                  std::cout << spaces << "<" << currentTest
                            << "> Test passed!\n";
                }
            }

          linesPrinted = std::ceil ((double)charactersPrinted / width);
        }

      for (auto i = 0; i < linesPrinted + 1; i++)
        std::cout << "\033[A\33[2K";

      std::cout << "<" << i + 1 << "> "
                << "(" << totalTimeMS << " ms) "
                << color (functions[i] + ".h:", "Green") << " (" << currentTest
                << "/" << currentTest << ")" << '\n';

      inputFile.close ();
      expectedFile.close ();
    }

  std::cout << color ("All tests passed successfully!\n", "Green");
}