#pragma once

#include <cstdlib>
#include <cstring>

struct fraction
{
  char *numerator;
  char *denominator;
};

extern "C" struct fraction create_fraction (const char *n, const char *d);
extern "C" void delete_fraction (struct fraction f);