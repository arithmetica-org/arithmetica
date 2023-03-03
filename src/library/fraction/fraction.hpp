#pragma once

#include <cstdlib>
#include <cstring>

#ifndef _fraction_h_
#define _fraction_h_
struct fraction
{
  char *numerator;
  char *denominator;
};
#endif

extern "C" struct fraction create_fraction (const char *n, const char *d);
extern "C" void delete_fraction (struct fraction f);