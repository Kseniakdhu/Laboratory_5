#ifndef FIXED_BLOCK_MEMORY_RESOURCE_H
#define FIXED_BLOCK_MEMORY_RESOURCE_H

#include <memory_resource>
#include <vector>
#include <cstddef>

class Fixed_Block_Memory_Resource : public std::pmr::memory_resource {
    private:
        struct Memory_Block{
            size_t size{0};
            size_t offset{0};
            bool is_allocated{false};
        };

        void* block_memory;
        size_t block_size;
        std::vector<Memory_Block> used_blocks;

    public:
        Fixed_Block_Memory_Resource(size_t block_size);
        ~Fixed_Block_Memory_Resource();
        void* do_allocate(size_t bytes, size_t alignment) override;
        void do_deallocate(void* p, size_t bytes, size_t alignment) override;
        bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
};

#endif
