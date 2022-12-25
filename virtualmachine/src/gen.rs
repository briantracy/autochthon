
#[derive(Debug, Clone, Copy)]
pub enum Register {
    Ip,
    Sp,
    Fp,
    Rv,
    Cond,
    A1,
    A2,
    A3,
    A4,
    R1,
    R2,
    R3,
    R4,
}
const NUM_REGISTERS: usize = 13;

#[derive(Debug, Clone, Copy)]
pub enum Instruction {
    Push(u8),
    Pop(u8),
    Fill(i32, u8),
    Call(u8),
    Jump(i32),
    Add(u8, u8, u8),
    Sub(u8, u8, u8),
    Loadbyte(u8, u8),
    Loadword(u8, u8),
    Storebyte(u8, u8),
    Storeword(u8, u8),
    Loadsym(i32, u8),
    Nop(),
    Debug(),
}
pub const LARGEST_INSTRUCTION_SIZE: usize = 6;
