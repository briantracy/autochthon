
from typing import List, Tuple, Mapping
import yaml


class ISAConfig:
    '''
    Parse the /isa.yaml definition into its sections for consumption
    by the code generators.
    '''

    @staticmethod
    def from_file(filename: str):
        with open(filename) as f:
            return ISAConfig(f.read())

    def __init__(self, config_text: str):
        self._parsed = yaml.safe_load(config_text)

    def instructions(self) -> List[Tuple[str, List[str]]]:
        '''
            Returns a list of (instruction_name, [arguments]) pairs
            [{'push': ['reg']}, {'add': ['reg', 'reg', 'reg']}] ->
            [('push', ['reg']), ('add', ['reg', 'reg', 'reg'])]
        '''
        def tupleize_and_validate(ent):
            if len(ent.keys()) != 1:
                raise AssertionError(f'Invalid instruction definition format: {ent}')
            instr_name = list(ent.keys())[0]
            args = ent[instr_name]
            if any(arg != 'reg' and arg != 'word' for arg in args):
                raise AssertionError(f'Invalid instruction argument: {ent}')
            return (instr_name, args)

        return list(map(tupleize_and_validate, self._parsed['instructions']))

    def registers(self) -> List[str]:
        return self._parsed['registers']

    def pagesize(self) -> int:
        return int(self._parsed['architecture']['pagesize'])

    def symbol_info(self) -> Mapping[str, List[str]]:
        return self._parsed['symbols']



if __name__ == '__main__':
    config = ISAConfig('''
instructions:
  - add: [reg, reg, reg]
registers: [Ip, Sp]
''')
    assert config.instructions() == [('add', ['reg', 'reg', 'reg'])]
    assert config.registers() == ['Ip', 'Sp']

