ifeq ($(OS), Windows_NT)
	RM = del /Q
	FILE = compiler.exe
else
	ifeq ($(shell uname), Linux)
		RM = rm -f
		FILE = compiler
	endif
endif

rat18s_compiler : main.cpp lexer.cpp lexer.h parser.cpp parser.h 
	g++ -std=c++11 main.cpp lexer.cpp parser.cpp semantics.cpp -o compiler

clean : 
	$(RM) $(FILE)