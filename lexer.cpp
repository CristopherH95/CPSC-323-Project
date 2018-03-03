#include "lexer.h"

lexer::lexer() {
    //constructor
}

lexer::~lexer() {
    //destructor
}

//TODO: Documentation
bool lexer::is_keyword(const std::string& word) const {
    bool found = false;

    if (rat18s_keywords.count(word) > 0) {
        found = true;
    }

    return found;
}

//TODO: Documentation
bool lexer::is_seperator(const std::string& symbol) const {
    bool found = false;

    if (rat18s_seperators.count(symbol) > 0) {
        found = true;
    }

    return found;
}

//TODO: Documentation
bool lexer::is_operator(const std::string& symbol) const {
    bool found = false;

    if (rat18s_operators.count(symbol) > 0) {
        found = true;
    }

    return found;
}

//TODO: Documentation
void lexer::add_token(const std::string& type, const std::string& word) {
    token next_token;

    next_token.type = type;
    next_token.lexeme = word;
    if (next_token.type == ident_tok && !(identifiers.count(next_token.lexeme) > 0)) {
        identifiers.insert(next_token.lexeme);
    }
    p_tokens.push_back(next_token);
}

//TODO: Documentation
void lexer::eval_seperators(const std::string& word, std::vector<std::string>& words) {
    int i = 0;
    int pos = 0;
    int count_no_sep = 0;
    bool found_sep = false;
    std::string check;

    std::cerr << "EVAL SEPERATORS BEGIN" << std::endl;
    while (i < word.size()) {
        check = "";
        check += word[i];

        if ((is_seperator(check) || word[i] == rat18s_cmt_symbol) && found_sep && word.size() <= i + 1) {
            std::cerr << "condition 1" << std::endl;
            std::cerr << word.substr(pos, count_no_sep) << std::endl;
            if (!word.substr(pos, count_no_sep).empty()) {
                words.push_back(word.substr(pos, count_no_sep));
            }
            found_sep = false;
            std::cerr << check << std::endl;
            words.push_back(check);
        }
        else if ((is_seperator(check) || word[i] == rat18s_cmt_symbol) && !found_sep && word.size() <= i + 1) {
            std::cerr << "condition 2" << std::endl;
            std::cerr << word.substr(pos, count_no_sep) << std::endl;
            if (!word.substr(pos, count_no_sep).empty()) {
                words.push_back(word.substr(pos, count_no_sep));
            }
            std::cerr << word.substr(word.size() - 1, 1) << std::endl;
            words.push_back(word.substr(word.size() - 1, 1));
        }
        else if (!(is_seperator(check) || word[i] == rat18s_cmt_symbol) && found_sep && word.size() <= i + 1) {
            count_no_sep++;
            std::cerr << "condition 3" << std::endl;
            std::cerr << word.substr(pos, count_no_sep) << std::endl;
            words.push_back(word.substr(pos, count_no_sep));
        }
        else if ((is_seperator(check) || word[i] == rat18s_cmt_symbol) && !found_sep) {
            std::cerr << "condition 4" << std::endl;
            if (i > 0 && pos == 0) {
                std::cerr << word.substr(pos, i) << std::endl;
                words.push_back(word.substr(pos, i));
            }
            pos = i + 1;
            std::cerr << check << std::endl;
            words.push_back(check);
            found_sep = true;
            pos = i + 1;
            count_no_sep = 0;
        }
        else if (found_sep && !(is_seperator(check) || word[i] == rat18s_cmt_symbol)) {
            std::cerr << "condition 5" << std::endl;
            count_no_sep++;
        }
        else if (found_sep && (is_seperator(check) || word[i] == rat18s_cmt_symbol)) {
            std::cerr << "condition 6" << std::endl;
            std::cerr << word.substr(pos, count_no_sep) << std::endl;
            words.push_back(word.substr(pos, count_no_sep));
            found_sep = false;
            i--;
        }
        else if (!found_sep && !(is_seperator(check) || word[i] == rat18s_cmt_symbol)) {
            std::cerr << "condition 7" << std::endl;
            count_no_sep++;
        }
        i++;
    }

    if (count_no_sep == word.size()) {
        words.push_back(word);
    }
    std::cerr << "EVAL SEPERATORS END" << std::endl;
}

