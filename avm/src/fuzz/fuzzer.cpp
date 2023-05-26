
#include <libavm/intrinsic.h>
#include <libavm/program.h>

#include <stdint.h>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  std::vector<VMByte> bytes(Data, Data + Size);
  const auto p = Program{bytes};
  return 0;  // Values other than 0 and -1 are reserved for future use.
}
