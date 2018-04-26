#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
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
const std::string ident_tok = "<Identifier>";
const std::string integer_tok = "<Integer>";
const std::string real_tok = "<Real>";
const std::string op_tok = "operator";
const std::string com_tok = "comment";
const std::string err_tok = "error";

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
//comment marker symbol
const char rat18s_cmt_symbol = '!';

//Token struct
struct token {
    std::string type;
    std::string lexeme;
    unsigned int line_number;
};


class lexer {
    public:
        lexer();
        ~lexer();
        token next_token();
        const std::deque<token>& get_tokens() const;
        bool check_tokens(std::ostream& output_dest, bool err_strm_output = true);
        bool check_tokens();
        bool exist_tokens() const;
        bool is_id_defined(const std::string check_id) const;
        bool is_identifier(const std::string& to_check);
        bool is_integer(const std::string& to_check);
        bool is_real(const std::string& to_check);
        void add_token(const std::string& type, const std::string& word, unsigned int l_num);
        void add_token(token copy_from);
        void process_file(std::istream& input_file);
        bool is_keyword(const std::string& word) const;
        bool is_seperator(const std::string& symbol) const;
        bool is_operator(const std::string& symbol) const;
        void eval_seperators(const std::string& word, std::vector<std::string>& words);
        void print_tokens(std::ostream& output_dest) const;
        //public members/methods
    private:
        //private members
        const int realState[10][3] =   { 
                                            {1,2,-99},
                                            {-99,-99,3},
                                            {4,5,3},
                                            {6,7,-99},
                                            {4,5,3},
                                            {4,5,3},
                                            {8,9,-99},
                                            {8,9,-99},
                                            {8,9,-99},
                                            {8,9,-99} 
                                        }; //value of '-99' is used as a default to no state transition
        const int integerState[5][2] =  { 
                                            {1,2},
                                            {-99,-99},
                                            {3,4},
                                            {3,4},
                                            {3,4} 
                                        }; //value of '-99' is used as a default to no state transition
        const int identifierState[4][3] =   { 
                                                {1,-99,-99},
                                                {1,3,2},
                                                {-99,-99,-99},
                                                {1,3,2} 
                                            }; //value of '-99' is used as a default to no state transition
        std::set<std::string> identifiers;
        std::deque<token> p_tokens;
};
