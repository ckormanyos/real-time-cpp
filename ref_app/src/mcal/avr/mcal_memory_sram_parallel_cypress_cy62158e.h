///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_SRAM_PARALLEL_CYPRESS_CY62158E_2020_05_01_H
  #define MCAL_MEMORY_SRAM_PARALLEL_CYPRESS_CY62158E_2020_05_01_H

  #include <array>
  #include <cstddef>
  #include <cstdint>

  #include <mcal/mcal_helper.h>

  #include <util/utility/util_noncopyable.h>

  namespace mcal { namespace memory { namespace sram {

  template<typename sram_parallel_port_word16_addr_04_to_19_type,
           typename sram_parallel_port_pin_addr03_type,
           typename sram_parallel_port_pin_addr02_type,
           typename sram_parallel_port_pin_addr01_type,
           typename sram_parallel_port_pin_addr00_type,
           typename sram_parallel_port_pin_ce1_not_type,
           typename sram_parallel_port_pin_ce2_____type,
           typename sram_parallel_port_pin_oe__not_type,
           typename sram_parallel_port_pin_we__not_type,
           typename sram_parallel_port_word08_data_type,
           const std::uint8_t nop_count,
           const bool has_disable_enable_interrupts>
  class memory_sram_parallel_cypress_cy62158e : private util::noncopyable
  {
  private:
    // The CY62158E MoBL(R)is a high performance CMOS static RAM
    // organized as 1024K words by 8 bits (i.e., 1 Mbyte).
    static auto nibble_port_pin_functions(const std::uint8_t nibble_value) -> void
    {
      switch(nibble_value)
      {
                 case  0: { sram_parallel_port_pin_addr00_type::set_pin_low (); sram_parallel_port_pin_addr01_type::set_pin_low (); sram_parallel_port_pin_addr02_type::set_pin_low (); sram_parallel_port_pin_addr03_type::set_pin_low (); break; }
                 case  1: { sram_parallel_port_pin_addr00_type::set_pin_high(); sram_parallel_port_pin_addr01_type::set_pin_low (); sram_parallel_port_pin_addr02_type::set_pin_low (); sram_parallel_port_pin_addr03_type::set_pin_low (); break; }
                 case  2: { sram_parallel_port_pin_addr00_type::set_pin_low (); sram_parallel_port_pin_addr01_type::set_pin_high(); sram_parallel_port_pin_addr02_type::set_pin_low (); sram_parallel_port_pin_addr03_type::set_pin_low (); break; }
                 case  3: { sram_parallel_port_pin_addr00_type::set_pin_high(); sram_parallel_port_pin_addr01_type::set_pin_high(); sram_parallel_port_pin_addr02_type::set_pin_low (); sram_parallel_port_pin_addr03_type::set_pin_low (); break; }
                 case  4: { sram_parallel_port_pin_addr00_type::set_pin_low (); sram_parallel_port_pin_addr01_type::set_pin_low (); sram_parallel_port_pin_addr02_type::set_pin_high(); sram_parallel_port_pin_addr03_type::set_pin_low (); break; }
                 case  5: { sram_parallel_port_pin_addr00_type::set_pin_high(); sram_parallel_port_pin_addr01_type::set_pin_low (); sram_parallel_port_pin_addr02_type::set_pin_high(); sram_parallel_port_pin_addr03_type::set_pin_low (); break; }
                 case  6: { sram_parallel_port_pin_addr00_type::set_pin_low (); sram_parallel_port_pin_addr01_type::set_pin_high(); sram_parallel_port_pin_addr02_type::set_pin_high(); sram_parallel_port_pin_addr03_type::set_pin_low (); break; }
                 case  7: { sram_parallel_port_pin_addr00_type::set_pin_high(); sram_parallel_port_pin_addr01_type::set_pin_high(); sram_parallel_port_pin_addr02_type::set_pin_high(); sram_parallel_port_pin_addr03_type::set_pin_low (); break; }
                 case  8: { sram_parallel_port_pin_addr00_type::set_pin_low (); sram_parallel_port_pin_addr01_type::set_pin_low (); sram_parallel_port_pin_addr02_type::set_pin_low (); sram_parallel_port_pin_addr03_type::set_pin_high(); break; }
                 case  9: { sram_parallel_port_pin_addr00_type::set_pin_high(); sram_parallel_port_pin_addr01_type::set_pin_low (); sram_parallel_port_pin_addr02_type::set_pin_low (); sram_parallel_port_pin_addr03_type::set_pin_high(); break; }
                 case 10: { sram_parallel_port_pin_addr00_type::set_pin_low (); sram_parallel_port_pin_addr01_type::set_pin_high(); sram_parallel_port_pin_addr02_type::set_pin_low (); sram_parallel_port_pin_addr03_type::set_pin_high(); break; }
                 case 11: { sram_parallel_port_pin_addr00_type::set_pin_high(); sram_parallel_port_pin_addr01_type::set_pin_high(); sram_parallel_port_pin_addr02_type::set_pin_low (); sram_parallel_port_pin_addr03_type::set_pin_high(); break; }
                 case 12: { sram_parallel_port_pin_addr00_type::set_pin_low (); sram_parallel_port_pin_addr01_type::set_pin_low (); sram_parallel_port_pin_addr02_type::set_pin_high(); sram_parallel_port_pin_addr03_type::set_pin_high(); break; }
                 case 13: { sram_parallel_port_pin_addr00_type::set_pin_high(); sram_parallel_port_pin_addr01_type::set_pin_low (); sram_parallel_port_pin_addr02_type::set_pin_high(); sram_parallel_port_pin_addr03_type::set_pin_high(); break; }
                 case 14: { sram_parallel_port_pin_addr00_type::set_pin_low (); sram_parallel_port_pin_addr01_type::set_pin_high(); sram_parallel_port_pin_addr02_type::set_pin_high(); sram_parallel_port_pin_addr03_type::set_pin_high(); break; }
        default: case 15: { sram_parallel_port_pin_addr00_type::set_pin_high(); sram_parallel_port_pin_addr01_type::set_pin_high(); sram_parallel_port_pin_addr02_type::set_pin_high(); sram_parallel_port_pin_addr03_type::set_pin_high(); break; }
      }
    }

  public:
    memory_sram_parallel_cypress_cy62158e()
    {
      // Initialize the parallel sram control pins.
      sram_parallel_port_pin_ce1_not_type::set_pin_high();
      sram_parallel_port_pin_ce2_____type::set_pin_low();
      sram_parallel_port_pin_oe__not_type::set_pin_high();
      sram_parallel_port_pin_we__not_type::set_pin_high();

      sram_parallel_port_pin_ce1_not_type::set_direction_output();
      sram_parallel_port_pin_ce2_____type::set_direction_output();
      sram_parallel_port_pin_oe__not_type::set_direction_output();
      sram_parallel_port_pin_we__not_type::set_direction_output();

      // Set the microcontroller 8-bit port word to input.
      // This is the port that is used for data read/write.
      // the default direction.
      sram_parallel_port_word08_data_type::set_direction_input();

      // Initialize the 16-bit port word in the port expander.
      // This is the port that is used for the upper word
      // (bits 4-19) of the memory addresses.
      sram_parallel_port_word16_addr_04_to_19_type::set_port(UINT16_C(0));
      sram_parallel_port_word16_addr_04_to_19_type::set_direction_output();

      // Initialize individual address bit ports of the
      // microcontroller. These ports are used for the
      // lower nibble (bits 0...3) of the memory addresses.
      sram_parallel_port_pin_addr00_type::set_pin_low();
      sram_parallel_port_pin_addr01_type::set_pin_low();
      sram_parallel_port_pin_addr02_type::set_pin_low();
      sram_parallel_port_pin_addr03_type::set_pin_low();

      sram_parallel_port_pin_addr03_type::set_direction_output();
      sram_parallel_port_pin_addr02_type::set_direction_output();
      sram_parallel_port_pin_addr01_type::set_direction_output();
      sram_parallel_port_pin_addr00_type::set_direction_output();
    }

    ~memory_sram_parallel_cypress_cy62158e() = default;

    auto write(const std::uint32_t address_to_write, const std::uint8_t source_byte_to_write) -> void
    {
      // According to Document Number: 38-05684 Rev. *L:
      // To write to the device, take Chip Enables (CE1_NOT LOW and CE2
      // HIGH) and Write Enable (WE_NOT) input LOW. Data on the eight I/O
      // pins (I/O0 through I/O7) is then written into the location specified
      // on the address pins (A0 through A19).

      // In detail, then, consider:
      // Figure 6. Write Cycle No. 1 (WE_NOT Controlled)
      // Document Number: 38-05684 Rev. *L Page 9 of 17

      // Set the low 4 (nibble) bits of the address on portb.0-3.
      nibble_port_pin_functions(static_cast<std::uint8_t>(address_to_write & UINT8_C(0x0F)));

      const std::uint16_t input_word16_addr_04_to_19 = static_cast<std::uint16_t>(address_to_write >> 4U);

      // Set the high 16 (word) bits of the address.
      // Set these if (and only if) the high 16 (word) bits
      // of the address has changed.
      if(my_word16_addr_04_to_19 != input_word16_addr_04_to_19)
      {
        sram_parallel_port_word16_addr_04_to_19_type::set_port(input_word16_addr_04_to_19);

        my_word16_addr_04_to_19 = input_word16_addr_04_to_19;
      }

      // Assert the control pins to select the memory device.
      sram_parallel_port_pin_ce2_____type::set_pin_high();
      sram_parallel_port_pin_ce1_not_type::set_pin_low();

      // Set the microcontroller port value (i.e., of port_address_read_write_data)
      sram_parallel_port_word08_data_type::set_port(source_byte_to_write);

      mcal::helper::disable_all_interrupts<has_disable_enable_interrupts>();

      // Set the microcontroller port direction (i.e., of port_address_read_write_data)
      // to output (to write out the data).
      sram_parallel_port_word08_data_type::set_direction_output();

      // Assert WE_NOT to low in order to latch out the byte.
      sram_parallel_port_pin_we__not_type::set_pin_low();

      mcal::helper::nop_maker<nop_count>::execute_n();

      // De-assert WE_NOT.
      sram_parallel_port_pin_we__not_type::set_pin_high();

      mcal::helper::enable_all_interrupts<has_disable_enable_interrupts>();

      // De-assert the control pins to un-select the memory device.
      sram_parallel_port_pin_ce1_not_type::set_pin_high();
      sram_parallel_port_pin_ce2_____type::set_pin_low();

      // Set the microcontroller port (i.e., port_address_read_write_data)
      // back to input (default direction).
      sram_parallel_port_word08_data_type::set_direction_input();
    }

    auto write_n(const std::uint32_t address_to_write,
                 const std::size_t   count,
                 const std::uint8_t* source_input_to_write) -> void
    {
      // Write n bytes, when n can be 1 but should
      // be greater than 1 for improved efficiency.

      // Set the low 4 (nibble) bits of the address on portb.0-3.
            std::uint8_t  input_word08_addr_00_to_03 = static_cast<std::uint8_t> (address_to_write & UINT8_C(0x0F));
      const std::uint16_t input_word16_addr_04_to_19 = static_cast<std::uint16_t>(address_to_write >> 4U);

      // Set the high 16 (word) bits of the address.
      // Set these if (and only if) the high 16 (word) bits
      // of the address has changed.
      if(my_word16_addr_04_to_19 != input_word16_addr_04_to_19)
      {
        my_word16_addr_04_to_19 = input_word16_addr_04_to_19;

        sram_parallel_port_word16_addr_04_to_19_type::set_port(my_word16_addr_04_to_19);
      }

      // Set the microcontroller port direction (i.e., of port_address_read_write_data)
      // to output (to write out the data).
      sram_parallel_port_word08_data_type::set_direction_output();

      for(std::size_t i = 0U; i < count; ++i)
      {
        if(input_word08_addr_00_to_03 == UINT8_C(0x10))
        {
          // Important:
          // By design, the body of this if-clause will *not*
          // be executed on the zero'th trip through the enclosing
          // for-loop.
          input_word08_addr_00_to_03 = 0U;

          ++my_word16_addr_04_to_19;

          // Set the high 16 (word) bits of the address.
          sram_parallel_port_word16_addr_04_to_19_type::set_port(my_word16_addr_04_to_19);
        }

        // Set the low 4 (nibble) bits of the address on portb.0-3.
        nibble_port_pin_functions(input_word08_addr_00_to_03);

        // Assert the control pins to select the memory device.
        sram_parallel_port_pin_ce2_____type::set_pin_high();
        sram_parallel_port_pin_ce1_not_type::set_pin_low();

        // Set the microcontroller port value (i.e., of port_address_read_write_data)
        sram_parallel_port_word08_data_type::set_port(*(source_input_to_write + i));

        mcal::helper::disable_all_interrupts<has_disable_enable_interrupts>();

        // Assert WE_NOT to low in order to latch out the byte.
        sram_parallel_port_pin_we__not_type::set_pin_low();

        mcal::helper::nop_maker<nop_count>::execute_n();

        // De-assert WE_NOT.
        sram_parallel_port_pin_we__not_type::set_pin_high();

        mcal::helper::enable_all_interrupts<has_disable_enable_interrupts>();

        ++input_word08_addr_00_to_03;
      }

      // De-assert the control pins to un-select the memory device.
      sram_parallel_port_pin_ce1_not_type::set_pin_high();
      sram_parallel_port_pin_ce2_____type::set_pin_low();

      // Set the microcontroller port (i.e., port_address_read_write_data)
      // back to input (default direction).
      sram_parallel_port_word08_data_type::set_direction_input();
    }

    auto read(const std::uint32_t address_to_read) -> std::uint8_t
    {
      // According to Document Number: 38-05684 Rev. *L:
      // To read from the device, take Chip Enables (CE1_NOT LOW and CE2
      // HIGH) and OE_NOT LOW while forcing the WE_NOT HIGH. Under these
      // conditions, the contents of the memory location specified by the
      // address pins appear on the I/O pins.

      // In detail, then, consider:
      // Figure 5. Read Cycle No. 2 (OE_NOT Controlled)
      // Document Number: 38-05684 Rev. *L Page 8 of 17

      // Set the low 4 (nibble) bits of the address on portb.0-3.
      nibble_port_pin_functions(static_cast<std::uint8_t>(address_to_read & UINT8_C(0x0F)));

      const std::uint16_t input_word16_addr_04_to_19 = static_cast<std::uint16_t>(address_to_read >> 4U);

      // Set the high 16 (word) bits of the address.
      // Set these if (and only if) the high 16 (word) bits
      // of the address has changed.
      if(my_word16_addr_04_to_19 != input_word16_addr_04_to_19)
      {
        sram_parallel_port_word16_addr_04_to_19_type::set_port(input_word16_addr_04_to_19);

        my_word16_addr_04_to_19 = input_word16_addr_04_to_19;
      }

      // Assert the control pins to select the memory device.
      sram_parallel_port_pin_ce2_____type::set_pin_high();
      sram_parallel_port_pin_ce1_not_type::set_pin_low();

      mcal::helper::disable_all_interrupts<has_disable_enable_interrupts>();

      // Assert OE_NOT to low and also disable write in order to strobe in the byte.
      sram_parallel_port_pin_oe__not_type::set_pin_low();
      sram_parallel_port_pin_we__not_type::set_pin_high();

      mcal::helper::nop_maker<nop_count + 1U>::execute_n();

      // Get the byte to read.
      const std::uint8_t byte_to_read = sram_parallel_port_word08_data_type::read_port();

      // De-assert OE_NOT after reading the byte.
      sram_parallel_port_pin_oe__not_type::set_pin_high();

      mcal::helper::enable_all_interrupts<has_disable_enable_interrupts>();

      // De-assert the control pins to un-select the memory device.
      sram_parallel_port_pin_ce1_not_type::set_pin_high();
      sram_parallel_port_pin_ce2_____type::set_pin_low();

      return byte_to_read;
    }

    auto read_n(const std::uint32_t address_to_read,
                const std::size_t   count,
                      std::uint8_t* dest_to_store_read_data) -> void
    {
      // Read n bytes, when n can be 1 but should
      // be greater than 1 for improved efficiency.

            std::uint8_t  input_word08_addr_00_to_03 = static_cast<std::uint8_t> ((address_to_read) & UINT8_C(0x0F));
      const std::uint16_t input_word16_addr_04_to_19 = static_cast<std::uint16_t>((address_to_read) >> 4U);

      // Set the low 4 (nibble) bits of the address on portb.0-3.
      nibble_port_pin_functions(input_word08_addr_00_to_03);

      // Set the high 16 (word) bits of the address.
      // Set these if (and only if) the high 16 (word) bits
      // of the address has changed.
      if(my_word16_addr_04_to_19 != input_word16_addr_04_to_19)
      {
        my_word16_addr_04_to_19 = input_word16_addr_04_to_19;

        sram_parallel_port_word16_addr_04_to_19_type::set_port(my_word16_addr_04_to_19);
      }

      // Assert the control pins to select the memory device.
      sram_parallel_port_pin_ce2_____type::set_pin_high();
      sram_parallel_port_pin_ce1_not_type::set_pin_low();

      mcal::helper::disable_all_interrupts<has_disable_enable_interrupts>();

      // Assert OE_NOT to low in order to begin strobing
      // in the byte stream.
      sram_parallel_port_pin_oe__not_type::set_pin_low();
      sram_parallel_port_pin_we__not_type::set_pin_high();

      mcal::helper::nop_maker<nop_count + 1U>::execute_n();

      *dest_to_store_read_data = sram_parallel_port_word08_data_type::read_port();

      for(std::size_t i = 1U; i < count; ++i)
      {
        ++input_word08_addr_00_to_03;

        if(input_word08_addr_00_to_03 == UINT8_C(0x10))
        {
          input_word08_addr_00_to_03 = 0U;

          ++my_word16_addr_04_to_19;

          // Set the high 16 (word) bits of the address.
          sram_parallel_port_word16_addr_04_to_19_type::set_port(my_word16_addr_04_to_19);
        }

        // Set the low 4 (nibble) bits of the address on portb.0-3.
        nibble_port_pin_functions(input_word08_addr_00_to_03);

        *(dest_to_store_read_data + i) = sram_parallel_port_word08_data_type::read_port();
      }

      // De-assert OE_NOT after reading n bytes.
      sram_parallel_port_pin_oe__not_type::set_pin_high();

      mcal::helper::enable_all_interrupts<has_disable_enable_interrupts>();

      // De-assert the control pins to un-select the memory device.
      sram_parallel_port_pin_ce1_not_type::set_pin_high();
      sram_parallel_port_pin_ce2_____type::set_pin_low();
    }

  private:
    std::uint16_t my_word16_addr_04_to_19 { };
  };

  } } } // namespace mcal::memory::sram

#endif // MCAL_MEMORY_SRAM_PARALLEL_CYPRESS_CY62158E_2020_05_01_H
