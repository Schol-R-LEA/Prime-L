#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <iostream>
#include <streambuf>
#include <typeinfo>
#include "atom.h"
#include "read.h"


Atom* read_expression(std::ifstream& src)
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


Atom* read_list(std::ifstream& src)
{
    Atom* head = read_expression(src);

    if(typeid(*head) == typeid(RightParen))
    {
        return new Pair();
    }

    Atom* tail = read_expression(src);

    if (typeid(*tail) == typeid(Dot))
    {
        return new Pair(head, read_expression(src));
    }
    else if(typeid(*tail) == typeid(RightParen))
    {
        return new Pair(head);
    }
    else if(typeid(*tail) == typeid(Pair))
    {
        return new Pair(head, new Pair(tail, read_list(src)));
    }
    else
    {
        return new Pair(head, new Pair(tail, read_list(src)));
    }

}



Atom* read_symbol(char start_ch, std::ifstream& src)
{
    char ch = start_ch;
    std::string ostr = "";

    while (!src.eof())
    {
        ostr += ch;
        char temp = src.peek();

        if (std::iswspace(temp) || temp == '(' || temp == ')')
        {
            break;
        }
        src >> ch;
    }
    return new Symbol(ostr);
}



Atom* read_number(char start_ch, std::ifstream& src)
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

