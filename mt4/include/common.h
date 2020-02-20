#pragma once

#include <vector>
#include <string>
#include <unordered_set>

struct token_rule_t
{
    bool            skip{false};
    std::string     name;
    std::string     rule;
    std::string     code;
};

using token_rule_list_t = std::vector<token_rule_t>;

struct syntax_rule_t
{
    using rules_set_t = std::unordered_set<std::string>;

    struct rule_rhs_t
    {
        std::vector<std::string> extract_names() const
        {
            std::vector<std::string> result;
            for (auto&& str : names_with_arguments)
            {
                auto pos = str.find('(');
                if (pos == std::string::npos)
                    result.push_back(str);
                else
                    result.emplace_back(str.substr(0, pos));
            }
            return result;
        }

        std::vector<std::string>    names_with_arguments;
        std::string                 code;
    };

    std::string             name;
    std::string             args;
    std::vector<rule_rhs_t> rhs;
    rules_set_t             first;
    rules_set_t             follow;
};

