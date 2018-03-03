#include <iostream>
#include <fstream>
#include <string>
#include "lexer.h"
using namespace std;

int main(int argc, char** argv) {
    lexer rat18s_lex = lexer();
    string file_to_process;
    fstream input_file;

    cout << "Program begin" << endl;
    if (argc < 2) {
        cout << "USAGE: <program calling name> <file name>" << endl;
    }
    else {
        file_to_process = string(argv[1]);
        cout << "File to process: " << file_to_process << endl;
        input_file.open(file_to_process);
        rat18s_lex.process_file(input_file);
        rat18s_lex.print_tokens(cout);
        input_file.close();
    }

    return 0;
}