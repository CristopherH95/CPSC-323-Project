#pragma once
#include <iostream>
#include <stack>
#include <map>
#include <list>
#include <set>
#include <utility>
#include <vector>
#include <string>
#include "lexer.h"
#include "semantics.h"

//Semantic actions
const std::string NIL = "";
const std::string GEN_INSTR = "geninstr";
const std::string SAVE_ADDR = "saveaddr";
const std::string INV_ADDR = "invalidateaddr";
const std::string SAVE_ELSE_MARK = "saveelseaddr";
const std::string ELSE_JUMP = "jumpelse";
const std::string GET_ADDR = "getaddr";
const std::string PUSH_JUMP = "pushjmp";
const std::string BCK_PTCH = "backpatch";
const std::string PUSH_INT_INSTR = "PUSHI";
const std::string PUSH_MEM_INSTR = "PUSHM";
const std::string POP_MEM_INSTR = "POPM";
const std::string STD_OUT_INSTR = "STDOUT";
const std::string STD_IN_INSTR = "STDIN";
const std::string ADD_INSTR = "ADD";
const std::string SUB_INSTR = "SUB";
const std::string MUL_INSTR = "MUL";
const std::string DIV_INSTR = "DIV";
const std::string GRT_INSTR = "GRT";
const std::string LES_INSTR = "LES";
const std::string EQU_INSTR = "EQU";
const std::string NEQ_INSTR = "NEQ";
const std::string GEQ_INSTR = "GEQ";
const std::string LEQ_INSTR = "LEQ";
const std::string JMPZ_INSTR = "JUMPZ";
const std::string JMP_INSTR = "JUMP";
const std::string LBL_INSTR = "LABEL";
const std::string ADD_SYM_TABLE = "addtable";
const std::string CHK_SYM_TABLE = "checktable";
const std::string CHK_ASSIGN_DEST = "isassignvalid";
const std::string SAVE_VAR = "savevariable";
const std::string SAVE_TOK = "save";
const std::string USE_SAVED = "reversetok";
const std::string USE_VAR = "reversevar";
const std::string CHK_COND = "checkcdop";
const std::string PREP_STDIN = "expectinput";
const std::string CHK_INT = "checkisint";
const std::string PREP_ELSE = "prepelse";
const std::string PREP_MATH = "prepmath";

//set to check if symbol in parsing stack is for semantics
const std::set<std::string> semantic_symbols = {NIL, GEN_INSTR, SAVE_ADDR, GET_ADDR, PUSH_JUMP,
                                                BCK_PTCH, PUSH_INT_INSTR, PUSH_MEM_INSTR,
                                                POP_MEM_INSTR, STD_OUT_INSTR, STD_IN_INSTR,
                                                ADD_INSTR, SUB_INSTR, MUL_INSTR, DIV_INSTR,
                                                GRT_INSTR, LES_INSTR, EQU_INSTR, NEQ_INSTR, 
                                                GEQ_INSTR, LEQ_INSTR, JMPZ_INSTR, JMP_INSTR, 
                                                LBL_INSTR, ADD_SYM_TABLE, CHK_SYM_TABLE,
                                                SAVE_TOK, USE_SAVED, CHK_COND, SAVE_VAR, USE_VAR,
                                                SAVE_ELSE_MARK, ELSE_JUMP, PREP_STDIN, CHK_INT,
                                                CHK_ASSIGN_DEST, INV_ADDR, PREP_ELSE, PREP_MATH};

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
const std::string GREATER_OR_EQ = "=>";
const std::string LESS_OR_EQ = "=<";
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

//productions typedef
typedef std::vector<std::string> prod;

