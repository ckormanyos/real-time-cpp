///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_RP2350_2024_09_16_H
  #define MCAL_CPU_RP2350_2024_09_16_H

  #include <cstdint>

  namespace mcal { namespace cpu { namespace rp2350 {

  auto multicore_sync(const std::uint32_t CpuId) -> void;
  auto start_core1() -> bool;

  } } } // namespace mcal::cpu::rp2350

#endif // MCAL_CPU_RP2350_2024_09_16_H
