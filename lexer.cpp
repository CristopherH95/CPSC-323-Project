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
    p_tokens.push_back(next_token);
}

//TODO: Documentation
void lexer::eval_seperators(const std::string& word, std::vector<std::string>& words) {
    int i = 0;
    int pos;
    int count_from_sep;
    int count_no_sep = 0;
    bool found_sep = false;
    std::string check;

    while (i < word.size()) {
        check = "";
        check += word[i];

        if (is_seperator(check) && found_sep && word.size() <= i + 1) {
            words.push_back(word.substr(pos, count_from_sep));
            found_sep = false;
            words.push_back(check);
        }
        else if (is_seperator(check) && !found_sep && word.size() <= i + 1) {
            words.push_back(word.substr(0, count_no_sep));
            words.push_back(word.substr(word.size() - 1, 1));
        }
        else if (is_seperator(check) && !found_sep) {
            words.push_back(check);
            found_sep = true;
            pos = i + 1;
            count_from_sep = 0;
        }
        else if (found_sep && !is_seperator(check)) {
            count_from_sep++;
        }
        else if (found_sep && is_seperator(check)) {
            words.push_back(word.substr(pos, count_from_sep));
            found_sep = false;
            i--;
        }
        else if (!found_sep && !is_seperator(check)) {
            count_no_sep++;
        }
        i++;
    }

    if (count_no_sep == word.size()) {
        words.push_back(word);
    }
}

//TODO: Documentation
void lexer::process_file(std::istream& input_file) {
    std::string word;
    bool comment;
    std::string comment_text = "";
    int word_end;
    std::vector<std::string> seperated_words;

    while (input_file >> word) {
        std::cerr << "Current word: " << word << std::endl;
        word_end = word.size() - 1;

        if (word[0] == '!' && comment == false) {
            std::cerr << "Comment found, tracking..." << std::endl;
            comment = true;
            comment_text += word + " ";
            continue;
        }
        else if ((word[0] == '!' || word[word_end] == '!') && comment == true) {
            std::cerr << "Comment complete." << std::endl;
            comment = false;
            comment_text += word;
            this->add_token(com_tok, comment_text);
            comment_text = "";
            continue;
        }
        if (!comment) {
            if (word.size() <= 2 && is_seperator(word)) {
                std::cerr << "STRING IS SEP: " << word << std::endl;
                std::cerr << "Skipping further seperator parse..." << std::endl;
                this->add_token(sep_tok, word);
                continue;
            }
            else if (word.size() <= 2 && is_operator(word)) {
                std::cerr << "STRING IS OP: " << word << std::endl;
                std::cerr << "Skipping further seperator parse..." << std::endl;
                this->add_token(op_tok, word);
                continue;
            }
            seperated_words.clear();
            std::cerr << "Beginning seperator parse..." << std::endl;
            eval_seperators(word, seperated_words);
            std::cerr << "SEPERATED WORDS: " << std::endl;
            for (int i = 0; i < seperated_words.size(); i++) {
                std::cerr << seperated_words[i] << " " << std::endl;
            }
            std::cerr << "Seperator parse done, checking tokens..." << std::endl;
            for (int i = 0; i < seperated_words.size(); i++) {
                if (seperated_words[i].size() <= 2) {
                    if (is_operator(seperated_words[i])) {
                        std::cerr << "STRING IS OP: " << seperated_words[i] << std::endl;
                        this->add_token(op_tok, seperated_words[i]);
                        continue;
                    }
                    else if (is_seperator(seperated_words[i])) {
                        std::cerr << "STRING IS SEP: " << seperated_words[i] << std::endl;
                        this->add_token(sep_tok, seperated_words[i]);
                        continue;
                    }
                }
                if (is_identifier(seperated_words[i])) {
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
                else if (is_integer(seperated_words[i])) {
                    std::cerr << "STRING IS INT: " << seperated_words[i] << std::endl;
                    this->add_token(integer_tok, seperated_words[i]);
                }
                else if (is_real(seperated_words[i])) {
                    std::cerr << "STRING IS REAL: " << seperated_words[i] << std::endl;
                    this->add_token(real_tok, seperated_words[i]);
                }
                else {
                    std::cerr << "STRING IS ERROR: " << seperated_words[i] << std::endl;
                    this->add_token(err_rok, seperated_words[i]);
                }
            }
            std::cerr << "Tokens checked from seperator parse." << std::endl;
        }
        else {
            comment_text = comment_text + word + " ";
        }
    }

    std::cerr << "Processing complete." << std::endl;
}

bool lexer::is_identifier(const std::string& token) {
    	int currentState = 0;
	std::string word;
	word = token;
	int input = 99; //make starting value unattainable
	for (int i = 0; i < word.size(); i++) //loop through each char of string word
	{
		if (isalpha(word[i]))
			input = 0; //input is a letter
		else if (isdigit(word[i]))
			input = 1; //input is a digit
		else if (word[i] == '$')
			input = 2; //input is a $ (dollar sign)
		else
			return false;
		switch (input)
		{
			case 0: //state transition for letter input
				if (currentState == -99)
				{
					return false;
				}
				else
					currentState = identifierState[currentState][input];
				break;
			case 1: //state transition for digit input
				if (currentState == -99)
				{
					return false;
				}
				else
					currentState = identifierState[currentState][input];
				break;
			case 2:
				if (currentState == -99)
				{
					return false;
				}
				else
					currentState = identifierState[currentState][input];
				break;
			default: return false;
				break;
		}
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

bool lexer::is_integer(const std::string& token) {
    	int currentState = 0;
	std::string word;
	word = token;
	int input = 99; //set default to non-attainable input value
	for (int i = 0; i < word.size(); i++) //loop through each char of string word
	{
		if (isdigit(word[i]))
			if (word[i] == '0')
				input = 0;
			else
				input = 1; //input is a digit
		else
		{
			return false;
			break;
		}

		switch (input)
		{
			case 0: //input is a 0
				if (currentState == -99) //checks if there exists a valid state transition
				{
					return false;
				}
				else
					currentState = identifierState[currentState][input]; //POTENTIAL ERROR NEED TO REFERENCE CLASS ARRAY
				break;
			case 1:
				if (currentState == -99) //checks if there exists a valid state transition
				{
					return false;
				}
				else
					currentState = identifierState[currentState][input]; //POTENTIAL ERROR NEED TO REFERENCE CLASS ARRAY
				break;
			default: return false;
				break;
		}
	}
	switch (currentState)
	{
		case 1:
		case 2:
		case 3:
		case 4:
			return true; //return true for currentState = 1,2,3,4
			break;
		default:
			return false;
			break;
	}
    
}

bool lexer::is_real(const std::string& token) {
    int currentState = 0;
	std::string word;
	word = token;
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
