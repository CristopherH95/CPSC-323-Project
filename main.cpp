#include <iostream>
#include <fstream>
#include <string>
#include "lexer.h"
using namespace std;

int main(int argc, char** argv) {
    lexer rat18s_lex = lexer();
    string file_to_process;
    string target_file;
    fstream input_file;
    ofstream output_file;

    if (argc < 3) {
        cout << "USAGE: rat18s_lexer <input file name> <output file name>" << endl;
    }
    else {
        cout << "Starting lexical analyzer. . ." << endl;
        file_to_process = string(argv[1]);
        target_file = string(argv[2]);
        cout << "Processing file: " << file_to_process << endl;
        cout << "Saving tokens to file: " << target_file << endl;
        input_file.open(file_to_process);
        rat18s_lex.process_file(input_file);
        output_file.open(target_file);
        rat18s_lex.print_tokens(output_file);
        output_file.close();
        input_file.close();
        cout << "Done." << endl;
    }

    return 0;
}