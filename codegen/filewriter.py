
import os

class CodeFileWriter:
    '''
    This class is used to format text and write generated code files.
    '''
    def __init__(self, filename: str, tabwidth=4):
        self._filename = filename
        self._tabwidth = tabwidth
        self._buffer = ''
        self._indent = 0

    def indent(self):
        self._indent += 1
    def outdent(self):
        self._indent -= 1

    def append(self, line: str):
        self._buffer += (self._tab() + line + '\n')

    def write(self):
        with open(self._filename, "w", os.O_TRUNC) as f:
            f.write(self._buffer)

    def _tab(self):
        return ' ' * self._indent * self._tabwidth



class StandardOutWriter(CodeFileWriter):
    def __init__(self):
        super().__init__('')

    def write(self):
        print(self._buffer)