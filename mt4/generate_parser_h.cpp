#include "generate_parser_h.h"

#include "generator_context.h"


#include <fstream>

void generate_parser_h(generator_context* ptr, char const* fname)
{
    std::ofstream out(fname);
    out << "#pragma once\n"
           "\n"
           "#include \"lexer.h\"\n"
           "#include <memory>\n"
           "#include <vector>\n"
           "\n";

    out << ptr->header << "\n\n"
           "struct parser_context\n"
           "{\n"
           "    virtual\n"
           "    std::string get_text() const\n"
           "    {\n"
           "        std::string str;\n"
           "        for (auto& tok : children)\n"
           "            str += tok->get_text();\n"
           "        return str;\n"
           "    }\n\n";

    for (auto&& decl_line : ptr->decl_fields)
        out << "    " << decl_line << '\n';

    out << "\n"
           "    std::vector<std::unique_ptr<parser_context>> children;\n"
           "};\n\n";

    for (auto&& rule : ptr->token_rules)
    {
        out << "struct " << format_context(rule.name) << "\n";
        out << "        : public parser_context\n"
               "{\n"
               "    " << format_context(rule.name) << "(token_t tok)\n"
               "        : tok(std::move(tok))\n"
               "    {};\n\n"
               "    std::string get_text() const override\n"
               "    {\n"
               "        std::string result;\n"
               "        result += tok.get_view();\n"
               "        return result;\n"
               "    }\n"
               "\n"
               "    token_t tok;\n"
               "};\n";

    }

    for (auto&& rule : ptr->syntax_rules)
    {
        out << "struct " << format_context(rule.name) << "\n";
        out << "        : public parser_context\n"
               "{};\n\n";
    }

    for (auto&& rule : ptr->syntax_rules)
    {
        out << "std::unique_ptr<" << format_context(rule.name) << "> "
            << format_parser_func(rule.name) << "(lexer&";
        if (!rule.args.empty())
            out << ", " << rule.args;
        out << ");\n";
    }
}