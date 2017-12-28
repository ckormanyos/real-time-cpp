#ifndef UTIL_SAFETY_DRAM_MEMORY_REFRESH_2013_11_22_H_
  #define UTIL_SAFETY_DRAM_MEMORY_REFRESH_2013_11_22_H_

  #include <mcal_irq.h>
  #include <util/safety/memory/util_safety_memory_base.h>

  namespace util
  {
    namespace safety
    {
      // This class refreshes DRAM by writing and reading patterns.
      // Alternating patterns of 0x55 and 0xAA are written and
      // subsequently read back. This will refresh each DRAM byte
      // and ensure that each DRAM byte can be properly written
      // and read. The value present in the byte will be backed up
      // and subsequently restored prior to and after the pattern write
      // and read-back operation (of course, with interrupts disabled).

      template<typename memory_address_type,
               const std::size_t memory_list_count>
      class dram_memory_refresh : public memory_base<memory_address_type, memory_list_count>
      {
      public:
        typedef memory_base<memory_address_type, memory_list_count> memory_base_type;
        typedef typename memory_base_type::memory_list_type memory_list_type;

        dram_memory_refresh(const memory_list_type& memory_blocks) : memory_base_type(memory_blocks) { }

        virtual ~dram_memory_refresh() { }

      private:
        virtual void initialize() { }
        virtual void finalize  () { }

        virtual void process_one_byte(volatile std::uint8_t* pointer_to_memory);
      };
    }
  }

  template <typename memory_address_type,
            const std::size_t memory_list_count>
  void util::safety::dram_memory_refresh<memory_address_type, memory_list_count>::process_one_byte(volatile std::uint8_t* pointer_to_memory)
  {
    // The DRAM refersh operation is done in an atomic sequence
    // (i.e., with all interrupts disabled).

    // Disable all interrupts.
    mcal::irq::disable_all();

    // Backup the memory.
    const std::uint8_t memory_backup = *pointer_to_memory;

    // Write the pattern 0x55 to the memory and read it back.
    *pointer_to_memory = static_cast<std::uint8_t>(0x55U);
    const bool read_back_result1 = (*pointer_to_memory == static_cast<std::uint8_t>(0x55U));

    // Write the pattern 0xAA to the memory and read it back.
    *pointer_to_memory = static_cast<std::uint8_t>(0xAAU);
    const bool read_back_result2 = (*pointer_to_memory == static_cast<std::uint8_t>(0xAAU));

    // Restore the memory from the backup.
    *pointer_to_memory = memory_backup;

    // Enable all interrupts.
    mcal::irq::enable_all();

    // Verify the result of the DRAM refresh operation.
    const bool read_back_is_ok = (read_back_result1 && read_back_result2);

    memory_base_type::result_of_process = (read_back_is_ok ? memory_base_type::result_is_finished_and_correct
                                                           : memory_base_type::result_is_finished_and_wrong);
  }

#endif // UTIL_SAFETY_DRAM_MEMORY_REFRESH_2013_11_22_H_
