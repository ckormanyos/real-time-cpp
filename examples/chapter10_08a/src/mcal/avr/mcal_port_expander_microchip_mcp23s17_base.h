///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_WORD_EXPANDER_MICROCHIP_MCP23S17_BASE_2020_10_04_H_
  #define MCAL_PORT_WORD_EXPANDER_MICROCHIP_MCP23S17_BASE_2020_10_04_H_

  #include <util/utility/util_communication.h>
  #include <util/utility/util_two_part_data_manipulation.h>

  namespace mcal { namespace port {

  template<const std::uint8_t hardware_address>
  class port_regs_expander_microchip_mcp23s17_base
  {
  protected:
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

    static constexpr std::uint8_t addr_enable  = UINT8_C(0x08);

    static constexpr std::uint8_t my_address   = ((hardware_address > addr_max) ? addr_max : hardware_address);

    static constexpr std::uint8_t my_cmd_write = std::uint8_t(UINT8_C(0x40) | std::uint8_t(my_address << 1U));
    static constexpr std::uint8_t my_cmd__read = std::uint8_t(UINT8_C(0x41) | std::uint8_t(my_address << 1U));

  protected:
    port_regs_expander_microchip_mcp23s17_base(util::communication_base& com) noexcept
      : my_com(com)
    {
      // Set the address-enable bit.
      my_com.select();
      my_com.send(my_cmd_write);
      my_com.send(reg_iocona);
      my_com.send(addr_enable);
      my_com.deselect();
    }

    std::uint16_t read__word(const std::uint8_t reg)
    {
      std::uint8_t byte_to_read_lo = std::uint8_t();
      std::uint8_t byte_to_read_hi = std::uint8_t();

      my_com.select();
      my_com.send(my_cmd__read);
      my_com.send(reg);
      my_com.send(UINT8_C(0));
      my_com.recv(byte_to_read_lo);
      my_com.send(UINT8_C(0));
      my_com.recv(byte_to_read_hi);
      my_com.deselect();

      return util::make_long(byte_to_read_lo, byte_to_read_hi);
    }

    void write_word(const std::uint8_t reg, const std::uint16_t word_to_write) noexcept
    {
      my_com.select();
      my_com.send(my_cmd_write);
      my_com.send(reg);
      my_com.send(util::lo_part<std::uint8_t>(word_to_write));
      my_com.send(util::hi_part<std::uint8_t>(word_to_write));
      my_com.deselect();
    }

  private:
    util::communication_base& my_com;
  };

  } } // namespace mcal::port

#endif // MCAL_PORT_WORD_EXPANDER_MICROCHIP_MCP23S17_BASE_2020_10_04_H_
