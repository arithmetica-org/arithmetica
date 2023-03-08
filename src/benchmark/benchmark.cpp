#include "get_percent_improvement.hpp"
#include <algorithm>
#include <call_arithmetica.hpp>
#include <cmath>
#include <color.hpp>
#include <curl/curl.h>
#include <fstream>
#include <get_current_directory.hpp>
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

static size_t
write_callback (char *ptr, size_t size, size_t nmemb, void *userdata)
{
  // Do nothing with the received data
  return size * nmemb;
}

std::string get_cpu_name ();

// Linux
#ifdef __linux__
#include <cpuid.h>
std::string
get_cpu_name ()
{
  char CPUBrandString[0x40];
  unsigned int CPUInfo[4] = { 0, 0, 0, 0 };

  __cpuid (0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
  unsigned int nExIds = CPUInfo[0];

  memset (CPUBrandString, 0, sizeof (CPUBrandString));

  for (unsigned int i = 0x80000000; i <= nExIds; ++i)
    {
      __cpuid (i, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);

      if (i == 0x80000002)
        memcpy (CPUBrandString, CPUInfo, sizeof (CPUInfo));
      else if (i == 0x80000003)
        memcpy (CPUBrandString + 16, CPUInfo, sizeof (CPUInfo));
      else if (i == 0x80000004)
        memcpy (CPUBrandString + 32, CPUInfo, sizeof (CPUInfo));
    }

  return CPUBrandString;
}
// Windows
#elif _WIN32
std::string
get_cpu_name ()
{
  return "some random windows cpu idk (probs intel) use linux";
}
#endif

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
  std::cout << "Benchmarking arithmetica:\n\n";
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
  std::vector<double> benchmark_hertz;

  std::string benchmark_identifier;
  std::string upload_server = "1FAIpQLSc9Qdp2sxBD9sal-0YeoeIg6ys_OJ-"
                              "yek16CsndcFRvejrt5A",
              upload_key = "1369257619",
              upload_number
              = "4957582068535559811"; // public upload server, key, and number

  if (argc > 1)
    {
      std::vector<std::string> _functions;
      for (auto i = 1; i < argc; i++)
        {
          if (std::string (argv[i]) == "--unique-identifier")
            {
              if (i + 1 < argc)
                {
                  benchmark_identifier = argv[i + 1];
                  i++;
                }
              else
                {
                  std::cout << "Error: --unique-identifier requires an "
                               "identifier.\n";
                  return 1;
                }
              continue;
            }
          if (std::string (argv[i]) == "--upload")
            {
              if (i + 3 < argc)
                {
                  upload_server = argv[i + 1];
                  upload_key = argv[i + 2];
                  upload_number = argv[i + 3];
                  i += 3;
                }
              else
                {
                  std::cout
                      << "Error: --upload requires exactly three arguments.\n";
                  return 1;
                }
              continue;
            }

          _functions.push_back (argv[i]);
          benchmark = true;
        }
      if (benchmark)
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
          arithmetica_inputs.push_back (inputs);
        }
      inputFile.close ();
      expectedFile.close ();

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
              // Since we're using GitHub Actions, we can't keep printing to
              // stdout, so we'll just print the last result.
              // std::cout << "\r  " << color (std::to_string (times), "Green")
              //           << " runs in "
              //           << color (std::to_string (time_elapsed), "Green")
              //           << " ms" << std::flush;
            }
          times++;
        }

      benchmark_hertz.push_back (times * 1000 / time_elapsed);
      std::cout << "\r  " << color (std::to_string (times), "Green")
                << " runs in "
                << color (std::to_string (time_elapsed), "Green")
                << " ms\n    "
                << color (std::to_string (times * 1000 / time_elapsed),
                          "Green")
                << " Hz" << std::endl;
    }

  if (benchmark_identifier.empty ())
    {
      std::cout << "No unique identifier was provided. Use "
                   "--unique-identifier to provide one, if you want to upload "
                   "the results of the benchmark.\n";
      return 0;
    }

  std::cout << "Uploading benchmark results!\n";
  std::string json_content = "{\"identifier\":%20\"" + benchmark_identifier
                             + "\",%0D%0A\"cpu_name\":\"" + get_cpu_name ()
                             + "\",%0D%0A\"benchmarks\":{";
  for (auto i = 0; i < functions.size (); i++)
    {
      json_content += "\"" + functions[i] + "\":%20"
                      + std::to_string (benchmark_hertz[i]);
      if (i != functions.size () - 1)
        json_content += ",%20%0D%0A";
    }
  json_content += "}}";

  std::string curl_postfields = "entry." + upload_key + "=" + json_content
                                + "&fvv=1&"
                                  "partialResponse=%5Bnull%2Cnull%2C%22-"
                                + upload_number
                                + "%22%5D&"
                                  "pageHistory=0&fbzx=-"
                                + upload_number;
  std::string curl_opturl
      = "https://docs.google.com/forms/d/e/" + upload_server + "/formResponse";

  CURL *curl = curl_easy_init ();
  if (curl)
    {
      // 1FAIpQLSfJET2Dte8QYHhaKmDiG9gE0HDVjt3YMtRT6UGU8fE4jnc5DA
      //
      curl_easy_setopt (curl, CURLOPT_URL, curl_opturl.c_str ());
      curl_easy_setopt (curl, CURLOPT_POSTFIELDS, curl_postfields.c_str ());
      curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, write_callback);

      CURLcode res = curl_easy_perform (curl);
      if (res != CURLE_OK)
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror (res)
                  << std::endl;

      curl_easy_cleanup (curl);
    }

  std::cout << "Benchmark results uploaded!\n";

  // If this is not running on a GH Actions runner, then we'll just exit.
  if (benchmark_identifier.find ("commit") == std::string::npos)
    return 0;

  // We can now compare the results of the benchmark to the previous results.
  // format: commit-<commit_number>
  int commit_number = std::stoi (benchmark_identifier.substr (7));
  std::string previous_commit = "commit-" + std::to_string (commit_number - 1);

  std::cout << "Comparing benchmark results to previous commit:\n";
  for (auto &i : get_percent_improvement (previous_commit,
                                          benchmark_identifier, upload_server))
    {
      std::cout << "  " << i.first << ": " << i.second << "% improvement.\n";
    }
}