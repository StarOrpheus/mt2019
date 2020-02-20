#include "lexer.h"

#include <cassert>
#include <regex>

token_t::token_t(token_id_t id, std::string_view const& view)
    : id(id), view(view)
{}

std::string_view token_t::get_view() const
{
    assert(id != token_id_t::END);
    return view;
}

token_id_t token_t::get_id() const
{
    return id;
}

lexer::lexer(std::istream& istr)
        : input(istr)
{
    buffer.push_back('$');
    buffer.reserve(10000000);
    tail = std::string_view(&buffer.back(), 0);
}

token_t lexer::get_current_tok()
{
    if (!current_tok)
        return *(current_tok = next_token());
    return *current_tok;
}

token_t lexer::next_token()
{
    do
    {
        next_token_impl();
    }
    while (is_skipped(current_tok->get_id()));

    return *current_tok;
}

void lexer::next_token_impl()
{
    assert(!current_tok
           || current_tok->get_id() != token_id_t::END);

    if (tail.empty())
    {
        int c = input.get();
        if (c == -1)
        {
            current_tok = token_t{token_id_t::END,
                                  std::string_view(nullptr, 0)};
            return;
        }

        buffer.push_back(c);
        tail = std::string_view(&buffer.back(), 1);
    }

    while (true)
    {
        auto res = match_any();
        if (res)
        {
            while (true)
            {
                auto res2 = match_any();
                if (res2)
                {
                    res = res2;
                    current_tok.emplace(*res2, tail);
                }
                else
                    break;

                int c = input.get();
                if (c == -1)
                    break;

                buffer.push_back(c);
                tail = std::string_view(&buffer.back() - tail.size(), tail.size() + 1);
            }
            tail = std::string_view (
                    tail.data() + current_tok->get_view().size(),
                    tail.size() - current_tok->get_view().size()
                    );
            return;
        }

        int c = input.get();
        if (c == -1)
        {
            current_tok = token_t{token_id_t::END,
                                  std::string_view(nullptr, 0)};
            return;
        }

        buffer.push_back(c);
        tail = std::string_view(&buffer.back() - tail.size(), tail.size() + 1);
    }
}

std::optional<token_id_t> lexer::match_any()
{
    std::string tail_string(tail.cbegin(), tail.cend());


    {
        std::regex re("static");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_STATIC;
    }
    {
        std::regex re("extern");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_EXTERN;
    }
    {
        std::regex re("auto");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_AUTO;
    }
    {
        std::regex re("register");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_REGISTER;
    }
    {
        std::regex re("void");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_VOID;
    }
    {
        std::regex re("char");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_CHAR;
    }
    {
        std::regex re("short");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_SHORT;
    }
    {
        std::regex re("int");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_INT;
    }
    {
        std::regex re("long");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_LONG;
    }
    {
        std::regex re("float");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_FLOAT;
    }
    {
        std::regex re("double");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_DOUBLE;
    }
    {
        std::regex re("signed");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_SIGNED;
    }
    {
        std::regex re("unsigned");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_UNSIGNED;
    }
    {
        std::regex re("volatile");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_VOLATILE;
    }
    {
        std::regex re("const");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_CONST;
    }
    {
        std::regex re("[a-zA-Z_]+[a-zA-Z_0-9]*");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_IDENTIFIER;
    }
    {
        std::regex re(";");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_SEMI;
    }
    {
        std::regex re("\\*");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_POINTER;
    }
    {
        std::regex re("\\(");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_OPEN_PARANTHESIS;
    }
    {
        std::regex re("\\)");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_CLOSE_PARANTHESIS;
    }
    {
        std::regex re(",");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_COMMA;
    }
    {
        std::regex re("EPS");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_EPS;
    }
    {
        std::regex re("[ \\t\\r\\n]");
        if (std::regex_match(tail_string, re))
            return token_id_t::TOKEN_WHITESPACE;
    }

    return {};
}
bool lexer::is_skipped(token_id_t id) const
{
    switch (id)
    {
    case token_id_t::TOKEN_STATIC: return false;
    case token_id_t::TOKEN_EXTERN: return false;
    case token_id_t::TOKEN_AUTO: return false;
    case token_id_t::TOKEN_REGISTER: return false;
    case token_id_t::TOKEN_VOID: return false;
    case token_id_t::TOKEN_CHAR: return false;
    case token_id_t::TOKEN_SHORT: return false;
    case token_id_t::TOKEN_INT: return false;
    case token_id_t::TOKEN_LONG: return false;
    case token_id_t::TOKEN_FLOAT: return false;
    case token_id_t::TOKEN_DOUBLE: return false;
    case token_id_t::TOKEN_SIGNED: return false;
    case token_id_t::TOKEN_UNSIGNED: return false;
    case token_id_t::TOKEN_VOLATILE: return false;
    case token_id_t::TOKEN_CONST: return false;
    case token_id_t::TOKEN_IDENTIFIER: return false;
    case token_id_t::TOKEN_SEMI: return false;
    case token_id_t::TOKEN_POINTER: return false;
    case token_id_t::TOKEN_OPEN_PARANTHESIS: return false;
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: return false;
    case token_id_t::TOKEN_COMMA: return false;
    case token_id_t::TOKEN_EPS: return false;
    case token_id_t::TOKEN_WHITESPACE: return true;
    case token_id_t::END: return false;
    }
    assert(false && "Non-reachable section expected!");
    return false;
}
