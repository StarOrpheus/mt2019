#include "generate_parser_cpp.h"

#include "generator_context.h"

#include <fstream>

static inline
std::ostream& print_ptr(std::string const& rule_name, std::ostream& out)
{
    out << "std::unique_ptr<" << format_context(rule_name) << "> ";
    return out;
}

static inline
std::string extract_args(std::string const& name)
{
    auto pos = name.find('(');
    if (pos == std::string::npos)
        return "";

    auto result = name.substr(pos + 1);
    result.pop_back();
    return result;
}

void generate_parser_cpp(generator_context* ptr, char const* fname)
{
    std::ofstream out(fname);

    out << "#include \"parser.h\"\n";
    out << "#include <cassert>\n\n";

    for (auto&& rule : ptr->syntax_rules)
    {
        std::unordered_set<std::string> used_tokens;

        print_ptr(rule.name, out) << format_parser_func(rule.name) << "(lexer& lex";
        if (!rule.args.empty())
            out << ", " << rule.args;

        out << ")\n"
               "{\n"
                "    auto result = std::make_unique<"
            << format_context(rule.name) << ">();\n";

        out << "    auto cur_tok = lex.get_current_tok();\n";
        out << "    switch(cur_tok.get_id())\n"
               "    {\n";

        std::string follow_code = "break;";

        for (auto&& rhs : rule.rhs)
        {
            if (rhs.names_with_arguments.size() == 1
                && rhs.names_with_arguments[0] == "EPS")
            {
                follow_code = rhs.code + "\nbreak;";
                continue;
            }

            auto extracted = rhs.extract_names();
            auto first = ptr->calculate_first(extracted.begin(), extracted.end());
            for (auto&& token_rule : ptr->token_rules)
            {
                auto tok_name = format_token(token_rule.name);
                if (first.count(tok_name))
                {
                    out << "    case token_id_t::" << tok_name << ":\n";
                    assert(!used_tokens.count(tok_name));
                    used_tokens.insert(tok_name);
                }
            }
            out << "    {\n";

            int i = 0;
            for (auto& name : extracted)
            {
                if (ptr->is_token(name))
                {
                    out << "        result->children.emplace_back(std::make_unique<" << format_context(name) << ">(lex.get_current_tok()));\n";
                    out << "        lex.next_token();\n";
                }
                else
                {
                    out << "        result->children.emplace_back(" << format_parser_func(name) << "(lex";

                    auto args = extract_args(rhs.names_with_arguments[i]);
                    if (!args.empty())
                        out << ", " << args;
                    out << "));\n";
                }

                out << "        auto& " << name << i << " = *result->children.back();\n\n";
                ++i;
            }

            out << "        " << rhs.code << std::endl;

            out << "        break;\n";
            out << "    }\n";
        }

        for (auto&& tok_name : rule.follow)
        {
            if (!used_tokens.count(tok_name))
            {
                out << "    case token_id_t::" << tok_name << ": " << follow_code << "\n";
                used_tokens.insert(tok_name);
            }
        }

        for (auto&& token_rule : ptr->token_rules)
        {
            auto tok_name = format_token(token_rule.name);

            if (!used_tokens.count(tok_name))
                out << "    case token_id_t::" << tok_name << ": assert(false && \"Unexpected token!\");\n";
        }

        out << "    }\n\n";
        out << "    return std::move(result);\n";
        out << "}\n\n";
    }
}