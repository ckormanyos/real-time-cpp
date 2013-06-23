///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstddef>
#include <cstdint>
#include <algorithm>

extern "C" void __my_startup();
extern "C" void undefined_instruction_handler();
extern "C" void svc_handler();
extern "C" void abort_handler();
extern "C" void irq_handler();
extern "C" void fiq_handler();

namespace
{
  constexpr std::uint32_t am335x_vector_base = 0x4030FC00UL;
  constexpr std::size_t   am335x_vector_size = 14U;

  void vector_base_address_set(const std::uint32_t addr)
  {
    asm("mcr p15, #0, %[value], c12, c0, 0":: [value] "r" (addr));
  }
}

extern "C"
const volatile std::uint32_t __isr_vector_rom_copy[am335x_vector_size] __attribute__((section(".isr_vector_rom_copy")));

extern "C"
const volatile std::uint32_t __isr_vector_rom_copy[am335x_vector_size] =
{
  0xE59FF018UL,
  0xE59FF018UL,
  0xE59FF018UL,
  0xE59FF018UL,
  0xE59FF014UL,
  0xE24FF008UL,
  0xE59FF010UL,
  0xE59FF010UL,
  reinterpret_cast<std::uint32_t>(__my_startup),
  reinterpret_cast<std::uint32_t>(undefined_instruction_handler),
  reinterpret_cast<std::uint32_t>(svc_handler),
  reinterpret_cast<std::uint32_t>(abort_handler),
  reinterpret_cast<std::uint32_t>(irq_handler),
  reinterpret_cast<std::uint32_t>(fiq_handler)
};

namespace crt
{
  void init_system_interrupt_vectors() __attribute__((section(".startup")));

  void init_system_interrupt_vectors()
  {
    vector_base_address_set(am335x_vector_base);

    std::copy(__isr_vector_rom_copy,
              __isr_vector_rom_copy + am335x_vector_size,
              reinterpret_cast<std::uint32_t*>(am335x_vector_base));
  }
}
