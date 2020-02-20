project(test0)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR})
add_library(lexer STATIC lexer.cpp)
add_library(parser STATIC parser.cpp)

add_executable(main main.cpp)
target_link_libraries(main parser lexer)
