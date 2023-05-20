
// This should not be called module.

/// The module binary is laid out as follow:
/// <header>       (fixed length)
/// <symbol table> (variable length)
/// <data section> (variable length)
/// <code section> (variable length)
#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub struct ExecutableHeader {
    symbol_table_location: u32,
    data_section_location: u32,
    code_section_location: u32
}

impl ExecutableHeader {
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

    fn is_valid(&self) -> bool {
        self.symbol_table_location <= self.data_section_location &&
        self.data_section_location <= self.code_section_location
    }
}

#[derive(Debug, Eq, PartialEq)]
pub struct Executable {
    symbol_table_bytes: Vec<u8>,
    data_section_bytes: Vec<u8>,
    code_section_bytes: Vec<u8>
}

impl Executable {
    pub fn from_bytes(bytes: Vec<u8>) -> Option<Self> {
        let header = ExecutableHeader::from_bytes(&bytes[0..])?;
        if !header.is_valid() || bytes.len() <= header.code_section_location as usize {
            return None
        }
        let sym_slice = &bytes[header.symbol_table_location as usize .. header.data_section_location as usize];
        let data_slice = &bytes[header.data_section_location as usize .. header.code_section_location as usize];
        let code_slice = &bytes[header.code_section_location as usize ..];
        Some(Self {
            symbol_table_bytes: sym_slice.into(),
            data_section_bytes: data_slice.into(),
            code_section_bytes: code_slice.into()
        })
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn header_from_bytes() {
        assert_eq!(None, ExecutableHeader::from_bytes(&[]));
        assert_eq!(None, ExecutableHeader::from_bytes(&[1,2,3,4,5,6,7,8,9,10,11]));
        assert_eq!(Some(ExecutableHeader {
            symbol_table_location: 1,
            data_section_location: 2,
            code_section_location: 3
        }), ExecutableHeader::from_bytes(&[0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3]))
    }

    #[test]
    fn executable_from_bytes() {
        assert_eq!(None, Executable::from_bytes(vec![]));
        assert_eq!(Executable {
            symbol_table_bytes: vec![0xaa, 0xaa, 0xaa, 0xaa],
            data_section_bytes: vec![0xbb, 0xbb, 0xbb, 0xbb],
            code_section_bytes: vec![0xcc, 0xcc, 0xcc, 0xcc]
        }, Executable::from_bytes(vec![
            00, 00, 00, 0x0C,
            00, 00, 00, 0x10,
            00, 00, 00, 0x14,
            0xaa, 0xaa, 0xaa, 0xaa,
            0xbb, 0xbb, 0xbb, 0xbb,
            0xcc, 0xcc, 0xcc, 0xcc
        ]).unwrap());
    }
}