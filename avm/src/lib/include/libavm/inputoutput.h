
#ifndef AVM_INPUTOUTPUT_H
#define AVM_INPUTOUTPUT_H

#include <libavm/intrinsic.h>

#include <istream>
#include <ostream>

/*
 * Encapsulate IO for a running program
 */
class InputOutput {
    // This is kind of gross, we are taking non owning pointers to streams
    // because the standard use case is just stdio (which we can't own), but
    // we want to support passing in local streams as well.
    std::istream *input_;
    std::ostream *output_;
public:
    InputOutput(std::istream *is, std::ostream *os);
    static InputOutput stdio();

    void writeByte(VMByte b);
    /// Returns a full VMWord for error handling purposes (-1 on error/EOF).
    VMWord readByte();
};

#endif
