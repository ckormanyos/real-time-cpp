///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_EXPANDER_MICROCHIP_MCP23S17_2020_04_21_H_
  #define MCAL_PORT_EXPANDER_MICROCHIP_MCP23S17_2020_04_21_H_

  #include <algorithm>
  #include <array>

  #include <util/utility/util_communication.h>
  #include <util/utility/util_noncopyable.h>
  #include <util/utility/util_two_part_data_manipulation.h>

  namespace mcal { namespace port { namespace expander {

  class port_expander_microchip_mcp23s17 : private util::noncopyable
  {
  private:
    static constexpr std::uint8_t reg_iodira   = UINT8_C(0x00);  // MCP23x17 I/O Direction Register
    static constexpr std::uint8_t reg_iodirb   = UINT8_C(0x01);  // 1 = Input (default), 0 = Output

    static constexpr std::uint8_t reg_ipola    = UINT8_C(0x02);  // MCP23x17 Input Polarity Register
    static constexpr std::uint8_t reg_ipolb    = UINT8_C(0x03);  // 0 = Normal (default)(low reads as 0), 1 = Inverted (low reads as 1)

    static constexpr std::uint8_t reg_gpintena = UINT8_C(0x04);  // MCP23x17 Interrupt on Change Pin Assignements
    static constexpr std::uint8_t reg_gpintenb = UINT8_C(0x05);  // 0 = No Interrupt on Change (default), 1 = Interrupt on Change

    static constexpr std::uint8_t reg_defvala  = UINT8_C(0x06);  // MCP23x17 Default Compare Register for Interrupt on Change
    static constexpr std::uint8_t reg_defvalb  = UINT8_C(0x07);  // Opposite of what is here will trigger an interrupt (default = 0)

    static constexpr std::uint8_t reg_intcona  = UINT8_C(0x08);  // MCP23x17 Interrupt on Change Control Register
    static constexpr std::uint8_t reg_intconb  = UINT8_C(0x09);  // 1 = pin is compared to DEFVAL, 0 = pin is compared to previous state (default)

    static constexpr std::uint8_t reg_iocona   = UINT8_C(0x0A);  // MCP23x17 Configuration Register
    static constexpr std::uint8_t reg_ioconb   = UINT8_C(0x0B);  //     Also Configuration Register

    static constexpr std::uint8_t reg_gppua    = UINT8_C(0x0C);  // MCP23x17 Weak Pull-Up Resistor Register
    static constexpr std::uint8_t reg_gppub    = UINT8_C(0x0D);  // INPUT ONLY: 0 = No Internal 100k Pull-Up (default) 1 = Internal 100k Pull-Up 

    static constexpr std::uint8_t reg_intfa    = UINT8_C(0x0E);  // MCP23x17 Interrupt Flag Register
    static constexpr std::uint8_t reg_intfb    = UINT8_C(0x0F);  // READ ONLY: 1 = This Pin Triggered the Interrupt

    static constexpr std::uint8_t reg_intcapa  = UINT8_C(0x10);  // MCP23x17 Interrupt Captured Value for Port Register
    static constexpr std::uint8_t reg_intcapb  = UINT8_C(0x11);  // READ ONLY: State of the Pin at the Time the Interrupt Occurred

    static constexpr std::uint8_t reg_gpioa    = UINT8_C(0x12);  // MCP23x17 GPIO Port Register
    static constexpr std::uint8_t reg_gpiob    = UINT8_C(0x13);  // Value on the Port - Writing Sets Bits in the Output Latch

    static constexpr std::uint8_t reg_olata    = UINT8_C(0x14);  // MCP23x17 Output Latch Register
    static constexpr std::uint8_t reg_olatb    = UINT8_C(0x15);  // 1 = Latch High, 0 = Latch Low (default) Reading Returns Latch State, Not Port Value!

    static constexpr std::uint8_t cmd_write    = UINT8_C(0x40);
    static constexpr std::uint8_t cmd__read    = UINT8_C(0x41);

    static constexpr std::uint8_t addr_max     = UINT8_C(7);

  public:
    port_expander_microchip_mcp23s17(      util::communication_base& com,
                                     const std::uint8_t              address = 0U)
      : my_com        (com),
        my_address    ((std::min)(addr_max, address)),
        my_state_is_ok(true),
        my_pdir       (0xFFFF),    // Default I/O mode is input (with direction bit set, input is high) --> 0xFFFF
        my_port       (0x0000)     // Default output state is low --> 0x0000
     {
       static constexpr std::uint8_t addr_enable = UINT8_C(0x08);

       write_byte(reg_iocona, addr_enable);
     }

    ~port_expander_microchip_mcp23s17() = default;

    void set_direction_output(const std::uint8_t bpos)
    {
      my_pdir &= (~(UINT16_C(1) << bpos));

      my_state_is_ok &= write_word(reg_iodira, my_pdir);
    }

    void set_direction_input(const std::uint8_t bpos)
    {
      my_pdir |= (UINT16_C(1) << bpos);

      my_state_is_ok &= write_word(reg_iodira, my_pdir);
    }

    void set_pin_high(const std::uint8_t bpos)
    {
      my_port |= (UINT16_C(1) << bpos);

      my_state_is_ok &= write_word(reg_gpioa, my_port);
    }

    void set_pin_low(const std::uint8_t bpos)
    {
      my_port &= (~(UINT16_C(1) << bpos));

      my_state_is_ok &= write_word(reg_gpioa, my_port);
    }

    bool read_input_value(const std::uint8_t bpos)
    {
      std::uint16_t value;

      my_state_is_ok &= read__word(reg_gpioa, value);

      const std::uint_fast8_t bval = std::uint_fast8_t((value >> bpos) & UINT8_C(1));

      return (bval != UINT8_C(0));
    }

    void toggle_pin(const std::uint8_t bpos)
    {
      my_port ^= (UINT16_C(1) << bpos);

      my_state_is_ok &= write_word(reg_gpioa, my_port);
    }

    void set_porta(const std::uint8_t porta_value)
    {
      my_port &= std::uint8_t(~UINT8_C(0xFF));
      my_port |= porta_value;

      my_state_is_ok &= write_word(reg_gpioa, my_port);
    }

    void set_portb(const std::uint8_t portb_value)
    {
      my_port &= std::uint16_t(~UINT16_C(0xFF00));

      my_port |= std::uint16_t(std::uint16_t(portb_value) << 8U);

      my_state_is_ok &= write_word(reg_gpioa, my_port);
    }

    void set_port(const std::uint16_t port_value)
    {
      my_port = port_value;

      my_state_is_ok &= write_word(reg_gpioa, my_port);
    }

    void set_porta_direction_output()
    {
      my_pdir &= std::uint8_t(~UINT8_C(0xFF));

      my_state_is_ok &= write_word(reg_iodira, my_pdir);
    }

    void set_portb_direction_output()
    {
      my_pdir &= std::uint16_t(~UINT16_C(0xFF00));

      my_state_is_ok &= write_word(reg_iodira, my_pdir);
    }

    void set_port_direction_output()
    {
      my_pdir = UINT16_C(0x0000);

      my_state_is_ok &= write_word(reg_iodira, my_pdir);
    }

    void set_porta_direction_input()
    {
      my_pdir |= std::uint8_t(UINT8_C(0xFF));

      my_state_is_ok &= write_word(reg_iodira, my_pdir);
    }

    void set_portb_direction_input()
    {
      my_pdir |= std::uint16_t(UINT16_C(0xFF00));

      my_state_is_ok &= write_word(reg_iodira, my_pdir);
    }

    void set_port_direction_input()
    {
      my_pdir = UINT16_C(0xFFFF);

      my_state_is_ok &= write_word(reg_iodira, my_pdir);
    }

    bool state_is_ok() const noexcept
    {
      return my_state_is_ok;
    }

  private:
    util::communication_base& my_com;
    const std::uint8_t        my_address;
    bool                      my_state_is_ok;
    std::uint16_t             my_pdir;
    std::uint16_t             my_port;

    bool read__byte(const std::uint8_t reg, std::uint8_t& byte_to_read)
    {
      const std::array<std::uint8_t, 3U> cmd =
      {{
        std::uint8_t(cmd__read | std::uint8_t(my_address << 1U)),
        reg,
        UINT8_C(0xFF)
      }};

      my_com.select();
      const bool send_is_ok = my_com.send_n(cmd.cbegin(), cmd.cend());
      my_com.deselect();

      std::uint8_t value;
      const bool recv_is_ok = my_com.recv(value);

      byte_to_read = (recv_is_ok ? value : UINT8_C(0));

      return (send_is_ok && recv_is_ok);
    }

    bool read__word(const std::uint8_t reg, std::uint16_t& word_to_read)
    {
      const std::array<std::uint8_t, 4U> cmd =
      {{
        std::uint8_t(cmd__read | std::uint8_t(my_address << 1U)),
        reg,
        UINT8_C(0xFF),
        UINT8_C(0xFF)
      }};

      std::uint8_t dummy_lo = std::uint8_t();
      std::uint8_t dummy_hi = std::uint8_t();

      bool send_is_ok = true;
      bool recv_is_ok = true;

      my_com.select();
      send_is_ok &= my_com.send_n(cmd.cbegin(), cmd.cbegin() + 3U);
      recv_is_ok &= my_com.recv(dummy_lo);
      send_is_ok &= my_com.send_n(cmd.cbegin() + 3U, cmd.cend());
      recv_is_ok &= my_com.recv(dummy_hi);
      my_com.deselect();

      word_to_read = (recv_is_ok ? util::make_long(dummy_lo, dummy_hi) : UINT16_C(0));

      return (send_is_ok && recv_is_ok);
    }

    bool write_byte(const std::uint8_t reg, const std::uint8_t byte_to_write)
    {
      const std::array<std::uint8_t, 3U> cmd =
      {{
        std::uint8_t(cmd_write | std::uint8_t(my_address << 1U)),
        reg,
        byte_to_write
      }};

      my_com.select();
      const bool send_is_ok = my_com.send_n(cmd.cbegin(), cmd.cend());
      my_com.deselect();

      return send_is_ok;
    }

    bool write_word(const std::uint8_t reg, const std::uint16_t word_to_write)
    {
      const std::array<std::uint8_t, 4U> cmd =
      {{
        std::uint8_t(cmd_write | std::uint8_t(my_address << 1U)),
        reg,
        util::lo_part<std::uint8_t>(word_to_write),
        util::hi_part<std::uint8_t>(word_to_write)
      }};

      my_com.select();
      const bool send_is_ok = my_com.send_n(cmd.cbegin(), cmd.cend());
      my_com.deselect();

      return send_is_ok;
    }

    port_expander_microchip_mcp23s17() = delete;
  };

  } } } // namespace mcal::port::expander

#endif // MCAL_PORT_EXPANDER_MICROCHIP_MCP23S17_2020_04_21_H_
