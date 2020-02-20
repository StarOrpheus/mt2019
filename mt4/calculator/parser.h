#pragma once

#include "lexer.h"
#include <memory>
#include <vector>


    #include "pw.h"


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

    int value;

    std::vector<std::unique_ptr<parser_context>> children;
};

struct DIVISION_context
        : public parser_context
{
    DIVISION_context(token_t tok)
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
struct MINUS_context
        : public parser_context
{
    MINUS_context(token_t tok)
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
struct PLUS_context
        : public parser_context
{
    PLUS_context(token_t tok)
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
struct MULTIPLICATION_context
        : public parser_context
{
    MULTIPLICATION_context(token_t tok)
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
struct NUMBER_context
        : public parser_context
{
    NUMBER_context(token_t tok)
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
struct OPEN_context
        : public parser_context
{
    OPEN_context(token_t tok)
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
struct CLOSE_context
        : public parser_context
{
    CLOSE_context(token_t tok)
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
struct POWER_context
        : public parser_context
{
    POWER_context(token_t tok)
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
struct expr_context
        : public parser_context
{};

struct expr_rhs_context
        : public parser_context
{};

struct second_context
        : public parser_context
{};

struct second_rhs_context
        : public parser_context
{};

struct pw_context
        : public parser_context
{};

struct pw_rhs_context
        : public parser_context
{};

struct unar_context
        : public parser_context
{};

struct first_context
        : public parser_context
{};

std::unique_ptr<expr_context> parse_expr(lexer&);
std::unique_ptr<expr_rhs_context> parse_expr_rhs(lexer&, int lhs );
std::unique_ptr<second_context> parse_second(lexer&);
std::unique_ptr<second_rhs_context> parse_second_rhs(lexer&, int lhs );
std::unique_ptr<pw_context> parse_pw(lexer&);
std::unique_ptr<pw_rhs_context> parse_pw_rhs(lexer&, int lhs );
std::unique_ptr<unar_context> parse_unar(lexer&);
std::unique_ptr<first_context> parse_first(lexer&);
