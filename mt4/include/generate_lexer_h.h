#pragma once

#include "common.h"

void generate_lexer_h(token_rule_list_t const&,
                      char const* fname = "lexer.h");