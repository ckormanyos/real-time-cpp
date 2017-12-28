#ifndef UTIL_SAFETY_MEMORY_BLOCK_2013_11_25_H_
  #define UTIL_SAFETY_MEMORY_BLOCK_2013_11_25_H_

  #include <cstddef>

  namespace util
  {
    namespace safety
    {
      template<typename memory_address_type>
      struct memory_block
      {
        const memory_address_type memory_block_start;
        const std::size_t         memory_block_size;

        memory_block(const memory_address_type start,
                     const std::size_t         size) : memory_block_start(start),
                                                       memory_block_size (size) { }

        memory_block() : memory_block_start(static_cast<memory_address_type>(0U)),
                         memory_block_size (static_cast<std::size_t>(0U)) { }

        memory_block(const memory_block& other_memory_block) : memory_block_start(other_memory_block.memory_block_start),
                                                               memory_block_size (other_memory_block.memory_block_size) { }

        memory_block& operator=(const memory_block& other_memory_block)
        {
          memory_block_start = other_memory_block.memory_block_start;
          memory_block_size  = other_memory_block.memory_block_size;

          return *this;
        }
      };
    }
  }

#endif // UTIL_SAFETY_MEMORY_BLOCK_2013_11_25_H_
