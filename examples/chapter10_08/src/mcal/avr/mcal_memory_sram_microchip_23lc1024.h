///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_SRAM_MICROCHIP_23LC1024_2020_04_11_H_
  #define MCAL_MEMORY_SRAM_MICROCHIP_23LC1024_2020_04_11_H_

  #include <array>

  #include <mcal_memory_sram.h>
  #include <util/utility/util_communication.h>
  #include <util/utility/util_noncopyable.h>

  namespace mcal { namespace memory { namespace sram {

  class memory_sram_microchip_23lc1024 : private util::noncopyable
  {
  private:
    // instruction   instruction    HEX       instruction
    //    name          format      code      description
    //
    //    READ        0000 0011     0x03      Read data from memory array beginning at selected address
    //    WRITE       0000 0010     0x02      Write data to memory array beginning at selected address
    //    EDIO        0011 1011     0x3B      Enter Dual I/O access (enter SDI bus mode)
    //    EQIO        0011 1000     0x38      Enter Quad I/O access (enter SQI bus mode)
    //    RSTIO       1111 1111     0xFF      Reset Dual and Quad access (revert to SPI bus mode)
    //    RDMR        0000 0101     0x05      Read Mode Register
    //    WRMR        0000 0001     0x01      Write Mode Register

    static constexpr std::uint8_t read__cmd = UINT8_C(0x03);
    static constexpr std::uint8_t write_cmd = UINT8_C(0x02);
    static constexpr std::uint8_t rdmr__cmd = UINT8_C(0x05);
    static constexpr std::uint8_t wrmr__cmd = UINT8_C(0x01);

  public:
    memory_sram_microchip_23lc1024(util::communication_base& com)
      : my_com        (com),
        my_state_is_ok(true)
    {
      my_com.select_channel(0U);

      my_state_is_ok &= set_mode_sequence();
    }

    ~memory_sram_microchip_23lc1024() = default;

    bool select_channel(const std::size_t index)
    {
      return my_com.select_channel(index);
    }

    bool read_byte(const std::uint32_t address, std::uint8_t& byte_to_read)
    {
      // Read one byte from external serial memory.

      const std::array<std::uint8_t, 5U> cmd =
      {{
        read__cmd,
        std::uint8_t((address & UINT32_C(0x0001FFFF)) >> 16U),
        std::uint8_t((address & UINT32_C(0x0001FFFF)) >>  8U),
        std::uint8_t((address & UINT32_C(0x0001FFFF)) >>  0U),
        UINT8_C(0xFF)
      }};

      // Read one byte from memory.
      my_com.select();
      my_state_is_ok &= my_com.send_n(cmd.cbegin(), cmd.cend());
      my_com.deselect();

      my_state_is_ok &= my_com.recv(byte_to_read);

      return my_state_is_ok;
    }

    bool read_dword(const std::uint32_t address, std::uint32_t& dword_to_read)
    {
      // Read a dword from external serial memory.

      const std::array<std::uint8_t, 5U> cmd =
      {{
        read__cmd,
        std::uint8_t((address & UINT32_C(0x0001FFFF)) >> 16U),
        std::uint8_t((address & UINT32_C(0x0001FFFF)) >>  8U),
        std::uint8_t((address & UINT32_C(0x0001FFFF)) >>  0U),
        UINT8_C(0xFF)
      }};

      my_com.select();
      my_state_is_ok &= my_com.send_n(cmd.cbegin(), cmd.end());
      my_state_is_ok &= my_com.recv(*(reinterpret_cast<std::uint8_t*>(&dword_to_read) + 0U));
      my_state_is_ok &= my_com.send(UINT8_C(0xFF));
      my_state_is_ok &= my_com.recv(*(reinterpret_cast<std::uint8_t*>(&dword_to_read) + 1U));
      my_state_is_ok &= my_com.send(UINT8_C(0xFF));
      my_state_is_ok &= my_com.recv(*(reinterpret_cast<std::uint8_t*>(&dword_to_read) + 2U));
      my_state_is_ok &= my_com.send(UINT8_C(0xFF));
      my_state_is_ok &= my_com.recv(*(reinterpret_cast<std::uint8_t*>(&dword_to_read) + 3U));
      my_com.deselect();

      return my_state_is_ok;
    }

    bool write_byte(const std::uint32_t address, const std::uint8_t byte_to_write)
    {
      // Write one byte to external serial memory.

      const std::array<std::uint8_t, 5U> cmd =
      {{
        write_cmd,
        std::uint8_t((address & UINT32_C(0x0001FFFF)) >> 16U),
        std::uint8_t((address & UINT32_C(0x0001FFFF)) >>  8U),
        std::uint8_t((address & UINT32_C(0x0001FFFF)) >>  0U),
        byte_to_write
      }};

      my_com.select();
      my_state_is_ok &= my_com.send_n(cmd.cbegin(), cmd.cend());
      my_com.deselect();

      return my_state_is_ok;
    }

    bool write_dword(const std::uint32_t address, const std::uint32_t dword_to_write)
    {
      // Write a dword to external serial memory.

      const std::array<std::uint8_t, 8U> cmd =
      {{
        write_cmd,
        std::uint8_t((address & UINT32_C(0x0001FFFF)) >> 16U),
        std::uint8_t((address & UINT32_C(0x0001FFFF)) >>  8U),
        std::uint8_t((address & UINT32_C(0x0001FFFF)) >>  0U),
        *(reinterpret_cast<const std::uint8_t*>(&dword_to_write) + 0U),
        *(reinterpret_cast<const std::uint8_t*>(&dword_to_write) + 1U),
        *(reinterpret_cast<const std::uint8_t*>(&dword_to_write) + 2U),
        *(reinterpret_cast<const std::uint8_t*>(&dword_to_write) + 3U),
      }};

      my_com.select();
      my_state_is_ok &= my_com.send_n(cmd.cbegin(), cmd.cend());
      my_com.deselect();

      return my_state_is_ok;
    }

    bool state_is_ok() const noexcept
    {
      return my_state_is_ok;
    }

  private:
    util::communication_base& my_com;
    bool my_state_is_ok;

    bool set_mode_byte()
    {
      bool result_is_ok = true;

      my_com.select();
      result_is_ok &= my_com.send(wrmr__cmd);
      result_is_ok &= my_com.send(UINT8_C(0x00));
      my_com.deselect();

      return result_is_ok;
    }

    bool set_mode_sequence()
    {
      bool result_is_ok = true;

      my_com.select();
      result_is_ok &= my_com.send(wrmr__cmd);
      result_is_ok &= my_com.send(UINT8_C(0x40));
      my_com.deselect();

      return result_is_ok;
    }

    memory_sram_microchip_23lc1024() = delete;
  };

  } } } // namespace mcal::memory::sram

#endif // MCAL_MEMORY_SRAM_MICROCHIP_23LC1024_2020_04_11_H_
