///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_2025_02_22_H
  #define MCAL_CPU_2025_02_22_H

  #define MY_PROGMEM

  #include <cstdint>

  namespace mcal { namespace cpu {

  auto init() -> void;

  auto post_init() noexcept -> void;

  inline auto nop() noexcept -> void { asm volatile("nop"); }

  } } // namespace mcal::cpu

#endif // MCAL_CPU_2025_02_22_H
