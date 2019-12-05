#include <cassert>
#include <unordered_map>
#include <sstream>

#include "parser.h"

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; }; // (1)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;  // (2)

template<typename VarT, typename T>
bool variant_eq(VarT const& var, T&& val)
{
    return var == VarT(std::forward<T>(val));
}

static inline
ast_ptr parse_type_qualifier_list(lexer& lex)
{
    ast_ptr result = std::make_unique<ast_node>();
    result->kind = node_kind::TYPE_QUALIFIER_LIST;

    while (lex.get_current().index() == 2)
    {
        result->args.push_back(std::make_unique<ast_node>());
        result->args.back()->kind = node_kind::TYPE_QUALIFIER;
        result->args.back()->data = lex.get_current();

        lex.read_token();
    }

    if (result->args.size() == 1)
        return std::move(result->args[0]);
    else
        return std::move(result);
}

static inline
ast_ptr parse_pointer(lexer& lex)
{
    ast_ptr result = std::make_unique<ast_node>();
    result->kind = node_kind::POINTER;
    assert(variant_eq(lex.get_current(), special_symbols::ASTERISK));
    result->args.push_back(std::make_unique<ast_node>(lex.get_current()));

    auto& cur = lex.read_token();
    if (cur.index() == 2)
        result->args.push_back(parse_type_qualifier_list(lex));

    if (variant_eq(lex.get_current(), special_symbols::ASTERISK))
        result->args.push_back(parse_pointer(lex));

    return std::move(result);
}

static inline
ast_ptr parse_declarator(lexer& lex);

static inline
ast_ptr parse_direct_declarator(lexer& lex)
{
    ast_ptr result = std::make_unique<ast_node>();
    result->kind = node_kind::DIRECT_DECLARATOR;

    std::visit(
        overloaded {
            [&lex] (storage_class_specifier) { assert(false); },
            [&lex] (type_specifier) { assert(false); },
            [&lex] (type_qualifier) { assert(false); },
            [&lex, &result] (std::string const&)
            {
                result->data = std::move(lex.get_current());
                lex.read_token();
            },
            [&lex, &result] (special_symbols sym)
            {
                if (sym != special_symbols::OPEN_PARANTHESIS)
                    throw std::runtime_error("Unexpected token");
                result->args.push_back(std::make_unique<ast_node>(lex.get_current()));

                auto& tok = lex.read_token();
                result->args.push_back(parse_declarator(lex));
                result->args.push_back(std::make_unique<ast_node>(lex.get_current()));
                assert(variant_eq(lex.get_current(), special_symbols::CLOSE_PARANTHESIS));
                lex.read_token();
            },
        },
        lex.get_current()
    );

    return std::move(result);
}

static inline
ast_ptr parse_declarator(lexer& lex)
{
    auto result = std::make_unique<ast_node>();
    result->kind = node_kind::DECLARATOR;

    std::visit(
        overloaded {
            [&lex] (storage_class_specifier) { assert(false); },
            [&lex] (type_specifier) { assert(false); },
            [&lex] (type_qualifier) { assert(false); },
            [&lex, &result] (std::string const&)
            {
                result->kind = node_kind::DIRECT_DECLARATOR;
                result->data = std::move(lex.get_current());
                lex.read_token();
            },
            [&lex, &result] (special_symbols sym)
            {
                if (sym == special_symbols::ASTERISK)
                    result->args.push_back(parse_pointer(lex));
                result->args.push_back(parse_direct_declarator(lex));
            },
        },
        lex.get_current()
    );

    return std::move(result);
}

static inline
ast_ptr parse_declarator_list(lexer& lex)
{
    ast_ptr result = std::make_unique<ast_node>();

    while (lex.get_current().index() > 2)
    {
        bool stop = false;
        std::visit (
                overloaded {
                        [&result, &lex] (std::string const&) { result->args.push_back(parse_declarator(lex)); },
                        [&result, &lex, &stop] (special_symbols symb)
                        {
                            if (symb == special_symbols::OPEN_PARANTHESIS
                                || symb == special_symbols::ASTERISK)
                                result->args.push_back(parse_declarator(lex));
                            else
                                stop = true;
                        },
                        [] (storage_class_specifier) { assert(false); },
                        [] (type_specifier) { assert(false); },
                        [] (type_qualifier) { assert(false); },
                },
                lex.get_current()
        );

        if (stop)
            break;

        if (!variant_eq(lex.get_current(), special_symbols::COMMA))
            break;
        result->args.push_back(std::make_unique<ast_node>(lex.get_current()));
        lex.read_token();
    }

    if (result->args.size() == 1)
    {
        result->kind = node_kind::DECLARATOR;
        return std::move(result->args[0]);
    }


    result->kind = node_kind::DECLARATOR_LIST;
    return std::move(result);
}

