#ifndef READ_H
#define READ_H

#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <sstream>


class invalid_numeric_value_exception
{
public:
    invalid_numeric_value_exception() {};
};


class unexpected_end_of_file_exception
{
public:
    unexpected_end_of_file_exception() {};
};


void read_src_file(std::stringstream& src, std::ifstream& src_file);

Atom* read_expression(std::stringstream& src);
Atom* read_list(std::stringstream& src);
Atom* read_number(char start_ch, std::stringstream& src);
Atom* read_symbol(char start_ch, std::stringstream& src);

#endif