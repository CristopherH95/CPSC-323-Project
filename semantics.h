#pragma once
#include <map>
#include <vector>
#include <stack>
#include <list>
#include <string>
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <iomanip>

struct symbol {
    std::string ident;
    unsigned int loc;
    std::string type;
};

struct instr {
    unsigned int addr;
    std::string oper;
    std::string oprnd;
};

class semantic {
    public:
        semantic();
        ~semantic();
        bool exists_symbol(const std::string& sym_to_check);
        symbol get_symbol(const std::string& sym_to_get);
        bool add_symbol(const std::string& sym_to_add, const std::string& sym_type);
        bool exec_semantics(const std::list<std::string>& semant);
        void print_table(std::ostream& output_dest, bool err_out = true);
        void print_instructions(std::ostream& output_dest, bool err_out = true);
        void print_table();
        unsigned int pop_jmp_stack();
        void gen_instr(const std::string& oper, const std::string& op_arg);
        void back_patch(const std::string& jmp_addr);

    private:
        std::map<std::string, symbol> sym_table;
        unsigned int memory_counter;
        std::stack<std::string> jmp_stack;
        unsigned int last_instr_loc;
        std::vector<instr> instructions;
};