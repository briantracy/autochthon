
#ifndef AVM_INTERPRETER_H
#define AVM_INTERPRETER_H

#include <libavm/memory.h>
#include <libavm/symbol.h>

#include <memory>

class Interpreter {
    DebugMemory memory_;
    SymbolTable symbolTable_;
};

#endif