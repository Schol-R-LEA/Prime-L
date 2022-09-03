#include <iostream>
#include <string>
#include <typeinfo>
#include "atom.h"

Pair::~Pair()
{
    if (car != nullptr)
    {
        delete car;
        car = nullptr;
    }
    if (cdr != nullptr)
    {
        delete cdr;
        cdr = nullptr;
    }
}


std::string to_string_list_helper(Pair *p)
{

    std::string midpoint = " . ";

    if (p == nullptr)
    {
        return "";
    }

    if (p->get_car() == nullptr)
    {
        if (p->get_cdr() == nullptr)
        {
            return "";
        }
        else
        {
            return "()" + midpoint + p->get_cdr()->to_string();
        }
    }
    else if (p->get_cdr() == nullptr)
    {
        return p->get_car()->to_string();
    }
    else
    {
        if (typeid(*(p->get_cdr())) == typeid(Pair))
        {
            return p->get_car()->to_string()
                   + " " 
                   + to_string_list_helper(dynamic_cast<Pair *>(p->get_cdr()));
        }
        else
        {
            return p->get_car()->to_string() + midpoint + p->get_cdr()->to_string();
        }
    }
}


std::string Pair::to_string()
{
    return "(" + to_string_list_helper(dynamic_cast<Pair *>(this)) + ")";
}