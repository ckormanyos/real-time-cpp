///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstddef>
#include <cstdint>
#include <algorithm>

extern "C" void Entry           ();
extern "C" void UndefInstHandler();
extern "C" void SVCHandler      ();
extern "C" void AbortHandler    ();
extern "C" void IRQHandler      ();
extern "C" void FIQHandler      ();

namespace
{
  constexpr std::uint32_t am335x_vector_base = 0x4030FC00UL;
  constexpr std::size_t   am335x_vector_size = 14U;

  inline void CP15VectorBaseAddrSet(std::uint32_t addr)
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
  reinterpret_cast<std::uint32_t>(Entry),
  reinterpret_cast<std::uint32_t>(UndefInstHandler),
  reinterpret_cast<std::uint32_t>(SVCHandler),
  reinterpret_cast<std::uint32_t>(AbortHandler),
  reinterpret_cast<std::uint32_t>(IRQHandler),
  reinterpret_cast<std::uint32_t>(FIQHandler)
};

namespace crt
{
  void init_isr_vectors() __attribute__((section(".startup")));
}

void crt::init_isr_vectors()
{
  CP15VectorBaseAddrSet(am335x_vector_base);

  std::copy(__isr_vector_rom_copy,
            __isr_vector_rom_copy + am335x_vector_size,
            reinterpret_cast<std::uint32_t*>(am335x_vector_base));
}
