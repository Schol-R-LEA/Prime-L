#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>
#include "atom.h"
#include "read.h"


void read_src_file(std::stringstream& src, std::ifstream& src_file)
{
    while (src_file)
    {
        src << src_file.rdbuf();
    }
}



Atom* read_expression(std::stringstream& src)
{
    if (src.eof())
    {
        throw new unexpected_end_of_file_exception();
    }

    char ch;
    src >> ch;

    if (std::iswspace(ch))
    {
        return read_expression(src);
    }
    else if (ch == '.')
    {
        return new Dot();
    }
    else if (ch == '(')
    {
        return read_list(src);
    }
    else if (ch == ')')
    {
        return new RightParen();
    }
    else if (std::isdigit(ch))
    {
        return read_number(ch, src);
    }
    else
    {
        return (read_symbol(ch, src));
    }
}


Atom* read_list(std::stringstream& src)
{
    Atom* head = read_expression(src);

    if (head == nullptr)
    {
        return nullptr;
    }

    if (typeid(*head) == typeid(RightParen))
    {
        return nullptr;
    }
    else if (typeid(*head) == typeid(Dot))
    {
        auto last = read_expression(src);
        // sanity check - is the next token a right parenthesis?
        auto next = read_expression(src);
        if (typeid(*next) != typeid(RightParen))
        {
            throw new malformed_improper_list_exception();
        }
        return last;
    }

    Atom* tail = read_expression(src);

    if (typeid(*tail) == typeid(Dot))
    {
        auto last = read_expression(src);
        Pair* temp = new Pair(head, last);
        // sanity check - is the next token a right parenthesis?
        auto next = read_expression(src);
        if (typeid(*next) != typeid(RightParen))
        {
            throw new malformed_improper_list_exception();
        }
        return temp;
    }
    if (typeid(*tail) == typeid(RightParen))
    {
        return new Pair(head);
    }
    else
    {
        return new Pair(head, new Pair(tail, read_list(src)));
    }
}



Atom* read_symbol(char start_ch, std::stringstream& src)
{
    char ch = start_ch;
    std::string ostr = "";

    while (!src.eof())
    {
        ostr += ch;
        char temp = src.peek();

        if (std::iswspace(temp) || temp == '.' || temp == '(' || temp == ')')
        {
            break;
        }
        src >> ch;
    }
    return new Symbol(ostr);
}



Atom* read_number(char start_ch, std::stringstream& src)
{
    char ch = start_ch;
    std::string ostr = "";
    bool fp = false;

    while (!src.eof())
    {
        if (ch == '.')
        {
            if (fp)
            {
                throw new invalid_numeric_value_exception();
            }
            else
            {
                fp = true;
            }
        }
        ostr += ch;
        char temp = src.peek();
        if (std::isdigit(temp) || temp == '.')
        {
            src >> ch;
        }
        else
        {
            break;
        }
    }

    if (fp)
    {
        return new FP_Double(std::strtod(ostr.c_str(), nullptr));
    }
    else
    {
        return new Integer64(std::strtol(ostr.c_str(), nullptr, 10));
    }
}

