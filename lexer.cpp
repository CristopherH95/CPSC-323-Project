#include "lexer.h"

lexer::lexer() {
    //constructor
}

lexer::~lexer() {
    //destructor
}

bool lexer::is_identifier(const string& token) {
    //finite state machine check for identifier
}

bool lexer::is_integer(const string& token) {
    //finite state machine check for integer
}

bool lexer::is_real(const string& token) {
    //finite state machine check for real
}