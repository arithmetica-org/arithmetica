cmake_minimum_required(VERSION 3.16)

project(arithmetica C)

enable_language(ASM_NASM)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_BMO "Build basic math operations" ON)
option(ENABLE_TESTS "Build tests" ON)
option(ENABLE_BENCHMARK "Build benchmark" OFF)
option(ARITHMETICA_BUILD_SHARED "Build shared library" OFF)

set(BMO_SOURCE_DIR "")

if(BUILD_BMO)
    include(FetchContent)

    message(STATUS "Fetching basic_math_operations...")
    FetchContent_Declare(bmo
        GIT_REPOSITORY https://github.com/avighnac/basic_math_operations
        GIT_TAG main
    )
    FetchContent_GetProperties(bmo)
    if(NOT bmo_POPULATED)
        message(STATUS "Populating basic_math_operations...")
        FetchContent_Populate(bmo)
    endif()

    set(BMO_SOURCE_DIR "${bmo_SOURCE_DIR}/src/library")
    add_subdirectory(${BMO_SOURCE_DIR})
endif()

add_subdirectory(src/library)

if (ENABLE_TESTS)
    add_subdirectory(src/tests)
endif()

if (ENABLE_BENCHMARK)
    add_subdirectory(src/benchmark)
endif()

set(CMAKE_CXX_STANDARD 17)