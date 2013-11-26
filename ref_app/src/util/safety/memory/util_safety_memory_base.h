#ifndef _UTIL_SAFETY_MEMORY_BASE_2013_11_22_H_
  #define _UTIL_SAFETY_MEMORY_BASE_2013_11_22_H_

  #include <array>
  #include <cstdint>
  #include <util/safety/memory/util_safety_dram_memory_block.h>
  #include <util/utility/util_noncopyable.h>

  namespace util
  {
    namespace safety
    {
      template<typename memory_address_type,
               const std::size_t memory_list_count>
      class memory_base : private util::noncopyable
      {
      public:
        virtual ~memory_base() { }

        bool get_result_of_process() const { return result_of_process; }

        void service()
        {
          if(!process_is_initialized)
          {
            initialize();

            process_is_initialized = true;
          }

          if(memory_list.empty())
          {
            return;
          }

          bool increment_memory_list_index = false;

          const bool memory_block_is_empty = (memory_list[memory_list_index].memory_block_size == static_cast<std::size_t>(0U));

          if(memory_block_is_empty)
          {
            // Skip this memory block if it is empty, and increment the memory list index.
            increment_memory_list_index = true;
          }
          else
          {
            // Obtain a pointer to the next byte of memory in the refresh.
            volatile std::uint8_t* pointer_to_memory = reinterpret_cast<volatile std::uint8_t*>(memory_list[memory_list_index].memory_block_start + memory_block_index);

            // Refresh one byte of memory. Surround this with disable / enable
            // interrutps in order to ensure data consistency.
            process_one_byte(pointer_to_memory);

            // Did we reach the end of a memory block?
            if(++memory_block_index >= memory_list[memory_list_index].memory_block_size)
            {
              // Reset the memory block index.
              memory_block_index = static_cast<std::size_t>(0U);

              increment_memory_list_index = true;
            }
          }

          // Did we reach the end of the memory list?
          if(increment_memory_list_index && (++memory_list_index >= memory_list.size()))
          {
            // Reset the memory list index.
            memory_list_index = static_cast<std::size_t>(0U);

            finalize();

            process_is_initialized = false;
          }
        }

      protected:
        typedef std::array<dram_memory_block<memory_address_type>, memory_list_count> memory_list_type;

        bool result_of_process;

        memory_base(const memory_list_type& memory_blocks) : result_of_process     (true),
                                                             memory_list           (memory_blocks),
                                                             process_is_initialized(false),
                                                             memory_list_index     (0U),
                                                             memory_block_index    (0U) { }
      private:
        const memory_list_type& memory_list;
        bool                    process_is_initialized;
        std::size_t             memory_list_index;
        std::size_t             memory_block_index;

        virtual void initialize() = 0;
        virtual void finalize  () = 0;

        virtual void process_one_byte(volatile std::uint8_t*) = 0;
      };
    }
  }

#endif // _UTIL_SAFETY_MEMORY_BASE_2013_11_22_H_
