#include <unordered_map>
#include "lexer.h"


lexer::lexer(std::istream& inp)
    : input(inp)
{}

token_t& lexer::get_current()
{
    return  current;
}

token_t& lexer::read_token()
{
    static const std::unordered_map<std::string, storage_class_specifier>
            str_to_storage_class_specifier =
            {
                    {"extern", storage_class_specifier::EXTERN},
                    {"static", storage_class_specifier::STATIC},
                    {"auto", storage_class_specifier::AUTO},
                    {"register", storage_class_specifier::REGISTER}
            };

    static const std::unordered_map<std::string, type_specifier>
            str_to_type_specifier =
            {
                    {"void", type_specifier::VOID},
                    {"char", type_specifier::CHAR},
                    {"short", type_specifier::SHORT},
                    {"int", type_specifier::INT},
                    {"long", type_specifier::LONG},
                    {"float", type_specifier::FLOAT},
                    {"double", type_specifier::DOUBLE},
                    {"signed", type_specifier::SIGNED},
                    {"unsigned", type_specifier::UNSIGNED}
            };

    static const std::unordered_map<std::string, type_qualifier>
            str_to_type_qualifier =
            {
                    {"const", type_qualifier::CONST},
                    {"volatile", type_qualifier::VOLATILE},
            };

    static const std::unordered_map<char, special_symbols>
            char_to_spec_symbol =
            {
                    {'*', special_symbols::ASTERISK},
                    {';', special_symbols::SEMICOLON},
                    {'(', special_symbols::OPEN_PARANTHESIS},
                    {')', special_symbols::CLOSE_PARANTHESIS},
                    {',', special_symbols::COMMA},
            };

    if (tail.empty())
    {
        buf.clear();
        if (input >> buf)
            tail = std::string_view{buf.data(), buf.size()};
        else
            return current = special_symbols::END;
    }

    size_t i = 0;
    for (; i < tail.size(); ++i)
    {
        auto it = char_to_spec_symbol.find(tail[i]);
        if (it == char_to_spec_symbol.end())
            continue;

        if (i == 0)
        {
            tail = std::string_view {tail.data() + 1, tail.size() - 1};
            return current = it->second;
        }


        break;
    }

    std::string cur_str{tail.data(), i};
    tail = std::string_view{tail.data() + i, tail.size() - i};

    {
        auto it = str_to_storage_class_specifier.find(cur_str);
        if (it != str_to_storage_class_specifier.end())
            return current = it->second;
    }
    {
        auto it = str_to_type_specifier.find(cur_str);
        if (it != str_to_type_specifier.end())
            return current = it->second;
    }
    {
        auto it = str_to_type_qualifier.find(cur_str);
        if (it != str_to_type_qualifier.end())
            return current = it->second;
    }

    return current = std::move(cur_str);
}