//these correspond to all the productions from our set
const prod PRODE = { empty };
const prod PROD1 = { OFD, PERCENT, ODL, SL  };
const prod PROD2 = { FD };
const prod PROD3 = { FN, FDP };
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
//modded for semantics
const prod PROD15 = { SAVE_TOK, ADD_SYM_TABLE, LIT_INT, IDS };
//modded for semantics
const prod PROD16 = { SAVE_TOK, ADD_SYM_TABLE, LIT_BOOL, IDS };
//modded for semantics
const prod PROD17 = { SAVE_TOK, ADD_SYM_TABLE, LIT_REAL, IDS };
//modded for semantics
const prod PROD18 = { SAVE_VAR, GET_ADDR, ABS_IDENTIFIER, IDSP };
//modded for semantics
const prod PROD19 = { COMM, ADD_SYM_TABLE, USE_SAVED, IDS };
const prod PROD20 = { S, SLP };
const prod PROD21 = { CP };
const prod PROD22 = { A };
const prod PROD23 = { IF };
const prod PROD24 = { RET };
//modded for semantics
const prod PROD25 = { PR, GEN_INSTR, STD_OUT_INSTR, NIL };
//modded for semantics
const prod PROD26 = { PREP_STDIN, SC, GEN_INSTR, STD_IN_INSTR, NIL, GEN_INSTR, POP_MEM_INSTR, GET_ADDR, USE_VAR };
const prod PROD27 = { WH };
const prod PROD28 = { LCURL, SL, RCURL };
//modded for semantics
const prod PROD29 = { SAVE_TOK, CHK_SYM_TABLE, CHK_ASSIGN_DEST, ABS_IDENTIFIER, EQ, E, GEN_INSTR, POP_MEM_INSTR, GET_ADDR, USE_SAVED, SEMICOL };
//modded for semantics
const prod PROD30 = { PREP_ELSE, SAVE_ADDR, LIT_IF, LPARAN, COND, RPARAN, S, BCK_PTCH, IFP };
//modded for semantics
const prod PROD31 = { SAVE_ELSE_MARK, LIT_ELSE, S, ELSE_JUMP, INV_ADDR, LIT_ENDIF };
const prod PROD32 = { INV_ADDR, LIT_ENDIF };
const prod PROD33 = { LIT_RET, RETP };
const prod PROD34 = { SEMICOL };
const prod PROD35 = { E, SEMICOL };
const prod PROD36 = { LIT_PUT, LPARAN, E, RPARAN, SEMICOL };
const prod PROD37 = { LIT_GET, LPARAN, IDS, RPARAN, SEMICOL };
//modded for semantics
const prod PROD38 = { SAVE_ADDR, GEN_INSTR, LBL_INSTR, NIL, LIT_WH, LPARAN, COND, RPARAN, S, GEN_INSTR, JMP_INSTR, BCK_PTCH };
//modded for semantics
const prod PROD39 = { E, RE, E, CHK_COND };
//modded for semantics
const prod PROD40 = { SAVE_TOK, EQEQ };
//modded for semantics
const prod PROD41 = { SAVE_TOK, NEQ };
//modded for semantics
const prod PROD42 = { SAVE_TOK, GREATER_THAN };
//modded for semantics
const prod PROD43 = { SAVE_TOK, LESS_THAN };
//modded for semantics
const prod PROD44 = { SAVE_TOK, GREATER_OR_EQ };
//modded for semantics
const prod PROD45 = { SAVE_TOK, LESS_OR_EQ };
//modded for semantics
const prod PROD46 = { T, EPPP };
const prod PROD47 = { EP };
const prod PROD48 = { EPP };
//modded for semantics
const prod PROD49 = { CHK_INT, PLUS_SYM, T, GEN_INSTR, ADD_INSTR, NIL, EP };
//modded for semantics
const prod PROD50 = { CHK_INT, MINUS_SYM, T, GEN_INSTR, SUB_INSTR, NIL, EPP };
const prod PROD51 = { FCTR, TPPP };
const prod PROD52 = { TP };
const prod PROD53 = { TPP };
//modded for semantics
const prod PROD54 = { CHK_INT, MULT, FCTR, GEN_INSTR, MUL_INSTR, NIL, TP };
//modded for semantics
const prod PROD55 = { CHK_INT, DIV, FCTR, GEN_INSTR, DIV_INSTR, NIL, TPP };
const prod PROD56 = { MINUS_SYM, PRIM };
const prod PROD57 = { PRIM };
//modded for semantics
const prod PROD58 = { PREP_MATH, CHK_SYM_TABLE, GEN_INSTR, PUSH_MEM_INSTR, GET_ADDR, ABS_IDENTIFIER, PRIMP };
//modded for semantics
const prod PROD59 = { GEN_INSTR, PUSH_INT_INSTR, ABS_INTEGER };
const prod PROD60 = { LPARAN, E, RPARAN };
const prod PROD61 = { ABS_REAL };
//modded for semantics
const prod PROD62 = { GEN_INSTR, PUSH_INT_INSTR, LIT_TRUE };
//modded for semantics
const prod PROD63 = { GEN_INSTR, PUSH_INT_INSTR, LIT_FALSE };
const prod PROD64 = { LPARAN, IDS, RPARAN }; 

class parser {
    public:
        parser();
        ~parser();
        bool is_valid(const std::pair<std::string, std::string>& check_key) const;
        std::string prod_to_string(const prod& production) const;
        void initialize_parse();
        bool parse(lexer& rat18s_lex, std::ostream& db_output_dest, semantic& sem_analyzer);
        bool parse(lexer& rat18s_lex, semantic& sem_analyzer);
        void derive_next(const token& in_sym, const std::string& curr_sym, 
                         std::ostream& db_output_dest, bool& good_parse, semantic& sem_analyzer);
        void derive_next(const token& in_sym, const std::string& curr_sym, 
                         bool& good_parse, semantic& sem_analyzer);
        bool is_semantic_symbol(const std::string& sym) const;
        const std::list<std::string>& get_semantics() const;
        
    private:
        std::map<std::pair<std::string, std::string>, prod> parse_table;
        std::stack<std::string> parsing_stack;
        std::list<std::string> semantics_list;
        token semantic_token;
        token semantic_var;
};