#pragma once

#include "fraction.hpp"

extern "C" struct fraction add_fraction (struct fraction frac1,
                                         struct fraction frac2);
extern "C" struct fraction multiply_fraction (struct fraction frac1,
                                              struct fraction frac2);
extern "C" struct fraction parse_fraction (const char *frac);
extern "C" struct fraction power_fraction (struct fraction base_in,
                                           struct fraction exponent_in,
                                           size_t accuracy);
extern "C" struct fraction simplify_parsed_fraction (struct fraction frac);
extern "C" struct fraction subtract_fraction (struct fraction frac1,
                                              struct fraction frac2);