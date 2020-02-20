#pragma once

struct generator_context;

void generate_parser_cpp(generator_context* ptr,
                         char const* fname = "parser.cpp");