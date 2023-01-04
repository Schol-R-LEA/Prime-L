#ifndef ATOM_H
#define ATOM_H

#include <string>
#include <cstdint>


class Atom
{
public:
    Atom() {};
    virtual ~Atom() {};
    virtual std::string to_string() {return "";};
};


class Symbol: public Atom
{
private:
    std::string literal;


public:
    Symbol(std::string s): literal(s) {};
    std::string value() {return literal;};
    virtual std::string to_string() {return literal;};
};

class Dot: public Atom
{
private:

public:
    Dot() {};
};


class RightParen: public Atom
{
private:

public:
    RightParen() {};
};


class Comment: public Atom
{
private:
    std::string comment;

public:
    Comment(std::string c): comment(c) {};
};


class Number: public Atom
{
private:

public:
    Number() {};
};


class Integer64: public Number
{
private:
    long long literal;
public:
    Integer64(long long i): literal(i) {};
    long long value() {return literal;};
    virtual std::string to_string() {return std::to_string(literal);};
};


class FP_Double: public Number
{
private:
    double literal;
public:
    FP_Double(double i): literal(i) {};
    double value() {return literal;};
    virtual std::string to_string() {return std::to_string(literal);};
};


class StringLiteral: public Atom
{
private:
    std::string literal;
public:
    StringLiteral(std::string s): literal(s) {};
    std::string value() {return literal;};
    virtual std::string to_string() {return literal;};
};



class Pair: public Atom
{
protected:
    Atom *car, *cdr;
public:
    Pair(): car(nullptr), cdr(nullptr) {};
    Pair(Atom* head): car(head), cdr(nullptr) {};
    Pair(Atom* head, Atom* tail): car(head), cdr(tail) {};
    virtual ~Pair();
    virtual std::string to_string();
    void set_car(Atom* a) {car = a;};
    void set_cdr(Atom* a) {cdr = a;};
    Atom* get_car() {return car;};
    Atom* get_cdr() {return cdr;};
};

#endif