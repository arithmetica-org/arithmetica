cmake_minimum_required(VERSION 3.22)

project(arithmetica C)

enable_language(ASM_NASM)

add_subdirectory(src/library)

option(ENABLE_TESTS "Build tests" OFF)

if (ENABLE_TESTS)
    add_subdirectory(src/basic_math_operations/src/library)
    add_subdirectory(src/tests)
endif()
