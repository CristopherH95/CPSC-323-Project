#pragma once
#include <iostream>
#include <stack>
#include <map>
#include <utility>
#include <vector>
#include <string>
#include "lexer.h"

//Non-terminal symbols
const std::string RAT18S = "<RAT18S>"; 
const std::string OFD = "<Opt Function Definitions>";
const std::string FD = "<Function Definitions>";
const std::string FDP = "<Function Definitions Prime>";
const std::string FN = "<Function>";
const std::string OPL = "<Opt Parameter List>";
const std::string PL = "<Parameter List>";
const std::string PLP = "<Parameter List Prime>";
const std::string P = "<Parameter>";
const std::string Q = "<Qualifier>";
const std::string B = "<Body>";
const std::string ODL = "<Opt Declaration List>";
const std::string DL = "<Declaration List>";
const std::string DLP = "<Declaration List Prime>";
const std::string D = "<Declaration>";
const std::string IDS = "<IDs>";
const std::string IDSP = "<IDs Prime>";
const std::string SL = "<Statement List>";
const std::string SLP = "<Statement List Prime>";
const std::string S = "<Statement>";
const std::string CP = "<Compound>";
const std::string A = "<Assign>";
const std::string IF = "<IF>";
const std::string IFP = "<IF Prime>";
const std::string RET = "<Return>";
const std::string RETP = "<Return Prime>";
const std::string PR = "<Print>";
const std::string SC = "<Scan>";
const std::string WH = "<While>";
const std::string COND = "<Condition>";
const std::string RE = "<Relop>";
const std::string E = "<Expression>";
const std::string EPPP = "<Expression Prime3>";
const std::string EP = "<Expression Prime>";
const std::string EPP = "<Expression Prime2>";
const std::string T = "<Term>";
const std::string TPPP = "<Term Prime3>";
const std::string TP = "<Term Prime>";
const std::string TPP = "<Term Prime2>";
const std::string FCTR = "<Factor>";
const std::string PRIM = "<Primary>";
const std::string PRIMP = "<Primary Prime>";

//Terminals
const std::string PERCENT = "%%";
const std::string FUNCTION = "function";
const std::string LBRACK = "[";
const std::string RBRACK = "]";
const std::string COMM = ",";
const std::string COLON = ":";
const std::string LIT_INT = "int";
const std::string LIT_BOOL = "boolean";
const std::string LIT_REAL = "real";
const std::string LCURL = "{";
const std::string RCURL = "}";
const std::string SEMICOL = ";";
const std::string LPARAN = "(";
const std::string RPARAN = ")";
const std::string EQ = "=";
const std::string LIT_IF = "if";
const std::string LIT_ELSE = "else";
const std::string LIT_ENDIF = "endif";
const std::string LIT_RET = "return";
const std::string LIT_PUT = "put";
const std::string LIT_GET = "get";
const std::string LIT_WH = "while";
const std::string EQEQ = "==";
const std::string NEQ = "^=";
const std::string GREATER_THAN = ">";
const std::string LESS_THAN = "<";
const std::string GREATER_OR_EQ = ">=";
const std::string LESS_OR_EQ = "<=";
const std::string PLUS_SYM = "+";
const std::string MINUS_SYM = "-";
const std::string MULT = "*";
const std::string DIV = "/";
const std::string ABS_INTEGER = "<Integer>";
const std::string ABS_REAL = "<Real>";
const std::string ABS_IDENTIFIER = "<Identifier>";
const std::string LIT_TRUE = "true";
const std::string LIT_FALSE = "false";
const std::string END = "$";
const std::string empty = "<empty>";

typedef std::vector<std::string> prod;

