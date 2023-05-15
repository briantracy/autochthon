
#ifndef AVM_INTRINSIC_H
#define AVM_INTRINSIC_H

#include <cstdint>


/**
 * A word inside the VM is a 4 byte, signed, big-endian quantity.
 * We simulate this with an unsigned 4 byte quantity so that we may
 * better visualize it as a series of 4 bytes that we can bit shift.
 */
using VMWord = std::uint32_t;
using VMByte = std::uint8_t;

/**
 * When interacting with VM words on the host side, we need to get numerical
 * values for them (for example, when accessing memory at a certain address).
 * They are 4 bytes and signed, so i32 is the appropriate type
 */
using HostWord = std::int32_t;

namespace Intrinsic {
    HostWord toHostWord(VMWord vmword);
}

#endif
