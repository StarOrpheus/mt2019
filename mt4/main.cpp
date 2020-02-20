#include <iostream>
#include <filesystem>
#include <fstream>
#include <future>

#include "common.h"
#include "formatting.h"
#include "generator_context.h"
#include "generate_lexer_h.h"
#include "generate_lexer_cpp.h"
#include "generate_parser_h.h"
#include "generate_parser_cpp.h"
#include "antlr4-runtime.h"
#include "GrammarSchemeLexer.h"
#include "GrammarSchemeParser.h"
#include "GrammarSchemeBaseVisitor.h"

using namespace antlr4;

class rules_gathering_visitor
    : public GrammarSchemeBaseVisitor
{
    antlrcpp::Any
    visitTokenRule(GrammarSchemeParser::TokenRuleContext* ctx) override
    {
        std::cerr << ctx->getText() << std::endl;

        token_rule_t current_rule;

        current_rule.name = ctx->children[0]->getText();
        current_rule.rule = ctx->children[2]->getText();
        assert(current_rule.rule.size() > 2);
        current_rule.rule
            = current_rule.rule.substr(1, current_rule.rule.size() - 2);

        switch (ctx->children.size())
        {
        case 4: break;
        case 5:
        {
            if (auto ptr = dynamic_cast<GrammarSchemeParser::CodeContext*>(ctx->children[3]);
                ptr)
            {
                current_rule.code = ptr->getText();
            }
            else
                current_rule.skip = true;
            break;
        }
        case 6:
        {
            if (auto ptr = dynamic_cast<GrammarSchemeParser::CodeContext*>(ctx->children[3]);
                    ptr)
            {
                current_rule.code = ptr->getText();
            }
            else
                assert(false);
            current_rule.skip = true;
            break;
        }
        default:
        {
            unsigned long childs = ctx->children.size();
            std::cerr << "Children: " << childs << std::endl;
        }
            assert(false);
            return defaultResult();
        }

        token_rules.emplace_back(std::move(current_rule));
        return defaultResult();
    }

    antlrcpp::Any
    visitMoreNames(GrammarSchemeParser::MoreNamesContext* ctx) override
    {
        assert(current_rule != nullptr);

        auto& rule = current_rule->rhs.emplace_back();
        for (auto&& fragment : ctx->children)
        {
            if (auto ptr = dynamic_cast<GrammarSchemeParser::NameContext*>(fragment);
                    ptr)
            {
                rule.names_with_arguments.emplace_back(ptr->getText());
                continue;
            }

            if (auto ptr = dynamic_cast<GrammarSchemeParser::CodeContext*>(fragment);
                    ptr)
            {
                assert(rule.code.empty());
                rule.code = ptr->getText();
                continue;
            }
        }
        return defaultResult();
    }

    antlrcpp::Any
    visitWideIdentsList(GrammarSchemeParser::WideIdentsListContext* ctx) override
    {
        assert(current_rule != nullptr);
        assert(current_rule->args.empty());

        for (auto* ptr : ctx->children)
            current_rule->args += ptr->getText() + ' ';
        return defaultResult();
    }

    antlrcpp::Any
    visitSyntaxRule(GrammarSchemeParser::SyntaxRuleContext* ctx) override
    {
        syntax_rule_t rule;

        rule.name = ctx->children[0]->getText();
        current_rule = &rule;
        visitChildren(ctx);
        syntax_rules.emplace_back(std::move(rule));
        current_rule = nullptr;
        return defaultResult();
    }

public:
    antlrcpp::Any visitHeader(GrammarSchemeParser::HeaderContext* ctx) override
    {
        header = ctx->children[1]->getText().substr(1);
        header.pop_back();
        return defaultResult();
    }

public:
    antlrcpp::Any visitField(GrammarSchemeParser::FieldContext* ctx) override
    {
        std::string decl_line;

        for (size_t i = 0; i < ctx->children.size() - 1; ++i)
            decl_line += ctx->children[i]->getText() + " ";
        decl_line.back() = ';';

        fields.push_back(std::move(decl_line));

        return defaultResult();
    }

public:
    std::vector<token_rule_t>& get_token_rules() noexcept
    {
        return token_rules;
    }

    std::vector<syntax_rule_t>& get_syntax_rules() noexcept
    {
        return syntax_rules;
    }

    std::vector<std::string>& get_fields() noexcept
    {
        return fields;
    }

    std::string& get_header() noexcept
    {
        return header;
    }

private:
    std::vector<token_rule_t>   token_rules;
    std::vector<syntax_rule_t>  syntax_rules;
    std::vector<std::string>    fields;
    std::string                 header;

    syntax_rule_t*              current_rule;
};

