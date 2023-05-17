cmake_minimum_required(VERSION 3.16)

project(tests CXX)

enable_language(CXX)

add_executable(tests test.cpp)

target_link_libraries(tests arithmetica)
target_link_libraries(tests basic_math_operations)
target_link_libraries(tests gmp)
target_link_libraries(tests curl)

target_include_directories(tests PRIVATE "../library")