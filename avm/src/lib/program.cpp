
#include "libavm/symbol.h"
#include <libavm/intrinsic.h>
#include <libavm/program.h>

#include <stdint.h>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

namespace ProgramDetail {

struct ProgramOffsets {
    size_t symbolTable, dataSection, codeSection;
};

ProgramOffsets parseSectionLocations(const std::vector<VMByte> &program) {
    if (program.size() < 12) {
        throw ProgramLoadError{"cannot extract section locations: program too small: " + std::to_string(program.size())};
    }
    const HostWord symbolTableStart = Intrinsic::toHostWord({program.at(0), program.at(1), program.at(2), program.at(3)});
    const HostWord dataSectionStart = Intrinsic::toHostWord({program.at(4), program.at(5), program.at(6), program.at(7)});
    const HostWord codeSectionStart = Intrinsic::toHostWord({program.at(8), program.at(9), program.at(10), program.at(11)});
    if (symbolTableStart < 0 || dataSectionStart < 0 || codeSectionStart < 0 ||
        symbolTableStart > dataSectionStart || dataSectionStart > codeSectionStart ||
        symbolTableStart >= static_cast<int64_t>(program.size())) {
        throw ProgramLoadError{"Invalid section locations (symtab, data, code), programSize: "};
    }
    return ProgramOffsets{
        static_cast<size_t>(symbolTableStart),
        static_cast<size_t>(dataSectionStart),
        static_cast<size_t>(codeSectionStart)
    };
}


}

Program::Program(std::string_view filePath) {
    (void)filePath;
    throw ProgramLoadError{"notimplemented: loading program from file"};
}

Program::Program(const std::vector<VMByte> &rawBytes) {
    parse(rawBytes);
}

void Program::parse(const std::vector<VMByte> &rawBytes) {
    const auto offsets = ProgramDetail::parseSectionLocations(rawBytes);

}