//TODO: Documentation
void lexer::process_file(std::istream& input_file) {
    std::string word;
    bool comment = false;
    std::string comment_text = "";
    std::vector<std::string> seperated_words;

    while (input_file >> word) {
        std::cerr << "Current word: " << word << std::endl;
        seperated_words.clear();
        std::cerr << "Beginning seperator checks..." << std::endl;
        eval_seperators(word, seperated_words);
        std::cerr << "SEPERATED WORDS AFTER CHECKS: " << std::endl;
        for (int i = 0; i < seperated_words.size(); i++) {
            std::cerr << seperated_words[i] << " " << std::endl;
        }
        std::cerr << "Seperator checks done, checking tokens..." << std::endl;
        for (int i = 0; i < seperated_words.size(); i++) {
            if (seperated_words[i][0] == rat18s_cmt_symbol && comment == false) {
                std::cerr << "Comment found, tracking..." << std::endl;
                comment = true;
                comment_text += seperated_words[i] + " ";
            }
            else if (seperated_words[i][0] == rat18s_cmt_symbol && comment == true) {
                std::cerr << "Comment complete." << std::endl;
                comment = false;
                comment_text += seperated_words[i];
                this->add_token(com_tok, comment_text);
                comment_text = "";
                continue;
            }
            else if (comment) {
                std::cerr << "text is a comment: " << seperated_words[i] << std::endl;
                comment_text = comment_text + seperated_words[i] + " ";
            }
            if (!comment && seperated_words[i][0] == '-') {
                std::cerr << "STRING IS OP: " << seperated_words[i][0] << std::endl;
                this->add_token(op_tok, std::string(1, seperated_words[i][0]));
                seperated_words[i].erase(0, 1);
            }
            if (!comment && is_operator(seperated_words[i])) {
                std::cerr << "STRING IS OP: " << seperated_words[i] << std::endl;
                this->add_token(op_tok, seperated_words[i]);
                continue;
            }
            else if (!comment && is_seperator(seperated_words[i])) {
                std::cerr << "STRING IS SEP: " << seperated_words[i] << std::endl;
                this->add_token(sep_tok, seperated_words[i]);
                continue;
            }
            else if (!comment && is_identifier(seperated_words[i])) {
                std::cerr << "STRING IS ID: " << seperated_words[i] << std::endl;
                std::cerr << "Performing additional check...";
                if (!is_keyword(seperated_words[i])) {
                    std::cerr << "Identified as identifier." << std::endl;
                    this->add_token(ident_tok, seperated_words[i]);
                }
                else {
                    std::cerr << "Identified as keyword." << std::endl;
                    this->add_token(keyw_tok, seperated_words[i]);
                }
            }
            else if (!comment && is_integer(seperated_words[i])) {
                std::cerr << "STRING IS INT: " << seperated_words[i] << std::endl;
                this->add_token(integer_tok, seperated_words[i]);
            }
            else if (!comment && is_real(seperated_words[i])) {
                std::cerr << "STRING IS REAL: " << seperated_words[i] << std::endl;
                this->add_token(real_tok, seperated_words[i]);
            }
            else if (!comment) {
                std::cerr << "STRING IS ERROR: " << seperated_words[i] << std::endl;
                this->add_token(err_rok, seperated_words[i]);
            }
        }
    }

    std::cerr << "Processing complete." << std::endl;
}


bool lexer::is_identifier(const std::string& token) {
    //finite state machine check for identifier
    return false;
}

bool lexer::is_integer(const std::string& token) {
    //finite state machine check for integer
    return false;
}

bool lexer::is_real(const std::string& token) {
    //finite state machine check for real
    return false;
}

//TODO: Documentation
void lexer::print_tokens(std::ostream& output_dest) const {
    output_dest << std::setw(50) << std::left << "tokens" << std::right
                << "lexemes" << std::endl;
    output_dest << std::setw(60) << std::setfill('-') << "";
    output_dest << std::setfill(' ') << std::endl;
    for (int i = 0; i < p_tokens.size(); i++) {
        output_dest << std::setw(50) << std::left << p_tokens[i].type
                    << std::right << p_tokens[i].lexeme;
        output_dest << std::endl;
    }
}