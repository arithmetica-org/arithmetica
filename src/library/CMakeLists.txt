project(arithmetica C)

enable_language(C)
enable_language(CXX)

if (UNIX)
add_library(
    arithmetica

    arithmetica.c
    arithmetica.cpp
    
    linux/strlen.asm
    linux/truncate.asm
)
endif (UNIX)

if (WIN32)
add_library(
    arithmetica

    arithmetica.c
    arithmetica.cpp
    
    windows/strlen.asm
    windows/truncate.asm
)
endif (WIN32)

target_include_directories(arithmetica PRIVATE "../basic_math_operations/src/library")