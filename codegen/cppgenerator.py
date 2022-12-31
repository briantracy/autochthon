
from filewriter import CodeFileWriter
from isaconfig import ISAConfig

class CppGenerator:
    '''
    Generate the necessary Cpp structures
    '''

    def __init__(self, config: ISAConfig, output: CodeFileWriter):
        self._config = config
        self._output = output

    def generate(self):
        self._generate_prelude()
        self._generate_opcode_enum()
        self._generate_registers_enum()

    def _generate_prelude(self):
        self._output.append('#include <cstdint>')
        self._output.append('')

    def _generate_opcode_enum(self):
        self._output.indent(0)
        self._output.append('enum class Opcode : uint8_t {')
        self._output.indent(1)
        for (idx, (name, _)) in enumerate(self._config.instructions()):
            self._output.append(f'{name.capitalize()} = {idx},')
        self._output.indent(0)
        self._output.append('}')

    def _generate_registers_enum(self):
        self._output.indent(0)
        self._output.append('enum class Register : uint8_t {')
        self._output.indent(1)
        for (idx, name) in enumerate(self._config.registers()):
            self._output.append(f'{name.capitalize()} = {idx},')
        self._output.indent(0)
        self._output.append('}')