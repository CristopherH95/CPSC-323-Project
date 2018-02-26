#include "lexer.h"

lexer::lexer() {
    //constructor
}

lexer::~lexer() {
    //destructor
}

bool lexer::is_identifier(const std::string& token) {
    //finite state machine check for identifier
}

bool lexer::is_integer(const std::string& token) {
    //finite state machine check for integer
}

bool lexer::is_real(const std::string& token) {
    //finite state machine check for real
}