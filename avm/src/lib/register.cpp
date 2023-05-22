
#include <libavm/intrinsic.h>
#include <libavm/register.h>

#include <stdint.h>

HostWord Registers::getRegisterValue(RegisterName name) const {
    return regs_.at(static_cast<size_t>(name));
}