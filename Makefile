CC=g++
OPTIONS=-Wall -Werror -Wpedantic -std=c++20
SRC=src
INCLUDE=-Iinclude
TEST=tests
BIN=bin

main: atom read
	$(CC) $(OPTIONS) $(INCLUDE) $(SRC)/main.cpp $(BIN)/atom.o $(BIN)/read.o -o $(BIN)/prime-l

testast: read atom
	$(CC) $(OPTIONS) $(INCLUDE) $(TEST)/test-ast.cpp $(BIN)/atom.o $(BIN)/read.o -o $(BIN)/test-ast


testread: read atom
	$(CC) $(OPTIONS) $(INCLUDE) $(TEST)/test-expr-reading.cpp $(BIN)/atom.o $(BIN)/read.o -o $(BIN)/test-expr-reading


read:
	$(CC) $(OPTIONS) $(INCLUDE) -c $(SRC)/read.cpp -o $(BIN)/read.o

atom:
	$(CC) $(OPTIONS) $(INCLUDE) -c $(SRC)/atom.cpp -o $(BIN)/atom.o