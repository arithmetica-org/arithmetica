#include "call_arithmetica.hpp"
#include "color.hpp"
#include "get_current_directory.hpp"
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
main (int argc, char **argv)
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

  bool benchmark = false;

  if (argc > 1)
    {
      benchmark = true;
      std::vector<std::string> _functions;
      for (auto i = 1; i < argc; i++)
        _functions.push_back (argv[i]);
      functions = _functions;
    }

  std::string currentDir = get_current_directory ();
  std::replace (currentDir.begin (), currentDir.end (), '\\', '/');
  if (currentDir.find ("build") != std::string::npos)
    currentDir = currentDir.substr (0, currentDir.find ("build"));
  if (currentDir.back () != '/')
    currentDir.push_back ('/');

  for (auto i = 0; i < functions.size (); i++)
    {
      std::cout << "<" << i + 1 << "> "
                << color (functions[i] + ":", "Magenta") << '\n';

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
      double totalTimeMS = 0;
      std::vector<std::vector<std::string> > arithmetica_inputs;
      while (std::getline (inputFile, input))
        {
          std::string inputsStr;
          std::string spaces
              = "   " + std::string (std::to_string (i + 1).length (), ' ');
          currentTest++;
          auto _inputs = split_string (input, ' ');
          std::vector<std::string> inputs = { functions[i] };
          std::copy (_inputs.begin (), _inputs.end (),
                     std::back_inserter (inputs));
          for (auto i = 0; i < _inputs.size (); i++)
            {
              inputsStr += _inputs[i];
              if (i != _inputs.size () - 1)
                inputsStr += ", ";
            }
          std::string Expected;
          std::getline (expectedFile, Expected);
          double timeMS;
          arithmetica_inputs.push_back (inputs);
          std::string res = call_arithmetica (inputs, timeMS);
          totalTimeMS += timeMS;
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
              std::cout << spaces << "<" << currentTest << "> (" << timeMS
                        << " ms) " << color (functions[i], "Yellow") << "("
                        << color_digits (inputsStr, "Green")
                        << ") = " << color_digits (res, "Green") << '\n';
            }
        }

      std::cout << "<" << i + 1 << "> "
                << "(" << totalTimeMS << " ms) "
                << color (functions[i] + ":", "Green") << " (" << currentTest
                << "/" << currentTest << ")" << '\n';

      inputFile.close ();
      expectedFile.close ();

      // Benchmark if enabled
      if (!benchmark)
        continue;

      std::cout << "Benchmarking " << color (functions[i], "Magenta") << ":\n";

      // Calculate how many times the function runs in 5 seconds.
      int times = 0;
      double time_elapsed = 0;
      while (time_elapsed < 5000)
        {
          for (auto &i : arithmetica_inputs)
            {
              double timeMS;
              call_arithmetica (i, timeMS);
              time_elapsed += timeMS;
              std::cout << "\r" << color (std::to_string (times), "Green")
                        << " runs in "
                        << color (std::to_string (time_elapsed), "Green")
                        << " ms" << std::flush;
            }
          times++;
        }

      // Print the Hz: this should be the main benchmark.
      std::cout << "\r" << color (std::to_string (times), "Green")
                << " runs in "
                << color (std::to_string (time_elapsed), "Green") << " ms\n"
                << color (std::to_string (times * 1000 / time_elapsed),
                          "Green")
                << " Hz" << std::endl;
    }

  std::cout << color ("All tests passed successfully!\n", "Green");
}
