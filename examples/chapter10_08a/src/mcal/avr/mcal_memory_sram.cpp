///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>

#include <mcal_memory_sram.h>
#include <mcal_memory_sram_parallel_cypress_cy62167gn.h>
#include <mcal_port.h>
#include <mcal_port_pin_dummy.h>
#include <mcal_port_word.h>

namespace
{
  // SRAM port word expander configuration.
  using mcal_memory_sram_parallel_port_word_addr_04_to_19_type = mcal::port::port_word_expander<std::uint16_t>;

  using mcal_memory_sram_parallel_port_pin_addr03_type         = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portb, 3U>;
  using mcal_memory_sram_parallel_port_pin_addr02_type         = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portb, 2U>;
  using mcal_memory_sram_parallel_port_pin_addr01_type         = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portb, 1U>;
  using mcal_memory_sram_parallel_port_pin_addr00_type         = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portb, 0U>;

  using mcal_memory_sram_parallel_port_pin_ce1not_type         = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, 4U>;
  using mcal_memory_sram_parallel_port_pin_ce2____type         = mcal::port::port_pin_dummy; // Pullup over 2.2k to +5V
  using mcal_memory_sram_parallel_port_pin_oe_not_type         = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, 5U>;
  using mcal_memory_sram_parallel_port_pin_we_not_type         = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portb, 4U>;

  using mcal_memory_sram_parallel_port_word_data_08_type       = mcal::port::port_word<std::uint8_t,
                                                                                       std::uint8_t,
                                                                                       mcal::reg::portd>;

  #if 0
  using mcal_memory_sram_parallel_type                         = mcal::memory::sram::memory_sram_parallel_cypress_cy62158e
                                                                   <mcal_memory_sram_parallel_port_word_addr_04_to_19_type,
                                                                    mcal_memory_sram_parallel_port_pin_addr03_type,
                                                                    mcal_memory_sram_parallel_port_pin_addr02_type,
                                                                    mcal_memory_sram_parallel_port_pin_addr01_type,
                                                                    mcal_memory_sram_parallel_port_pin_addr00_type,
                                                                    mcal_memory_sram_parallel_port_pin_ce1not_type,
                                                                    mcal_memory_sram_parallel_port_pin_ce2____type,
                                                                    mcal_memory_sram_parallel_port_pin_oe_not_type,
                                                                    mcal_memory_sram_parallel_port_pin_we_not_type,
                                                                    mcal_memory_sram_parallel_port_word_data_08_type,
                                                                    0U,
                                                                    true>;
  #else
  using mcal_memory_sram_parallel_port_pin_addr20_type         = mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, 2U>;

  using mcal_memory_sram_parallel_type                         = mcal::memory::sram::memory_sram_parallel_cypress_cy62167gn
                                                                   <mcal_memory_sram_parallel_port_pin_addr20_type,
                                                                    mcal_memory_sram_parallel_port_word_addr_04_to_19_type,
                                                                    mcal_memory_sram_parallel_port_pin_addr03_type,
                                                                    mcal_memory_sram_parallel_port_pin_addr02_type,
                                                                    mcal_memory_sram_parallel_port_pin_addr01_type,
                                                                    mcal_memory_sram_parallel_port_pin_addr00_type,
                                                                    mcal_memory_sram_parallel_port_pin_ce1not_type,
                                                                    mcal_memory_sram_parallel_port_pin_ce2____type,
                                                                    mcal_memory_sram_parallel_port_pin_oe_not_type,
                                                                    mcal_memory_sram_parallel_port_pin_we_not_type,
                                                                    mcal_memory_sram_parallel_port_word_data_08_type,
                                                                    0U,
                                                                    true>;
  #endif

  mcal_memory_sram_parallel_type& mcal_memory_sram_device()
  {
    static mcal_memory_sram_parallel_type sram0;

    return sram0;
  }
}

extern "C"
uint8_t mcal_memory_sram_read_byte(const mcal_sram_uintptr_t src_addr)
{
  const std::uint8_t by = mcal_memory_sram_device().read(src_addr);

  return by;
}

extern "C"
uint16_t mcal_memory_sram_read_word(const mcal_sram_uintptr_t src_addr)
{
  uint16_t dest = 0U;

  mcal_memory_sram_device().read_n(src_addr, 2U, (std::uint8_t*) &dest);

  return dest;
}

extern "C"
uint32_t mcal_memory_sram_read_dword(const mcal_sram_uintptr_t src_addr)
{
  uint32_t dest = 0U;

  mcal_memory_sram_device().read_n(src_addr, 4U, (std::uint8_t*) &dest);

  return dest;
}

extern "C"
uint64_t mcal_memory_sram_read_qword(const mcal_sram_uintptr_t src_addr)
{
  uint64_t dest = 0U;

  mcal_memory_sram_device().read_n(src_addr, 8U, (std::uint8_t*) &dest);

  return dest;
}

extern "C"
void mcal_memory_sram_write_byte(const uint8_t src_value, const mcal_sram_uintptr_t dest_addr)
{
  mcal_memory_sram_device().write(dest_addr, src_value);
}

extern "C"
void mcal_memory_sram_write_word(const uint16_t src_value, const mcal_sram_uintptr_t dest_addr)
{
  const uint16_t local_src_value = src_value;

  mcal_memory_sram_device().write_n(dest_addr, 2U, (const uint8_t*) &local_src_value);
}

extern "C"
void mcal_memory_sram_write_dword(const uint32_t src_value, const mcal_sram_uintptr_t dest_addr)
{
  const uint32_t local_src_value = src_value;

  mcal_memory_sram_device().write_n(dest_addr, 4U, (const uint8_t*) &local_src_value);
}

extern "C"
void mcal_memory_sram_write_qword(const uint64_t src_value, const mcal_sram_uintptr_t dest_addr)
{
  const uint64_t local_src_value = src_value;

  mcal_memory_sram_device().write_n(dest_addr, 8U, (const uint8_t*) &local_src_value);
}
