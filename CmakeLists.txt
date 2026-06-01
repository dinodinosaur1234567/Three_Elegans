cmake_minimum_required(VERSION 3.16)

project(Three_Elegans C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# -----------------------------
# SOURCE FILES (engine core)
# -----------------------------
file(GLOB_RECURSE CORE_SOURCES
    src/*.c
)

# -----------------------------
# BUILD THE RUNTIME LIBRARY
# -----------------------------
add_library(Three_Elegans SHARED ${CORE_SOURCES})

# Public headers
target_include_directories(Three_Elegans PUBLIC include)

# -----------------------------
# TEST / DEMO EXECUTABLE
# -----------------------------
add_executable(demo examples/demo.c)

target_link_libraries(demo Three_Elegans)