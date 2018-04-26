#include "lexer.h"

lexer::lexer() {
    //constructor
}

lexer::~lexer() {
    //destructor
}

//get_tokens
//parameters: none
//returns: none
//This function will return a constant reference to the p_tokens member
const std::deque<token>& lexer::get_tokens() const {
    return p_tokens;
}

//check_tokens (overload)
//parameters: output_dest is a ostream destination for debug output, err_strm_output decides whether to also output to cerr
//returns: true/false (whether tokens contained errors or not)
//This function will remove all comment tokens, check for error tokens, and
//add an END symbol for the parser
bool lexer::check_tokens(std::ostream& output_dest, bool err_strm_output) {
    bool good_check = true;
    token end_mark;
    end_mark.lexeme = "$";
    end_mark.type = "END";
    end_mark.line_number = 0;

    for (std::deque<token>::iterator it = p_tokens.begin(); it != p_tokens.end();) {
        if (it->type == com_tok) {
            it = p_tokens.erase(it);
        }
        else if (it->type == err_tok) {
            output_dest << "Error invalid token: '" << it->lexeme
                        << "' on line " << it->line_number << std::endl;
            if (err_strm_output) {
                std::cerr << "Error invalid token: '" << it->lexeme
                            << "' on line " << it->line_number << std::endl;
            }
            good_check = false;
            ++it;
        }
        else {
            ++it;
        }
    }
    if (good_check) {
        p_tokens.push_back(end_mark);
    }

    return good_check;
}

//check_tokens
//parameters: none
//returns: true/false (whether tokens contained errors or not)
//This function will remove all comment tokens, check for error tokens, and
//add an END symbol for the parser
bool lexer::check_tokens() {
    bool good_check = true;
    token end_mark;
    end_mark.lexeme = "$";
    end_mark.type = "END";
    end_mark.line_number = 0;

    for (std::deque<token>::iterator it = p_tokens.begin(); it != p_tokens.end();) {
        if (it->type == com_tok) {
            it = p_tokens.erase(it);
        }
        else if (it->type == err_tok) {
            std::cerr << "Error invalid token: '" << it->lexeme
                        << "' on line " << it->line_number << std::endl;
            good_check = false;
            ++it;
        }
        else {
            ++it;
        }
    }
    if (good_check) {
        p_tokens.push_back(end_mark);
    }

    return good_check;
}

//exist_tokens
//parameters: none
//returns: true/false
//This function returns a boolean value for whether there exists any more tokens
bool lexer::exist_tokens() const {
    return !(p_tokens.empty());
}

//is_id_defined
//parameters: check_id (string) is the identifier name to check
//returns: true/false
//This function will check if the given name has been defined as an identifier
bool lexer::is_id_defined(const std::string check_id) const {
    bool found = false;

    if (identifiers.count(check_id) > 0) {
        found = true;
    }

    return found;
}

//next_token
//parameters: none
//returns: token
//This function will return the first token in order and then pop it from p_tokens
token lexer::next_token() {
    token first_token;

    first_token = p_tokens.front();
    p_tokens.pop_front();

    return first_token;
}

//is_keyword
//parameters: symbol (string) is the symbol to check
//returns: true/false
//This function will check if the given symbol is defined as a keyword in lexer.h
bool lexer::is_keyword(const std::string& word) const {
    bool found = false;

    if (rat18s_keywords.count(word) > 0) {
        found = true;
    }

    return found;
}

//is_seperator
//parameters: symbol (string) is the symbol to check
//returns: true/false
//This function will check if the given symbol is defined as a seperator in lexer.h
bool lexer::is_seperator(const std::string& symbol) const {
    bool found = false;

    if (rat18s_seperators.count(symbol) > 0) {
        found = true;
    }

    return found;
}

//is_operator
//parameters: symbol (string) is the symbol to check
//returns: true/false
//This function will check if the given symbol is defined as an operator in lexer.h
bool lexer::is_operator(const std::string& symbol) const {
    bool found = false;

    if (rat18s_operators.count(symbol) > 0) {
        found = true;
    }

    return found;
}

//add_token
//parameters: type (string) is the desired token type, word (string) is the lexeme
//returns: none
//This function will add a token to the lexer's p_tokens member variable with the
//given type and lexeme
void lexer::add_token(const std::string& type, const std::string& word, unsigned int l_num) {
    token next_token;

    next_token.type = type;
    next_token.lexeme = word;
    next_token.line_number = l_num;
    if (next_token.type == ident_tok && !(identifiers.count(next_token.lexeme) > 0)) {
        identifiers.insert(next_token.lexeme);
    }
    p_tokens.push_back(next_token);
}

