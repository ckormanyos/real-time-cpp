#ifndef _UTIL_SAFETY_DRAM_MEMORY_REFRESH_2013_11_22_H_
  #define _UTIL_SAFETY_DRAM_MEMORY_REFRESH_2013_11_22_H_

  #include <mcal_irq.h>
  #include <util/safety/memory/util_safety_memory_base.h>

  namespace util
  {
    namespace safety
    {
      template<typename memory_address_type,
               const std::size_t memory_list_count>
      class dram_memory_refresh : public memory_base<memory_address_type, memory_list_count>
      {
      public:
        typedef typename memory_base<memory_address_type, memory_list_count>::memory_list_type memory_list_type;

        dram_memory_refresh(const memory_list_type& memory_blocks) : memory_base<memory_address_type, memory_list_count>(memory_blocks) { }

        virtual ~dram_memory_refresh() { }

      private:
        virtual void initialize() { }
        virtual void finalize  () { }

        virtual void process_one_byte(volatile std::uint8_t* pointer_to_memory)
        {
          mcal::irq::disable_all();

          // Backup the memory.
          const std::uint8_t memory_backup = *pointer_to_memory;

          // Write the pattern 0x55 to the memory and read it back.
          *pointer_to_memory = static_cast<std::uint8_t>(0x55U);
          memory_base<memory_address_type, memory_list_count>::result_of_process &= (*pointer_to_memory == static_cast<std::uint8_t>(0x55U));

          // Write the pattern 0xAA to the memory and read it back.
          *pointer_to_memory = static_cast<std::uint8_t>(0xAAU);
          memory_base<memory_address_type, memory_list_count>::result_of_process &= (*pointer_to_memory == static_cast<std::uint8_t>(0xAAU));

          // Restore the memory from the backup.
          *pointer_to_memory = memory_backup;

          mcal::irq::enable_all();
        }
      };
    }
  }

#endif // _UTIL_SAFETY_DRAM_MEMORY_REFRESH_2013_11_22_H_
