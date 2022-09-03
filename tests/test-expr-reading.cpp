#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <typeinfo>
#include <iostream>
#include <sstream>
#include "atom.h"
#include "read.h"


TEST_SUITE("constructing atoms and lists")
{
    TEST_CASE("empty list")
    {
        Pair* test = new Pair();
        CHECK(test->get_car() == nullptr);
        CHECK(test->get_cdr() == nullptr);
        CHECK(test->to_string() == "()");
        delete test;
    }

    TEST_CASE("integer")
    {
        Integer64* test = new Integer64(69);
        CHECK(test->value() == 69);
        CHECK(test->to_string() == "69");
        delete test;
    }

    TEST_CASE("floating-point number")
    {
        FP_Double* test = new FP_Double(6.9);
        CHECK(test->value() == 6.9);
        CHECK(test->to_string() == "6.900000");
        delete test;
    }

    TEST_CASE("symbol #1")
    {
        Symbol* test = new Symbol("foo");
        CHECK(test->value() == "foo");
        CHECK(test->to_string() == "foo");
        delete test;
    }

    TEST_CASE("symbol #2")
    {
        Symbol* test = new Symbol("an-atom");
        CHECK(test->value() == "an-atom");
        CHECK(test->to_string() == "an-atom");
        delete test;
    }


    TEST_CASE("list of one element")
    {
        Pair* test = new Pair(new Symbol("foo"));
        CHECK(typeid(*(test->get_car())) == typeid(Symbol));
        Symbol* test_symbol = dynamic_cast<Symbol*>(test->get_car());
        CHECK(test_symbol->value() == "foo");
        CHECK(test->to_string() == "(foo)");
        delete test;
    }

    TEST_CASE("improper list of two elements")
    {
        Pair* test = new Pair(new Symbol("foo"), new Symbol("bar"));
        Symbol* test_car = dynamic_cast<Symbol*>(test->get_car());
        CHECK(test_car->value() == "foo");
        Symbol* test_cdr = dynamic_cast<Symbol*>(test->get_cdr());
        CHECK(test_cdr->value() == "bar");
        CHECK(test->to_string() == "(foo . bar)");
        delete test;
    }


    TEST_CASE("proper list of two integer elements")
    {
        Pair* test = new Pair(new Integer64(2), new Pair(new Integer64(5)));
        CHECK(typeid(*(test->get_car())) == typeid(Integer64));
        Integer64* test_car = dynamic_cast<Integer64*>(test->get_car());
        CHECK(test_car->value() == 2);
        CHECK(typeid(*(test->get_cdr())) == typeid(Pair));
        Pair* test_cdr = dynamic_cast<Pair*>(test->get_cdr());
        Atom* test_cadr = test_cdr->get_car();
        CHECK(typeid(*test_cadr) == typeid(Integer64));
        Integer64* test_num = dynamic_cast<Integer64*>(test_cadr);
        CHECK(test_num->value() == 5);
        CHECK(test->to_string() == "(2 5)");
        delete test;
    }


    TEST_CASE("proper list of two symbol elements")
    {
        Pair* test = new Pair(new Symbol("foo"), new Pair(new Symbol("bar")));
        CHECK(typeid(*(test->get_car())) == typeid(Symbol));
        Symbol* test_car = dynamic_cast<Symbol*>(test->get_car());
        CHECK(test_car->value() == "foo");
        CHECK(typeid(*(test->get_cdr())) == typeid(Pair));
        Pair* test_cdr = dynamic_cast<Pair*>(test->get_cdr());
        Atom* test_cadr = test_cdr->get_car();
        CHECK(typeid(*test_cadr) == typeid(Symbol));
        Symbol* test_symbol = dynamic_cast<Symbol*>(test_cadr);
        CHECK(test_symbol->value() == "bar");
        CHECK(test->to_string() == "(foo bar)");
        delete test;
    }

    TEST_CASE("proper list of three elements")
    {
        Pair* test = new Pair(new Symbol("foo"), new Pair(new Symbol("bar"), new Pair(new Symbol("baz"))));
        CHECK(typeid(*(test->get_car())) == typeid(Symbol));
        Symbol* test_car = dynamic_cast<Symbol*>(test->get_car());
        CHECK(test_car->value() == "foo");
        CHECK(typeid(*(test->get_cdr())) == typeid(Pair));
        Pair* test_cdr = dynamic_cast<Pair*>(test->get_cdr());
        Atom* test_cadr = test_cdr->get_car();
        CHECK(typeid(*test_cadr) == typeid(Symbol));
        Symbol* test_symbol = dynamic_cast<Symbol*>(test_cadr);
        CHECK(test_symbol->value() == "bar");
        CHECK(test->to_string() == "(foo bar baz)");
        delete test;
    }

    TEST_CASE("improper list of three elements")
    {
        Pair* test = new Pair(new Symbol("foo"), new Pair(new Symbol("bar"), new Symbol("baz")));
        CHECK(typeid(*(test->get_car())) == typeid(Symbol));
        Symbol* test_car = dynamic_cast<Symbol*>(test->get_car());
        CHECK(test_car->value() == "foo");
        CHECK(typeid(*(test->get_cdr())) == typeid(Pair));
        Pair* test_cdr = dynamic_cast<Pair*>(test->get_cdr());
        Atom* test_cadr = test_cdr->get_car();
        CHECK(typeid(*test_cadr) == typeid(Symbol));
        Symbol* test_symbol = dynamic_cast<Symbol*>(test_cadr);
        CHECK(test_symbol->value() == "bar");
        Atom* test_cddr = test_cdr->get_cdr();
        test_symbol = dynamic_cast<Symbol*>(test_cddr);
        CHECK(typeid(*test_cddr) == typeid(Symbol));
        CHECK(test_symbol->value() == "baz");
        CHECK(test->to_string() == "(foo bar . baz)");
        delete test;
    }

    TEST_CASE("list of a symbol and a list")
    {
        Pair* test = new Pair(new Symbol("foo"), new Pair(new Pair(new Symbol("bar"), new Pair(new Symbol("baz")))));
        CHECK(typeid(*(test->get_car())) == typeid(Symbol));
        Symbol* test_car = dynamic_cast<Symbol*>(test->get_car());
        CHECK(test_car->value() == "foo");
        CHECK(typeid(*(test->get_cdr())) == typeid(Pair));
        Pair* test_cdr = dynamic_cast<Pair*>(test->get_cdr());
        Atom* test_cadr = test_cdr->get_car();
        CHECK(typeid(*test_cadr) == typeid(Pair));
        Pair* test_inner_list = dynamic_cast<Pair*>(test_cadr);
        CHECK(test_inner_list->to_string() == "(bar baz)");
        CHECK(test->to_string() == "(foo (bar baz))");
        delete test;
    }
}

