#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <vector>
#include "atom.h"


class duplicate_symbol_exception
{
public:
    duplicate_symbol_exception() {};
};


class invalid_symbol_exception
{
public:
    invalid_symbol_exception() {};
};

class SymbolTableNode
{
private:
    Symbol* symbol;
    SymbolTableNode *left, *right;

public:
    SymbolTableNode(Symbol* sym): symbol(sym), left(nullptr), right(nullptr) {};
    ~SymbolTableNode();
    Symbol* get_symbol() {return symbol; };
    SymbolTableNode* seek(std::string key);
    void insert(Symbol* sym);
    uint32_t size();
    std::string to_string();
};


class SymbolTable
{
private:
    std::string scope_description;
    SymbolTable *parent;
    std::vector<SymbolTable> children;
    SymbolTableNode *symbols;


public:
    SymbolTable(): scope_description("<none>"), parent(nullptr), symbols(nullptr) {};
    SymbolTable(std::string sd): scope_description(sd), parent(nullptr), symbols(nullptr) {};
    SymbolTable(std::string sd, SymbolTable *p): scope_description(sd), parent(p), symbols(nullptr) {};
    ~SymbolTable();

    void insert(Symbol* sym);
    void new_scope(SymbolTable& child);
    SymbolTableNode* find_local(std::string key);
    SymbolTableNode* find_in_scope(std::string key);
    uint32_t depth();
    uint32_t size();
    uint32_t size_in_scope();
    std::vector<SymbolTable> get_children();
    SymbolTableNode* get_symbols();
    std::string get_description();
    SymbolTable* get_parent();
    std::string get_scope();

    std::string to_string();

};

#endif