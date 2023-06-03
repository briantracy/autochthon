
#ifndef AVM_REGISTER_H
#define AVM_REGISTER_H

#include <libavm/intrinsic.h>

#include <array>
#include <stddef.h>
#include <stdint.h>

enum class RegisterName : uint8_t {
    Ip, Sp, Bp, Rv,
    A1, A2, A3, A4,
    R1, R2, R3, R4
};

class Registers {
    std::array<HostWord, static_cast<size_t>(RegisterName::R4) + 1> regs_;

    bool isValidRegister(VMByte value) const;
public:
    HostWord getRegisterValue(RegisterName name) const;
};

#endif
