#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <ios>
#include <typeinfo>
#include "atom.h"
#include "read.h"


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <source> <destination>" << std::endl;
        std::exit(-1);
    }

    std::string src_filename = argv[1], dest_filename = argv[2];

    std::ifstream src_file;
    src_file.open(src_filename);
    std::ofstream dest_file;
    dest_file.open(dest_filename);

    Atom* expression = read_expression(src_file);
    dest_file << expression->to_string() << std::endl;

    delete expression;
    src_file.close();
    dest_file.close();

    return 0;
}
