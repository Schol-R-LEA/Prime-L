#ifndef ABSTRACT_SYNTAX_TREE_H
#define ABSTRACT_SYNTAX_TREE_H

#include <string>
#include <iostream>
#include <vector>
#include "atom.h"
#include "symbol_table.h"


class AbstractSyntaxTree
{
private:
    Atom* head;
    SymbolTable* top_level;
    Atom* parsed;
    Atom* parse(Atom* current, SymbolTable* syms);

public:
    AbstractSyntaxTree(Atom* h);
    ~AbstractSyntaxTree();
};

AbstractSyntaxTree optimize_asts(std::vector<AbstractSyntaxTree*> asts);

#endif