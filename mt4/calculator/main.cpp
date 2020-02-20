#include "parser.h"

#include <sstream>
#include <iostream>

int main()
{
    std::string s;
    while (std::cin >> s)
    {
        std::stringstream ss{s};

        lexer lex(ss);

        auto tree = parse_expr(lex);
        std::cout << tree->get_text() << " = " << tree->value << std::endl;
    }

}