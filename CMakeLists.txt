cmake_minimum_required(VERSION 3.16.3)
project(c-testing)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options("$<$<CONFIG:RELEASE>:-std=c11;-Werror;-Wextra;-Wall;-pedantic;-O3;>")
add_compile_options("$<$<CONFIG:DEBUG>:-std=c11;-Werror;-Wextra;-Wall;-pedantic;-g;>")

add_subdirectory(deps)
include(cmake/c_testing.cmake)
enable_testing()

include(c_verify)
include(c_verify_clang_format)
include(c_verify_clang_tidy)
enable_c_verify()
enable_c_verify_clang_format()
enable_c_verify_clang_tidy()

add_subdirectory(source)
add_subdirectory(unit-tests)
