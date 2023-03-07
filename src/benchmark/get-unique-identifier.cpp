#include <fstream>
#include <iostream>

int
main (int argc, char **argv)
{
  if (argc < 2)
    return 0;

  std::ifstream in (argv[1]);
  std::string version;
  std::getline (in, version);

  version = version.substr (version.find ('-') + 1, version.length ());
  version = version.substr (version.find ('.') + 1, version.length ());
  std::string patch = version.substr (0, version.find ('.'));

  std::string uid = "commit-" + patch;

  std::cout << uid << std::endl;

  // Rewrite version to same file.
  in.close ();
  std::ofstream out (argv[1]);
  out << uid;
  out.close ();
}