#include "parser.h"
#include <cassert>

std::unique_ptr<storage_class_specifier_context> parse_storage_class_specifier(lexer& lex)
{
    auto result = std::make_unique<storage_class_specifier_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_EXTERN:
    {
        result->children.emplace_back(std::make_unique<EXTERN_context>(lex.get_current_tok()));
        lex.next_token();
        auto& EXTERN = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_STATIC:
    {
        result->children.emplace_back(std::make_unique<STATIC_context>(lex.get_current_tok()));
        lex.next_token();
        auto& STATIC = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_AUTO:
    {
        result->children.emplace_back(std::make_unique<AUTO_context>(lex.get_current_tok()));
        lex.next_token();
        auto& AUTO = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_REGISTER:
    {
        result->children.emplace_back(std::make_unique<REGISTER_context>(lex.get_current_tok()));
        lex.next_token();
        auto& REGISTER = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_SEMI: break;
    case token_id_t::TOKEN_POINTER: break;
    case token_id_t::TOKEN_OPEN_PARANTHESIS: break;
    case token_id_t::END: break;
    case token_id_t::TOKEN_IDENTIFIER: break;
    case token_id_t::TOKEN_VOID: break;
    case token_id_t::TOKEN_INT: break;
    case token_id_t::TOKEN_CHAR: break;
    case token_id_t::TOKEN_LONG: break;
    case token_id_t::TOKEN_CONST: break;
    case token_id_t::TOKEN_UNSIGNED: break;
    case token_id_t::TOKEN_SHORT: break;
    case token_id_t::TOKEN_SIGNED: break;
    case token_id_t::TOKEN_DOUBLE: break;
    case token_id_t::TOKEN_FLOAT: break;
    case token_id_t::TOKEN_VOLATILE: break;
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_COMMA: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<type_specifier_context> parse_type_specifier(lexer& lex)
{
    auto result = std::make_unique<type_specifier_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_VOID:
    {
        result->children.emplace_back(std::make_unique<VOID_context>(lex.get_current_tok()));
        lex.next_token();
        auto& VOID = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_CHAR:
    {
        result->children.emplace_back(std::make_unique<CHAR_context>(lex.get_current_tok()));
        lex.next_token();
        auto& CHAR = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_SHORT:
    {
        result->children.emplace_back(std::make_unique<SHORT_context>(lex.get_current_tok()));
        lex.next_token();
        auto& SHORT = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_INT:
    {
        result->children.emplace_back(std::make_unique<INT_context>(lex.get_current_tok()));
        lex.next_token();
        auto& INT = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_LONG:
    {
        result->children.emplace_back(std::make_unique<LONG_context>(lex.get_current_tok()));
        lex.next_token();
        auto& LONG = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_FLOAT:
    {
        result->children.emplace_back(std::make_unique<FLOAT_context>(lex.get_current_tok()));
        lex.next_token();
        auto& FLOAT = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_DOUBLE:
    {
        result->children.emplace_back(std::make_unique<DOUBLE_context>(lex.get_current_tok()));
        lex.next_token();
        auto& DOUBLE = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_SIGNED:
    {
        result->children.emplace_back(std::make_unique<SIGNED_context>(lex.get_current_tok()));
        lex.next_token();
        auto& SIGNED = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_UNSIGNED:
    {
        result->children.emplace_back(std::make_unique<UNSIGNED_context>(lex.get_current_tok()));
        lex.next_token();
        auto& UNSIGNED = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_SEMI: break;
    case token_id_t::TOKEN_IDENTIFIER: break;
    case token_id_t::TOKEN_OPEN_PARANTHESIS: break;
    case token_id_t::TOKEN_REGISTER: break;
    case token_id_t::TOKEN_POINTER: break;
    case token_id_t::TOKEN_AUTO: break;
    case token_id_t::TOKEN_EXTERN: break;
    case token_id_t::TOKEN_STATIC: break;
    case token_id_t::TOKEN_CONST: break;
    case token_id_t::TOKEN_VOLATILE: break;
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_COMMA: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<type_qualifier_context> parse_type_qualifier(lexer& lex)
{
    auto result = std::make_unique<type_qualifier_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_CONST:
    {
        result->children.emplace_back(std::make_unique<CONST_context>(lex.get_current_tok()));
        lex.next_token();
        auto& CONST = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_VOLATILE:
    {
        result->children.emplace_back(std::make_unique<VOLATILE_context>(lex.get_current_tok()));
        lex.next_token();
        auto& VOLATILE = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_SEMI: break;
    case token_id_t::TOKEN_IDENTIFIER: break;
    case token_id_t::TOKEN_OPEN_PARANTHESIS: break;
    case token_id_t::TOKEN_REGISTER: break;
    case token_id_t::TOKEN_LONG: break;
    case token_id_t::TOKEN_POINTER: break;
    case token_id_t::TOKEN_AUTO: break;
    case token_id_t::TOKEN_EXTERN: break;
    case token_id_t::TOKEN_STATIC: break;
    case token_id_t::TOKEN_CHAR: break;
    case token_id_t::TOKEN_INT: break;
    case token_id_t::TOKEN_SIGNED: break;
    case token_id_t::TOKEN_SHORT: break;
    case token_id_t::TOKEN_DOUBLE: break;
    case token_id_t::TOKEN_FLOAT: break;
    case token_id_t::TOKEN_VOID: break;
    case token_id_t::TOKEN_UNSIGNED: break;
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_COMMA: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<declaration_specifiers_context> parse_declaration_specifiers(lexer& lex)
{
    auto result = std::make_unique<declaration_specifiers_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_STATIC:
    case token_id_t::TOKEN_EXTERN:
    case token_id_t::TOKEN_AUTO:
    case token_id_t::TOKEN_REGISTER:
    {
        result->children.emplace_back(parse_storage_class_specifier(lex));
        auto& storage_class_specifier = *result->children.back();

        result->children.emplace_back(parse_declaration_specifiers_continuation(lex));
        auto& declaration_specifiers_continuation = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_VOID:
    case token_id_t::TOKEN_CHAR:
    case token_id_t::TOKEN_SHORT:
    case token_id_t::TOKEN_INT:
    case token_id_t::TOKEN_LONG:
    case token_id_t::TOKEN_FLOAT:
    case token_id_t::TOKEN_DOUBLE:
    case token_id_t::TOKEN_SIGNED:
    case token_id_t::TOKEN_UNSIGNED:
    {
        result->children.emplace_back(parse_type_specifier(lex));
        auto& type_specifier = *result->children.back();

        result->children.emplace_back(parse_declaration_specifiers_continuation(lex));
        auto& declaration_specifiers_continuation = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_VOLATILE:
    case token_id_t::TOKEN_CONST:
    {
        result->children.emplace_back(parse_type_qualifier(lex));
        auto& type_qualifier = *result->children.back();

        result->children.emplace_back(parse_declaration_specifiers_continuation(lex));
        auto& declaration_specifiers_continuation = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_OPEN_PARANTHESIS: break;
    case token_id_t::TOKEN_IDENTIFIER: break;
    case token_id_t::TOKEN_POINTER: break;
    case token_id_t::TOKEN_SEMI: break;
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_COMMA: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<declaration_specifiers_continuation_context> parse_declaration_specifiers_continuation(lexer& lex)
{
    auto result = std::make_unique<declaration_specifiers_continuation_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_STATIC:
    case token_id_t::TOKEN_EXTERN:
    case token_id_t::TOKEN_AUTO:
    case token_id_t::TOKEN_REGISTER:
    case token_id_t::TOKEN_VOID:
    case token_id_t::TOKEN_CHAR:
    case token_id_t::TOKEN_SHORT:
    case token_id_t::TOKEN_INT:
    case token_id_t::TOKEN_LONG:
    case token_id_t::TOKEN_FLOAT:
    case token_id_t::TOKEN_DOUBLE:
    case token_id_t::TOKEN_SIGNED:
    case token_id_t::TOKEN_UNSIGNED:
    case token_id_t::TOKEN_VOLATILE:
    case token_id_t::TOKEN_CONST:
    {
        result->children.emplace_back(parse_declaration_specifiers(lex));
        auto& declaration_specifiers = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_SEMI: 
break;
    case token_id_t::TOKEN_POINTER: 
break;
    case token_id_t::TOKEN_IDENTIFIER: 
break;
    case token_id_t::TOKEN_OPEN_PARANTHESIS: 
break;
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_COMMA: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<type_qualifier_list_context> parse_type_qualifier_list(lexer& lex)
{
    auto result = std::make_unique<type_qualifier_list_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_VOLATILE:
    case token_id_t::TOKEN_CONST:
    {
        result->children.emplace_back(parse_type_qualifier(lex));
        auto& type_qualifier = *result->children.back();

        result->children.emplace_back(parse_type_qualifier_list_continuation(lex));
        auto& type_qualifier_list_continuation = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_OPEN_PARANTHESIS: break;
    case token_id_t::TOKEN_IDENTIFIER: break;
    case token_id_t::TOKEN_POINTER: break;
    case token_id_t::TOKEN_STATIC: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EXTERN: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_AUTO: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_REGISTER: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_VOID: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CHAR: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SHORT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_INT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_LONG: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_FLOAT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_DOUBLE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_UNSIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SEMI: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_COMMA: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<type_qualifier_list_continuation_context> parse_type_qualifier_list_continuation(lexer& lex)
{
    auto result = std::make_unique<type_qualifier_list_continuation_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_VOLATILE:
    case token_id_t::TOKEN_CONST:
    {
        result->children.emplace_back(parse_type_qualifier_list(lex));
        auto& type_qualifier_list = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_OPEN_PARANTHESIS: 
break;
    case token_id_t::TOKEN_IDENTIFIER: 
break;
    case token_id_t::TOKEN_POINTER: 
break;
    case token_id_t::TOKEN_STATIC: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EXTERN: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_AUTO: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_REGISTER: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_VOID: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CHAR: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SHORT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_INT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_LONG: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_FLOAT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_DOUBLE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_UNSIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SEMI: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_COMMA: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<pointer_context> parse_pointer(lexer& lex)
{
    auto result = std::make_unique<pointer_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_POINTER:
    {
        result->children.emplace_back(std::make_unique<POINTER_context>(lex.get_current_tok()));
        lex.next_token();
        auto& POINTER = *result->children.back();

        result->children.emplace_back(parse_pointer_continuation(lex));
        auto& pointer_continuation = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_OPEN_PARANTHESIS: 
break;
    case token_id_t::TOKEN_IDENTIFIER: 
break;
    case token_id_t::TOKEN_STATIC: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EXTERN: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_AUTO: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_REGISTER: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_VOID: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CHAR: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SHORT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_INT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_LONG: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_FLOAT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_DOUBLE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_UNSIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_VOLATILE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CONST: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SEMI: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_COMMA: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<pointer_continuation_context> parse_pointer_continuation(lexer& lex)
{
    auto result = std::make_unique<pointer_continuation_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_VOLATILE:
    case token_id_t::TOKEN_CONST:
    case token_id_t::TOKEN_EPS:
    {
        result->children.emplace_back(parse_type_qualifier_list_continuation(lex));
        auto& type_qualifier_list_continuation = *result->children.back();

        result->children.emplace_back(parse_pointer(lex));
        auto& pointer = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_IDENTIFIER: 
break;
    case token_id_t::TOKEN_OPEN_PARANTHESIS: 
break;
    case token_id_t::TOKEN_STATIC: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EXTERN: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_AUTO: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_REGISTER: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_VOID: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CHAR: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SHORT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_INT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_LONG: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_FLOAT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_DOUBLE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_UNSIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SEMI: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_POINTER: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_COMMA: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<direct_declarator_context> parse_direct_declarator(lexer& lex)
{
    auto result = std::make_unique<direct_declarator_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_IDENTIFIER:
    {
        result->children.emplace_back(std::make_unique<IDENTIFIER_context>(lex.get_current_tok()));
        lex.next_token();
        auto& IDENTIFIER = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_OPEN_PARANTHESIS:
    {
        result->children.emplace_back(std::make_unique<OPEN_PARANTHESIS_context>(lex.get_current_tok()));
        lex.next_token();
        auto& OPEN_PARANTHESIS = *result->children.back();

        result->children.emplace_back(parse_declarator(lex));
        auto& declarator = *result->children.back();

        result->children.emplace_back(std::make_unique<CLOSE_PARANTHESIS_context>(lex.get_current_tok()));
        lex.next_token();
        auto& CLOSE_PARANTHESIS = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_SEMI: break;
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: break;
    case token_id_t::TOKEN_COMMA: break;
    case token_id_t::TOKEN_POINTER: break;
    case token_id_t::TOKEN_STATIC: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EXTERN: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_AUTO: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_REGISTER: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_VOID: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CHAR: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SHORT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_INT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_LONG: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_FLOAT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_DOUBLE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_UNSIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_VOLATILE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CONST: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EPS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<declarator_context> parse_declarator(lexer& lex)
{
    auto result = std::make_unique<declarator_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_POINTER:
    case token_id_t::TOKEN_EPS:
    {
        result->children.emplace_back(parse_pointer(lex));
        auto& pointer = *result->children.back();

        result->children.emplace_back(parse_direct_declarator(lex));
        auto& direct_declarator = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_IDENTIFIER:
    case token_id_t::TOKEN_OPEN_PARANTHESIS:
    {
        result->children.emplace_back(parse_direct_declarator(lex));
        auto& direct_declarator = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_SEMI: break;
    case token_id_t::TOKEN_COMMA: break;
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: break;
    case token_id_t::TOKEN_STATIC: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EXTERN: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_AUTO: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_REGISTER: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_VOID: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CHAR: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SHORT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_INT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_LONG: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_FLOAT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_DOUBLE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_UNSIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_VOLATILE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CONST: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<declarator_list_context> parse_declarator_list(lexer& lex)
{
    auto result = std::make_unique<declarator_list_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_IDENTIFIER:
    case token_id_t::TOKEN_POINTER:
    case token_id_t::TOKEN_OPEN_PARANTHESIS:
    case token_id_t::TOKEN_EPS:
    {
        result->children.emplace_back(parse_declarator(lex));
        auto& declarator = *result->children.back();

        result->children.emplace_back(parse_declarator_list_continuation(lex));
        auto& declarator_list_continuation = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_SEMI: break;
    case token_id_t::TOKEN_STATIC: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EXTERN: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_AUTO: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_REGISTER: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_VOID: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CHAR: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SHORT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_INT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_LONG: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_FLOAT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_DOUBLE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_UNSIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_VOLATILE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CONST: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_COMMA: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<declarator_list_continuation_context> parse_declarator_list_continuation(lexer& lex)
{
    auto result = std::make_unique<declarator_list_continuation_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_IDENTIFIER:
    case token_id_t::TOKEN_POINTER:
    case token_id_t::TOKEN_OPEN_PARANTHESIS:
    case token_id_t::TOKEN_EPS:
    {
        result->children.emplace_back(parse_declarator(lex));
        auto& declarator = *result->children.back();

        result->children.emplace_back(std::make_unique<COMMA_context>(lex.get_current_tok()));
        lex.next_token();
        auto& COMMA = *result->children.back();

        result->children.emplace_back(parse_declarator_list(lex));
        auto& declarator_list = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_SEMI: 
break;
    case token_id_t::TOKEN_STATIC: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EXTERN: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_AUTO: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_REGISTER: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_VOID: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CHAR: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SHORT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_INT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_LONG: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_FLOAT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_DOUBLE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_UNSIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_VOLATILE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CONST: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_COMMA: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<declaration_context> parse_declaration(lexer& lex)
{
    auto result = std::make_unique<declaration_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_STATIC:
    case token_id_t::TOKEN_EXTERN:
    case token_id_t::TOKEN_AUTO:
    case token_id_t::TOKEN_REGISTER:
    case token_id_t::TOKEN_VOID:
    case token_id_t::TOKEN_CHAR:
    case token_id_t::TOKEN_SHORT:
    case token_id_t::TOKEN_INT:
    case token_id_t::TOKEN_LONG:
    case token_id_t::TOKEN_FLOAT:
    case token_id_t::TOKEN_DOUBLE:
    case token_id_t::TOKEN_SIGNED:
    case token_id_t::TOKEN_UNSIGNED:
    case token_id_t::TOKEN_VOLATILE:
    case token_id_t::TOKEN_CONST:
    {
        result->children.emplace_back(parse_declaration_specifiers(lex));
        auto& declaration_specifiers = *result->children.back();

        result->children.emplace_back(parse_declaration_continuation(lex));
        auto& declaration_continuation = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_IDENTIFIER:
    case token_id_t::TOKEN_POINTER:
    case token_id_t::TOKEN_OPEN_PARANTHESIS:
    case token_id_t::TOKEN_EPS:
    {
        result->children.emplace_back(parse_declarator_list(lex));
        auto& declarator_list = *result->children.back();

        result->children.emplace_back(std::make_unique<SEMI_context>(lex.get_current_tok()));
        lex.next_token();
        auto& SEMI = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_SEMI: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_COMMA: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

std::unique_ptr<declaration_continuation_context> parse_declaration_continuation(lexer& lex)
{
    auto result = std::make_unique<declaration_continuation_context>();
    auto cur_tok = lex.get_current_tok();
    switch(cur_tok.get_id())
    {
    case token_id_t::TOKEN_SEMI:
    {
        result->children.emplace_back(std::make_unique<SEMI_context>(lex.get_current_tok()));
        lex.next_token();
        auto& SEMI = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_IDENTIFIER:
    case token_id_t::TOKEN_POINTER:
    case token_id_t::TOKEN_OPEN_PARANTHESIS:
    case token_id_t::TOKEN_EPS:
    {
        result->children.emplace_back(parse_declarator_list(lex));
        auto& declarator_list = *result->children.back();

        result->children.emplace_back(std::make_unique<SEMI_context>(lex.get_current_tok()));
        lex.next_token();
        auto& SEMI = *result->children.back();

        
        break;
    }
    case token_id_t::TOKEN_STATIC: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_EXTERN: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_AUTO: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_REGISTER: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_VOID: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CHAR: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SHORT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_INT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_LONG: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_FLOAT: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_DOUBLE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_SIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_UNSIGNED: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_VOLATILE: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CONST: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_CLOSE_PARANTHESIS: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_COMMA: assert(false && "Unexpected token!");
    case token_id_t::TOKEN_WHITESPACE: assert(false && "Unexpected token!");
    }

    return std::move(result);
}

