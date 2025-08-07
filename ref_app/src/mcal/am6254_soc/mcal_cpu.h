///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_2025_07_30_H
  #define MCAL_CPU_2025_07_30_H

  #if defined(__cplusplus)
  #include <cstdint>
  #else
  #include <stdint.h>
  #endif

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  void mcal_cpu_secure_acquire_spin_lock(volatile uint32_t*);
  void mcal_cpu_secure_release_spin_lock(volatile uint32_t*);

  static inline void mcal_cpu_nop(void);

  #if defined(__cplusplus)
  }
  #endif

  #if defined(__cplusplus)
  namespace mcal
  {
    namespace cpu
    {
      auto init() -> void;

      inline auto post_init() -> void { }

      inline auto nop() noexcept -> void { asm volatile("nop"); }

      inline auto acquire_spin_lock(volatile std::uint32_t* p_sync) noexcept -> void { mcal_cpu_secure_acquire_spin_lock(p_sync); }
      inline auto release_spin_lock(volatile std::uint32_t* p_sync) noexcept -> void { mcal_cpu_secure_release_spin_lock(p_sync); }
    }
  }
  #endif

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  static inline void mcal_cpu_nop(void) { __asm volatile("nop"); }

  #if defined(__cplusplus)
  }
  #endif

#endif // MCAL_CPU_2025_07_30_H
