#include <gtest/gtest.h>

#include <libavm/interpreter.h>
#include <libavm/intrinsic.h>
#include <libavm/memory.h>
#include <libavm/program.h>

#include <stdint.h>

#include <iostream>

TEST(InterpreterTest, fromFile) {
    const auto helloWorld = Program{"src/test/programs/hello_world.bin"};
    Interpreter interp{helloWorld};
}