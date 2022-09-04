#ifndef ABSTRACT_SYNTAX_TREE_H
#define ABSTRACT_SYNTAX_TREE_H

#include <string>
#include <iostream>
#include <vector>
#include "atom.h"


class AbstractSyntaxTree
{
private:
    Atom* head;

public:
    AbstractSyntaxTree();
    AbstractSyntaxTree(Atom* head);
    ~AbstractSyntaxTree();
};

AbstractSyntaxTree optimize_asts(std::vector<AbstractSyntaxTree> asts);

#endif