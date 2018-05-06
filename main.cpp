#include <iostream>
#include <fstream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "semantics.h"
using namespace std;

//main is currently configured to output only parser data
int main(int argc, char** argv) {
    lexer rat18s_lex = lexer();
    parser rat18s_par = parser();
    semantic rat18s_sem = semantic();
    string file_to_process;
    string target_file;
    fstream input_file;
    ofstream output_file;
    bool good;

    if (argc < 3) {
        cout << "USAGE: " << argv[0] << " <input file name> <output file name>" << endl;
    }
    else {
        cout << "Starting compilation process. . ." << endl;
        file_to_process = string(argv[1]);
        target_file = string(argv[2]);
        cout << "Processing file: " << file_to_process << endl;
        cout << "Saving compilation output to file: " << target_file << endl;
        input_file.open(file_to_process);
        rat18s_lex.process_file(input_file);
        output_file.open(target_file);
        good = rat18s_lex.check_tokens();
        if (good) {
            rat18s_par.initialize_parse();
            good = rat18s_par.parse(rat18s_lex, rat18s_sem);
        }
        good = rat18s_sem.exec_semantics(rat18s_par.get_semantics());
        if (good) {
            rat18s_sem.print_instructions(output_file, false);
            output_file << endl << "SYMBOL TABLE" << endl;
            rat18s_sem.print_table(output_file, false);
        }
        output_file.close();
        input_file.close();
        if (!good) {
            cout << "Compilation failed." << endl;
        }
        else {
            output_file << "Done." << endl;
            cout << "Done." << endl;
        }
    }

    return 0;
}