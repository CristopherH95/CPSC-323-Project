#include "semantics.h"

semantic::semantic() {
    memory_counter = 2000;
    last_instr_loc = 1;
}

semantic::~semantic() {
    //destructor
}

bool semantic::exists_symbol(const std::string& sym_to_check) {
    bool found = false;

    if (sym_table.count(sym_to_check) > 0) {
        found = true;
    }

    return found;
}

bool semantic::add_symbol(const std::string& sym_to_add, const std::string& sym_type) {
    bool success = false;
    memory_counter++;
    symbol n_sym;
    n_sym.ident = sym_to_add;
    n_sym.type = sym_type;
    n_sym.loc = memory_counter;

    std::cerr << "SYM_TO_ADD: " << sym_to_add << std::endl;
    std::cerr << "SYM_TYPE: " << sym_type << std::endl;

    sym_table.insert(std::make_pair(sym_to_add, n_sym));
    if (this->exists_symbol(sym_to_add)) {
        success = true;
    }
    else {
        std::cerr << "SYMBOL NOT FOUND IN TABLE AFTER CREATION" << std::endl;
        memory_counter--;
    }

    return success;
}

bool compare_symbols(const symbol& a, const symbol& b) {
    return a.loc < b.loc;
}

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

unsigned int semantic::pop_jmp_stack() {
    unsigned int temp = std::stoi(jmp_stack.top());
    jmp_stack.pop();

    return temp;
}

void semantic::gen_instr(const std::string& oper, const std::string& op_arg) {
    instr n_instruct;
    n_instruct.addr = last_instr_loc;
    n_instruct.oper = oper;
    std::cerr << "OPERAND: " << oper << std::endl;
    std::cerr << "OPERAND_ARG: " << op_arg << std::endl;
    n_instruct.oprnd = op_arg;
    instructions.push_back(n_instruct);
    last_instr_loc++;
}

void semantic::back_patch(const std::string& jmp_addr) {
    unsigned int temp_addr = this->pop_jmp_stack();
    instructions[temp_addr - 1].oprnd = jmp_addr;
}

void semantic::exec_semantics(const std::list<std::string>& semant) {
    typedef std::list<std::string> semant_list;
    bool end_args = false;
    bool check_oper = false;
    bool check_op_arg = false;
    bool get_address = false;
    bool exec_gen_instr = false;
    bool perf_jmp = false;
    bool n_symbol = false;
    bool n_symbol_type = false;
    bool chk_symbol = false;
    std::string temp_var_type = "";
    std::string temp_str = "";
    std::string oper = "";
    std::string op_arg = "";
    std::string addr = "";
    symbol temp_sym;

    for (std::string i : semant) {
        std::cerr << "SEMANTIC COMMAND: " << i << std::endl;
        if (i == "addtable") {
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
            addr = std::to_string(last_instr_loc);
            continue;
        }
        if (i == "getaddr") {
            get_address = true;
            continue;
        }
        if (i == "pushjmp") {
            jmp_stack.push(std::to_string(last_instr_loc));
            continue;
        }
        if (i == "backpatch") {
            this->back_patch(std::to_string(last_instr_loc));
            continue;
        }
        if (n_symbol && n_symbol_type) {
            temp_var_type = i;
            std::cerr << "TYPE: " << temp_var_type << std::endl;
            n_symbol_type = false;
        }
        if (n_symbol && get_address && !n_symbol_type) {
            std::cerr << "VAR NAME: " << i << std::endl;
            if (!this->add_symbol(i, temp_var_type)) {
                std::cerr << "Failed to create variable: '" << i << "' in the symbol table, variable may have"
                          << " been previously declared." << std::endl;
                break;
            }
            else {
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
            check_op_arg = true;
            continue;
        }
        else if (exec_gen_instr && check_op_arg && !get_address) {
            op_arg = i;
            check_op_arg = false;
            end_args = true;
        }
        else if (check_op_arg && get_address) {
            if (chk_symbol) {
                if (!this->exists_symbol(i)) {
                    std::cerr << "Error: variable '" << i << "' was used before it was declared." << std::endl;
                    break;
                }
                chk_symbol = false;
            }
            temp_sym = sym_table[i];
            op_arg = std::to_string(temp_sym.loc);
            get_address = false;
            check_op_arg = false;
            end_args = true;
        }
        if (exec_gen_instr && end_args && !perf_jmp) {
            this->gen_instr(oper, op_arg);
            end_args = false;
            exec_gen_instr = false;
        }
        else if (exec_gen_instr && end_args && perf_jmp) {
            this->gen_instr(oper, addr);
            end_args = false;
            exec_gen_instr = false;
            perf_jmp = false;
        }
        this->print_table();
    }
    this->gen_instr("", "");    //this is to eliminate issue where jumps can sometimes be written to the 
                                //non-existant last line of the program
}