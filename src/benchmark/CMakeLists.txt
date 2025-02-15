cmake_minimum_required(VERSION 3.16)

project(benchmark CXX)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(benchmark benchmark.cpp)

target_link_libraries(benchmark arithmetica)
target_link_libraries(benchmark basic_math_operations)
target_link_libraries(benchmark curl)

target_include_directories(benchmark PRIVATE "../library")
target_include_directories(benchmark PRIVATE "../tests")
if (APPLE)
    target_include_directories(benchmark PRIVATE "/opt/homebrew/include")
endif()