#include <iostream>
#include <vector>
#include <Fixed_Block_Memory_Resource.h>
#include <stdexcept>

using namespace std;

Fixed_Block_Memory_Resource::Fixed_Block_Memory_Resource(size_t block_size)
    : block_memory(nullptr), block_size(block_size){
    block_memory = new char[block_size];
    used_blocks.emplace_back(Memory_Block{block_size, 0, false});
    cout << "Allocator has been created with size " << block_size << endl;
    }

Fixed_Block_Memory_Resource:: ~Fixed_Block_Memory_Resource(){
    delete[] static_cast<char*>(block_memory);
    cout << "Allocator has been destroyed" << endl;
}

void* Fixed_Block_Memory_Resource::do_allocate(size_t bytes, size_t alignment){
    for (auto i = used_blocks.begin(); i != used_blocks.end(); ++i){
        if (!(i->is_allocated)){
            size_t new_block_offset = (i->offset + alignment - 1) & ~(alignment - 1);
            if (new_block_offset + bytes <= i->offset + i->size){
                i->is_allocated = true;
                if (i->size >  (bytes + (new_block_offset - i->offset))){
                    size_t remaining_offset = new_block_offset + bytes;
                    size_t remaining_size = i->size - (remaining_offset - i->offset);
                    used_blocks.insert(i + 1, Memory_Block{remaining_size, remaining_offset, false});
                    i->size = remaining_offset - i->offset;
                }
                void* p = static_cast<char*>(block_memory) + new_block_offset;
                cout << "Allocated at offset: " << new_block_offset << endl;
                return p;
            }
        }
    }
    throw runtime_error("Block not create");
}

void Fixed_Block_Memory_Resource::do_deallocate(void* p, size_t bytes, size_t alignment){
    char* char_ptr = static_cast<char*>(p);
    char* block_start = static_cast<char*>(block_memory);
    size_t begin_offset = char_ptr - block_start; // 0x1016 - 0x1000 = 22
    for (auto i = used_blocks.begin(); i != used_blocks.end(); ++i){
        if (i->offset == begin_offset && i->is_allocated){ 
            i->is_allocated = false;
            cout << "Deallocated blocs at offset " << begin_offset << endl;

            auto j = i + 1;
            if (!j->is_allocated && j != used_blocks.end()){
                i->size += j->size;
                used_blocks.erase(j);
            }
            return;
        }
    }
    throw runtime_error("Trying to deallocate non-allocated block");
}

bool Fixed_Block_Memory_Resource::do_is_equal(const std::pmr::memory_resource& other) const noexcept{
    return this == &other;
}

