project(arithmetica C)

enable_language(C)
enable_language(CXX)

if (UNIX)
set(linux_sources
arithmetica.c
arithmetica.cpp

linux/strlen_arithmetica.asm
linux/truncate.asm
)
add_library(arithmetica STATIC ${linux_sources})
add_library(arithmetica_sh SHARED ${linux_sources})
set_target_properties(arithmetica_sh PROPERTIES OUTPUT_NAME "arithmetica")
target_include_directories(arithmetica_sh PRIVATE "../basic_math_operations/src/library")
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
