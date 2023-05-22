
#ifndef AVM_INTERPRETER_H
#define AVM_INTERPRETER_H

#include "libavm/intrinsic.h"
#include <libavm/memory.h>
#include <libavm/register.h>
#include <libavm/symbol.h>

class Interpreter {
    DebugMemory memory_;
    SymbolTable symbolTable_;
    Registers registers_;
};

#endif