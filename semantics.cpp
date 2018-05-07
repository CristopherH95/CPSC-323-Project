#include "semantics.h"

semantic::semantic() {
    memory_counter = 2000;
    last_instr_loc = 1;
}

semantic::~semantic() {
    //destructor
}

//exists_symbol
//parameters: sym_to_check is a string representing the identifier to check in the symbol table
//returns: true/false
//This method will determine whether a given string is a previously declared identifier
//in the symbol table
bool semantic::exists_symbol(const std::string& sym_to_check) {
    bool found = false;

    if (sym_table.count(sym_to_check) > 0) {
        found = true;
    }

    return found;
}

//get_symbol
//parameters: sym_to_get is a string representing the identifier to get from the symbol table
//returns: symbol (struct)
//This method will get the identifier corresponding to the given symbol in the symbol table
symbol semantic::get_symbol(const std::string& sym_to_get) {
    symbol temp_sym;

    temp_sym = sym_table[sym_to_get];

    return temp_sym;
}

//add_symbol
//parameters: sym_to_add is a string representing the name of the symbol,
//            sym_type is a string representing the type of the new symbol
//returns: true/false (successfully added or not)
//This method adds a new symbol to the symbol table, with the given type and memory location
//derived from the internal memory counter
bool semantic::add_symbol(const std::string& sym_to_add, const std::string& sym_type) {
    bool success = false;
    memory_counter++;
    symbol n_sym;
    n_sym.ident = sym_to_add;
    n_sym.type = sym_type;
    n_sym.loc = memory_counter;

    //std::cerr << "SYM_TO_ADD: " << sym_to_add << std::endl;
    //std::cerr << "SYM_TYPE: " << sym_type << std::endl;

    sym_table.insert(std::make_pair(sym_to_add, n_sym));
    if (this->exists_symbol(sym_to_add)) {
        success = true;
    }
    else {
        //std::cerr << "SYMBOL NOT FOUND IN TABLE AFTER CREATION" << std::endl;
        memory_counter--;
    }

    return success;
}

//compare_symbols
//parameters: a and b are symbols to compare to each other
//returns: true/false
//This function is a helper function for sorting symbols
bool compare_symbols(const symbol& a, const symbol& b) {
    return a.loc < b.loc;
}

//print_table
//parameters: output_dest is an output stream to output to, err_out is a boolean value
//            which determines whether to also output to the error stream (default is yes)
//returns: none
//This method will print the symbol table to the given output stream
void semantic::print_table(std::ostream& output_dest, bool err_out) {
    typedef std::map<std::string, symbol> table_data;
    std::vector<symbol> print_container;

    for (table_data::iterator it = sym_table.begin(); it != sym_table.end(); ++it) {
        print_container.push_back(it->second);
    }

    std::sort(print_container.begin(), print_container.end(), compare_symbols);
    if (err_out) {
        std::cerr << std::setw(30) << std::left << "identifier" << std::setw(20)
                  << "memory location"
                  << std::setw(20) << "type" << std::endl;
        std::cerr << std::setw(70) << std::setfill('-') << "";
        std::cerr << std::setfill(' ') << "" << std::endl;

        for (int i = 0; i < print_container.size(); i++) {
            std::cerr << std::setw(30) << std::left << print_container[i].ident
                      << std::setw(20) << print_container[i].loc 
                      << std::setw(20) << print_container[i].type;
            std::cerr << std::endl;
        }
    }
    output_dest << std::setw(30) << std::left << "identifier" << std::setw(20)
                << "memory location"
                << std::setw(20) << "type" << std::endl;
    output_dest << std::setw(70) << std::setfill('-') << "";
    output_dest << std::setfill(' ') << "" << std::endl;

    for (int i = 0; i < print_container.size(); i++) {
        output_dest << std::setw(30) << std::left << print_container[i].ident
                    << std::setw(20) << print_container[i].loc 
                    << std::setw(20) << print_container[i].type;
        output_dest << std::endl;
    }
}

//print_table (overload)
//parameters: none
//returns: none
//This method overload will print the symbol table only to the error stream
void semantic::print_table() {
    typedef std::map<std::string, symbol> table_data;
    std::vector<symbol> print_container;

    for (table_data::iterator it = sym_table.begin(); it != sym_table.end(); ++it) {
        print_container.push_back(it->second);
    }

    std::sort(print_container.begin(), print_container.end(), compare_symbols);
    std::cerr << std::setw(30) << std::left << "identifier" << std::setw(20)
                << "memory location"
                << std::setw(20) << "type" << std::endl;
    std::cerr << std::setw(70) << std::setfill('-') << "";
    std::cerr << std::setfill(' ') << "" << std::endl;

    for (int i = 0; i < print_container.size(); i++) {
        std::cerr << std::setw(30) << std::left << print_container[i].ident
                    << std::setw(20) << print_container[i].loc 
                    << std::setw(20) << print_container[i].type;
        std::cerr << std::endl;
    }
}

