#include "lexer_sample.h"

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
        tail = std::string_view(tail.data(), tail.size() + 1);
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
                tail = std::string_view(tail.data(), tail.size() + 1);
            }

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
        tail = std::string_view(tail.data(), tail.size() + 1);
    }
}

std::optional<token_id_t> lexer::match_any()
{
    std::string tail_string(tail.cbegin(), tail.cend());

    {
        std::regex re("keker");
        if (std::regex_match(tail_string, re))
            return {};
    }
    // ...

    return {};
}

bool lexer::is_skipped(token_id_t id) const
{
    switch (id)
    {
    }
    assert(false && "Non-reachable section expected!");
    return false;
}

