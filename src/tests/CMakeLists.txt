cmake_minimum_required(VERSION 3.16)

project(tests CXX)

enable_language(CXX)

add_executable(tests test.cpp)

target_link_libraries(tests arithmetica)
target_link_libraries(tests basic_math_operations)

target_include_directories(tests PRIVATE "../library")

add_executable(tests2 test2.cpp)
target_link_libraries(tests2 arithmetica)
target_link_libraries(tests2 basic_math_operations)
target_include_directories(tests2 PRIVATE "../library")