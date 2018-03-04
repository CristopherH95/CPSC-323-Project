all: lexer

lexer: main.o lexer.o
	g++ -std=c++0x main.cpp lexer.cpp -o lexer

main.o: main.cpp
	g++ -std=c++0x -c main.cpp

lexer.o: lexer.cpp
	g++ -std=c++0x -c lexer.cpp

cleen:
	rm -rf *o lexer