//print_instructions
//parameters: output_dest is an output stream to print the instructions to, err_out is a boolean
//            value determining whether to also print to the error stream (default is yes)
//returns: none
//This method will print the currently created instructions to the given output stream
void semantic::print_instructions(std::ostream& output_dest, bool err_out) {
    output_dest << std::setfill('-') << std::setw(20) << "";
    output_dest << "INSTRUCTIONS";
    output_dest << std::setw(20) << "";
    output_dest << std::setfill(' ') << std::endl;
    for (int i = 1; i < last_instr_loc; i++) {
        output_dest << std::setw(20) << std::left << instructions[i - 1].addr
                    << std::setw(10) << instructions[i - 1].oper
                    << std::setw(5) << instructions[i - 1].oprnd;
        output_dest << std::endl;
    }
    if (err_out) {
        std::cerr << std::setfill('-') << std::setw(20) << "";
        std::cerr << "INSTRUCTIONS";
        std::cerr << std::setw(20) << "";
        std::cerr << std::setfill(' ') << std::endl;
        for (int i = 1; i < last_instr_loc; i++) {
            std::cerr << std::setw(20) << std::left << instructions[i - 1].addr
                        << std::setw(10) << instructions[i - 1].oper
                        << std::setw(5) << instructions[i - 1].oprnd;
            std::cerr << std::endl;
        }
    }
}

//pop_jmp_stack
//parameters: none
//returns: none
//This method pops from the jump stack and returns the value it popped
unsigned int semantic::pop_jmp_stack() {
    unsigned int temp = std::stoi(jmp_stack.top());
    jmp_stack.pop();
    //std::cerr << temp << std::endl;

    return temp;
}

//gen_instr
//parameters: oper is the operator to generate, op_arg is the argument for the operator
//returns: none
//This method will create an instruction based on the given operator and its argument
void semantic::gen_instr(const std::string& oper, const std::string& op_arg) {
    instr n_instruct;
    n_instruct.addr = last_instr_loc;
    n_instruct.oper = oper;
    //std::cerr << "OPERAND: " << oper << std::endl;
    //std::cerr << "OPERAND_ARG: " << op_arg << std::endl;
    n_instruct.oprnd = op_arg;
    instructions.push_back(n_instruct);
    last_instr_loc++;
}

//back_patch
//parameters: jmp_addr is the value to change the previous jump argument to
//returns: none
//This method can be used to change a jump instruction's argument later on
void semantic::back_patch(const std::string& jmp_addr) {
    unsigned int temp_addr = this->pop_jmp_stack();
    instructions[temp_addr - 1].oprnd = jmp_addr;
}

