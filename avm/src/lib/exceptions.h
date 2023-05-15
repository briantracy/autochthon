
#ifndef AVM_EXCEPTIONS_H
#define AVM_EXCEPTIONS_H

#include <stdexcept>

struct BinaryReaderError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct MemoryReadException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

#endif