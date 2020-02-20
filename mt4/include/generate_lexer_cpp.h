#pragma once

#include "common.h"

void generate_lexer_cpp(token_rule_list_t const&,
                        char const* fname = "lexer.cpp");