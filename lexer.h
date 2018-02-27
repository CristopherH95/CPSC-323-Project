#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <string>
//any more includes


/*
    ***TABLES***

    Where L = the set of all letters in the alphabet
          D = the set of all digits 0-9
         /x/= accepting state
        ->x = starting state

    Identifier:
        L   D    {$}
->  1   2   ""   ""
   /2/  2   4    3
   /3/  ""  ""   ""
    4   2   4    3   

   Integer:
       {0}  {1-9}
->  1   2   3
   /2/  ""  ""
   /3/  4   5
   /4/  4   5
   /5/  4   5

   Real:
       {0}  {1-9}   {.}
->  1   2   3       ""
    2   ""  ""      4
    3   5   6       4
    4   7   8       ""
    5   5   6       4
    6   5   6       4
   /7/   9   10     ""
   /8/   9   10     ""
   /9/   9   10     ""
   /10/  9   10     ""
*/

//Token names here
const std::string sep_tok = "seperator";
const std::string keyw_tok = "keyword";
const std::string ident_tok = "identifier";
const std::string integer_tok = "integer";
const std::string real_tok = "real";
const std::string op_tok = "operator";
const std::string com_tok = "comment";
const std::string err_rok = "error";

//Keywords
const std::set<std::string> rat18s_keywords = {"int", "if", "else", 
                                            "endif", "while", "return",
                                            "get", "put", "boolean",
                                            "real", "function", "true",
                                            "false"};
//Seperators
const std::set<std::string> rat18s_seperators = {"%%", "[", "]",
                                            ";", ":", ",",
                                            "(", ")", "{", "}"};
//Operators
const std::set<std::string> rat18s_operators = {"==", "^=", ">", 
                                            "<", "=>", "=<", "+", "-",
                                            "*", "/", "="};

//Token struct
struct token {
    std::string type;
    std::string lexeme;
};


class lexer {
    public:
        lexer();
        ~lexer();
        bool is_identifier(const std::string& token);
        bool is_integer(const std::string& token);
        bool is_real(const std::string& token);
        void add_token(const std::string& type, const std::string& word);
        void process_file(std::istream& input_file);
        bool is_keyword(const std::string& word) const;
        bool is_seperator(const std::string& symbol) const;
        bool is_operator(const std::string& symbol) const;
        void eval_seperators(const std::string& word, std::vector<std::string>& words);
        void print_tokens(std::ostream& output_dest) const;
        //public members/methods
    private:
        //private members
        std::vector<token> p_tokens;
};