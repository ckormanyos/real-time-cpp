///////////////////////////////////////////////////////////////////////////////
//  Copyright Amine Chalandi 2024.
//  Copyright Christopher Kormanyos 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// ***************************************************************************************
// Filename    : util.s (now util.cpp)
//
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 04.09.2024
// 
// Description : low-level utility functions
// 
// ***************************************************************************************

#include <cstdint>

extern "C" auto arch_spin_lock  (std::uint32_t*) noexcept -> void __attribute__((naked));
extern "C" auto arch_spin_unlock(std::uint32_t*) noexcept -> void __attribute__((naked));

extern "C"
auto arch_spin_lock(std::uint32_t*) noexcept -> void
{
  asm volatile("mov     r1, #1");              // Set r1 to 1 (lock acquired)
  asm volatile(".L_loop:");
  asm volatile("ldaex   r2, [r0]");            // Load exclusive value
  asm volatile("cmp     r2, #0");              // Check if lock is free
  asm volatile("bne     .L_loop");             // Retry if not free
  asm volatile("strex   r2, r1, [r0]");        // Try to acquire the lock
  asm volatile("cmp     r2, #0");              // Check if successful
  asm volatile("bne     .L_loop");             // Retry if not
  asm volatile("dmb");                         // Ensure memory ordering after acquiring the lock
  asm volatile("bx      lr");                  // Return unconditionally
}

extern "C"
auto arch_spin_unlock(std::uint32_t*) noexcept -> void
{
  asm volatile("dmb");                         // Ensure memory operations before unlocking
  asm volatile("mov     r1, #0");              // Clear the lock
  asm volatile("stl     r1, [r0]");            // Store with release semantics
  asm volatile("bx      lr");                  // Return unconditionally
}