//exec_semantics
//parameters: semant is a list of strings representing semantic instructions
//returns: true/false (no errors/error found)
//This method will go through the semantic instructions and generate object code
bool semantic::exec_semantics(const std::list<std::string>& semant) {
    std::cerr << "Beginning semantic analysis and code generation..." << std::endl;
    bool success = true;
    bool end_args = false;
    bool check_oper = false;
    bool check_op_arg = false;
    bool get_address = false;
    bool exec_gen_instr = false;
    bool perf_jmp = false;
    bool n_symbol = false;
    bool n_symbol_type = false;
    bool chk_symbol = false;
    bool saved_addr = false;
    bool expect_input = false;
    bool check_int_type = false;
    bool get_error_line = false;
    bool chk_assignment = false;
    bool chk_bool_type = false;
    std::string temp_var_type = "";
    std::string temp_str = "";
    std::string temp_type_check = "";
    std::string oper = "";
    std::string op_arg = "";
    std::string addr_else = "";
    std::string else_jump_back_patch = "";
    std::string else_jump = "";
    std::stack<std::string> addr;
    unsigned int iter_addr;
    symbol temp_sym;

    for (std::string i : semant) {
        //std::cerr << "SEMANTIC COMMAND: " << i << std::endl;
        if (i == "addtable" && !expect_input) {
            n_symbol = true;
            n_symbol_type = true;
            continue;
        }
        if (i == "checktable") {
            chk_symbol = true;
            continue;
        }
        if (i == "geninstr") {
            exec_gen_instr = true;
            check_oper = true;
            continue;
        }
        if (i == "saveaddr") {
            addr.push(std::to_string(last_instr_loc));
            saved_addr = true;
            continue;
        }
        if (i == "saveelseaddr") {
            addr_else = std::to_string(last_instr_loc);
            this->gen_instr("JUMP", "");
            this->gen_instr("LABEL", "");
            continue;
        }
        if (i == "getaddr") {
            get_address = true;
            continue;
        }
        if (i == "pushjmp") {
            jmp_stack.push(std::to_string(last_instr_loc));
            else_jump = std::to_string(last_instr_loc);
            continue;
        }
        if (i == "backpatch") {
            this->back_patch(std::to_string(last_instr_loc));
            else_jump_back_patch = std::to_string(last_instr_loc);
            continue;
        }
        if (i == "expectinput") {
            expect_input = true;
            continue;
        }
        if (i == "checkisint") {
            check_int_type = true;
            continue;
        }
        if (i == "isassignvalid") {
            chk_assignment = true;
            continue;
        }
        if (i == "invalidateaddr") {
            addr.pop();
            continue;
        }
        if (!success && get_error_line) {
            std::cerr << i << std::endl;
            break;
        }
        if (chk_assignment && chk_symbol) {
            if (!this->exists_symbol(i)) {
                std::cerr << "Error: variable '" << i << "' was used before it was declared on line ";
                success = false;
                get_error_line = true;
                continue;
            }
            else {
                if (this->get_symbol(i).type == "boolean") {
                    chk_bool_type = true;
                }
                chk_symbol = false;
                chk_assignment = false;
                continue;
            }
        }
        if (expect_input && get_address) {
            if (!this->exists_symbol(i)) {
                std::cerr << "Error: variable '" << i << "' was used before it was declared on line ";
                success = false;
                get_error_line = true;
                continue;
            }
            expect_input = false;
            get_address = false;
        }
        if (i == "jumpelse") {
            jmp_stack.push(addr_else);
            this->back_patch(std::to_string(last_instr_loc));
            iter_addr = std::stoi(else_jump_back_patch);
            iter_addr++;
            jmp_stack.push(else_jump);
            this->back_patch(std::to_string(iter_addr));
        }
        if (n_symbol && n_symbol_type) {
            temp_var_type = i;
            //std::cerr << "TYPE: " << temp_var_type << std::endl;
            n_symbol_type = false;
        }
        if (n_symbol && get_address && !n_symbol_type) {
            //std::cerr << "VAR NAME: " << i << std::endl;
            if (this->exists_symbol(i)) {
                std::cerr << "Error: attempting to re-declare variable '" << i << "' on line ";
                success = false;
                get_error_line = true;
                continue;
            }
            if (!this->add_symbol(i, temp_var_type)) {
                std::cerr << "Failed to create variable: '" << i << "' in the symbol table, is there enough memory remaining" 
                          << " for the variable?" << std::endl;
                success = false;
                break;
            }
            else {
                //default value
                this->gen_instr("PUSHI", "0");
                this->gen_instr("POPM", std::to_string(this->get_symbol(i).loc));
                get_address = false;
                n_symbol = false;
                continue;
            }
        }
        if (exec_gen_instr && check_oper) {
            oper = i;
            if (oper == "JUMP") {
                perf_jmp = true;
            }
            check_oper = false;
            if (saved_addr && perf_jmp) {
                check_op_arg = false;
                end_args = true;
            }
            else {
                check_op_arg = true;
            }
            //continue;
        }
        else if (exec_gen_instr && check_op_arg && !get_address) {
            op_arg = i;
            check_op_arg = false;
            end_args = true;
        }
        else if (check_op_arg && get_address) {
            if (chk_symbol) {
                if (!this->exists_symbol(i)) {
                    std::cerr << "Error: variable '" << i << "' was used before it was declared on line ";
                    success = false;
                    get_error_line = true;
                    continue;
                }
                chk_symbol = false;
                temp_type_check = i;
            }
            if (check_int_type) {
                if (this->get_symbol(i).type != "int") {
                    std::cerr << "Error: attempting to perform arithmetic operations on non-int type on line ";
                    success = false;
                    get_error_line = true;
                    continue;
                }
                check_int_type = false;
            }
            temp_sym = sym_table[i];
            op_arg = std::to_string(temp_sym.loc);
            get_address = false;
            check_op_arg = false;
            end_args = true;
        }
        if (exec_gen_instr && end_args && !perf_jmp) {
            if (chk_bool_type && (oper == "PUSHI" || oper == "PUSHM")) {
                if (oper == "PUSHI" && op_arg != "1" && op_arg != "0") {
                    std::cerr << "Error: attempting to assign a non-boolean value to a boolean type on line ";
                    success = false;
                    get_error_line = true;
                    continue;
                }
                else if (oper == "PUSHM" && this->get_symbol(temp_type_check).type != "boolean") {
                    std::cerr << "Error: attempting to assign a non-boolean value to a boolean type on line ";
                    success = false;
                    get_error_line = true;
                    continue;
                }
                else {
                    chk_bool_type = false;
                }
            }
            this->gen_instr(oper, op_arg);
            end_args = false;
            exec_gen_instr = false;
        }
        else if (exec_gen_instr && end_args && perf_jmp && saved_addr) {
            this->gen_instr(oper, addr.top());
            addr.pop();
            end_args = false;
            exec_gen_instr = false;
            perf_jmp = false;
            if (addr.empty()) {
                saved_addr = false;
            }
        }
    }
    this->gen_instr("", "");    //this is to eliminate issue where jumps can sometimes be written to the 
                                //non-existant last line of the program
    return success;
}