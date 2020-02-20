#include "parser.h"

#include <sstream>
#include <iostream>

int main()
{
    std::stringstream ss("int const volatile * const * f;");

    lexer lex(ss);

    auto tree = parse_declaration(lex);
    std::cout << tree->get_text() << std::endl;
}