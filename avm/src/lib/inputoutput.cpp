

#include <libavm/inputoutput.h>
#include <libavm/intrinsic.h>

#include <iostream>

InputOutput::InputOutput(std::istream *is, std::ostream *os) :
    input_{is}, output_{os} {}

InputOutput InputOutput::stdio() {
    return {&std::cin, &std::cout};
}

void InputOutput::writeByte(VMByte b) {
    output_->put(static_cast<char>(b));
}

VMWord InputOutput::readByte() {
    char b = 0;
    if (*input_ >> b) {
        return Intrinsic::fromHostWord(b);
    } else {
        return Intrinsic::fromHostWord(-1);
    }
}
