cmake_minimum_required(VERSION 3.16)

project(arithmetica C)

enable_language(C)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

set(c_cpp_sources
    arithmetica.cpp

    arccos.c
    arcsin.c
    arctan.c
    check_accuracy.c
    cosine.c
    exponential.c
    factorial.c
    fraction_to_continued_fraction.c
    igcd.c
    ilcm.c
    natural_logarithm.c
    power.c
    power_integer.c
    repeating_decimal_to_fraction.c
    simplify_arithmetic_expression.c
    sine.c
    square_root.c
    tangent.c
    terminating_decimal_to_fraction.c

    fraction/Fraction.cpp
    fraction/fraction.c
    fraction/add_fraction.c
    fraction/multiply_fraction.c
    fraction/parse_fraction.c
    fraction/power_fraction.c
    fraction/simplify_parsed_fraction.c
    fraction/subtract_fraction.c

    complex/complex_arithmetica.c
    complex/add_complex.c
    complex/divide_complex.c
    complex/exponential_complex.c
    complex/multiply_complex.c
    complex/square_root_complex.c
    complex/subtract_complex.c

    geometry/construct_regular_polygon.cpp
    # geometry/construct_regular_polygon.c
)

set(include_directories
    "../basic_math_operations/src/library"
    "geometry"
    "fraction"
    "complex"
    "."
)

if (UNIX)
    set(linux_sources
        linux/strlen_arithmetica.asm
        linux/truncate.asm
    )

    add_library(objlib OBJECT ${c_cpp_sources} ${linux_sources})
    set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)
    target_include_directories(objlib PRIVATE ${include_directories})

    add_library(arithmetica STATIC $<TARGET_OBJECTS:objlib>)
    add_library(arithmetica_sh SHARED $<TARGET_OBJECTS:objlib>)
    set_target_properties(arithmetica_sh PROPERTIES OUTPUT_NAME "arithmetica")
    target_include_directories(arithmetica_sh PRIVATE ${include_directories})
endif (UNIX)

if (WIN32)
    set(windows_sources
        windows/strlen.asm
        windows/truncate.asm
    )
    add_library(arithmetica STATIC ${c_cpp_sources} ${windows_sources})
endif (WIN32)

target_include_directories(arithmetica PRIVATE ${include_directories})