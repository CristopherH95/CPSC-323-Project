#pragma once
#include <fstream>
#include <map>
#include <vector>
#include <string>
//any more includes

//TODO: lexer methods/members
//Note: what is the best approach to implement state table?
//Note2: should we handle file within class or within main?

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


class lexer {
    public:
        lexer();
        ~lexer();
        bool is_identifier(const std::string& token);
        bool is_integer(const std::string& token);
        bool is_real(const std::string& token);
        //public members/methods
    private:
        //private members
        std::vector<std::string> tokens;    //NOTE: should we use strings as tokens, or a structure for tokens?
};