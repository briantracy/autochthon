#include <gtest/gtest.h>

#include <libavm/inputoutput.h>
#include <libavm/interpreter.h>
#include <libavm/intrinsic.h>
#include <libavm/memory.h>
#include <libavm/program.h>

#include <stdint.h>

#include <iostream>

TEST(InterpreterTest, fromFile) {
    const auto helloWorld = Program{"src/test/programs/hello_world.bin"};
    //Interpreter interp{helloWorld};
    auto io = InputOutput::stdio();
    VMByte b;
    while ((b = io.readByte()) != 0x77) {
        io.writeByte(b);
    }
}