TEST_SUITE("reading s-expressions and converting them to strings")
{
    TEST_CASE("empty file")
    {
        std::stringstream src;
        src << "";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "");
        delete test;
    }

    TEST_CASE("integer")
    {
        std::stringstream src;
        src << "42";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "42");
        delete test;
    }

    TEST_CASE("floating-point number")
    {
        std::stringstream src;
        src << "17.23";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "17.230000");
        delete test;
    }

    TEST_CASE("symbol #1")
    {
        std::stringstream src;
        src << "foo";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "foo");
        delete test;
    }

    TEST_CASE("symbol #2")
    {
        std::stringstream src;
        src << "an-atom";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "an-atom");
        delete test;
    }

    TEST_CASE("null list")
    {
        std::stringstream src;
        src << "()";
        Atom* test = read_expression(src);
        CHECK(test == nullptr);
        delete test;
    }

    TEST_CASE("list of one element")
    {
        std::stringstream src;
        src << "(foo)";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "(foo)");
        delete test;
    }

    TEST_CASE("improper list of two elements")
    {
        std::stringstream src;
        src << "(foo . bar)";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "(foo . bar)");
        delete test;
    }

    TEST_CASE("proper list of two integer elements with extra spaces")
    {
        std::stringstream src;
        src << "(23     42)";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "(23 42)");
        delete test;
    }

    TEST_CASE("proper list of two elements with extra spaces")
    {
        std::stringstream src;
        src << "(foo     bar)";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "(foo bar)");
        delete test;
    }

    TEST_CASE("proper list of three elements")
    {
        std::stringstream src;
        src << "(foo bar quux)";
        Atom* test = read_expression(src);
        Pair* test_list = dynamic_cast<Pair*>(test);
        CHECK(typeid(*(test_list->get_car())) == typeid(Symbol));
        Symbol* test_car = dynamic_cast<Symbol*>(test_list->get_car());
        CHECK(test_car->value() == "foo");
        CHECK(typeid(*(test_list->get_cdr())) == typeid(Pair));
        Pair* test_cdr = dynamic_cast<Pair*>(test_list->get_cdr());
        Atom* test_cadr = test_cdr->get_car();
        CHECK(typeid(*test_cadr) == typeid(Symbol));
        Symbol* test_symbol = dynamic_cast<Symbol*>(test_cadr);
        CHECK(test_symbol->value() == "bar");
        CHECK(test->to_string() == "(foo bar quux)");
        delete test;
    }

    TEST_CASE("improper list of three elements")
    {
        std::stringstream src;
        src << "(foo bar . quux)";
        Atom* test = read_expression(src);
        Pair* test_list = dynamic_cast<Pair*>(test);
        CHECK(typeid(*(test_list->get_car())) == typeid(Symbol));
        Symbol* test_car = dynamic_cast<Symbol*>(test_list->get_car());
        CHECK(test_car->value() == "foo");
        CHECK(typeid(*(test_list->get_cdr())) == typeid(Pair));
        Pair* test_cdr = dynamic_cast<Pair*>(test_list->get_cdr());
        Atom* test_cadr = test_cdr->get_car();
        CHECK(typeid(*test_cadr) == typeid(Symbol));
        Symbol* test_symbol = dynamic_cast<Symbol*>(test_cadr);
        CHECK(test_symbol->value() == "bar");
        Atom* test_cddr = test_cdr->get_cdr();
        CHECK(typeid(*test_cddr) == typeid(Symbol));
        test_symbol = dynamic_cast<Symbol*>(test_cddr);
        //CHECK(test_symbol->value() == "quux");
        CHECK(test->to_string() == "(foo bar . quux)");
        delete test;
    }

    TEST_CASE("malformed improper list")
    {
        std::stringstream src;
        src << "(foo bar . baz quux)";
        REQUIRE_THROWS(read_expression(src));
    }


    TEST_CASE("list of a symbol and a list")
    {
        std::stringstream src;
        src << "(foo (bar baz))";
        Atom* test = read_expression(src);
        CHECK(test->to_string() == "(foo (bar baz))");
        delete test;
    }

}