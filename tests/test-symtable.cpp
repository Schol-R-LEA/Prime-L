#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <typeinfo>
#include <iostream>
#include <sstream>
#include "atom.h"
#include "read.h"
#include "symbol_table.h"


TEST_SUITE("constructing symbol tables")
{
    SymbolTable* top = new SymbolTable(nullptr, "top-level")

    TEST_CASE("")
    {
        
    }
}