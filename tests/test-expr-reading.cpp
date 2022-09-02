#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iostream>
#include <sstream>
#include "atom.h"
#include "read.h"

TEST_SUITE("testing reading s-expressions and converting them to strings")
{
    TEST_CASE("empty file")
    {
        std::stringstream src;
        src << "";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "");
    }

    TEST_CASE("integer")
    {
        std::stringstream src;
        src << "42";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "42");
    }

    TEST_CASE("floating-point number")
    {
        std::stringstream src;
        src << "17.23";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "17.230000");
    }

    TEST_CASE("symbol #1")
    {
        std::stringstream src;
        src << "foo";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "foo");
    }

    TEST_CASE("symbol #2")
    {
        std::stringstream src;
        src << "an-atom";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "an-atom");
    }

    TEST_CASE("null list")
    {
        std::stringstream src;
        src << "()";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "()");
    }
    
    TEST_CASE("list of one element")
    {
        std::stringstream src;
        src << "(foo)";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "(foo)");
    }

    TEST_CASE("improper list of two elements")
    {
        std::stringstream src;
        src << "(foo . bar)";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "(foo . bar)");
    }


    TEST_CASE("proper list of two integer elements with extra spaces")
    {
        std::stringstream src;
        src << "(23     42)";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "(23 42)");
    }


    TEST_CASE("proper list of two elements with extra spaces")
    {
        std::stringstream src;
        src << "(foo     bar)";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "(foo bar)");
    }

    TEST_CASE("proper list of three elements")
    {
        std::stringstream src;
        src << "(foo bar quux)";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "(foo bar quux)");
    }

    TEST_CASE("improper list of three elements")
    {
        std::stringstream src;
        src << "(foo bar . quux)";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "(foo bar . quux)");
    }

    TEST_CASE("list of a symbol and a list")
    {
        std::stringstream src;
        src << "(foo (bar baz))";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "(foo (bar baz))");
    }

}