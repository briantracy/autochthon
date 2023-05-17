
#ifndef AVM_INTRINSIC_H
#define AVM_INTRINSIC_H

#include <cstdint>
#include <tuple>
#include <array>


// I am not sure we actually need a VMWord type, as everything should
// just be marshalled through memory. We should get and put 4tuples of bytes
// when interacting with memory.

/**
 * A word inside the VM is a 4 byte, signed, big-endian quantity.
 */
using VMByte = std::uint8_t;
using VMWord = std::array<VMByte, 4>;

/**
 * When interacting with VM words on the host side, we need to get numerical
 * values for them (for example, when accessing memory at a certain address).
 * They are 4 bytes and signed, so i32 is the appropriate type.
 */
using HostWord = std::int32_t;

namespace Intrinsic {
    HostWord toHostWord(VMWord vmword);
}

#endif
