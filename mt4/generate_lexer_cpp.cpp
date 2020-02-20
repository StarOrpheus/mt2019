#include "generate_lexer_cpp.h"

#include "formatting.h"

#include <fstream>

constexpr auto part1 =
        "#include \"lexer.h\"\n"
        "\n"
        "#include <cassert>\n"
        "#include <regex>\n"
        "\n"
        "token_t::token_t(token_id_t id, std::string_view const& view)\n"
        "    : id(id), view(view)\n"
        "{}\n"
        "\n"
        "std::string_view token_t::get_view() const\n"
        "{\n"
        "    assert(id != token_id_t::END);\n"
        "    return view;\n"
        "}\n"
        "\n"
        "token_id_t token_t::get_id() const\n"
        "{\n"
        "    return id;\n"
        "}\n"
        "\n"
        "lexer::lexer(std::istream& istr)\n"
        "        : input(istr)\n"
        "{\n"
        "    buffer.push_back('$');\n"
        "    buffer.reserve(10000000);\n"
        "    tail = std::string_view(&buffer.back(), 0);\n"
        "}\n"
        "\n"
        "token_t lexer::get_current_tok()\n"
        "{\n"
        "    if (!current_tok)\n"
        "        return *(current_tok = next_token());\n"
        "    return *current_tok;\n"
        "}\n"
        "\n"
        "token_t lexer::next_token()\n"
        "{\n"
        "    do\n"
        "    {\n"
        "        next_token_impl();\n"
        "    }\n"
        "    while (is_skipped(current_tok->get_id()));\n"
        "\n"
        "    return *current_tok;\n"
        "}\n"
        "\n"
        "void lexer::next_token_impl()\n"
        "{\n"
        "    assert(!current_tok\n"
        "           || current_tok->get_id() != token_id_t::END);\n"
        "\n"
        "    if (tail.empty())\n"
        "    {\n"
        "        int c = input.get();\n"
        "        if (c == -1)\n"
        "        {\n"
        "            current_tok = token_t{token_id_t::END,\n"
        "                                  std::string_view(nullptr, 0)};\n"
        "            return;\n"
        "        }\n"
        "\n"
        "        buffer.push_back(c);\n"
        "        tail = std::string_view(&buffer.back(), 1);\n"
        "    }\n"
        "\n"
        "    while (true)\n"
        "    {\n"
        "        auto res = match_any();\n"
        "        if (res)\n"
        "        {\n"
        "            while (true)\n"
        "            {\n"
        "                auto res2 = match_any();\n"
        "                if (res2)\n"
        "                {\n"
        "                    res = res2;\n"
        "                    current_tok.emplace(*res2, tail);\n"
        "                }\n"
        "                else\n"
        "                    break;\n"
        "\n"
        "                int c = input.get();\n"
        "                if (c == -1)\n"
        "                    break;\n"
        "\n"
        "                buffer.push_back(c);\n"
        "                tail = std::string_view(&buffer.back() - tail.size(), tail.size() + 1);\n"
        "            }\n"
        "            tail = std::string_view (\n"
        "                    tail.data() + current_tok->get_view().size(),\n"
        "                    tail.size() - current_tok->get_view().size()\n"
        "                    );\n"
        "            return;\n"
        "        }\n"
        "\n"
        "        int c = input.get();\n"
        "        if (c == -1)\n"
        "        {\n"
        "            current_tok = token_t{token_id_t::END,\n"
        "                                  std::string_view(nullptr, 0)};\n"
        "            return;\n"
        "        }\n"
        "\n"
        "        buffer.push_back(c);\n"
        "        tail = std::string_view(&buffer.back() - tail.size(), tail.size() + 1);\n"
        "    }\n"
        "}\n"
        "\n"
        "std::optional<token_id_t> lexer::match_any()\n"
        "{\n"
        "    std::string tail_string(tail.cbegin(), tail.cend());\n"
        "\n";

static std::string escape(std::string const& e)
{
    std::string result;
    for (char c : e)
        if (c == '\\')
            result += "\\\\";
        else
            result += c;
    return result;
}

void generate_lexer_cpp(token_rule_list_t const& list, char const* fname)
{
    std::ofstream out(fname);
    out << part1 << std::endl;
    for (auto&& rule : list)
    {
        out << "    {\n";
        out << "        std::regex re(\"" << escape(rule.rule) << "\");\n";
        out << "        if (std::regex_match(tail_string, re))\n"
               "            return token_id_t::" << format_token(rule.name) << ";\n";
        out << "    }\n";
    }

    out << "\n"
           "    return {};\n"
           "}\n";

    out << "bool lexer::is_skipped(token_id_t id) const\n"
           "{\n"
           "    switch (id)\n"
           "    {\n";

    for (auto&& rule : list)
    {
        out << "    case token_id_t::" << format_token(rule.name)
            << ": return " << (rule.skip ? "true;\n" : "false;\n");
    }

    out << "    case token_id_t::END: return false;\n";

    out << "    }\n"
           "    assert(false && \"Non-reachable section expected!\");\n"
           "    return false;\n"
           "}\n";
}
