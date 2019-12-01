#pragma once

#include <memory>
#include <vector>
#include <optional>

#include "lexer.h"

struct ast_node;

using ast_ptr = std::unique_ptr<ast_node>;

enum class node_kind
{
    STORAGE_CLASS_SPECIFIER,
    TYPE_SPECIFIER,
    TYPE_QUALIFIER,
    TYPE_QUALIFIER_LIST,
    POINTER,
    DIRECT_DECLARATOR,
    DECLARATOR,
    DECLARATOR_LIST,
    DECLARATION_SPECIFIERS,
    DECLARATION
};

struct ast_node
{
    node_kind               kind;
    std::optional<token_t>  data;
    std::vector<ast_ptr>    args;
};

ast_ptr parse(std::istream& input);

std::string to_string(ast_ptr const& ast);

std::string to_dot_repr(ast_ptr const& ast);