static inline
ast_ptr parse_decl_specifiers(lexer& lex)
{
    ast_ptr result = std::make_unique<ast_node>();
    result->kind = node_kind::DECLARATION_SPECIFIERS;

    while (lex.get_current().index() <= 2)
    {
        result->args.push_back(std::make_unique<ast_node>());
        result->args.back()->kind
            = std::visit(
                overloaded {
                    [] (storage_class_specifier) -> node_kind { return node_kind::STORAGE_CLASS_SPECIFIER; },
                    [] (type_specifier) -> node_kind { return node_kind::TYPE_SPECIFIER; },
                    [] (type_qualifier) -> node_kind { return node_kind::TYPE_QUALIFIER; },
                    [] (std::string const&) -> node_kind { assert(false); },
                    [] (special_symbols) -> node_kind { assert(false); },
                },
                lex.get_current()
              );

        result->args.back()->data = lex.get_current();

        lex.read_token();
    }

    return std::move(result);
}

static inline
ast_ptr parse_decl(lexer& lex)
{
    auto& tok = lex.read_token();

    bool got_semicolon = false;
    ast_ptr current_node = std::make_unique<ast_node>();
    current_node->kind = node_kind::DECLARATION;

    current_node->args.push_back(
        std::visit(
            overloaded {
                [&lex] (storage_class_specifier) -> ast_ptr { return parse_decl_specifiers(lex); },
                [&lex] (type_specifier) -> ast_ptr { return parse_decl_specifiers(lex); },
                [&lex] (type_qualifier) -> ast_ptr { return parse_decl_specifiers(lex); },
                [&lex] (std::string const&) -> ast_ptr { return parse_declarator_list(lex); },
                [&lex] (special_symbols sym) -> ast_ptr { return parse_declarator_list(lex); },
            },
            tok
        )
    );

    current_node->args.push_back(
        std::visit(
            overloaded
                {
                    [&lex] (storage_class_specifier) -> ast_ptr { assert(false); },
                    [&lex] (type_specifier) -> ast_ptr { assert(false); },
                    [&lex] (type_qualifier) -> ast_ptr { assert(false); },
                    [&lex] (std::string const&) -> ast_ptr { return parse_declarator_list(lex); },
                    [&lex, &got_semicolon] (special_symbols sym) -> ast_ptr
                    {
                        if (sym != special_symbols::SEMICOLON)
                            return parse_declarator_list(lex);
                        else
                            return nullptr;
                    },
                },
            lex.get_current()
        )
    );

    if (!current_node->args.empty() && current_node->args.back() == nullptr)
        current_node->args.pop_back();

    if (variant_eq(lex.get_current(), special_symbols::SEMICOLON))
        current_node->args.push_back(std::make_unique<ast_node>(lex.get_current()));

//    if (got_semicolon)
//        current_node->args.pop_back();

    return std::move(current_node);
}

ast_ptr parse(std::istream& input)
{
    lexer lex(input);

    return parse_decl(lex);
}

static inline
void to_string_impl(std::stringstream& ss, storage_class_specifier specifier)
{
    static const std::unordered_map<storage_class_specifier, std::string>
            spec_to_str =
            {
                    {storage_class_specifier::EXTERN, "extern"},
                    {storage_class_specifier::STATIC, "static"},
                    {storage_class_specifier::AUTO, "auto"},
                    {storage_class_specifier::REGISTER, "register"}
            };

    auto it = spec_to_str.find(specifier);
    assert(it != spec_to_str.end());
    ss << it->second;

    switch (specifier)
    {
        case storage_class_specifier::EXTERN:
            ss << "extern";
            break;
        case storage_class_specifier::STATIC:
            ss << "static";
            break;
        case storage_class_specifier::AUTO:
            ss << "auto";
            break;
        case storage_class_specifier::REGISTER:
            ss << "register";
            break;
        default:
            assert(false);
    }
}

static inline
void to_string_impl(std::stringstream& ss, type_specifier specifier)
{
    switch (specifier)
    {
        case type_specifier::VOID:
            ss << "void";
            break;
        case type_specifier::CHAR:
            ss << "char";
            break;
        case type_specifier::SHORT:
            ss << "short";
            break;
        case type_specifier::INT:
            ss << "int";
            break;
        case type_specifier::LONG:
            ss << "long";
            break;
        case type_specifier::FLOAT:
            ss << "float";
            break;
        case type_specifier::DOUBLE:
            ss << "double";
            break;
        case type_specifier::SIGNED:
            ss << "signed";
            break;
        case type_specifier::UNSIGNED:
            ss << "unsigned";
            break;
        default:
            assert(false);
    }
}

static inline
void to_string_impl(std::stringstream& ss, type_qualifier specifier)
{
    switch (specifier)
    {
        case type_qualifier::CONST:
            ss << "const";
            break;
        case type_qualifier::VOLATILE:
            ss << "volatile";
            break;
        default:
            assert(false);
    }
}

