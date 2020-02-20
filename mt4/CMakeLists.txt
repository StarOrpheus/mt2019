project(mt4)

cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)

#include directory with Antlr sources!
#include_directories(/home/Zahar.Koval/Devel/antlr/runtime/src/)
include_directories(include)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(CMAKE_CXX_FLAGS "-pthread ${CMAKE_CXX_FLAGS}")
endif()

add_library(lexer STATIC GrammarSchemeLexer.cpp)
target_link_libraries(lexer antlr4-runtime)
add_library(parser STATIC GrammarSchemeParser.cpp)
target_link_libraries(parser antlr4-runtime)

add_library(formatting STATIC formatting.cpp)
add_library(lexer_h_generator STATIC generate_lexer_h.cpp)
target_link_libraries(lexer_h_generator formatting)
add_library(lexer_cpp_generator STATIC generate_lexer_cpp.cpp)
target_link_libraries(lexer_cpp_generator formatting)
add_library(parser_h_generator STATIC generate_parser_h.cpp)
target_link_libraries(parser_h_generator formatting)
add_library(parser_cpp_generator STATIC generate_parser_cpp.cpp)
target_link_libraries(parser_cpp_generator formatting)

add_executable(main main.cpp)
target_link_libraries(main antlr4-runtime lexer parser
        lexer_h_generator lexer_cpp_generator
        parser_h_generator parser_cpp_generator)

add_library(lexer_sample lexer_sample.cpp lexer_sample.h)
