


// #[derive(Debug, Clone, Copy, PartialEq, Eq)]
// #[repr(u8)]
// pub enum Visibility {
//     Public,
//     Private
// }

// impl Visibility {
//     fn from_byte(byte: u8) -> Option<Self> {
//         match byte {
//             b if b == (Self::Public as u8) => Some(Self::Public),
//             b if b == (Self::Private as u8) => Some(Self::Private),
//             _ => None
//         }
//     }
// }

// #[derive(Debug, Clone, Copy, PartialEq, Eq)]
// #[repr(u8)]
// pub enum Linkage {
//     Internal,
//     External
// }

// impl Linkage {
//     fn from_byte(byte: u8) -> Option<Self> {
//         match byte {
//             b if b == (Self::Internal as u8) => Some(Self::Internal),
//             b if b == (Self::External as u8) => Some(Self::External),
//             _ => None
//         }
//     }
// }

// #[derive(Debug, Clone, Copy, PartialEq, Eq)]
// #[repr(u8)]
// pub enum Kind {
//     Function,
//     Data
// }

// impl Kind {
//     fn from_byte(byte: u8) -> Option<Self> {
//         match byte {
//             b if b == (Self::Function as u8) => Some(Self::Function),
//             b if b == (Self::Data as u8) => Some(Self::Data),
//             _ => None
//         }
//     }
// }

use crate::gen::symbol::*;
use crate::bits;

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Symbol {
    pub visibility: Visibility, // 1 byte in module
    pub linkage: Linkage, // 1 byte in module
    pub kind: Kind, // 1 byte in module
    pub location: u32, // 4 bytes in module
    pub name: String // 1 byte in module (for size) + size bytes
}

trait BinaryDeserializable<T> {
    /// Deserialize a structure from the given bytes, starting at the given
    /// starting index. If successful, return the object and the number of bytes
    /// consumed.
    /// TODO: should this take an offset into the slice that represents the current
    /// progress into a larger byte array?
    fn from_bytes(bytes: &[u8]) -> Option<(T, usize)>;
}

trait BinarySerializable<T> {
    fn from_bytes(bytes: &[u8], starting_from: usize) -> Option<(T, usize)>;

    fn to_bytes(&self, buffer: &mut Vec<u8>);
}

impl BinaryDeserializable<u32> for u32 {
    fn from_bytes(bytes: &[u8]) -> Option<(u32, usize)> {
        todo!()
    }
}

impl BinarySerializable<u32> for u32 {
    fn from_bytes(bytes: &[u8], starting_from: usize) -> Option<(u32, usize)> {
        todo!()
    }

    fn to_bytes(&self, buffer: &mut Vec<u8>) {
        todo!()
    }
}

impl BinarySerializable<Symbol> for Symbol {
    fn from_bytes(bytes: &[u8], starting_from: usize) -> Option<(Symbol, usize)> {
        let mut sym = Symbol {

            kind: Kind::Data,
            visibility: Visibility::Private,
            linkage: Linkage::External,
            location: 0,
            name: "asf".to_owned()
        };
        let mut index = starting_from;

        Some((sym, 0))
    }

    fn to_bytes(&self, buffer: &mut Vec<u8>) {
        // We are running into an issue here where I do not know at what level
        // to draw the line of who is responsible for serializing what.
        // for example, should a u32 know how to serialize itself?
        // should I generate serialiation code for each of teh symbol enums?
        buffer.extend_from_slice(&[
            self.visibility as u8,
            self.linkage as u8,
            self.kind as u8
        ]);

    }
}

const SYMBOL_DATA_MIN_SIZE: usize = 8;

impl Symbol {

    // This is kind of disgusting (with the magic numbers and what not)
    pub fn from_bytes(bytes: &[u8]) -> Option<Self> {
        let mut total: usize = 0;
        let (val, size) = u32::from_bytes(bytes)?;
        total += size;
        let (val2, size2) = u32::from_bytes(&bytes[total..])?;
        if bytes.len() < SYMBOL_DATA_MIN_SIZE {
            return None;
        }
        let x = u32::from_bytes(&[1]);
        let name_length = bytes[7] as usize;
        println!("name length = {:?}", name_length);
        if bytes.len() < SYMBOL_DATA_MIN_SIZE + name_length {
            return None;
        }
        let visibility = Visibility::from_byte(bytes[0])?;
        let linkage = Linkage::from_byte(bytes[1])?;
        let kind = Kind::from_byte(bytes[2])?;
        let name = String::from_utf8(bytes[8..8+name_length].to_vec()).ok()?;
        return Some(Self {
            visibility, linkage, kind, location: 12u32, name
        })
    }
}

pub struct SymbolTable {
    symbols: Vec<Symbol>
}

impl SymbolTable {

    pub fn from_bytes(bytes: &[u8]) -> Option<Self> {
        if bytes.len() < 4 { return None; }
        let num_symbols = bits::interpret_big_endian_slice(&bytes[0..4]);
        if num_symbols < 0 { return None; }
        let mut symbols: Vec<Symbol> = Vec::new();
        for i in 0..num_symbols {

        }
        None
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn symbol_from_bytes() {
        assert_eq!(Symbol::from_bytes(&[]), None);
        assert_eq!(Symbol::from_bytes(&[1,2,3,4,5,6,7]), None);
        assert_eq!(Symbol::from_bytes(&[1,2,3]), None);

        assert_eq!(Symbol::from_bytes(&[1,1,1, 0xa,0xb,0xc,0xd, 0]).unwrap(), Symbol {
            visibility: Visibility::Private,
            linkage: Linkage::External,
            kind: Kind::Data,
            location: 12,
            name: "".into()
        });

        assert_eq!(Symbol::from_bytes(&[1,1,1, 0xa,0xb,0xc,0xd, 3, 'a' as u8, 'b' as u8, 'c' as u8]).unwrap(), Symbol {
            visibility: Visibility::Private,
            linkage: Linkage::External,
            kind: Kind::Data,
            location: 12,
            name: "abc".into()
        });
    }

}