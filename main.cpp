#include <iostream>
#include <fstream>
#include <string>
#include "lexer.h"
#include "parser.h"
using namespace std;

//main is currently configured to output only parser data
int main(int argc, char** argv) {
    lexer rat18s_lex = lexer();
    parser rat18s_par = parser();
    string file_to_process;
    string target_file;
    fstream input_file;
    ofstream output_file;

    if (argc < 3) {
        cout << "USAGE: " << argv[0] << " <input file name> <output file name>" << endl;
    }
    else {
        cout << "Starting compilation process. . ." << endl;
        file_to_process = string(argv[1]);
        target_file = string(argv[2]);
        cout << "Processing file: " << file_to_process << endl;
        cout << "Saving output to file: " << target_file << endl;
        input_file.open(file_to_process);
        rat18s_lex.process_file(input_file);
        rat18s_par.initialize_parse();
        output_file.open(target_file);
        rat18s_par.parse(rat18s_lex, output_file);
        output_file.close();
        input_file.close();
        cout << "Done." << endl;
    }

    return 0;
}