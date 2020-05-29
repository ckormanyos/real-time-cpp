#ifndef MCAL_MEMORY_SRAM_PARALLEL_CYPRESS_CY62167GN_2020_05_21_H_
  #define MCAL_MEMORY_SRAM_PARALLEL_CYPRESS_CY62167GN_2020_05_21_H_

  #include <mcal_memory_sram_parallel_cypress_cy62158e.h>
  #include <mcal/mcal_helper.h>

  namespace mcal { namespace memory { namespace sram {

  template<typename sram_parallel_port_pin_addr20_type,
           typename sram_parallel_port_word16_addr_04_to_19_type,
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
  class memory_sram_parallel_cypress_cy62167gn final
    : public mcal::memory::sram::memory_sram_parallel_cypress_cy62158e<sram_parallel_port_word16_addr_04_to_19_type,
                                                                       sram_parallel_port_pin_addr03_type,
                                                                       sram_parallel_port_pin_addr02_type,
                                                                       sram_parallel_port_pin_addr01_type,
                                                                       sram_parallel_port_pin_addr00_type,
                                                                       sram_parallel_port_pin_ce1_not_type,
                                                                       sram_parallel_port_pin_ce2_____type,
                                                                       sram_parallel_port_pin_oe__not_type,
                                                                       sram_parallel_port_pin_we__not_type,
                                                                       sram_parallel_port_word08_data_type,
                                                                       nop_count,
                                                                       has_disable_enable_interrupts>
  {
  private:
    // The CY62167GN is a high performance CMOS static RAM
    // organized as 1M words by 16 bits or 2M words by 8 bit
    // (i.e., 2 Mbyte).

    using base_class_type =
      mcal::memory::sram::memory_sram_parallel_cypress_cy62158e<sram_parallel_port_word16_addr_04_to_19_type,
                                                                sram_parallel_port_pin_addr03_type,
                                                                sram_parallel_port_pin_addr02_type,
                                                                sram_parallel_port_pin_addr01_type,
                                                                sram_parallel_port_pin_addr00_type,
                                                                sram_parallel_port_pin_ce1_not_type,
                                                                sram_parallel_port_pin_ce2_____type,
                                                                sram_parallel_port_pin_oe__not_type,
                                                                sram_parallel_port_pin_we__not_type,
                                                                sram_parallel_port_word08_data_type,
                                                                nop_count,
                                                                has_disable_enable_interrupts>;

  public:
    memory_sram_parallel_cypress_cy62167gn() : my_port_pin_addr20_is_high(false) { }

    ~memory_sram_parallel_cypress_cy62167gn() = default;

    void write(const std::uint32_t address_to_write, const std::uint8_t source_byte_to_write)
    {
      const bool input_port_pin_addr20_is_high = ((address_to_write & UINT32_C(0x00100000)) != UINT32_C(0));

      if(input_port_pin_addr20_is_high != my_port_pin_addr20_is_high)
      {
        (input_port_pin_addr20_is_high ? sram_parallel_port_pin_addr20_type::set_pin_high()
                                       : sram_parallel_port_pin_addr20_type::set_pin_low());

        my_port_pin_addr20_is_high = input_port_pin_addr20_is_high;

        base_class_type::write(std::uint32_t(address_to_write & UINT32_C(0xFFEFFFFF)), source_byte_to_write);
      }
      else
      {
        base_class_type::write(address_to_write, source_byte_to_write);
      }
    }

    void write_n(const std::uint32_t address_to_write,
                 const std::size_t   count,
                 const std::uint8_t* source_input_to_write)
    {
      const bool input_port_pin_addr20_is_high = ((address_to_write & UINT32_C(0x00100000)) != UINT32_C(0));

      if(input_port_pin_addr20_is_high != my_port_pin_addr20_is_high)
      {
        (input_port_pin_addr20_is_high ? sram_parallel_port_pin_addr20_type::set_pin_high()
                                       : sram_parallel_port_pin_addr20_type::set_pin_low());

        my_port_pin_addr20_is_high = input_port_pin_addr20_is_high;

        base_class_type::write_n(std::uint32_t(address_to_write & UINT32_C(0xFFEFFFFF)), count, source_input_to_write);
      }
      else
      {
        base_class_type::write_n(address_to_write, count, source_input_to_write);
      }
    }

    std::uint8_t read(const std::uint32_t address_to_read)
    {
      std::uint8_t read_value;

      const bool input_port_pin_addr20_is_high = ((address_to_read & UINT32_C(0x00100000)) != UINT32_C(0));

      if(input_port_pin_addr20_is_high != my_port_pin_addr20_is_high)
      {
        (input_port_pin_addr20_is_high ? sram_parallel_port_pin_addr20_type::set_pin_high()
                                       : sram_parallel_port_pin_addr20_type::set_pin_low());

        my_port_pin_addr20_is_high = input_port_pin_addr20_is_high;

        read_value = base_class_type::read(std::uint32_t(address_to_read & UINT32_C(0xFFEFFFFF)));
      }
      else
      {
        read_value = base_class_type::read(address_to_read);
      }

      return read_value;
    }

    void read_n(const std::uint32_t address_to_read,
                const std::size_t   count,
                      std::uint8_t* dest_to_store_read_data)
    {
      const bool input_port_pin_addr20_is_high = ((address_to_read & UINT32_C(0x00100000)) != UINT32_C(0));

      if(input_port_pin_addr20_is_high != my_port_pin_addr20_is_high)
      {
        (input_port_pin_addr20_is_high ? sram_parallel_port_pin_addr20_type::set_pin_high()
                                       : sram_parallel_port_pin_addr20_type::set_pin_low());

        my_port_pin_addr20_is_high = input_port_pin_addr20_is_high;

        base_class_type::read_n(std::uint32_t(address_to_read & UINT32_C(0xFFEFFFFF)), count, dest_to_store_read_data);
      }
      else
      {
        base_class_type::read_n(address_to_read, count, dest_to_store_read_data);
      }
    }

  private:
    bool my_port_pin_addr20_is_high;
  };

  } } } // namespace mcal::memory::sram

#endif // MCAL_MEMORY_SRAM_PARALLEL_CYPRESS_CY62167GN_2020_05_21_H_
