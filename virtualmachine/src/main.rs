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

    let j = gen::Foo::Bar::Baz;


}
