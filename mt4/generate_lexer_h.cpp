#include "generate_lexer_h.h"

#include "formatting.h"

#include <fstream>

constexpr static auto part1 =
        "#pragma once\n"
        "\n"
        "#include <string_view>\n"
        "#include <optional>\n"
        "#include <vector>\n"
        "#include <fstream>\n"
        "\n"
        "enum class token_id_t\n"
        "{\n"
        ;

constexpr static auto part2 =
        "    END\n"
        "};\n"
        "\n"
        "struct token_t\n"
        "{\n"
        "    token_t(token_id_t id, std::string_view const& view);\n"
        "\n"
        "    std::string_view get_view() const;\n"
        "    token_id_t get_id() const;\n"
        "\n"
        "private:\n"
        "    token_id_t          id;\n"
        "    std::string_view    view;\n"
        "};\n"
        "\n"
        "\n"
        "struct lexer\n"
        "{\n"
        "    explicit lexer(std::istream&);\n"
        "\n"
        "    token_t get_current_tok();\n"
        "    token_t next_token();\n"
        "\n"
        "private:\n"
        "    void next_token_impl();\n"
        "\n"
        "    std::optional<token_id_t> match_any();\n"
        "\n"
        "    bool is_skipped(token_id_t id) const;\n"
        "\n"
        "private:\n"
        "    std::istream&               input;\n"
        "    std::vector<char>           buffer;\n"
        "    std::string_view            tail;\n"
        "    std::optional<token_t>      current_tok;\n"
        "};\n\n"
        ;

void generate_lexer_h(token_rule_list_t const& list, char const* fname)
{
    std::ofstream output(fname);
    output << part1;
    for (auto&& rule : list)
        output << "    " << format_token(rule.name) << ",\n";
    output << part2 << std::endl;
}
