#![allow(dead_code)]


mod gen;
mod symbol;
mod memory;
use symbol::*;

fn main() {
    let j = Symbol {
        visibility: Visibility::Public,
        linkage: Linkage::External,
        kind: Kind::Data,
        location: 0x100
    };
    let p = memory::Page::new(true);
    println!("Hello, world!: {:?}, {:?}", j, p.is_executable());
}
