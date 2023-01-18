

use crate::gen::PAGE_SIZE;


#[derive(Debug, Copy, Clone)]
pub enum MemoryAccessError {
    ReadUnmapped,
    IllegalAddress
}
pub trait Memory {
    fn get_bytes(&self, start: usize, length: usize) -> Result<Vec<u8>, MemoryAccessError>;
    fn set_bytes(&mut self, start: usize, bytes: &[u8]) -> Option<MemoryAccessError>;
}

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



// pub struct PagedMemory {
//     pages: HashMap<usize, Page>
// }

pub struct DebugMemory {
    memory: [u8; 1000]
}

impl DebugMemory {
    pub fn new() -> Self {
        Self { memory: [0; 1000] }
    }
}

impl Memory for DebugMemory {

    fn get_bytes(&self, start: usize, length: usize) -> Result<Vec<u8>, MemoryAccessError> {
        let mut buff: Vec<u8> = Vec::new();
        buff.extend_from_slice(&self.memory[start..start + length]);
        Ok(buff)
    }

    fn set_bytes(&mut self, start: usize, bytes: &[u8]) -> Option<MemoryAccessError> {
        &self.memory[start..start + bytes.len()].copy_from_slice(bytes);
        None
    }
}


// ///
// /// TODO(bct): currently woefully unaware of page boundaries
// impl Memory {
//     pub fn new() -> Self {
//         Memory { pages: HashMap::new() }
//     }

//     pub fn read_bytes(&self, start: i32, length: usize) -> Result<&[u8], MemoryAccessError> {
//         let page_index = self.page_index_for_address(start)
//             .ok_or(MemoryAccessError::ReadFromUnmappedPage)?;
//         let page = self.pages.get(&page_index).ok_or(MemoryAccessError::ReadFromUnmappedPage)?;
//         return Ok(&page.data[page_index % PAGE_SIZE..])
//     }

//     pub fn write_bytes(&mut self, start: i32, bytes: &[u8]) {
//     }

//     fn page_and_offset_for_address(&self, address: i32) -> Option<(usize, usize)> {
//         if address < 0 {
//             None
//         } else {
//             Some(address as usize % PAGE_SIZE)
//         }
//     }
// }