static
void debug_context(generator_context const& context)
{
    std::cerr << "Fields:\n";
    for (auto&& str : context.decl_fields)
        std::cerr << '\t' << str << std::endl;
    std::cerr << std::endl;

    for (auto&& rule : context.syntax_rules)
    {
        std::cerr << rule.name << "(" << rule.args << ")" << std::endl;
        std::cerr << "FIRST: ";
        for (auto&& str : rule.first)
            std::cerr << str << " ";
        std::cerr << std::endl;

        std::cerr << "FOLLOW: ";
        for (auto&& str : rule.follow)
            std::cerr << str << " ";
        std::cerr << std::endl;
        std::cerr << std::endl;

        for (auto&& rhs : rule.rhs)
        {
            std::cerr << "\t\t";
            for (auto&& name : rhs.extract_names())
                std::cerr << name << " ";
            std::cerr << std::endl;
            std::cerr << "\t\t" << rhs.code << std::endl << std::endl;
        }
    }
}

static void make_name_refs(generator_context& context)
{
    for (auto&& rule : context.token_rules)
    {
        auto it = context.name_to_token_rule.find(rule.name);
        assert(it == context.name_to_token_rule.end());
        context.name_to_token_rule.emplace(rule.name, &rule);
    }

    for (auto&& rule : context.syntax_rules)
    {
        auto it = context.name_to_syntax_rule.find(rule.name);
        assert(it == context.name_to_syntax_rule.end());
        context.name_to_syntax_rule.emplace(rule.name, &rule);
    }

    for (auto&& rule : context.syntax_rules)
        for (auto&& rhs : rule.rhs)
        {
            std::vector<std::string> extracted_names = rhs.extract_names();
            for (auto&& name : extracted_names)
            {
                assert(context.name_to_syntax_rule.count(name)
                       || context.name_to_token_rule.count(name)
                          && "Error: unrecognized name!");
            }
        }
}

static
void generate_first_set(generator_context& context)
{
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (auto&& rule : context.syntax_rules)
            for (auto&& rhs : rule.rhs)
            {
                auto extracted = rhs.extract_names();
                auto last = rule.first.size();
                auto frst = context.calculate_first(extracted.cbegin(), extracted.cend());
                rule.first.insert(frst.begin(), frst.end());
                changed |= last != rule.first.size();
            }
    }
}

static
void generate_follow_set(generator_context& context)
{
    std::string EPS = format_token("EPS");
    context.syntax_rules[0].follow.emplace("END");
    bool changed = true;
    while (changed)
    {
        changed = false;
        for (auto&& rule : context.syntax_rules)
        {
            for (auto&& rhs : rule.rhs)
            {
                auto extracted = rhs.extract_names();

                for (size_t i = 0; i < extracted.size(); ++i)
                {
                    auto& B = extracted[i];
                    auto it = context.name_to_syntax_rule.find(B);
                    if (it == context.name_to_syntax_rule.end())
                        continue;
                    auto& B_rule = *it->second;

                    size_t last = it->second->follow.size();
                    auto first = context.calculate_first(extracted.begin() + (i + 1), extracted.end());
                    B_rule.follow.insert(first.begin(), first.end());

                    if (first.count(EPS)
                        || i == extracted.size() - 1)
                        B_rule.follow.insert(rule.follow.begin(), rule.follow.end());

                    changed |= (B_rule.follow.size() != last);
                }
            }
        }
    }

    for (auto&& rule : context.syntax_rules)
    {
        auto it = rule.follow.find(EPS);
        if (it != rule.follow.end())
            rule.follow.erase(it);
    }
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./generate GRAMMAR.gr" << std::endl;
        return -1;
    }

    if (!std::filesystem::exists(argv[1]))
    {
        std::cerr << "File \"" << argv[1] << "\" not found!" << std::endl;
        return -1;
    }

    generator_context context;
    try
    {
        std::ifstream       input(argv[1]);
        ANTLRInputStream    input_stream(input);
        GrammarSchemeLexer  lexer(&input_stream);
        CommonTokenStream   tokens(&lexer);
        GrammarSchemeParser parser(&tokens);

        auto tree = parser.grammarSpec();

        rules_gathering_visitor visitor;
        visitor.visitGrammarSpec(tree);
        std::cerr << std::endl;

        context.token_rules     = std::move(visitor.get_token_rules());
        context.syntax_rules    = std::move(visitor.get_syntax_rules());
        context.decl_fields     = std::move(visitor.get_fields());
        context.header          = std::move(visitor.get_header());
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error occured: " << e.what() << std::endl;
        return -1;
    }

    auto f1 = std::async(std::launch::async, generate_lexer_h, context.token_rules, "lexer.h");
    auto f2 = std::async(std::launch::async, generate_lexer_cpp, context.token_rules, "lexer.cpp");

    make_name_refs(context);

    generate_first_set(context);
    generate_follow_set(context);

    auto f3 = std::async(std::launch::async, generate_parser_h, &context, "parser.h");
    auto f4 = std::async(std::launch::async, generate_parser_cpp, &context, "parser.cpp");


    debug_context(context);

    f1.wait();
    f2.wait();
    f3.wait();
    f4.wait();
}