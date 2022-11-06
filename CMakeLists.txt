project(arithmetica C)

add_subdirectory(src/library)

option(ENABLE_TESTS "Build tests" ON)

if (ENABLE_TESTS)
    add_subdirectory(src/basic_math_operations/src/library)
    add_subdirectory(src/tests)
endif()