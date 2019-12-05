#include "3rd-party/gtest/gtest.h"

#include "parser.h"

template<typename Arg>
void assert_eq(token_t& tok, Arg&& arg)
{
    assert(std::get<Arg>(tok) == arg);
}

TEST(lexer, storage_class_specifier_tokens)
{
    std::stringstream ss("extern static auto register");
    lexer lex(ss);

    assert_eq(lex.read_token(), storage_class_specifier::EXTERN);
    assert_eq(lex.read_token(), storage_class_specifier::STATIC);
    assert_eq(lex.read_token(), storage_class_specifier::AUTO);
    assert_eq(lex.read_token(), storage_class_specifier::REGISTER);
    assert_eq(lex.read_token(), special_symbols::END);
}

TEST(lexer, type_specifier_tokens)
{
    std::stringstream ss("void char short int long float double signed unsigned");
    lexer lex(ss);

    assert_eq(lex.read_token(), type_specifier::VOID);
    assert_eq(lex.read_token(), type_specifier::CHAR);
    assert_eq(lex.read_token(), type_specifier::SHORT);
    assert_eq(lex.read_token(), type_specifier::INT);
    assert_eq(lex.read_token(), type_specifier::LONG);
    assert_eq(lex.read_token(), type_specifier::FLOAT);
    assert_eq(lex.read_token(), type_specifier::DOUBLE);
    assert_eq(lex.read_token(), type_specifier::SIGNED);
    assert_eq(lex.read_token(), type_specifier::UNSIGNED);
    assert_eq(lex.read_token(), special_symbols::END);
}

TEST(lexer, type_qualifier_tokens)
{
    std::stringstream ss("const volatile");
    lexer lex(ss);

    assert_eq(lex.read_token(), type_qualifier::CONST);
    assert_eq(lex.read_token(), type_qualifier::VOLATILE);
    assert_eq(lex.read_token(), special_symbols::END);
}

TEST(lexer, spec_symbols_tokens)
{
    std::stringstream ss("*jopa;* ;asd()");
    lexer lex(ss);

    assert_eq(lex.read_token(), special_symbols::ASTERISK);
    assert_eq(lex.read_token(), std::string("jopa"));
    assert_eq(lex.read_token(), special_symbols::SEMICOLON);
    assert_eq(lex.read_token(), special_symbols::ASTERISK);

    assert_eq(lex.read_token(), special_symbols::SEMICOLON);
    assert_eq(lex.read_token(), std::string("asd"));
    assert_eq(lex.read_token(), special_symbols::OPEN_PARANTHESIS);
    assert_eq(lex.read_token(), special_symbols::CLOSE_PARANTHESIS);
    assert_eq(lex.read_token(), special_symbols::END);
}

TEST(parser, explicit_int_rule)
{
    std::stringstream ss("x;");
    assert(to_string(parse(ss)) == "([declaration] ([direct declarator] $x )( ; ))");
}

TEST(parser, empty_decl)
{
    std::stringstream ss("unsigned volatile int;");
    assert(to_string(parse(ss)) == "([declaration] ([declaration specifiers] ([type specifier] unsigned )([type qualifier] volatile )([type specifier] int ))( ; ))");
}

TEST(parser, basic_decl)
{
    std::stringstream ss("int x;");
    assert(to_string(parse(ss)) == "([declaration] ([declaration specifiers] ([type specifier] int ))([direct declarator] $x )( ; ))");
}

TEST(parser, single_int_pointer)
{
    std::stringstream ss("int* x;");
    assert(to_string(parse(ss)) == "([declaration] ([declaration specifiers] ([type specifier] int ))([declarator] ([pointer] ( * ))([direct declarator] $x ))( ; ))");
}

TEST(parser, decl_qualifiers)
{
    std::stringstream ss("const int volatile x;");
    assert(to_string(parse(ss)) == "([declaration] ([declaration specifiers] ([type qualifier] const )([type specifier] int )([type qualifier] volatile ))([direct declarator] $x )( ; ))");
}

TEST(parser, paranthesis)
{
    std::stringstream ss("int ((X));");
    assert(to_string(parse(ss)) == "([declaration] ([declaration specifiers] ([type specifier] int ))([declarator] ([direct declarator] ( ( )([declarator] ([direct declarator] ( ( )([direct declarator] $X )( ) )))( ) )))( ; ))");
}

TEST(parser, multiple_declarators)
{
    std::stringstream ss("int x, y;");
    assert(to_string(parse(ss)) == "([declaration] ([declaration specifiers] ([type specifier] int ))([declarator list] ([direct declarator] $x )( , )([direct declarator] $y ))( ; ))");
}

TEST(parser, specifiers_qualifiers)
{
    std::stringstream ss("volatile const int * const*** volatile*const* volatile (x);");
    assert(to_string(parse(ss)) == "([declaration] ([declaration specifiers] ([type qualifier] volatile )([type qualifier] const )([type specifier] int ))([declarator] ([pointer] ( * )([type qualifier] const )([pointer] ( * )([pointer] ( * )([pointer] ( * )([type qualifier] volatile )([pointer] ( * )([type qualifier] const )([pointer] ( * )([type qualifier] volatile )))))))([direct declarator] ( ( )([direct declarator] $x )( ) )))( ; ))");
}

int main(int argc, char* argv[])
{
    umask(0);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
