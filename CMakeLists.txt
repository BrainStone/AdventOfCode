cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(aoc)

include(CheckCXXCompilerFlag)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(NATIVE_COMPILE_FLAG "/favor:blend")
else ()
    check_cxx_compiler_flag("-march=native" HAS_MARCH_NATIVE)
    if (HAS_MARCH_NATIVE)
        set(NATIVE_COMPILE_FLAG "-march=native")
    endif ()
endif ()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON" FORCE)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

add_subdirectory(2024)