//add_token
//parameters: copy_from (token) is a token struct to add to the p_tokens member
//returns: none
//This function will add a token to the lexer's p_tokens member variable with the
//same values as the given token
void lexer::add_token(token copy_from) {
    if (copy_from.type == ident_tok && !(identifiers.count(copy_from.lexeme) > 0)) {
        identifiers.insert(copy_from.lexeme);
    }
    p_tokens.push_back(copy_from);
}

//eval_seperators
//parameters: word (string) is the word to check, words (vector of strings) stores the seperated words
//returns: none
//This function will seperate the 'seperator' symbols defined in lexer.h from the given word, and
//then it will place these seperated strings into the given vector
void lexer::eval_seperators(const std::string& word, std::vector<std::string>& words) {
    int i = 0;
    int pos = 0;
    int count_no_sep = 0;
    bool found_sep = false;
    std::string check;

    //std::cerr << "EVAL SEPERATORS BEGIN" << std::endl;
    while (i < word.size()) {
        check = "";
        check += word[i];

        if ((is_seperator(check) || word[i] == rat18s_cmt_symbol || is_operator(check)) && found_sep && word.size() <= i + 1) {
            //std::cerr << "condition 1" << std::endl;
            //std::cerr << word.substr(pos, count_no_sep) << std::endl;
            if (!word.substr(pos, count_no_sep).empty()) {
                words.push_back(word.substr(pos, count_no_sep));
            }
            found_sep = false;
            //std::cerr << check << std::endl;
            words.push_back(check);
        }
        else if ((is_seperator(check) || word[i] == rat18s_cmt_symbol || is_operator(check)) && !found_sep && word.size() <= i + 1) {
            //std::cerr << "condition 2" << std::endl;
            //std::cerr << word.substr(pos, count_no_sep) << std::endl;
            if (!word.substr(pos, count_no_sep).empty()) {
                words.push_back(word.substr(pos, count_no_sep));
            }
            //std::cerr << word.substr(word.size() - 1, 1) << std::endl;
            words.push_back(word.substr(word.size() - 1, 1));
        }
        else if (!(is_seperator(check) || word[i] == rat18s_cmt_symbol || is_operator(check)) && found_sep && word.size() <= i + 1) {
            count_no_sep++;
            //std::cerr << "condition 3" << std::endl;
            //std::cerr << word.substr(pos, count_no_sep) << std::endl;
            if (!word.substr(pos, count_no_sep).empty()) {
                words.push_back(word.substr(pos, count_no_sep));
            }
        }
        else if ((is_seperator(check) || word[i] == rat18s_cmt_symbol || is_operator(check)) && !found_sep) {
            //std::cerr << "condition 4" << std::endl;
            if (i > 0 && pos == 0) {
                //std::cerr << word.substr(pos, i) << std::endl;
                words.push_back(word.substr(pos, i));
            }
            pos = i + 1;
            //std::cerr << check << std::endl;
            words.push_back(check);
            found_sep = true;
            pos = i + 1;
            count_no_sep = 0;
        }
        else if (found_sep && !(is_seperator(check) || word[i] == rat18s_cmt_symbol || is_operator(check))) {
            //std::cerr << "condition 5" << std::endl;
            count_no_sep++;
        }
        else if (found_sep && (is_seperator(check) || word[i] == rat18s_cmt_symbol || is_operator(check))) {
            //std::cerr << "condition 6" << std::endl;
            //std::cerr << word.substr(pos, count_no_sep) << std::endl;
            if (!word.substr(pos, count_no_sep).empty()) {
                words.push_back(word.substr(pos, count_no_sep));
            }
            found_sep = false;
            i--;
        }
        else if (!found_sep && !(is_seperator(check) || word[i] == rat18s_cmt_symbol || is_operator(check))) {
            //std::cerr << "condition 7" << std::endl;
            count_no_sep++;
        }
        i++;
    }

    if (count_no_sep == word.size()) {
        words.push_back(word);
    }
    //std::cerr << "EVAL SEPERATORS END" << std::endl;
}

