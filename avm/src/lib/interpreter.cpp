
#include <libavm/interpreter.h>
#include <libavm/program.h>
#include <libavm/inputoutput.h>

#include <iostream>

Interpreter::Interpreter(const Program &program, const InputOutput &io) : memory_{100} {
    symbolTable_ = program.symbols;
    memory_.map(16, program.code);
    memory_.map(static_cast<HostWord>(program.code.size()) + 16, program.data);
    io_ = io;
    std::cout << memory_.debug();
}