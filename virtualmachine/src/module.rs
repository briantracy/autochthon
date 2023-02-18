
// This should not be called module.

/// The module binary is laid out as follow:
/// <header>       (fixed length)
/// <symbol table> (variable length)
/// <data section> (variable length)
/// <code section> (variable length)
#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub struct ModuleHeader {
    symbol_table_location: u32,
    data_section_location: u32,
    code_section_location: u32
}

impl ModuleHeader {
    pub fn from_bytes(bytes: &[u8]) -> Option<Self> {
        if bytes.len() < std::mem::size_of::<Self>() {
            None
        } else {
            Some(Self {
                symbol_table_location: u32::from_be_bytes(bytes[0..4].try_into().unwrap()),
                data_section_location: u32::from_be_bytes(bytes[4..8].try_into().unwrap()),
                code_section_location: u32::from_be_bytes(bytes[8..12].try_into().unwrap())
            })
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn from_bytes() {
        assert_eq!(None, ModuleHeader::from_bytes(&[]));
        assert_eq!(None, ModuleHeader::from_bytes(&[1,2,3,4,5,6,7,8,9,10,11]));
        assert_eq!(Some(ModuleHeader {
            symbol_table_location: 1,
            data_section_location: 2,
            code_section_location: 3
        }), ModuleHeader::from_bytes(&[0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3]))
    }
}