static inline
void to_string_impl(std::stringstream& ss, special_symbols specifier)
{
    switch (specifier)
    {
        case special_symbols::ASTERISK:
            ss << '*';
            break;
        case special_symbols::SEMICOLON:
            ss << ';';
            break;
        case special_symbols::OPEN_PARANTHESIS:
            ss << '(';
            break;
        case special_symbols::CLOSE_PARANTHESIS:
            ss << ')';
            break;
        case special_symbols::COMMA:
            ss << ',';
            break;
        case special_symbols::END:
        default:
            assert(false);
            break;
    }
}

static inline
void to_string_impl(std::stringstream& ss, node_kind kind)
{
    static const std::unordered_map<node_kind, std::string>
            char_to_spec_symbol =
            {
                    {node_kind::TERMINAL, ""},
                    {node_kind::STORAGE_CLASS_SPECIFIER, "[storage class specifier]"},
                    {node_kind::TYPE_SPECIFIER, "[type specifier]"},
                    {node_kind::TYPE_QUALIFIER, "[type qualifier]"},
                    {node_kind::TYPE_QUALIFIER_LIST, "[type qualifier list]"},
                    {node_kind::POINTER, "[pointer]"},
                    {node_kind::DIRECT_DECLARATOR, "[direct declarator]"},
                    {node_kind::DECLARATOR_LIST, "[declarator list]"},
                    {node_kind::DECLARATOR, "[declarator]"},
                    {node_kind::DECLARATION_SPECIFIERS, "[declaration specifiers]"},
                    {node_kind::DECLARATION, "[declaration]"},
            };

    auto it = char_to_spec_symbol.find(kind);
    assert(it != char_to_spec_symbol.end());
    ss << it->second;
}

static inline
void to_string_impl(std::stringstream& ss, token_t const& tok)
{
    std::visit(
            overloaded {
                    [&ss] (storage_class_specifier spec) { to_string_impl(ss, spec); },
                    [&ss] (type_specifier spec) { to_string_impl(ss, spec); },
                    [&ss] (type_qualifier spec) { to_string_impl(ss, spec); },
                    [&ss] (std::string const& str) { ss << "$" << str; },
                    [&ss] (special_symbols spec) { to_string_impl(ss, spec); },
            },
            tok
    );
}

void to_string_impl(std::stringstream& ss, ast_ptr const& ptr)
{
    ss << '(';
    to_string_impl(ss, ptr->kind);
    ss << " ";

    if (ptr->data)
    {
        to_string_impl(ss, *ptr->data);
        ss << " ";
    }

    for (auto&& x : ptr->args)
        to_string_impl(ss, x);

    ss << ')';
}

std::string to_string(ast_ptr const& ast)
{
    std::stringstream ss;
    to_string_impl(ss, ast);
    return ss.str();
}

static inline
char const* get_dot_color(std::stringstream& ss, node_kind kind)
{
    switch (kind)
    {
        case node_kind::TERMINAL:
            return "#b1bac1";
        case node_kind::STORAGE_CLASS_SPECIFIER:
            return "#151d1f";
        case node_kind::TYPE_SPECIFIER:
            return "#262d33";
        case node_kind::TYPE_QUALIFIER:
            return "#807b77";
        case node_kind::TYPE_QUALIFIER_LIST:
            return "#e6e1de";
        case node_kind::POINTER:
            return "#b1bac1";
        case node_kind::DIRECT_DECLARATOR:
            return "#92afbf";
        case node_kind::DECLARATOR:
            return "#4f8ba7";
        case node_kind::DECLARATOR_LIST:
            return "#103e55";
        case node_kind::DECLARATION_SPECIFIERS:
            return "#021d28";
        case node_kind::DECLARATION:
            return "#000d16";
        default:
            assert(false);
            return "#000000";
    }
}

static inline
void echo_node_info(std::stringstream& ss, ast_ptr const& ast)
{
    ss << "\tx" << ast.get() << " [label=\"";

    if (ast->data)
        to_string_impl(ss, *ast->data);
    else
        to_string_impl(ss, ast->kind);

    ss << "\" color=\"" << get_dot_color(ss, ast->kind) << "\"];\n";
}

void to_dot_repr(std::stringstream& ss, ast_ptr const& ast)
{
    for (auto&& chld : ast->args)
    {
        echo_node_info(ss, chld);
        ss << "\tx" << ast.get() << " -> x" << chld.get() << ";\n";
        to_dot_repr(ss, chld);
    }
}

std::string to_dot_repr(ast_ptr const& ast)
{
    std::stringstream ss;
    ss << "digraph AST {\n";
    echo_node_info(ss, ast);
    to_dot_repr(ss, ast);
    ss << "}";

    return ss.str();
}

ast_node::ast_node(token_t tok)
    : kind{node_kind::TERMINAL},
        data(std::move(tok)),
        args{}
{}
