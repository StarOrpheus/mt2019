#pragma once

#include "lexer.h"
#include <memory>
#include <vector>

struct parser_context
{
    virtual
    std::string get_text() const
    {
        std::string str;
        for (auto& tok : children)
            str += tok->get_text();
        return str;
    }


    std::vector<std::unique_ptr<parser_context>> children;
};

struct STATIC_context
        : public parser_context
{
    STATIC_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct EXTERN_context
        : public parser_context
{
    EXTERN_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct AUTO_context
        : public parser_context
{
    AUTO_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct REGISTER_context
        : public parser_context
{
    REGISTER_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct VOID_context
        : public parser_context
{
    VOID_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct CHAR_context
        : public parser_context
{
    CHAR_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct SHORT_context
        : public parser_context
{
    SHORT_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct INT_context
        : public parser_context
{
    INT_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct LONG_context
        : public parser_context
{
    LONG_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct FLOAT_context
        : public parser_context
{
    FLOAT_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct DOUBLE_context
        : public parser_context
{
    DOUBLE_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct SIGNED_context
        : public parser_context
{
    SIGNED_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct UNSIGNED_context
        : public parser_context
{
    UNSIGNED_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct VOLATILE_context
        : public parser_context
{
    VOLATILE_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct CONST_context
        : public parser_context
{
    CONST_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct IDENTIFIER_context
        : public parser_context
{
    IDENTIFIER_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct SEMI_context
        : public parser_context
{
    SEMI_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct POINTER_context
        : public parser_context
{
    POINTER_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct OPEN_PARANTHESIS_context
        : public parser_context
{
    OPEN_PARANTHESIS_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct CLOSE_PARANTHESIS_context
        : public parser_context
{
    CLOSE_PARANTHESIS_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct COMMA_context
        : public parser_context
{
    COMMA_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct EPS_context
        : public parser_context
{
    EPS_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct WHITESPACE_context
        : public parser_context
{
    WHITESPACE_context(token_t tok)
        : tok(std::move(tok))
    {};

    std::string get_text() const override
    {
        std::string result;
        result += tok.get_view();
        return result;
    }

    token_t tok;
};
struct storage_class_specifier_context
        : public parser_context
{};

struct type_specifier_context
        : public parser_context
{};

struct type_qualifier_context
        : public parser_context
{};

struct declaration_specifiers_context
        : public parser_context
{};

struct declaration_specifiers_continuation_context
        : public parser_context
{};

struct type_qualifier_list_context
        : public parser_context
{};

struct type_qualifier_list_continuation_context
        : public parser_context
{};

struct pointer_context
        : public parser_context
{};

struct pointer_continuation_context
        : public parser_context
{};

struct direct_declarator_context
        : public parser_context
{};

struct declarator_context
        : public parser_context
{};

struct declarator_list_context
        : public parser_context
{};

struct declarator_list_continuation_context
        : public parser_context
{};

struct declaration_context
        : public parser_context
{};

struct declaration_continuation_context
        : public parser_context
{};

std::unique_ptr<storage_class_specifier_context> parse_storage_class_specifier(lexer&);
std::unique_ptr<type_specifier_context> parse_type_specifier(lexer&);
std::unique_ptr<type_qualifier_context> parse_type_qualifier(lexer&);
std::unique_ptr<declaration_specifiers_context> parse_declaration_specifiers(lexer&);
std::unique_ptr<declaration_specifiers_continuation_context> parse_declaration_specifiers_continuation(lexer&);
std::unique_ptr<type_qualifier_list_context> parse_type_qualifier_list(lexer&);
std::unique_ptr<type_qualifier_list_continuation_context> parse_type_qualifier_list_continuation(lexer&);
std::unique_ptr<pointer_context> parse_pointer(lexer&);
std::unique_ptr<pointer_continuation_context> parse_pointer_continuation(lexer&);
std::unique_ptr<direct_declarator_context> parse_direct_declarator(lexer&);
std::unique_ptr<declarator_context> parse_declarator(lexer&);
std::unique_ptr<declarator_list_context> parse_declarator_list(lexer&);
std::unique_ptr<declarator_list_continuation_context> parse_declarator_list_continuation(lexer&);
std::unique_ptr<declaration_context> parse_declaration(lexer&);
std::unique_ptr<declaration_continuation_context> parse_declaration_continuation(lexer&);
