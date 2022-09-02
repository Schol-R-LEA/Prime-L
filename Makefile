CC=g++
OPTIONS=-Wall -Werror -Wpedantic -std=c++20
SRC=src
BIN=bin

main: atom read
	$(CC) $(OPTIONS) $(SRC)/main.cpp $(BIN)/atom.o $(BIN)/read.o -o $(BIN)/prime-l

read:
	$(CC) $(OPTIONS) -c $(SRC)/read.cpp -o $(BIN)/read.o

atom:
	$(CC) $(OPTIONS) -c $(SRC)/atom.cpp -o $(BIN)/atom.o