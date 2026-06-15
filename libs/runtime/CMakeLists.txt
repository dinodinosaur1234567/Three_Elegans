cmake_minimum_required(VERSION 3.16)
project(Three_Elegans C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE LIB_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.c
)

add_library(Three_Elegans STATIC ${LIB_SOURCES})

target_include_directories(Three_Elegans PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

add_executable(demo examples/demo.c)

target_link_libraries(demo PRIVATE Three_Elegans)

set_target_properties(Three_Elegans PROPERTIES
    PREFIX ""
)