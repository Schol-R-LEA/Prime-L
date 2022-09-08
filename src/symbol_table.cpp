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
            return left->seek(key);
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
            return right->seek(key);
        }
    }
}


void SymbolTableNode::insert(Symbol* sym)
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

            right = new SymbolTableNode(sym);
        }
        else
        {
            right->insert(sym);
        }
    }
}


uint32_t SymbolTableNode::size()
{
    return 1 + ((left == nullptr) ? 0 : left->size()) + ((right == nullptr) ? 0 : right->size());
}


std::string SymbolTableNode::to_string()
{
    std::string s = "";

    if (left != nullptr)
    {
        s += left->to_string() + ", ";
    }
    s += symbol->to_string();
    if (right != nullptr)
    {
        s += ", " + right->to_string();
    }

    return s;
}


SymbolTable::~SymbolTable()
{
    delete symbols;
}


void SymbolTable::insert(Symbol* sym)
{
    if (symbols == nullptr)
    {
        symbols = new SymbolTableNode(sym);
    }
    else
    {
        symbols->insert(sym);
    }
}


void SymbolTable::new_scope(SymbolTable& child)
{
    child.parent = this;
    children.push_back(child);
}



SymbolTableNode* SymbolTable::find_local(std::string key)
{
    return symbols->seek(key);
}


SymbolTableNode* SymbolTable::find_in_scope(std::string key)
{
    SymbolTableNode* node = this->find_local(key);
    if (node != nullptr)
    {
        return node;
    }
    else if (parent != nullptr)
    {
        return parent->find_in_scope(key);
    }
    else
    {
        return nullptr;
    }
}


uint32_t SymbolTable::depth()
{
    if (parent == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + parent->depth();
    }
}


uint32_t SymbolTable::size()
{
    return symbols->size();
}


uint32_t SymbolTable::size_in_scope()
{
    if (parent == nullptr)
    {
        return this->size();
    }
    else
    {
        return this->size() + parent->size_in_scope();
    }
}


std::vector<SymbolTable> SymbolTable::get_children()
{
    return children;
}


SymbolTableNode* SymbolTable::get_symbols()
{
    return symbols;
}


std::string SymbolTable::get_description()
{
    return scope_description;
}


SymbolTable* SymbolTable::get_parent()
{
    return parent;
}


std::string SymbolTable::get_scope()
{
    if (parent == nullptr)
    {
        return this->get_description();
    }
    return parent->get_scope() + "::" + this->get_description();
}


std::string SymbolTable::to_string()
{
    std::string s = "";
    std::string offset = "";
    if (parent != nullptr)
    {
        s += parent->to_string();
    }
    for (uint32_t i = 0; i < this->depth(); i++)
    {
        offset += "  ";
    }

    s += offset + scope_description + ":\n";

    if (symbols != nullptr)
    {
        s += offset + symbols->to_string() + "\n";
    }

    return s;
}