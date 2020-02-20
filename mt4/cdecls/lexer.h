#pragma once

#include <string_view>
#include <optional>
#include <vector>
#include <fstream>

enum class token_id_t
{
    TOKEN_STATIC,
    TOKEN_EXTERN,
    TOKEN_AUTO,
    TOKEN_REGISTER,
    TOKEN_VOID,
    TOKEN_CHAR,
    TOKEN_SHORT,
    TOKEN_INT,
    TOKEN_LONG,
    TOKEN_FLOAT,
    TOKEN_DOUBLE,
    TOKEN_SIGNED,
    TOKEN_UNSIGNED,
    TOKEN_VOLATILE,
    TOKEN_CONST,
    TOKEN_IDENTIFIER,
    TOKEN_SEMI,
    TOKEN_POINTER,
    TOKEN_OPEN_PARANTHESIS,
    TOKEN_CLOSE_PARANTHESIS,
    TOKEN_COMMA,
    TOKEN_EPS,
    TOKEN_WHITESPACE,
    END
};

struct token_t
{
    token_t(token_id_t id, std::string_view const& view);

    std::string_view get_view() const;
    token_id_t get_id() const;

private:
    token_id_t          id;
    std::string_view    view;
};


struct lexer
{
    explicit lexer(std::istream&);

    token_t get_current_tok();
    token_t next_token();

private:
    void next_token_impl();

    std::optional<token_id_t> match_any();

    bool is_skipped(token_id_t id) const;

private:
    std::istream&               input;
    std::vector<char>           buffer;
    std::string_view            tail;
    std::optional<token_t>      current_tok;
};


