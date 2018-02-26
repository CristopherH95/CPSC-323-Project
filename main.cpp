#include <iostream>
#include <string>
#include "lexer.h"
using namespace std;

//TODO: grab filename from command line (or other input) and run logic

int main(int argc, char** argv) {
    lexer rat18s_lex = lexer();
    string file_to_process;

    cout << "Program begin" << endl;
    if (argc < 2) {
        cout << "USAGE: <program calling name> <file name>" << endl;
    }
    else {
        file_to_process = string(argv[1]);
        cout << "File to process: " << argv[1] << endl;
        //do stuff
    }

    return 0;
}