//these correspond to all the productions from our set
const prod PRODE = { empty };
const prod PROD1 = { OFD, PERCENT, ODL, SL  };
const prod PROD2 = { FD };
const prod PROD3 = { FN, FDP };
//const prod PROD4 = { FD };
const prod PROD4 = { FUNCTION, ABS_IDENTIFIER, LBRACK, OPL, RBRACK, ODL, B };
const prod PROD5 = { PL };
const prod PROD6 = { P, PLP };
const prod PROD7 = { COMM, PL };
const prod PROD8 = { IDS, COLON, Q };
const prod PROD9 = { LIT_INT };
const prod PROD10 = { LIT_BOOL };
const prod PROD11 = { LIT_REAL };
const prod PROD12 = { LCURL, SL, RCURL };
const prod PROD13 = { DL };
const prod PROD14 = { D, SEMICOL, DLP };
//const prod PROD16 = { DL };
const prod PROD15 = { LIT_INT, IDS };
const prod PROD16 = { LIT_BOOL, IDS };
const prod PROD17 = { LIT_REAL, IDS };
const prod PROD18 = { ABS_IDENTIFIER, IDSP };
const prod PROD19 = { COMM, IDS };
const prod PROD20 = { S, SLP };
//const prod PROD21 = { SL };
const prod PROD21 = { CP };
const prod PROD22 = { A };
const prod PROD23 = { IF };
const prod PROD24 = { RET };
const prod PROD25 = { PR };
const prod PROD26 = { SC };
const prod PROD27 = { WH };
const prod PROD28 = { LCURL, SL, RCURL };
const prod PROD29 = { ABS_IDENTIFIER, EQ, E, SEMICOL };
const prod PROD30 = { LIT_IF, LPARAN, COND, RPARAN, S, IFP };
const prod PROD31 = { LIT_ELSE, S, LIT_ENDIF };
const prod PROD32 = { LIT_ENDIF };
const prod PROD33 = { LIT_RET, RETP };
const prod PROD34 = { SEMICOL };
const prod PROD35 = { E, SEMICOL };
const prod PROD36 = { LIT_PUT, LPARAN, E, RPARAN, SEMICOL };
const prod PROD37 = { LIT_GET, LPARAN, IDS, RPARAN, SEMICOL };
const prod PROD38 = { LIT_WH, LPARAN, COND, RPARAN, S };
const prod PROD39 = { E, RE, E };
const prod PROD40 = { EQEQ };
const prod PROD41 = { NEQ };
const prod PROD42 = { GREATER_THAN };
const prod PROD43 = { LESS_THAN };
const prod PROD44 = { GREATER_OR_EQ };
const prod PROD45 = { LESS_OR_EQ };
const prod PROD46 = { T, EPPP };
const prod PROD47 = { EP };
const prod PROD48 = { EPP };
const prod PROD49 = { PLUS_SYM, T, EP };
const prod PROD50 = { MINUS_SYM, T, EPP };
const prod PROD51 = { FCTR, TPPP };
const prod PROD52 = { TP };
const prod PROD53 = { TPP };
const prod PROD54 = { MULT, FCTR, TP };
const prod PROD55 = { DIV, FCTR, TPP };
const prod PROD56 = { MINUS_SYM, PRIM };
const prod PROD57 = { PRIM };
const prod PROD58 = { ABS_IDENTIFIER, PRIMP };
const prod PROD59 = { ABS_INTEGER };
const prod PROD60 = { LPARAN, E, RPARAN };
const prod PROD61 = { ABS_REAL };
const prod PROD62 = { LIT_TRUE };
const prod PROD63 = { LIT_FALSE };
const prod PROD64 = { LPARAN, IDS, RPARAN }; 

class parser {
    public:
        parser();
        ~parser();
        bool is_valid(const std::pair<std::string, std::string>& check_key) const;
        std::string prod_to_string(const prod& production) const;
        void initialize_parse();
        bool parse(lexer& rat18s_lex, std::ostream& db_output_dest);
        void derive_next(const token& in_sym, const std::string& curr_sym, std::ostream& db_output_dest, bool& fail_flag);
        
    private:
        std::map<std::pair<std::string, std::string>, prod> parse_table;
        std::stack<std::string> parsing_stack;
};