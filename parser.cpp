#include "parser.h"

//parser
//constructor of parser class which builds the parse table upon object creation
parser::parser() {
    //Parse table is a map using pairs of non-terminals and terminals
    std::cerr << "Constructing parse table";
    parse_table.insert(std::make_pair(std::make_pair(RAT18S, PERCENT), PROD1));
    parse_table.insert(std::make_pair(std::make_pair(OFD, PERCENT), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(FDP, PERCENT), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(RAT18S, FUNCTION), PROD1));
    parse_table.insert(std::make_pair(std::make_pair(OFD, FUNCTION), PROD2));
    parse_table.insert(std::make_pair(std::make_pair(FD, FUNCTION), PROD3));
    parse_table.insert(std::make_pair(std::make_pair(FDP, FUNCTION), PROD3));
    parse_table.insert(std::make_pair(std::make_pair(FN, FUNCTION), PROD4));
    parse_table.insert(std::make_pair(std::make_pair(OPL, RBRACK), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(PLP, RBRACK), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(PLP, COMM), PROD7));
    parse_table.insert(std::make_pair(std::make_pair(IDSP, COMM), PROD19));
    parse_table.insert(std::make_pair(std::make_pair(IDSP, COLON), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(Q, LIT_INT), PROD9));
    parse_table.insert(std::make_pair(std::make_pair(ODL, LIT_INT), PROD13));
    parse_table.insert(std::make_pair(std::make_pair(DL, LIT_INT), PROD14));
    parse_table.insert(std::make_pair(std::make_pair(DLP, LIT_INT), PROD14));
    parse_table.insert(std::make_pair(std::make_pair(D, LIT_INT), PROD15));
    parse_table.insert(std::make_pair(std::make_pair(Q, LIT_BOOL), PROD10));
    parse_table.insert(std::make_pair(std::make_pair(ODL, LIT_BOOL), PROD13));
    parse_table.insert(std::make_pair(std::make_pair(DL, LIT_BOOL), PROD14));
    parse_table.insert(std::make_pair(std::make_pair(DLP, LIT_BOOL), PROD14));
    parse_table.insert(std::make_pair(std::make_pair(D, LIT_BOOL), PROD16));
    parse_table.insert(std::make_pair(std::make_pair(Q, LIT_REAL), PROD11));
    parse_table.insert(std::make_pair(std::make_pair(ODL, LIT_REAL), PROD13));
    parse_table.insert(std::make_pair(std::make_pair(DL, LIT_REAL), PROD14));
    parse_table.insert(std::make_pair(std::make_pair(DLP, LIT_REAL), PROD14));
    parse_table.insert(std::make_pair(std::make_pair(D, LIT_REAL), PROD17));
    parse_table.insert(std::make_pair(std::make_pair(Q, LIT_REAL), PROD11));
    parse_table.insert(std::make_pair(std::make_pair(B, LCURL), PROD12));
    parse_table.insert(std::make_pair(std::make_pair(ODL, LCURL), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(DLP, LCURL), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(SL, LCURL), PROD20));
    parse_table.insert(std::make_pair(std::make_pair(S, LCURL), PROD21));
    parse_table.insert(std::make_pair(std::make_pair(CP, LCURL), PROD12));
    parse_table.insert(std::make_pair(std::make_pair(SLP, RCURL), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(IDSP, SEMICOL), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(RETP, SEMICOL), PROD34));
    parse_table.insert(std::make_pair(std::make_pair(RETP, LPARAN), PROD35));
    parse_table.insert(std::make_pair(std::make_pair(COND, LPARAN), PROD39));
    parse_table.insert(std::make_pair(std::make_pair(E, LPARAN), PROD46));
    parse_table.insert(std::make_pair(std::make_pair(T, LPARAN), PROD51));
    parse_table.insert(std::make_pair(std::make_pair(FCTR, LPARAN), PROD57));
    parse_table.insert(std::make_pair(std::make_pair(PRIM, LPARAN), PROD60));
    parse_table.insert(std::make_pair(std::make_pair(PRIMP, LPARAN), PROD64));
    std::cerr << ".";
    parse_table.insert(std::make_pair(std::make_pair(IDSP, RPARAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EPPP, RPARAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EP, RPARAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EPP, RPARAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPPP, RPARAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TP, RPARAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPP, RPARAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(PRIMP, RPARAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(ODL, LIT_IF), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(DLP, LIT_IF), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(SL, LIT_IF), PROD20));
    parse_table.insert(std::make_pair(std::make_pair(SLP, LIT_IF), PROD20));
    parse_table.insert(std::make_pair(std::make_pair(S, LIT_IF), PROD23));
    parse_table.insert(std::make_pair(std::make_pair(IF, LIT_IF), PROD30));
    parse_table.insert(std::make_pair(std::make_pair(IFP, LIT_ELSE), PROD31));
    parse_table.insert(std::make_pair(std::make_pair(IFP, LIT_ENDIF), PROD32));
    parse_table.insert(std::make_pair(std::make_pair(ODL, LIT_RET), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(DLP, LIT_RET), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(SL, LIT_RET), PROD20));
    parse_table.insert(std::make_pair(std::make_pair(SLP, LIT_RET), PROD20));
    parse_table.insert(std::make_pair(std::make_pair(S, LIT_RET), PROD24));
    parse_table.insert(std::make_pair(std::make_pair(RET, LIT_RET), PROD33));
    parse_table.insert(std::make_pair(std::make_pair(ODL, LIT_PUT), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(DLP, LIT_PUT), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(SL, LIT_PUT), PROD20));
    parse_table.insert(std::make_pair(std::make_pair(SLP, LIT_PUT), PROD20));
    parse_table.insert(std::make_pair(std::make_pair(S, LIT_PUT), PROD25));
    parse_table.insert(std::make_pair(std::make_pair(PR, LIT_PUT), PROD36));
    parse_table.insert(std::make_pair(std::make_pair(ODL, LIT_GET), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(DLP, LIT_GET), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(SL, LIT_GET), PROD20));
    parse_table.insert(std::make_pair(std::make_pair(SLP, LIT_GET), PROD20));
    parse_table.insert(std::make_pair(std::make_pair(S, LIT_GET), PROD26));
    parse_table.insert(std::make_pair(std::make_pair(SC, LIT_GET), PROD37));
    parse_table.insert(std::make_pair(std::make_pair(ODL, LIT_WH), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(DLP, LIT_WH), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(SL, LIT_WH), PROD20));
    parse_table.insert(std::make_pair(std::make_pair(SLP, LIT_WH), PROD20));
    parse_table.insert(std::make_pair(std::make_pair(S, LIT_WH), PROD27));
    parse_table.insert(std::make_pair(std::make_pair(WH, LIT_WH), PROD38));
    parse_table.insert(std::make_pair(std::make_pair(RE, EQEQ), PROD40));
    parse_table.insert(std::make_pair(std::make_pair(EPPP, EQEQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EP, EQEQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EPP, EQEQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPPP, EQEQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TP, EQEQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPP, EQEQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(PRIMP, EQEQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(ODL, EQEQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(RE, NEQ), PROD41));
    parse_table.insert(std::make_pair(std::make_pair(EPPP, NEQ), PRODE));
    std::cerr << ".";
    parse_table.insert(std::make_pair(std::make_pair(EP, NEQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EPP, NEQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPPP, NEQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TP, NEQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPP, NEQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(PRIMP, NEQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(ODL, NEQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(RE, GREATER_THAN), PROD42));
    parse_table.insert(std::make_pair(std::make_pair(EPPP, GREATER_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EP, GREATER_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EPP, GREATER_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPPP, GREATER_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TP, GREATER_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPP, GREATER_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(PRIMP, GREATER_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(ODL, GREATER_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(RE, LESS_THAN), PROD43));
    parse_table.insert(std::make_pair(std::make_pair(EPPP, LESS_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EP, LESS_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EPP, LESS_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPPP, LESS_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TP, LESS_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPP, LESS_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(PRIMP, LESS_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(ODL, LESS_THAN), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(RE, GREATER_OR_EQ), PROD44));
    parse_table.insert(std::make_pair(std::make_pair(EPPP, GREATER_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EP, GREATER_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EPP, GREATER_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPPP, GREATER_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TP, GREATER_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPP, GREATER_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(PRIMP, GREATER_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(ODL, GREATER_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(RE, LESS_OR_EQ), PROD45));
    parse_table.insert(std::make_pair(std::make_pair(EPPP, LESS_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EP, LESS_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EPP, LESS_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPPP, LESS_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TP, LESS_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPP, LESS_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(PRIMP, LESS_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(ODL, LESS_OR_EQ), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EPPP, PLUS_SYM), PROD47));
    parse_table.insert(std::make_pair(std::make_pair(EP, PLUS_SYM), PROD49));
    parse_table.insert(std::make_pair(std::make_pair(TPPP, PLUS_SYM), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TP, PLUS_SYM), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPP, PLUS_SYM), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(PRIMP, PLUS_SYM), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(RETP, MINUS_SYM), PROD35));
    parse_table.insert(std::make_pair(std::make_pair(COND, MINUS_SYM), PROD39));
    parse_table.insert(std::make_pair(std::make_pair(E, MINUS_SYM), PROD46));
    parse_table.insert(std::make_pair(std::make_pair(EPPP, MINUS_SYM), PROD48));
    parse_table.insert(std::make_pair(std::make_pair(EPP, MINUS_SYM), PROD50));
    parse_table.insert(std::make_pair(std::make_pair(T, MINUS_SYM), PROD51));
    parse_table.insert(std::make_pair(std::make_pair(TPPP, MINUS_SYM), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TP, MINUS_SYM), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPP, MINUS_SYM), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(FCTR, MINUS_SYM), PROD56));
    parse_table.insert(std::make_pair(std::make_pair(PRIMP, MINUS_SYM), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPPP, MULT), PROD52));
    parse_table.insert(std::make_pair(std::make_pair(TP, MULT), PROD54));
    parse_table.insert(std::make_pair(std::make_pair(PRIMP, MULT), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPPP, DIV), PROD53));
    parse_table.insert(std::make_pair(std::make_pair(TPP, DIV), PROD55));
    parse_table.insert(std::make_pair(std::make_pair(PRIMP, DIV), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(RETP, ABS_INTEGER), PROD35));
    parse_table.insert(std::make_pair(std::make_pair(COND, ABS_INTEGER), PROD39));
    parse_table.insert(std::make_pair(std::make_pair(E, ABS_INTEGER), PROD46));
    parse_table.insert(std::make_pair(std::make_pair(T, ABS_INTEGER), PROD51));
    parse_table.insert(std::make_pair(std::make_pair(FCTR, ABS_INTEGER), PROD57));
    parse_table.insert(std::make_pair(std::make_pair(PRIM, ABS_INTEGER), PROD59));
    parse_table.insert(std::make_pair(std::make_pair(RETP, ABS_REAL), PROD35));
    parse_table.insert(std::make_pair(std::make_pair(COND, ABS_REAL), PROD39));
    parse_table.insert(std::make_pair(std::make_pair(E, ABS_REAL), PROD46));
    parse_table.insert(std::make_pair(std::make_pair(T, ABS_REAL), PROD51));
    parse_table.insert(std::make_pair(std::make_pair(FCTR, ABS_REAL), PROD57));
    parse_table.insert(std::make_pair(std::make_pair(PRIM, ABS_REAL), PROD61));
    parse_table.insert(std::make_pair(std::make_pair(OPL, ABS_IDENTIFIER), PROD5));
    parse_table.insert(std::make_pair(std::make_pair(PL, ABS_IDENTIFIER), PROD6));
    parse_table.insert(std::make_pair(std::make_pair(P, ABS_IDENTIFIER), PROD8));
    parse_table.insert(std::make_pair(std::make_pair(ODL, ABS_IDENTIFIER), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(DLP, ABS_IDENTIFIER), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(IDS, ABS_IDENTIFIER), PROD18));
    parse_table.insert(std::make_pair(std::make_pair(SL, ABS_IDENTIFIER), PROD20));
    parse_table.insert(std::make_pair(std::make_pair(SLP, ABS_IDENTIFIER), PROD20));
    parse_table.insert(std::make_pair(std::make_pair(S, ABS_IDENTIFIER), PROD22));
    parse_table.insert(std::make_pair(std::make_pair(A, ABS_IDENTIFIER), PROD29));
    parse_table.insert(std::make_pair(std::make_pair(RETP, ABS_IDENTIFIER), PROD35));
    parse_table.insert(std::make_pair(std::make_pair(COND, ABS_IDENTIFIER), PROD39));
    parse_table.insert(std::make_pair(std::make_pair(E, ABS_IDENTIFIER), PROD46));
    parse_table.insert(std::make_pair(std::make_pair(T, ABS_IDENTIFIER), PROD51));
    parse_table.insert(std::make_pair(std::make_pair(FCTR, ABS_IDENTIFIER), PROD57));
    std::cerr << ".";
    parse_table.insert(std::make_pair(std::make_pair(PRIM, ABS_IDENTIFIER), PROD58));
    parse_table.insert(std::make_pair(std::make_pair(RETP, LIT_TRUE), PROD35));
    parse_table.insert(std::make_pair(std::make_pair(COND, LIT_TRUE), PROD39));
    parse_table.insert(std::make_pair(std::make_pair(E, LIT_TRUE), PROD46));
    parse_table.insert(std::make_pair(std::make_pair(T, LIT_TRUE), PROD51));
    parse_table.insert(std::make_pair(std::make_pair(FCTR, LIT_TRUE), PROD57));
    parse_table.insert(std::make_pair(std::make_pair(PRIM, LIT_TRUE), PROD62));
    parse_table.insert(std::make_pair(std::make_pair(RETP, LIT_FALSE), PROD35));
    parse_table.insert(std::make_pair(std::make_pair(COND, LIT_FALSE), PROD39));
    parse_table.insert(std::make_pair(std::make_pair(E, LIT_FALSE), PROD46));
    parse_table.insert(std::make_pair(std::make_pair(T, LIT_FALSE), PROD51));
    parse_table.insert(std::make_pair(std::make_pair(FCTR, LIT_FALSE), PROD57));
    parse_table.insert(std::make_pair(std::make_pair(PRIM, LIT_FALSE), PROD63));
    parse_table.insert(std::make_pair(std::make_pair(SLP, END), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EPPP, SEMICOL), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EP, SEMICOL), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(EPP, SEMICOL), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPPP, SEMICOL), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TP, SEMICOL), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(TPP, SEMICOL), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(PRIMP, SEMICOL), PRODE));
    std::cerr << "Done" << std::endl;
}

parser::~parser() {
    //destructor
}

//is_valid
//parameters: check_key is the pair of strings to check against the table
//returns: true/false
//This method checks the parse table to see if the given pair (a non-terminal and terminal)
//has a corresponding entry in the table.
bool parser::is_valid(const std::pair<std::string, std::string>& check_key) const {
    bool valid = false;

    if (parse_table.count(check_key) > 0) {
        valid = true;
    }

    return valid;
}

//prod_to_string
//parameters: prod (string vector) is the production to convert
//returns: string
//This method takes the given production and converts it into a string, with spaces
std::string parser::prod_to_string(const prod& production) const {
    std::string prod_as_string = "";

    for (int i = 0; i < production.size(); i++) {
        prod_as_string += production[i];
        prod_as_string += " ";
    }

    return prod_as_string;
}

//initialize_parse
//parameters: none
//returns: none
//This method prepares the parsing stack for parsing.
//It essentially empties the stack, and then pushes the end symbol and start symbol
void parser::initialize_parse() {
    //std::cerr << "Prepping parsing stack...";
    if (!parsing_stack.empty()) {
        while (!parsing_stack.empty()) {
            parsing_stack.pop();
        }
    }
    parsing_stack.push(END);
    parsing_stack.push(RAT18S);
    //std::cerr << "Done" << std::endl;
}

//parse
//parameters:rat18s_lex is a lexer object, which will need tokens for this method to work,
//           db_output_dest is an ostream to output any debug data (such as productions used)
//returns: true/false (success flag)
//This method will loop over the parsing process, as long as there are no errors, there are tokens
//and the stack has not reached the end symbol
bool parser::parse(lexer& rat18s_lex, std::ostream& db_output_dest) {
    std::cerr << "Beginning parse..." << std::endl;
    token curr_tok;
    std::string in_symbol;
    bool good_parse = true;

    while (good_parse && rat18s_lex.exist_tokens()) {
        curr_tok = rat18s_lex.next_token();
        db_output_dest << "Token: " << curr_tok.type << " Lexeme: " << curr_tok.lexeme << std::endl;

        if (curr_tok.type == ident_tok || curr_tok.type == integer_tok || curr_tok.type == real_tok) {
            in_symbol = curr_tok.type;
        }
        else {
            in_symbol = curr_tok.lexeme;
        }
        //std::cerr << "Stack top before derive: " << parsing_stack.top() << std::endl;
        this->derive_next(curr_tok, in_symbol, db_output_dest, good_parse);
    }
    if (good_parse) {
        std::cerr << "Parse complete" << std::endl;
        db_output_dest << "Parse complete" << std::endl;
    }
    else {
        std::cerr << "Parse failed." << std::endl;
        db_output_dest << "Parse failed." << std::endl;
    }

    return good_parse;
}

//derive_next
//parameters: in_sym is a token currently in the input, curr_sym is the string version of the token to use
//            when checking the parse table, db_output_dest is an ostream for debug output, and good_parse
//            is a flag which will be set to false if any errors are encountered
//returns: none
//This function will perform derivations based on the parse table, the input, and the parsing stack
void parser::derive_next(const token& in_sym, const std::string& curr_sym, std::ostream& db_output_dest, bool& good_parse) {
    //std::cerr << "Performing derivation..." << std::endl;
    //std::cerr << "Input symbol for derivation: " << curr_sym << std::endl;
    prod next_prod;
    int prod_end;

    if (this->is_valid(std::make_pair(parsing_stack.top(), curr_sym))) {
        //std::cerr << "Found entry in table for stack symbol and input symbol pair." << std::endl;
        do {
            //std::cerr << "Beginning application of productions..." << std::endl;
            //std::cerr << "Current stack top: " << parsing_stack.top() << std::endl;
            db_output_dest << parsing_stack.top() << " -> ";
            next_prod = parse_table[std::make_pair(parsing_stack.top(), curr_sym)];
            parsing_stack.pop();
            //std::cerr << "Production retrieved is: " << next_prod.size() << " symbols." << std::endl;
            prod_end = next_prod.size() - 1;
            if (next_prod[prod_end] != empty) {
                //std::cerr << "Applying production to parsing stack...";
                db_output_dest << this->prod_to_string(next_prod) << std::endl;
                for (int i = prod_end; i >= 0; i--) {
                    parsing_stack.push(next_prod[i]);
                }
                //std::cerr << "Done" << std::endl;
            }
            else {
                db_output_dest << this->prod_to_string(next_prod) << std::endl;
            }
        }while (this->is_valid(std::make_pair(parsing_stack.top(), curr_sym)) && 
                curr_sym != parsing_stack.top());
        
        if (curr_sym == parsing_stack.top()) {
            //db_output_dest << in_sym.type << " -> " << in_sym.lexeme << std::endl;
            parsing_stack.pop();
        }
        else if (!this->is_valid(std::make_pair(parsing_stack.top(), curr_sym))) {
            std::cerr << "Syntax error: unexpected token '" << in_sym.lexeme 
                           << "' at line " << in_sym.line_number
                           << std::endl;
            good_parse = false;
        }
        else {
            std::cerr << "Unexpected fail state while processing: '" << in_sym.lexeme
                           << "' at line " << in_sym.line_number
                           << ", check parser source code" << std::endl;
            good_parse = false;
        }
    }
    else if (curr_sym == parsing_stack.top()) {
        db_output_dest << "TERMINAL MATCH" << std::endl;
        parsing_stack.pop();
    }
    else {
        std::cerr << "Could not find symbol pair...fail state set." << std::endl;
        std::cerr << "Syntax error: unexpected token '" << in_sym.lexeme 
                       << "' at line " << in_sym.line_number
                       << std::endl;
        good_parse = false;
    }
    //std::cerr << "Stack top after derive: " << parsing_stack.top() << std::endl;
}