

#[derive(Debug, Clone, Copy)]
pub enum Visibility {
    Public,
    Private
}

#[derive(Debug, Clone, Copy)]
pub enum Linkage {
    Internal,
    External
}

#[derive(Debug, Clone, Copy)]
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
