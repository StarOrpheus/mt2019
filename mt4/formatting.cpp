#include "formatting.h"

std::string format_token(std::string const& rule_name)
{
    std::string result = "TOKEN_";
    for (char c : rule_name)
        result += std::toupper(c);
    return result;
}

std::string format_context(std::string const& rule_name)
{
    return rule_name + "_context";
}

std::string format_parser_func(std::string const& rule_name)
{
    return "parse_" + rule_name;
}
