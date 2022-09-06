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
    if (p == nullptr)
    {
        return "";
    }
    Atom *car = p->get_car(), *cdr = p->get_cdr();

    if (car == nullptr)
    {
        if (cdr == nullptr)
        {
            return "";
        }
        else
        {
            return "() " + cdr->to_string();
        }
    }
    else if (cdr == nullptr)
    {
        return car->to_string();
    }
    else if (typeid(*cdr) == typeid(Pair))
    {
        Pair* cdr_pair = dynamic_cast<Pair*>(cdr);
        Atom *cadr = cdr_pair->get_car(), *cddr = cdr_pair->get_cdr();
        if (cddr == nullptr)
        {
            if (cadr == nullptr)
            {
                return car->to_string();
            }
            else
            {
                return car->to_string() + " " + cadr->to_string();
            }
        }
        else if (typeid(*cddr) == typeid(Pair))
        {
            if (typeid(*car) == typeid(Pair))
            {
                return car->to_string() + " . " + cdr->to_string();
            }
            else
            {
                Pair* cddr_pair = dynamic_cast<Pair*>(cddr);
                return car->to_string()
                    + " " + cadr->to_string()
                    + ((cddr_pair->get_car() == nullptr)
                       ? ""
                       : " " + to_string_list_helper(cddr_pair));
            }
        }
        else
        {
            if (typeid(*car) == typeid(Pair))
            {
                return car->to_string()
                    + " . " + cdr->to_string();
            }
            else
            {
                return car->to_string()
                    + " " + cadr->to_string()
                    + " . "
                    + cddr->to_string();
            }
        }
    }
    else
    {
        return car->to_string() + " . " + cdr->to_string();
    }
}


std::string Pair::to_string()
{
    return "(" + to_string_list_helper(dynamic_cast<Pair *>(this)) + ")";
}