#pragma once

#include "formatting.h"

#include <unordered_map>
#include <cassert>
#include <common.h>

struct generator_context
{
    using name_to_token_rule_t = std::unordered_map<std::string, token_rule_t*>;
    using name_to_syntax_rule_t = std::unordered_map<std::string, syntax_rule_t*>;

    template<typename ForwardIt>
    std::unordered_set<std::string>
    calculate_first(ForwardIt&& start, ForwardIt&& last)
    {
        std::unordered_set<std::string> result;
        for (; start != last; ++start)
        {
            std::string const& name = *start;

            auto it1 = name_to_token_rule.find(name);
            if (it1 != name_to_token_rule.end())
            {
                size_t last = result.size();
                result.emplace(format_token(it1->second->name));
                break;
            }

            auto it2 = name_to_syntax_rule.find(name);
            assert(it2 != name_to_syntax_rule.end());

            result.insert(it2->second->first.begin(), it2->second->first.end());

            if (!it2->second->first.count("EPS"))
                break;
        }

        return result;
    }

    bool is_token(std::string const& name)
    {
        auto it = name_to_token_rule.find(name);
        return it != name_to_token_rule.end();
    }

    name_to_token_rule_t        name_to_token_rule;
    name_to_syntax_rule_t       name_to_syntax_rule;
    std::vector<token_rule_t>   token_rules;
    std::vector<syntax_rule_t>  syntax_rules;
    std::vector<std::string>    decl_fields;
    std::string                 header;
};
