#include <string>
#include <sstream>
#include <vector>
#include "abstract_syntax_tree.h"
#include "atom.h"

AbstractSyntaxTree::AbstractSyntaxTree(): head(nulltpr)
{
}


AbstractSyntaxTree::AbstractSyntaxTree(Atom* h): head(h)
{
}

AbstractSyntaxTree::~AbstractSyntaxTree()
{
    if (head != nullptr)
    {
        delete head;
    }
}

AbstractSyntaxTree optimize_asts(std::vector<AbstractSyntaxTree> asts)
{
    return asts;
}