project(lab2)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(CMAKE_CXX_FLAGS "-pthread ${CMAKE_CXX_FLAGS}")
endif()

add_subdirectory(3rd-party)

include_directories(include)

add_library(parser STATIC lexer.cpp parser.cpp)

add_executable(parser_main parser_main.cpp)
target_link_libraries(parser_main parser)

add_executable(all_tests all_tests.cpp)
target_link_libraries(all_tests gtest parser)
