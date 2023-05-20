

use crate::gen::PAGE_SIZE;


#[derive(Debug, Copy, Clone)]
pub enum MemoryAccessError {
    ReadUnmapped,
    IllegalAddress
}
pub trait Memory {
    fn get_word(&self, address: usize) -> Result<[u8; 4], MemoryAccessError>;
    fn get_byte(&self, address: usize) -> Result<u8, MemoryAccessError>;
    fn set_word(&mut self, address: usize, word: [u8; 4]) -> Result<(), MemoryAccessError>;
    fn set_byte(&mut self, address: usize, byte: u8) -> Result<(), MemoryAccessError>;

    /// Used to load in parts of the program
    fn map(&mut self, start: usize, bytes: &[u8]) -> Result<(), MemoryAccessError>;

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
    fn get_word(&self, address: usize) -> Result<[u8; 4], MemoryAccessError> {
        let mut word = [0u8; 4];
        word.copy_from_slice(&self.memory[address..address + 4]);
        Ok(word)
    }

    fn get_byte(&self, address: usize) -> Result<u8, MemoryAccessError> {
        todo!()
    }

    fn set_word(&mut self, address: usize, word: [u8; 4]) -> Result<(), MemoryAccessError> {
        self.memory[address..address+4].copy_from_slice(&word);
        Ok(())
    }

    fn set_byte(&mut self, address: usize, byte: u8) -> Result<(), MemoryAccessError> {
        todo!()
    }

    fn map(&mut self, start: usize, bytes: &[u8]) -> Result<(), MemoryAccessError> {
        todo!()
    }

    // fn get_bytes(&self, start: usize, length: usize) -> Result<Vec<u8>, MemoryAccessError> {
    //     let mut buff: Vec<u8> = Vec::new();
    //     buff.extend_from_slice(&self.memory[start..start + length]);
    //     Ok(buff)
    // }

    // fn set_bytes(&mut self, start: usize, bytes: &[u8]) -> Result<(), MemoryAccessError> {
    //     self.memory[start..start + bytes.len()].copy_from_slice(bytes);
    //     Ok(())
    // }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn simple_write_read() {
        let mut mem: Box<dyn Memory> = Box::new(DebugMemory::new());
        mem.set_word(0, [1,2,3,4]).expect("write failed");
        let bytes = mem.get_word(0).expect("read failed");
        assert_eq!(&bytes[..], &[1,2,3,4]);
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