//process_file
//parameters:input_file (istream) is the input stream handle to draw from
//returns: none
//This function will process a given input stream and tokenize all strings contained
void lexer::process_file(std::istream& input_file) {
    std::string word;
    bool comment = false;
    std::string comment_text = "";
    std::vector<std::string> seperated_words;
    std::string line;
    unsigned int line_num = 1;

    while (std::getline(input_file, line)) {
        std::stringstream ss(line);
        while (ss >> word) {
            //std::cerr << "Current word: " << word << std::endl;
            seperated_words.clear();
            //std::cerr << "Beginning seperator checks..." << std::endl;
            eval_seperators(word, seperated_words);
            for (int i = 0; i < seperated_words.size(); i++) {
                //std::cerr << seperated_words[i] << std::endl;
            }
            //std::cerr << "Seperator checks done, checking tokens..." << std::endl;
            for (int i = 0; i < seperated_words.size(); i++) {
                if (seperated_words[i][0] == rat18s_cmt_symbol && comment == false) {
                    //std::cerr << "Comment found, tracking..." << std::endl;
                    comment = true;
                    comment_text += seperated_words[i] + " ";
                }
                else if (seperated_words[i][0] == rat18s_cmt_symbol && comment == true) {
                    //std::cerr << "Comment complete." << std::endl;
                    comment = false;
                    comment_text += seperated_words[i];
                    this->add_token(com_tok, comment_text, line_num);
                    comment_text = "";
                    continue;
                }
                else if (comment) {
                    //std::cerr << "text is a comment: " << seperated_words[i] << std::endl;
                    comment_text = comment_text + seperated_words[i] + " ";
                }
                if (!comment && seperated_words[i].size() > 1 && seperated_words[i][0] == '-') {
                    //std::cerr << "STRING IS OP: " << seperated_words[i][0] << std::endl;
                    this->add_token(op_tok, std::string(1, seperated_words[i][0]), line_num);
                    seperated_words[i].erase(0, 1);
                }
                if (!comment && is_operator(seperated_words[i])) {
                    //std::cerr << "STRING IS OP: " << seperated_words[i] << std::endl;
                    this->add_token(op_tok, seperated_words[i], line_num);
                    continue;
                }
                else if (!comment && is_seperator(seperated_words[i])) {
                    //std::cerr << "STRING IS SEP: " << seperated_words[i] << std::endl;
                    this->add_token(sep_tok, seperated_words[i], line_num);
                    continue;
                }
                else if (!comment && is_identifier(seperated_words[i])) {
                    //std::cerr << "STRING IS ID: " << seperated_words[i] << std::endl;
                    //std::cerr << "Performing additional check...";
                    if (!is_keyword(seperated_words[i])) {
                        //std::cerr << "Identified as identifier." << std::endl;
                        this->add_token(ident_tok, seperated_words[i], line_num);
                    }
                    else {
                        //std::cerr << "Identified as keyword." << std::endl;
                        this->add_token(keyw_tok, seperated_words[i], line_num);
                    }
                }
                else if (!comment && is_integer(seperated_words[i])) {
                    //std::cerr << "STRING IS INT: " << seperated_words[i] << std::endl;
                    this->add_token(integer_tok, seperated_words[i], line_num);
                }
                else if (!comment && is_real(seperated_words[i])) {
                    //std::cerr << "STRING IS REAL: " << seperated_words[i] << std::endl;
                    this->add_token(real_tok, seperated_words[i], line_num);
                }
                else if (!comment) {
                    //std::cerr << "STRING IS ERROR: " << seperated_words[i] << std::endl;
                    this->add_token(err_tok, seperated_words[i], line_num);
                }
            }
        }
        line_num++;
    }

    std::cerr << "Processing complete." << std::endl;
}

//is_identifier
//parameters: to_check (string) is the word to check with the FSM
//returns: true/false
//This function will use a FSM state table to determine whether the given string is
//a valid 'identifier'
bool lexer::is_identifier(const std::string& to_check) {
    //std::cerr << "IDENTIFIER STATE MACHINE BEGIN" << std::endl;
    int currentState = 0;
	std::string word;
	word = to_check;
	int input = 99; //make starting value unattainable
	for (int i = 0; i < word.size(); i++) //loop through each char of string word
	{
		if (isalpha(word[i])) {
			input = 0; //input is a letter
        }
		else if (isdigit(word[i])) {
			input = 1; //input is a digit
        }
		else if (word[i] == '$') {
			input = 2; //input is a $ (dollar sign)
        }
		else {
			return false;
        }
        //std::cerr << "current state: " << currentState << std::endl;
        //std::cerr << "input value: " << input << std::endl;
		switch (input)
		{
			case 0: //state transition for letter input
				if (currentState == -99)
				{
					return false;
				}
				else {
					currentState = identifierState[currentState][input];
                }
				break;
			case 1: //state transition for digit input
				if (currentState == -99)
				{
					return false;
				}
				else {
					currentState = identifierState[currentState][input];
                }
				break;
			case 2:
				if (currentState == -99)
				{
					return false;
				}
				else {
					currentState = identifierState[currentState][input];
                }
				break;
			default: return false;
				break;
		}
        //std::cerr << "new state: " << currentState << std::endl;
	}

	switch (currentState)
	{
		case 1:
		case 2:
			return true; //return true for currentState = 1,2
			break;
		default:
			return false;
			break;
	}	
    
}

