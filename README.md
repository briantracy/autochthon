
# Autochthon Virtual Machine

The `avm` project is a collection of a few components:

1. A simple RISC instruction set
2. A binary representation of programs and data for this instruction set
3. A virtual machine to run these binaries
4. An assembler to make writing binaries easier
5. A linker to join together many binaries to create more interesting programs


# Todo

Assembly syntax for putting values in symbols

I really want the instruction set to be fixed length
    This seems like more of a design challenge than variable length instructions,
    and it would make implementation of disassembler much easier.

  Fixed length isn't actually any more difficult, you just shunt everything
  into registers. This really relegates interesting stuff to the compiler.

# Issues

1. How do we store a 32 bit literal in a register with one instruction?
  We can have two instructions, one to fill values in the upper and lower 16bits
  We can also just use shifts and multiple instructions
  We can have some IP relative scheme, but I'm not sure how that works.


32 bit instruction
first 5 bits are opcode (32 possible instructions)

4 bits for register selection
registers: zero, ip, sp, bp, cmp, rv, a1, a2, a3, a4,


add (5 bits) + 3(4bits) = 17bits (easy!)


1 opcode per arithmetic instruction, two variants per opcode
  - one is purely register based (a OP b -> c)
  - one works on a register with an immediate (a OP im -> a)


Instructions:
add
sub
mul               arithmetic (1 instruction) (4 bits for opcode) (3 bits for sub instr) (5 bits per reg) = 22bits
div
mod
shl
shr
fill
push (push)
pop
mov (reg -> reg)
call
load
store
debug


benefits of having 1 opcode per instruction vs 1 opcode per family of instructions

1 per instruction:
  easier encoding, code gen

1 per family
  fewer wasted opcodes

https://student.cs.uwaterloo.ca/~isg/res/mips/opcodes

I think we will go with 1 opcode per instruction, but the instruction
is either all registers, or registers with immediate.

add, sub, div, mul, mod all follow this format:
OP (reg, reg, reg) | OP (reg, imm) []

[5 bit opcode][1 bit switch]
                            [4 bit reg][4 bit reg][4 bit reg]
                            [4 bit reg][immediate]

shifts follow
OP (reg, reg) | OP (reg, imm)

bitwise follow OP=AND,XOR,OR
OP (reg, reg, reg)   [reg1 OP reg2 -> reg3]
No immediate syntax because we can't specify a full 32 bit mask


Symbols:

symbol table holds (at the most basic level) pairs of (index, address)
if you reference a symbol in your program, it will be included in the symbol table
the assembler converts these references to indices
When the program is loaded, the interpreter holds the mappings of (index, address)
The linker merges symbol tables and adjusts all symbolic instructions:
  Program A uses symbols 0-4, Program B uses symbols 0-8,
  Linked program C has symbols 0-12, with B's symbols being indices 5-12
For unresolved symbols (like references to standard library routines), the entry
 in the symbol table has a value of -1.
  (this indicates that we need to keep track of names as well, so that the right
   symbol can be found at link time across modules)

Maybe symbol table is
 (index, kind, name, address, linkage, protection)
 (0, function, "std:memcpy", 0x400, internal, public)
 (1, data, "std:errno", 0x900, internal, private)
  <-- This raises the question of how data segments are done.
  Code can be ip relative, but not data, because it will be relocated


# Binary Module Layout

Only static linking, all binaries are final when executed.
To link with things (like the standard library), you need to call the linker first.

Program Header
  location of sections
Symbol table
  list of symbols (each variable length)
    we know how long this is due to section lengths
Data section
Code section

When we map into the address space, we just map the code and data
Symbols can be modified in the VM because the VM stores them while executing
This means that the code and data sections can be put at any address, and the
offsets are just added to each symbol.

# Program Loading

1. Read entire binary file into memory
2. Check and validate header
  a. Sections must be in bounds and of non-negative size
3. Break binary file into bytes for symbol table, data, and code (this is an Executable object, i dont love that name)
4. Parse symbol table
  a. Validate that all symbol addresses are present (not -1)
  b. Verify all symbols are in bounds for their respective sections
    (functions point to addresses in code section, data point to data section)
  c. Verify that a main method exists
5. Load executable into address space
  a. Choose base address for sections
  b. Offset all symbols (data and code separately)
  c. Initialize heap
  d. (when paged memory) set correct permission bits
  e. Initialize stack with cmd args
6. Begin execution



Encoding Instructions

I think we should have just a generated opcode enum, and write the parser
by hand.


Heap
NewPage instruction returns a fresh page from the interpreter.
Alloc/Free instructions could be done (a little cheating). Ideally we would write
an allocator by hand.


Symbol Table

The symbol table is an interesting departure from real MIPS as it is data
that lives outside of the address space. I think this is alright because it
adds a unique twist to this system. I am not going all the way with real CPU
emulation, so it does not have to work exactly like a real CPU. In a way, I am
bridging real emulation with something like python bytecode.

The loadsym instruction allows for ASLR and PIC. It also removes the need for
relocations at link time because all cross module calls are done through symbols.

For in-module function calls, we use rip relative call instructions (no need for
loadsym). For this, we need a way to differentiate between an in module symbol
and an external one. I think for this, we can just reference a list of defined symbols
in the module, and everything outside of that list is external.

