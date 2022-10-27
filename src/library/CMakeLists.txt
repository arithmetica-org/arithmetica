project(arithmetica C)

enable_language(C)

add_library(
    arithmetica

    arithmetica.c
)

target_include_directories(arithmetica PRIVATE "../basic_math_operations/src/library")