
#ifndef AVM_INTERPRETER_H
#define AVM_INTERPRETER_H

#include <libavm/intrinsic.h>
#include <libavm/inputoutput.h>
#include <libavm/memory.h>
#include <libavm/program.h>
#include <libavm/register.h>
#include <libavm/symbol.h>

class Interpreter {
    DebugMemory memory_;
    SymbolTable symbolTable_;
    Registers registers_;
    InputOutput io_;

public:
    explicit Interpreter(const Program &, const InputOutput &);
    void step();
    void debug() const;
};

#endif