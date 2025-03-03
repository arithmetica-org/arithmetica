cmake_minimum_required(VERSION 3.16)

project(arithmetica C)

enable_language(C)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")

if(APPLE)
    set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -D__MACH__")
endif()

set(c_cpp_sources
    arithmetica.cpp

    check_accuracy.c

    func/arccos.c
    func/arcsin.c
    func/arctan.c
    func/natural_logarithm.c
    func/cosine.c
    func/exponential.c
    func/sine.c
    func/square_root.c
    func/tangent.c

    numeric/continued_fraction_to_fraction.c
    numeric/factorial.c
    numeric/find_roots_of_polynomial.c
    numeric/fraction_to_continued_fraction.c
    numeric/igcd.c
    numeric/ilcm.c
    numeric/power.c
    numeric/power_integer.c
    numeric/repeating_decimal_to_fraction.c
    numeric/simplify_arithmetic_expression.c
    numeric/terminating_decimal_to_fraction.c

    fraction/Fraction.cpp
    fraction/fraction.c
    fraction/add_fraction.c
    fraction/multiply_fraction.c
    fraction/parse_fraction.c
    fraction/power_fraction.c
    fraction/simplify_parsed_fraction.c
    fraction/subtract_fraction.c
    fraction/equal_fraction.c

    complex/complex_arithmetica.c
    complex/add_complex.c
    complex/divide_complex.c
    complex/exponential_complex.c
    complex/multiply_complex.c
    complex/square_root_complex.c
    complex/subtract_complex.c

    geometry/construct_regular_polygon.c

    algparser/algexpr.cpp
    algparser/add.cpp
    algparser/multiply.cpp
    algparser/divide.cpp
    algparser/simplify_term.cpp
    algparser/exponent_product.cpp
    algparser/exponent_sum.cpp
    algparser/exponent_exponent.cpp
    algparser/numeric_checks.cpp
    algparser/functions.cpp
    algparser/products.cpp
    algparser/terms.cpp
    algparser/simplify.cpp
    algparser/to_string.cpp
    algparser/prettify.cpp

    matrix/Matrix.cpp
    matrix/multiply.cpp
    matrix/invert.cpp
    matrix/to_string.cpp

    calculus/diff.cpp
)

set(include_directories
    ${BMO_SOURCE_DIR}
    "geometry"
    "fraction"
    "complex"
    "algparser"
    "matrix"
    "calculus"
    "."
)

if (UNIX)
    set(linux_sources
        linux/strlen_arithmetica.asm
        linux/truncate.asm
    )
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/linux)

    add_library(objlib OBJECT ${c_cpp_sources} ${linux_sources})
    set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)
    target_include_directories(objlib PRIVATE ${include_directories})

    add_library(arithmetica STATIC $<TARGET_OBJECTS:objlib>)
    if(ARITHMETICA_BUILD_SHARED)
        add_library(arithmetica_sh SHARED $<TARGET_OBJECTS:objlib>)
        set_target_properties(arithmetica_sh PROPERTIES OUTPUT_NAME "arithmetica")
        target_include_directories(arithmetica_sh PRIVATE ${include_directories})
    endif()
endif (UNIX)

if (WIN32)
    set(windows_sources
        windows/strlen.asm
        windows/truncate.asm
    )
    add_library(arithmetica STATIC ${c_cpp_sources} ${windows_sources})
endif (WIN32)

target_include_directories(arithmetica PRIVATE ${include_directories})