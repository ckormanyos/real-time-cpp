#ifndef UTIL_SAFETY_ROM_MEMORY_CHECKSUM_2013_11_27_H_
  #define UTIL_SAFETY_ROM_MEMORY_CHECKSUM_2013_11_27_H_

  #include <array>
  #include <limits>

  #include <mcal_cpu.h>
  #include <util/safety/memory/util_safety_memory_base.h>
  #include <util/utility/util_two_part_data_manipulation.h>

  namespace util
  {
    namespace safety
    {
      // This class verifies ROM integrity with a CRC-32 checksum.
      // A checksum of type CRC-32/MPEG-2 (based on nibbles) is
      // carried out over the ROM memory regions. The result is
      // subsequently compared with a pre-calculated result stored
      // at a secure location in ROM. This ensures the data integrity
      // of the ROM regions. The CRC-32/MPEG-2 is initialized with zero,
      // even though the standard uses initialization with 0xFFFFFFFF.
      // This is due to legacy calculations in the hex manipulation
      // program.

      template<typename memory_address_type,
               const std::size_t memory_list_count>
      class rom_memory_checksum : public memory_base<memory_address_type, memory_list_count>
      {
      public:
        typedef memory_base<memory_address_type, memory_list_count> memory_base_type;
        typedef typename memory_base_type::memory_list_type memory_list_type;

        rom_memory_checksum(const memory_list_type& memory_blocks,
                            const memory_address_type address);

        virtual ~rom_memory_checksum() { }

      private:
        std::uint32_t crc32_result;
        const memory_address_type address_of_result;

        virtual void initialize() { crc32_result = UINT32_C(0); }

        virtual void finalize();

        virtual void process_one_byte(volatile std::uint8_t* pointer_to_memory);
      };

      // The lookup table for the CRC-32/MPEG-2 (based on nibbles).
      const std::array<std::uint32_t, 16U> crc32_lookup_table =
      {{
        UINT32_C(0x00000000), UINT32_C(0x04C11DB7), UINT32_C(0x09823B6E), UINT32_C(0x0D4326D9),
        UINT32_C(0x130476DC), UINT32_C(0x17C56B6B), UINT32_C(0x1A864DB2), UINT32_C(0x1E475005),
        UINT32_C(0x2608EDB8), UINT32_C(0x22C9F00F), UINT32_C(0x2F8AD6D6), UINT32_C(0x2B4BCB61),
        UINT32_C(0x350C9B64), UINT32_C(0x31CD86D3), UINT32_C(0x3C8EA00A), UINT32_C(0x384fBDBD)
      }};
    }
  }

  template<typename memory_address_type,
           const std::size_t memory_list_count>
  util::safety::rom_memory_checksum<memory_address_type,
                                    memory_list_count>::rom_memory_checksum(const memory_list_type& memory_blocks,
                                                                            const memory_address_type address)
    : memory_base_type (memory_blocks),
      crc32_result     (0U),
      address_of_result(address)
  {
  }

  template <typename memory_address_type,
            const std::size_t memory_list_count>
  void util::safety::rom_memory_checksum<memory_address_type, memory_list_count>::finalize()
  {
    const std::uint8_t expected_result_byte0 = mcal::cpu::read_program_memory(reinterpret_cast<volatile std::uint8_t*>(address_of_result + 3U));
    const std::uint8_t expected_result_byte1 = mcal::cpu::read_program_memory(reinterpret_cast<volatile std::uint8_t*>(address_of_result + 2U));
    const std::uint8_t expected_result_byte2 = mcal::cpu::read_program_memory(reinterpret_cast<volatile std::uint8_t*>(address_of_result + 1U));
    const std::uint8_t expected_result_byte3 = mcal::cpu::read_program_memory(reinterpret_cast<volatile std::uint8_t*>(address_of_result + 0U));

    const std::uint32_t expected_result =
      util::make_long(util::make_long(expected_result_byte0, expected_result_byte1),
                      util::make_long(expected_result_byte2, expected_result_byte3));

    memory_base_type::result_of_process = ((crc32_result == expected_result) ? memory_base_type::result_is_finished_and_correct
                                                                             : memory_base_type::result_is_finished_and_wrong);
  }

  template <typename memory_address_type,
            const std::size_t memory_list_count>
  void util::safety::rom_memory_checksum<memory_address_type, memory_list_count>::process_one_byte(volatile std::uint8_t* pointer_to_memory)
  {
    // Name   : "CRC-32/MPEG-2"
    // Width  : 32
    // Poly   : 0x04C11DB7
    // Init   : 0 (Here, we use Init = 0, even though the standard is Init = 0xFFFFFFFF.)
    // RefIn  : False
    // RefOut : False
    // XorOut : 0x00000000
    // Check  : 0x89A1897F (Result of the crc32 of the string data "123456789")

    const std::uint8_t the_byte = mcal::cpu::read_program_memory(pointer_to_memory);

    // First calculate the lower 4 bits, then calculate the upper 4 bits.
    crc32_result = std::uint32_t(crc32_result << 4) ^ crc32_lookup_table[std::uint_fast8_t((std::uint_fast8_t(crc32_result >> 28) & UINT8_C(0x0F)) ^ (std::uint_fast8_t(the_byte >>    4 )))];
    crc32_result = std::uint32_t(crc32_result << 4) ^ crc32_lookup_table[std::uint_fast8_t((std::uint_fast8_t(crc32_result >> 28) & UINT8_C(0x0F)) ^ (std::uint_fast8_t(the_byte &  0x0FU)))];
  }

#endif // UTIL_SAFETY_ROM_MEMORY_CHECKSUM_2013_11_27_H_
