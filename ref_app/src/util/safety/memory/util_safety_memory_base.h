#ifndef UTIL_SAFETY_MEMORY_BASE_2013_11_22_H_
  #define UTIL_SAFETY_MEMORY_BASE_2013_11_22_H_

  #include <array>
  #include <cstdint>
  #include <util/safety/memory/util_safety_memory_block.h>
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
        typedef enum enum_result_type
        {
          result_is_finished_and_correct,
          result_is_finished_and_wrong,
          result_is_undetermined
        }
        result_type;

        virtual ~memory_base() { }

        result_type get_result_of_process() const { return result_of_process; }

        void service();

      protected:
        typedef std::array<memory_block<memory_address_type>, memory_list_count> memory_list_type;

        result_type result_of_process;

        memory_base(const memory_list_type& memory_blocks);

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

  template<typename memory_address_type, const std::size_t memory_list_count>
  util::safety::memory_base<memory_address_type,
                            memory_list_count>::memory_base(const memory_list_type& memory_blocks)
    : result_of_process     (result_is_undetermined),
      memory_list           (memory_blocks),
      process_is_initialized(false),
      memory_list_index     (0U),
      memory_block_index    (0U)
  {
  }

  template<typename memory_address_type, const std::size_t memory_list_count>
  void util::safety::memory_base<memory_address_type, memory_list_count>::service()
  {
    if(!process_is_initialized)
    {
      initialize();

      process_is_initialized = true;
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
      // Obtain a pointer to the next byte in the memory operation.
      volatile std::uint8_t* pointer_to_memory = reinterpret_cast<volatile std::uint8_t*>(memory_list[memory_list_index].memory_block_start +  memory_block_index);

      // Process two bytes in successive memory operations.
      process_one_byte(pointer_to_memory);

      ++memory_block_index;

      // Did we reach the end of a memory block?
      if(memory_block_index >= memory_list[memory_list_index].memory_block_size)
      {
        // Reset the memory block index.
        memory_block_index = static_cast<std::size_t>(0U);

        increment_memory_list_index = true;
      }
    }

    // Did we reach the end of the memory list?
    if(increment_memory_list_index)
    {
      ++memory_list_index;

      if(memory_list_index >= memory_list.size())
      {
        // Reset the memory list index.
        memory_list_index = static_cast<std::size_t>(0U);

        finalize();

        process_is_initialized = false;
      }
    }
  }

#endif // UTIL_SAFETY_MEMORY_BASE_2013_11_22_H_