//is_integer
//parameters:to_check (string) is the word to check with the FSM
//returns: true/false
//This function uses a FSM state table define in lexer.h to determine if the given string
//is a valid 'integer'
bool lexer::is_integer(const std::string& to_check) {
    //std::cerr << "INTEGER STATE MACHINE BEGIN" << std::endl;
    int currentState = 0;
	std::string word;
	word = to_check;
	int input = 99; //set default to non-attainable input value
	for (int i = 0; i < word.size(); i++) //loop through each char of string word
	{
        //std::cerr << "INTEGER LOOP...INPUT (RAW) IS: " << word[i] << std::endl;
		if (isdigit(word[i]))
			if (word[i] == '0')
				input = 0;
			else
				input = 1; //input is a digit
		else
		{
            //std::cerr << "INT: false, bad input" << std::endl;
			return false;
			break;
		}
		switch (input)
		{
			case 0: //input is a 0
				if (currentState == -99) //checks if there exists a valid state transition
				{
                    //std::cerr << "INT: false, no state" << std::endl;
					return false;
				}
				else    
                {
                    //std::cerr << "CURRENT STATE: " << currentState << std::endl;
                    //std::cerr << "INPUT VALUE: " << input << std::endl;
                    currentState = integerState[currentState][input];
                    //std::cerr << "NEW STATE: " << currentState << std::endl;
                } //POTENTIAL ERROR NEED TO REFERENCE CLASS ARRAY
				break;
			case 1:
				if (currentState == -99) //checks if there exists a valid state transition
				{
                    std::cerr << "INT: false, no state" << std::endl;
					return false;
				}
				else 
                {
                    //std::cerr << "CURRENT STATE: " << currentState << std::endl;
                    //std::cerr << "INPUT VALUE: " << input << std::endl;
					currentState = integerState[currentState][input];
                    //std::cerr << "NEW STATE: " << currentState << std::endl;
                } //POTENTIAL ERROR NEED TO REFERENCE CLASS ARRAY
				break;
			default:  /*std::cerr << "INT: false, no state" << std::endl;*/ return false;
				break;
		}
	}
    //std::cerr << "CURRENT STATE (END):" << currentState << std::endl;
	switch (currentState)
	{
		case 1:
		case 2:
		case 3:
		case 4:
            //std::cerr << "ID: true, accepting state" << std::endl;
			return true; //return true for currentState = 1,2,3,4
			break;
		default:
            //std::cerr << "ID: false, reject state" << std::endl;
			return false;
			break;
	}
    
}

//is_real
//parameters: to_check (string) is the word to check with the FSM
//returns: true/false
//This function will use a FSM state table defined in lexer.h to determine if the given string
//is a valid 'real'
bool lexer::is_real(const std::string& to_check) {
    int currentState = 0;
	std::string word;
	word = to_check;
	int input = 99; //set default to non-attainable input value
	for (int i = 0; i < word.size(); i++) //loop through each char of string word
	{
		if (isdigit(word[i]))
			if (word[i] == '0')
				input = 0; //input is a Zero
			else
				input = 1; //input is a digit
		else if (word[i] == '.')
			input = 2; //input is a '.' (DOT)
		else
		{
			return false;
		}

		switch (input)
		{
			case 0: //input is a 0
				if (currentState == -99) //checks if there exists a valid state transition
				{
					return false;
				}
				else
					currentState = realState[currentState][input]; //POTENTIAL ERROR NEED TO REFERENCE CLASS ARRAY	
				break;
			case 1: //input is a digit (1-9)
				if (currentState == -99) //checks if there exists a valid state transition
				{
					return false;
				}
				else
					currentState = realState[currentState][input]; //POTENTIAL ERROR NEED TO REFERENCE CLASS ARRAY	
				break;
			case 2: //input is a dot
				if (currentState == -99) //checks if there exists a valid state transition
				{
					return false;
				}
				else
					currentState = realState[currentState][input]; //POTENTIAL ERROR NEED TO REFERENCE CLASS ARRAY	
				break;
			default: return false;
				break;
		}
	}
	switch (currentState)
	{
		case 6:
		case 7:
		case 8:
		case 9:
			return true; //checks end state and returns true if in accepting state
			break;
		default:
			return false;
			break;
	}
    
}

//print_tokens
//parameters: output_dest (ostream) is the destination to print to
//returns: none
//This function will print a table of tokens and their respective lexemes to a given destination
void lexer::print_tokens(std::ostream& output_dest) const {
    output_dest << std::setw(30) << std::left << "tokens" << std::setw(20)
                << "lexemes"
                << std::setw(20) << "line number" << std::endl;
    output_dest << std::setw(70) << std::setfill('-') << "";
    output_dest << std::setfill(' ') << std::endl;
    for (int i = 0; i < p_tokens.size(); i++) {
        output_dest << std::setw(30) << std::left << p_tokens[i].type
                    << std::setw(20) << p_tokens[i].lexeme 
                    << std::setw(20) << p_tokens[i].line_number;
        output_dest << std::endl;
    }
}
