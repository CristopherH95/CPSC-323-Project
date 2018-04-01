#include "parser.h"

parser::parser() {
    //Parse table is a map using pairs of non-terminals and terminals
    parse_table.insert(std::make_pair(std::make_pair(RAT18S, PERCENT), PROD1));
    parse_table.insert(std::make_pair(std::make_pair(OFD, PERCENT), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(FDP, PERCENT), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(RAT18S, FUNCTION), PROD1));
    parse_table.insert(std::make_pair(std::make_pair(OFD, FUNCTION), PROD2));
    parse_table.insert(std::make_pair(std::make_pair(FD, FUNCTION), PROD3));
    parse_table.insert(std::make_pair(std::make_pair(FDP, FUNCTION), PROD2));
    parse_table.insert(std::make_pair(std::make_pair(FN, FUNCTION), PROD5));
    parse_table.insert(std::make_pair(std::make_pair(OPL, RBRACK), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(PLP, RBRACK), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(PLP, COMM), PROD8));
    parse_table.insert(std::make_pair(std::make_pair(IDSP, COMM), PROD19));
    parse_table.insert(std::make_pair(std::make_pair(IDSP, COLON), PRODE));
    parse_table.insert(std::make_pair(std::make_pair(Q, LIT_INT), PROD10));
    parse_table.insert(std::make_pair(std::make_pair(ODL, LIT_INT), PROD14));
    parse_table.insert(std::make_pair(std::make_pair(DL, LIT_INT), PROD15));
    parse_table.insert(std::make_pair(std::make_pair(DLP, LIT_INT), PROD14));
    parse_table.insert(std::make_pair(std::make_pair(D, LIT_INT), PROD17));
    parse_table.insert(std::make_pair(std::make_pair(Q, LIT_BOOL), PROD11));
    //TODO: Parse table inserts
}

parser::~parser() {

}

bool parser::is_valid(const std::pair<std::string, std::string>& check_key) const {
    bool valid = false;

    if (parse_table.count(check_key) > 0) {
        valid = true;
    }

    return valid;
}

std::string parser::prod_to_string(const prod& production) const {
    std::string prod_as_string = "";

    for (int i = 0; i < production.size(); i++) {
        prod_as_string += production[i];
    }

    return prod_as_string;
}

void parser::initialize_parse() {
    if (!parsing_stack.empty()) {
        while (!parsing_stack.empty()) {
            parsing_stack.pop();
        }
    }
    parsing_stack.push(END);
    parsing_stack.push(RAT18S);
}

bool parser::parse(lexer& rat18s_lex, std::ostream& db_output_dest) {
    token curr_tok;
    std::string in_symbol;
    bool fail_state = false;

    while (parsing_stack.top() != END && !fail_state) {
        curr_tok = rat18s_lex.next_token();
        db_output_dest << "Token: " << curr_tok.type << " Lexeme: " << curr_tok.lexeme << std::endl;

        if (curr_tok.type == ident_tok || curr_tok.type == integer_tok || curr_tok.type == real_tok) {
            in_symbol = curr_tok.type;
        }
        else {
            in_symbol = curr_tok.lexeme;
        }
        this->derive_next(curr_tok, in_symbol, db_output_dest, fail_state);
    }

    return fail_state;
}

void parser::derive_next(const token& in_sym, const std::string& curr_sym, std::ostream& db_output_dest, bool& fail_flag) {
    prod next_prod;

    if (this->is_valid(std::make_pair(parsing_stack.top(), curr_sym))) {
        do {
            db_output_dest << parsing_stack.top() << "->";
            parsing_stack.pop();
            next_prod = parse_table[std::make_pair(parsing_stack.top(), curr_sym)];
            db_output_dest << this->prod_to_string(next_prod);
            for (int i = next_prod.size() - 1; i >= 0; i--) {
                parsing_stack.push(next_prod[i]);
            }
        }while (this->is_valid(std::make_pair(parsing_stack.top(), curr_sym)) && 
                curr_sym != parsing_stack.top() &&
                parsing_stack.top() != END);
        
        if (!this->is_valid(std::make_pair(parsing_stack.top(), curr_sym))) {
            db_output_dest << "Syntax error: unexpected token " << in_sym.lexeme 
                           << " at line " << in_sym.line_number
                           << std::endl;
            fail_flag = true;
        }
        else if (curr_sym == parsing_stack.top()) {
            parsing_stack.pop();
        }
        else if (parsing_stack.top() == END) {
            db_output_dest << "END SYMBOL REACHED" << std::endl;
        }
        else {
            db_output_dest << "Unexpected fail state while processing: " << in_sym.lexeme
                           << " at line " << in_sym.line_number
                           << ", check parser source code" << std::endl;
            fail_flag = true;
        }
    }
    else {
        db_output_dest << "Syntax error: unexpected token " << in_sym.lexeme 
                       << " at line " << in_sym.line_number
                       << std::endl;
        fail_flag = true;
    }
}