CC=g++
OPTIONS=-Wall -Werror -Wpedantic -std=c++20
SRC=src
TEST=tests
BIN=bin

main: atom read
	$(CC) $(OPTIONS) $(SRC)/main.cpp $(BIN)/atom.o $(BIN)/read.o -o $(BIN)/prime-l


testread: read atom
	$(CC) $(OPTIONS) -I$(SRC) $(TEST)/test-expr-reading.cpp $(BIN)/atom.o $(BIN)/read.o -o $(BIN)/test-expr-reading


read:
	$(CC) $(OPTIONS) -c $(SRC)/read.cpp -o $(BIN)/read.o

atom:
	$(CC) $(OPTIONS) -c $(SRC)/atom.cpp -o $(BIN)/atom.o