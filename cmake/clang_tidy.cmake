# cmake/clang_tidy.cmake

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_CLANG_TIDY "Enable clang-tidy static analysis" ON)

if (ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if (CLANG_TIDY_EXE)
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        set(CMAKE_CXX_CLANG_TIDY
                ${CLANG_TIDY_EXE}
                -format-style=file
                -p=${CMAKE_BINARY_DIR}
        )
    else ()
        message(WARNING "clang-tidy not found!")
    endif ()
endif ()
