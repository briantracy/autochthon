
from filewriter import CodeFileWriter
from isaconfig import ISAConfig
from typing import Tuple

class RustGenerator:
    '''
    Generate the necessary rust structures in gen.rs (Instruction, Register, ...)
    '''

    def __init__(self, config: ISAConfig, output: CodeFileWriter):
        self._config = config
        self._output = output

    def generate(self):
        self._generate_registers_enum()
        self._generate_instructions_enum()
        self._generate_constants()
        self._generate_symbol_enums()


    def _generate_registers_enum(self):
        self._output.append('\n#[derive(Debug, Clone, Copy)]')
        self._output.append('pub enum Register {')
        self._output.indent()
        registers = self._config.registers()
        for regname in registers:
            self._output.append(f'{regname.capitalize()},')
        self._output.outdent()
        self._output.append('}')
        self._output.append(f'pub const NUM_REGISTERS: usize = {len(registers)};')

    def _generate_instructions_enum(self):
        self._output.append('\n#[derive(Debug, Clone, Copy)]')
        self._output.append('pub enum Instruction {')
        self._output.indent()
        for (name, args) in self._config.instructions():
            self._output.append(self._generate_single_instruction(name, args))
        self._output.outdent()
        self._output.append('}')
        self._output.append(f'pub const LARGEST_INSTRUCTION_SIZE: usize = {self._longest_instruction()};')

    def _generate_constants(self):
        self._output.append(f'pub const PAGE_SIZE: usize = {self._config.pagesize()};')

    def _generate_single_instruction(self, name: str, args) -> str:
        params = self._convert_instruction_args_to_rust_params(args)
        return f'{name.capitalize()}({params}),'

    def _convert_instruction_args_to_rust_params(self, args) -> str:
        def rust_type(arg: str) -> str:
            return self._instruction_arg_to_type_info(arg)[0]
        return ', '.join(map(rust_type, args))

    def _longest_instruction(self) -> int:
        '''
        The length of an instruction is 1 (for the opcode) + the sum
        of the sizes of its arguments.
        '''
        def argument_length(arg: str) -> int:
            return self._instruction_arg_to_type_info(arg)[1]
        arg_lists = (pair[1] for pair in self._config.instructions())
        return max(1 + sum(map(argument_length, args)) for args in arg_lists)

    def _instruction_arg_to_type_info(self, arg: str) -> Tuple[str, int]:
        '''Returns the rust type and size in bytes of an instruction arg'''
        return {
            'reg': ('u8', 1),
            'word': ('i32', 4)
        }[arg]

    def _generate_symbol_enums(self):
        self._output.append('')
        self._output.append('pub mod symbol {')
        self._output.indent()
        for (enum_name, cases) in self._config.symbol_info().items():
            self._output.append('#[derive(Debug, Clone, Copy, PartialEq, Eq)]')
            self._output.append('#[repr(u8)]')
            self._output.append(f'pub enum {enum_name.capitalize()} {{')
            self._output.indent()
            for case in cases:
                self._output.append(f'{case.capitalize()},')
            self._output.outdent()
            self._output.append('}')
            self._output.append(f'impl {enum_name.capitalize()} {{')
            self._output.indent()
            self._output.append('pub fn from_byte(byte: u8) -> Option<Self> {')
            self._output.indent()
            self._output.append('match byte {')
            self._output.indent()
            for case in cases:
                self._output.append(f'b if b == (Self::{case.capitalize()} as u8) => Some(Self::{case.capitalize()}),')
            self._output.append('_ => None')
            self._output.outdent()
            self._output.append('}')
            self._output.outdent()
            self._output.append('}')
            self._output.outdent()
            self._output.append('}')
        self._output.outdent()
        self._output.append('}')

