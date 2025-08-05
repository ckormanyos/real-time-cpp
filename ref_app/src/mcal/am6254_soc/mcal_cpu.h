///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_2009_02_14_H
  #define MCAL_CPU_2009_02_14_H

  #include <cstdint>

  extern "C" auto hw_acquire_spin_lock(volatile std::uint32_t*) noexcept -> void;
  extern "C" auto hw_release_spin_lock(volatile std::uint32_t*) noexcept -> void;

  namespace mcal
  {
    namespace cpu
    {
      void init();

      inline auto post_init() -> void { }

      inline auto nop() noexcept -> void { asm volatile("nop"); }

      inline auto acquire_spin_lock(volatile std::uint32_t* p_sync) noexcept -> void { hw_acquire_spin_lock(p_sync); }
      inline auto release_spin_lock(volatile std::uint32_t* p_sync) noexcept -> void { hw_release_spin_lock(p_sync); }
    }
  }

#endif // MCAL_CPU_2009_02_14_H
