
use std::collections::HashMap;

use crate::gen::PAGE_SIZE;

struct Page {
    writeable: bool,
    data: [u8; PAGE_SIZE]
}

impl Page {
    pub fn new(writeable: bool) -> Self {
        Self {
            writeable: writeable,
            data: [0; PAGE_SIZE]
        }
    }
    pub fn is_writeable(&self) -> bool { self.writeable }
    pub fn is_executable(&self) -> bool { !self.is_writeable() }
}


pub struct Memory {
    pages: HashMap<i32, Page>
}

pub enum MemoryAccessError {
    ReadFromUnmappedPage
}

impl Memory {
    pub fn new() -> Self {
        Memory { pages: HashMap::new() }
    }

    pub fn read_bytes(&self, start: i32, length: usize) -> Result<&[u8], MemoryAccessError> {
        let page_index = self.page_index_for_address(start)
            .ok_or(MemoryAccessError::ReadFromUnmappedPage)?;

    }

    pub fn write_bytes(&mut self, start: i32, bytes: &[u8]) {

    }

    fn page_index_for_address(&self, address: i32) -> Option<usize> {
        if address < 0 {
            None
        } else {
            Some(address as usize % PAGE_SIZE)
        }
    }
}