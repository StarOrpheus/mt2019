#include "parser.h"
#include <cassert>

std::unique_ptr<expr_context> parse_expr(lexer& lex)
{
    auto result = std::make_unique<expr_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_MINUS:
    case token_id_t::TOKEN_NUMBER:
    case token_id_t::TOKEN_OPEN:
    {
        result->children.emplace_back(parse_second(lex));
        auto& second0 = *result->children.back();

        result->children.emplace_back(parse_expr_rhs(lex, second0.value));
        auto& expr_rhs1 = *result->children.back();

        {result->value = expr_rhs1.value; }
        break;
    }
    case token_id_t::TOKEN_CLOSE: {result->value = 0; }
break;
    case token_id_t::END: {result->value = 0; }
break;
    case token_id_t::TOKEN_DIVISION: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_PLUS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_MULTIPLICATION: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_POWER: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<expr_rhs_context> parse_expr_rhs(lexer& lex, int lhs )
{
    auto result = std::make_unique<expr_rhs_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_PLUS:
    {
        result->children.emplace_back(std::make_unique<PLUS_context>(lex.get_current_tok()));
        lex.next_token();
        auto& PLUS0 = *result->children.back();

        result->children.emplace_back(parse_second(lex));
        auto& second1 = *result->children.back();

        result->children.emplace_back(parse_expr_rhs(lex, lhs + second1.value));
        auto& expr_rhs2 = *result->children.back();

        {result->value = expr_rhs2.value;}
        break;
    }
    case token_id_t::TOKEN_MINUS:
    {
        result->children.emplace_back(std::make_unique<MINUS_context>(lex.get_current_tok()));
        lex.next_token();
        auto& MINUS0 = *result->children.back();

        result->children.emplace_back(parse_second(lex));
        auto& second1 = *result->children.back();

        result->children.emplace_back(parse_expr_rhs(lex, lhs - second1.value));
        auto& expr_rhs2 = *result->children.back();

        {result->value = expr_rhs2.value;}
        break;
    }
    case token_id_t::TOKEN_CLOSE: {result->value = lhs;}
break;
    case token_id_t::END: {result->value = lhs;}
break;
    case token_id_t::TOKEN_DIVISION: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_MULTIPLICATION: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_NUMBER: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_OPEN: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_POWER: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<second_context> parse_second(lexer& lex)
{
    auto result = std::make_unique<second_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_MINUS:
    case token_id_t::TOKEN_NUMBER:
    case token_id_t::TOKEN_OPEN:
    {
        result->children.emplace_back(parse_pw(lex));
        auto& pw0 = *result->children.back();

        result->children.emplace_back(parse_second_rhs(lex, pw0.value));
        auto& second_rhs1 = *result->children.back();

        {result->value = second_rhs1.value;}
        break;
    }
    case token_id_t::TOKEN_CLOSE: break;
    case token_id_t::TOKEN_PLUS: break;
    case token_id_t::END: break;
    case token_id_t::TOKEN_DIVISION: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_MULTIPLICATION: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_POWER: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<second_rhs_context> parse_second_rhs(lexer& lex, int lhs )
{
    auto result = std::make_unique<second_rhs_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_MULTIPLICATION:
    {
        result->children.emplace_back(std::make_unique<MULTIPLICATION_context>(lex.get_current_tok()));
        lex.next_token();
        auto& MULTIPLICATION0 = *result->children.back();

        result->children.emplace_back(parse_pw(lex));
        auto& pw1 = *result->children.back();

        result->children.emplace_back(parse_second_rhs(lex, lhs * pw1.value));
        auto& second_rhs2 = *result->children.back();

        {result->value = second_rhs2.value;}
        break;
    }
    case token_id_t::TOKEN_DIVISION:
    {
        result->children.emplace_back(std::make_unique<DIVISION_context>(lex.get_current_tok()));
        lex.next_token();
        auto& DIVISION0 = *result->children.back();

        result->children.emplace_back(parse_pw(lex));
        auto& pw1 = *result->children.back();

        result->children.emplace_back(parse_second_rhs(lex, lhs / pw1.value));
        auto& second_rhs2 = *result->children.back();

        {result->value = pw1.value;}
        break;
    }
    case token_id_t::TOKEN_CLOSE: {result->value = lhs;}
break;
    case token_id_t::END: {result->value = lhs;}
break;
    case token_id_t::TOKEN_MINUS: {result->value = lhs;}
break;
    case token_id_t::TOKEN_PLUS: {result->value = lhs;}
break;
    case token_id_t::TOKEN_NUMBER: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_OPEN: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_POWER: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<pw_context> parse_pw(lexer& lex)
{
    auto result = std::make_unique<pw_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_MINUS:
    case token_id_t::TOKEN_NUMBER:
    case token_id_t::TOKEN_OPEN:
    {
        result->children.emplace_back(parse_unar(lex));
        auto& unar0 = *result->children.back();

        result->children.emplace_back(parse_pw_rhs(lex, unar0.value));
        auto& pw_rhs1 = *result->children.back();

        { result->value = pw_rhs1.value; }
        break;
    }
    case token_id_t::TOKEN_CLOSE: break;
    case token_id_t::TOKEN_PLUS: break;
    case token_id_t::END: break;
    case token_id_t::TOKEN_DIVISION: break;
    case token_id_t::TOKEN_MULTIPLICATION: break;
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_POWER: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<pw_rhs_context> parse_pw_rhs(lexer& lex, int lhs )
{
    auto result = std::make_unique<pw_rhs_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_POWER:
    {
        result->children.emplace_back(std::make_unique<POWER_context>(lex.get_current_tok()));
        lex.next_token();
        auto& POWER0 = *result->children.back();

        result->children.emplace_back(parse_unar(lex));
        auto& unar1 = *result->children.back();

        result->children.emplace_back(parse_pw_rhs(lex, unar1.value));
        auto& pw_rhs2 = *result->children.back();

        {result->value = pw(lhs, pw_rhs2.value);}
        break;
    }
    case token_id_t::TOKEN_MINUS: {result->value = lhs;}
break;
    case token_id_t::TOKEN_MULTIPLICATION: {result->value = lhs;}
break;
    case token_id_t::END: {result->value = lhs;}
break;
    case token_id_t::TOKEN_CLOSE: {result->value = lhs;}
break;
    case token_id_t::TOKEN_PLUS: {result->value = lhs;}
break;
    case token_id_t::TOKEN_DIVISION: {result->value = lhs;}
break;
    case token_id_t::TOKEN_NUMBER: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_OPEN: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<unar_context> parse_unar(lexer& lex)
{
    auto result = std::make_unique<unar_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_MINUS:
    {
        result->children.emplace_back(std::make_unique<MINUS_context>(lex.get_current_tok()));
        lex.next_token();
        auto& MINUS0 = *result->children.back();

        result->children.emplace_back(parse_first(lex));
        auto& first1 = *result->children.back();

        { result->value = -(first1.value); }
        break;
    }
    case token_id_t::TOKEN_NUMBER:
    case token_id_t::TOKEN_OPEN:
    {
        result->children.emplace_back(parse_first(lex));
        auto& first0 = *result->children.back();

        { result->value = first0.value; }
        break;
    }
    case token_id_t::TOKEN_CLOSE: break;
    case token_id_t::TOKEN_POWER: break;
    case token_id_t::TOKEN_PLUS: break;
    case token_id_t::END: break;
    case token_id_t::TOKEN_DIVISION: break;
    case token_id_t::TOKEN_MULTIPLICATION: break;
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<first_context> parse_first(lexer& lex)
{
    auto result = std::make_unique<first_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_NUMBER:
    {
        result->children.emplace_back(std::make_unique<NUMBER_context>(lex.get_current_tok()));
        lex.next_token();
        auto& NUMBER0 = *result->children.back();

        {
        result->value = 0;
        for (auto c : NUMBER0.get_text())
            assert(c >= '0' && c <= '9' && "Unexpected char in the NUMBER rule!");
        for (auto c : NUMBER0.get_text())
            result->value = (result->value * 10) + (c - '0');
    }
        break;
    }
    case token_id_t::TOKEN_OPEN:
    {
        result->children.emplace_back(std::make_unique<OPEN_context>(lex.get_current_tok()));
        lex.next_token();
        auto& OPEN0 = *result->children.back();

        result->children.emplace_back(parse_expr(lex));
        auto& expr1 = *result->children.back();

        result->children.emplace_back(std::make_unique<CLOSE_context>(lex.get_current_tok()));
        lex.next_token();
        auto& CLOSE2 = *result->children.back();

        {result->value = expr1.value; }
        break;
    }
    case token_id_t::TOKEN_CLOSE: break;
    case token_id_t::TOKEN_MULTIPLICATION: break;
    case token_id_t::TOKEN_MINUS: break;
    case token_id_t::TOKEN_DIVISION: break;
    case token_id_t::END: break;
    case token_id_t::TOKEN_PLUS: break;
    case token_id_t::TOKEN_POWER: break;
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

