#ifndef _complex_arithmetica_include_h_
#define _complex_arithmetica_include_h_

#include "complex_arithmetica.h"

struct complex_arithmetica add_complex (struct complex_arithmetica a,
                                        struct complex_arithmetica b);
struct complex_arithmetica
divide_complex (struct complex_arithmetica numerator,
                struct complex_arithmetica denominator, size_t accuracy);
struct complex_arithmetica exponential_complex (struct complex_arithmetica n,
                                                size_t accuracy);
struct complex_arithmetica multiply_complex (struct complex_arithmetica a,
                                             struct complex_arithmetica b);
struct complex_arithmetica square_root_complex (struct complex_arithmetica n,
                                                size_t accuracy);

#endif