project(arithmetica C)

enable_language(C)

if (UNIX)
add_library(
    arithmetica

    arithmetica.c
    
    linux/strlen.asm
    linux/truncate.asm
)
endif (UNIX)

if (WIN32)
add_library(
    arithmetica

    arithmetica.c
    
    windows/truncate.c
)
endif (WIN32)

target_include_directories(arithmetica PRIVATE "../basic_math_operations/src/library")