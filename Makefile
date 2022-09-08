CC=g++
OPTIONS=-Wall -Werror -Wpedantic -std=c++20
SRC=src
INCLUDE=-Iinclude
TEST=tests
BIN=bin

main: atom read symtab ast
	$(CC) $(OPTIONS) $(INCLUDE) $(SRC)/main.cpp $(BIN)/atom.o $(BIN)/read.o -o $(BIN)/prime-l

testast: ast atom
	$(CC) $(OPTIONS) $(INCLUDE) $(TEST)/test-ast.cpp $(BIN)/atom.o $(BIN)/abstract_syntax_tree.o -o $(BIN)/test-ast

testsymtab: symtab atom
	$(CC) $(OPTIONS) $(INCLUDE) $(TEST)/test-symtable.cpp $(BIN)/atom.o $(BIN)/symbol_table.o -o $(BIN)/test-symtab

testread: read atom
	$(CC) $(OPTIONS) $(INCLUDE) $(TEST)/test-expr-reading.cpp $(BIN)/atom.o $(BIN)/read.o -o $(BIN)/test-expr-reading

ast: atom
	$(CC) $(OPTIONS) $(INCLUDE) -c $(SRC)/abstract_syntax_tree.cpp -o $(BIN)/abstract_syntax_tree.o

symtab: atom
	$(CC) $(OPTIONS) $(INCLUDE) -c $(SRC)/symbol_table.cpp -o $(BIN)/symbol_table.o

read:
	$(CC) $(OPTIONS) $(INCLUDE) -c $(SRC)/read.cpp -o $(BIN)/read.o

atom:
	$(CC) $(OPTIONS) $(INCLUDE) -c $(SRC)/atom.cpp -o $(BIN)/atom.o