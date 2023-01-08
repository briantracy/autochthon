


#[derive(Debug, Clone, Copy)]
#[repr(u8)]
pub enum Visibility {
    Public,
    Private
}

#[derive(Debug, Clone, Copy)]
#[repr(u8)]
pub enum Linkage {
    Internal,
    External
}

#[derive(Debug, Clone, Copy)]
#[repr(u8)]
pub enum Kind {
    Function,
    Data
}

#[derive(Debug, Clone, Copy)]
pub struct Symbol {
    pub visibility: Visibility,
    pub linkage: Linkage,
    pub kind: Kind,
    pub location: u32
}

pub const SYMBOL_DATA_SIZE: usize = 1 + 1 + 1 + 4;

impl Symbol {
    pub fn from_bytes(bytes: &[u8]) -> Self {
        assert!(bytes.len() == SYMBOL_DATA_SIZE);
        Self {
            visibility: bytes[0] as Visibility
        }
    }
}
