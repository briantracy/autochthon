#![allow(dead_code)]

use memory::{DebugMemory, Memory};


mod gen;
mod symbol;
mod memory;
mod bits;
mod executable;

fn main() {

    // let mut buff: Vec<u8> = Vec::new();
    // buff.reserve(5);
    // buff.extend_from_slice(&[1,2,3,4,5]);
    // println!("slice = {:?}", buff);
    // let slice: &[u8] = &[0u8, 1u8, 2u8, 3u8, 4u8];
    // let arr: &[u8; 4] = slice.into();
    // let num = u32::from_be_bytes(*arr);
    // let mut mem = DebugMemory::new();
    // mem.set_bytes(0, &[1,2,3,4,5]).expect("err");
    // let buff = mem.get_bytes(0, 5).unwrap();

    // println!("clice = {:?}", buff);
}
