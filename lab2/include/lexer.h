#pragma once

#include <istream>
#include <variant>
#include <type_traits>

enum class storage_class_specifier
{
    EXTERN,
    STATIC,
    AUTO,
    REGISTER,
};

enum class type_specifier
{
    VOID,
    CHAR,
    SHORT,
    INT,
    LONG,
    FLOAT,
    DOUBLE,
    SIGNED,
    UNSIGNED,
};

enum class type_qualifier
{
    CONST,
    VOLATILE
};

enum class special_symbols
{
    ASTERISK,
    SEMICOLON,
    OPEN_PARANTHESIS,
    CLOSE_PARANTHESIS,
    COMMA,
    END,
};

using token_t = std::variant<storage_class_specifier, type_specifier, type_qualifier, std::string, special_symbols>;

struct lexer
{
    explicit lexer(std::istream&);

    token_t& get_current();
    token_t& read_token();

private:
    std::istream&       input;
    std::string         buf;
    std::string_view    tail;
    token_t             current;
};