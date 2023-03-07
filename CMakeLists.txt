cmake_minimum_required(VERSION 3.16)

project(arithmetica C)

enable_language(ASM_NASM)
enable_language(CXX)

add_subdirectory(src/library)

option(BUILD_BMO "Build basic math operations" ON)
option(ENABLE_TESTS "Build tests" OFF)
option(ENABLE_BENCHMARK "Build benchmark" OFF)

if(BUILD_BMO)
    add_subdirectory(src/basic_math_operations/src/library)
endif()

if (ENABLE_TESTS)
    add_subdirectory(src/tests)
endif()

if (ENABLE_BENCHMARK)
    add_subdirectory(src/benchmark)
endif()

set(CMAKE_CXX_STANDARD 17)