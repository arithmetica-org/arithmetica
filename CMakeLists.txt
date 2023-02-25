cmake_minimum_required(VERSION 3.16)

project(arithmetica C)

enable_language(ASM_NASM)
enable_language(CXX)

add_subdirectory(src/library)

option(ENABLE_TESTS "Build tests" ON)

if (ENABLE_TESTS)
    add_subdirectory(src/basic_math_operations/src/library)
    add_subdirectory(src/tests)
endif()

set(CMAKE_CXX_STANDARD 17)