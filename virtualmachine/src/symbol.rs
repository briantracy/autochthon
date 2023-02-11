


#[derive(Debug, Clone, Copy, PartialEq, Eq)]
#[repr(u8)]
pub enum Visibility {
    Public,
    Private
}

impl Visibility {
    fn from_byte(byte: u8) -> Option<Self> {
        match byte {
            b if b == (Self::Public as u8) => Some(Self::Public),
            b if b == (Self::Private as u8) => Some(Self::Private),
            _ => None
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
#[repr(u8)]
pub enum Linkage {
    Internal,
    External
}

impl Linkage {
    fn from_byte(byte: u8) -> Option<Self> {
        match byte {
            b if b == (Self::Internal as u8) => Some(Self::Internal),
            b if b == (Self::External as u8) => Some(Self::External),
            _ => None
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
#[repr(u8)]
pub enum Kind {
    Function,
    Data
}

impl Kind {
    fn from_byte(byte: u8) -> Option<Self> {
        match byte {
            b if b == (Self::Function as u8) => Some(Self::Function),
            b if b == (Self::Data as u8) => Some(Self::Data),
            _ => None
        }
    }
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Symbol {
    pub visibility: Visibility, // 1 byte in module
    pub linkage: Linkage, // 1 byte in module
    pub kind: Kind, // 1 byte in module
    pub location: u32, // 4 bytes in module
    pub name: String // 1 byte in module (for size) + size bytes
}

const SYMBOL_DATA_MIN_SIZE: usize = 8;

impl Symbol {

    pub fn from_bytes(bytes: &[u8]) -> Option<Self> {
        if bytes.len() < SYMBOL_DATA_MIN_SIZE {
            return None;
        }
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