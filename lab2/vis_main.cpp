#include <iostream>
#include <fstream>
#include <filesystem>

#include "parser.h"

int main()
{
    constexpr auto fname = "output.dot";

    auto ast = parse(std::cin);
    std::cout << to_string(ast) << std::endl;

    std::ofstream out(fname);
    out << to_dot_repr(ast) << std::endl;
    std::cout << "Dot file written into " << std::filesystem::absolute(fname);
}
