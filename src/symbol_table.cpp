#include <iostream>
#include <string>
#include "atom.h"
#include "symbol_table.h"


SymbolTableNode::~SymbolTableNode()
{
    if (left != nullptr)
    {
        delete left;
    }
    if (right != nullptr)
    {
        delete right;
    }
}


SymbolTableNode* SymbolTableNode::seek(std::string key)
{
    if (key == "" || symbol->to_string() == "")
    {
        return nullptr;
    }
    if (key == symbol->to_string())
    {
        return this;
    }
    else if (key < symbol->to_string())
    {
        if (left == nullptr)
        {
            return nullptr;
        }
        else 
        {
            left->seek(key);
        }
    }
    else
    {
        if (right == nullptr)
        {
            return nullptr;
        }
        else 
        {
            right->seek(key);
        }
    }
}


SymbolTableNode* SymbolTableNode::insert(Symbol* sym)
{
    if (sym->to_string() == "")
    {
        throw new invalid_symbol_exception();
    }
    if (sym->to_string() == symbol->to_string())
    {
        throw new duplicate_symbol_exception();
    }
    else if (sym->to_string()  < symbol->to_string())
    {
        if (left == nullptr)
        {
            left = new SymbolTableNode(sym);
            return left;
        }
        else
        {
            left->insert(sym);
        }
    }
    else
    {
        if (right == nullptr)
        {
            return nullptr;
        }
        else
        {
            right->seek(key);
        }
    }
}



SymbolTable::~SymbolTable()
{
    delete children;
}


void SymbolTable::insert(Symbol* sym)
{

}


SymbolTableNode* SymbolTable::find_local(std::string key)
{

}


SymbolTableNode* SymbolTable::find_in_scope(std::string key)
{

}


uint32_t SymbolTable::depth()
{

}


uint32_t SymbolTable::size()
{

}


vector<SymbolTable> SymbolTable::get_children()
{

}


std::string SymbolTable::get_description()
{

}


SymbolTable SymbolTable::get_parent()
{

}


std::string SymbolTable::get_scope()
{
    return scope_description;
}


std::string SymbolTable::to_string()
{

}