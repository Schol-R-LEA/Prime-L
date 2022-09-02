#ifndef READ_H
#define READ_H

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


Atom* read_expression(std::ifstream& src);
Atom* read_list(std::ifstream& src);
Atom* read_number(char start_ch, std::ifstream& src);
Atom* read_symbol(char start_ch, std::ifstream& src);

#endif