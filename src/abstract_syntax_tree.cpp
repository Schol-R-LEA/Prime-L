#include <string>
#include <sstream>
#include <vector>
#include "abstract_syntax_tree.h"
#include "atom.h"


AbstractSyntaxTree::AbstractSyntaxTree(Atom* h): head(h), parsed(nullptr), top_level(nullptr)
{
    top_level = new SymbolTable("<top-level>");

    parsed = parse(head, top_level);
}

AbstractSyntaxTree::~AbstractSyntaxTree()
{
    if (head != nullptr)
    {
        delete head;
    }
    delete top_level;
}

SymbolTable* AbstractSyntaxTree::parse(Atom* source, SymbolTable* syms)
{
    
}

AbstractSyntaxTree optimize_asts(std::vector<AbstractSyntaxTree*> asts)
{
    return asts;
}