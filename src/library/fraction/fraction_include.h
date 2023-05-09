#ifndef _fraction_include_h_
#define _fraction_include_h_

#include "fraction.h"
#include <stdbool.h>

struct fraction add_fraction (struct fraction frac1, struct fraction frac2);
struct fraction multiply_fraction (struct fraction frac1,
                                   struct fraction frac2);
struct fraction parse_fraction (const char *frac);
struct fraction power_fraction (struct fraction base_in,
                                struct fraction exponent_in, size_t accuracy);
struct fraction simplify_parsed_fraction (struct fraction frac);
struct fraction subtract_fraction (struct fraction frac1,
                                   struct fraction frac2);

bool equal_fraction (struct fraction _a, struct fraction _b);

#endif