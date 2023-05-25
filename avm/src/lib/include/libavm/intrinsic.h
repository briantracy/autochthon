
#ifndef AVM_INTRINSIC_H
#define AVM_INTRINSIC_H

#include <stdint.h>
#include <tuple>
#include <array>

/**
 * A word inside the VM is a 4 byte, signed, big-endian quantity.
 */
using VMByte = uint8_t;
using VMWord = std::array<VMByte, 4>;

/**
 * When interacting with VM words on the host side, we need to get numerical
 * values for them (for example, when accessing memory at a certain address).
 * They are 4 bytes and signed, so i32 is the appropriate type.
 */
using HostWord = int32_t;

namespace Intrinsic {
    HostWord toHostWord(VMWord vmWord);
    VMWord fromHostWord(HostWord hostWord);
}

#endif
