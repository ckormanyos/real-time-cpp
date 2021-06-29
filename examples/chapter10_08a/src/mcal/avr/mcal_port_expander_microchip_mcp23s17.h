///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_WORD_EXPANDER_MICROCHIP_MCP23S17_2020_04_21_H_
  #define MCAL_PORT_WORD_EXPANDER_MICROCHIP_MCP23S17_2020_04_21_H_

  #include <mcal_port_expander_microchip_mcp23s17_base.h>

  namespace mcal { namespace port {

  template<const std::uint8_t hardware_address>
  class port_word_expander_microchip_mcp23s17
    : public port_regs_expander_microchip_mcp23s17_base<hardware_address>
  {
  private:
    using base_class_type = port_regs_expander_microchip_mcp23s17_base<hardware_address>;

  public:
    port_word_expander_microchip_mcp23s17(util::communication_base& com) noexcept
      : base_class_type(com) { }

    void set_port(const std::uint16_t port_value) noexcept
    {
      base_class_type::write_word(base_class_type::reg_gpioa, port_value);
    }

    void set_direction_output() noexcept
    {
      // Set all ports to output (default is input 0xFFFF).
      base_class_type::write_word(base_class_type::reg_iodira, UINT16_C(0x0000));
    }

    void set_direction_input() noexcept
    {
      // Set all ports to input (default is input 0xFFFF).
      base_class_type::write_word(base_class_type::reg_iodira, UINT16_C(0xFFFF));
    }
  };

  template<const std::uint8_t hardware_address>
  class port_pin_expander_microchip_mcp23s17
    : public port_regs_expander_microchip_mcp23s17_base<hardware_address>
  {
  private:
    // This implementation uses read-modify-write sequences
    // to access port direction and value registers.
    // It is designed this way in order to avoid member
    // variables, even though read-modify-write might
    // be slower than some other potential implementations.

    using base_class_type = port_regs_expander_microchip_mcp23s17_base<hardware_address>;

  public:
    port_pin_expander_microchip_mcp23s17(util::communication_base& com) noexcept
      : base_class_type(com) { }


    virtual ~port_pin_expander_microchip_mcp23s17() = default;

    void set_direction_output(const std::uint8_t bpos) noexcept
    {
      const std::uint16_t dir = base_class_type::read__word(base_class_type::reg_iodira);

      base_class_type::write_word(base_class_type::reg_iodira,
                                  std::uint16_t(dir & std::uint16_t(~std::uint16_t(1ULL << bpos))));
    }

    void set_direction_input(const std::uint8_t bpos) noexcept
    {
      const std::uint16_t dir = base_class_type::read__word(base_class_type::reg_iodira);

      base_class_type::write_word(base_class_type::reg_iodira,
                                  std::uint16_t(dir | std::uint16_t(1ULL << bpos)));
    }

    void set_pin_high(const std::uint8_t bpos) noexcept
    {
      const std::uint16_t val = base_class_type::read__word(base_class_type::reg_gpioa);

      base_class_type::write_word(base_class_type::reg_gpioa,
                                  std::uint16_t(val | std::uint16_t(1ULL << bpos)));
    }

    void set_pin_low(const std::uint8_t bpos) noexcept
    {
      const std::uint16_t val = base_class_type::read__word(base_class_type::reg_gpioa);

      base_class_type::write_word(base_class_type::reg_gpioa,
                                  std::uint16_t(val & std::uint16_t(~std::uint16_t(1ULL << bpos))));
    }

    bool read_input_value(const std::uint8_t bpos) noexcept
    {
      const std::uint16_t val = base_class_type::read__word(base_class_type::reg_gpioa);

      return (std::uint_fast8_t((val >> bpos) & UINT8_C(1)) != UINT8_C(0));
    }

    void toggle_pin(const std::uint8_t bpos) noexcept
    {
      const std::uint16_t val = base_class_type::read__word(base_class_type::reg_gpioa);

      base_class_type::write_word(base_class_type::reg_gpioa,
                                  std::uint16_t(val ^ std::uint16_t(1ULL << bpos)));
    }
  };

  template<const std::uint8_t hardware_address>
  class port_pin_expander_microchip_mcp23s17_writeonly
    : public port_regs_expander_microchip_mcp23s17_base<hardware_address>
  {
  private:
    using base_class_type = port_regs_expander_microchip_mcp23s17_base<hardware_address>;

  public:
    port_pin_expander_microchip_mcp23s17_writeonly(util::communication_base& com) noexcept
      : base_class_type(com),
        my_pdir(0xFFFF),  // Default I/O mode is input (with direction bit set) --> 0xFFFF
        my_port(0x0000)   // Default output state is low --> 0x0000
    {
    }

    virtual ~port_pin_expander_microchip_mcp23s17_writeonly() = default;

    void set_direction_output(const std::uint8_t bpos) noexcept
    {
      my_pdir &= (~(UINT16_C(1) << bpos));

      base_class_type::write_word(base_class_type::reg_iodira, my_pdir);
    }

    void set_direction_input(const std::uint8_t bpos)
    {
      my_pdir |= (UINT16_C(1) << bpos);

      base_class_type::write_word(base_class_type::reg_iodira, my_pdir);
    }

    void set_pin_high(const std::uint8_t bpos) noexcept
    {
      my_port |= (UINT16_C(1) << bpos);

      base_class_type::write_word(base_class_type::reg_gpioa, my_port);
    }

    void set_pin_low(const std::uint8_t bpos) noexcept
    {
      my_port &= (~(UINT16_C(1) << bpos));

      base_class_type::write_word(base_class_type::reg_gpioa, my_port);
    }

    bool read_input_value(const std::uint8_t bpos) noexcept
    {
      // Unconditionally return false: The pins are write-only.

      static_cast<void>(bpos);

      return false;
    }

    void toggle_pin(const std::uint8_t bpos) noexcept
    {
      my_port ^= (UINT16_C(1) << bpos);

      base_class_type::write_word(base_class_type::reg_gpioa, my_port);
    }

  private:
    std::uint16_t my_pdir;
    std::uint16_t my_port;
  };

  } } // namespace mcal::port

#endif // MCAL_PORT_WORD_EXPANDER_MICROCHIP_MCP23S17_2020_04_21_H_
