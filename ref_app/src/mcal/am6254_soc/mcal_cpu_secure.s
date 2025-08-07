///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from:

// ***************************************************************************************
// Filename    : boot.s
// 
// Core        : ARM Cortex-A53
// 
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 16.05.2025
// 
// Description : multicore ARM Cortex-A53 (ARMv8-A) startup code
// 
// ***************************************************************************************

.section .text
.type mcal_cpu_secure_acquire_spin_lock,@function
.align 3
.globl mcal_cpu_secure_acquire_spin_lock

mcal_cpu_secure_acquire_spin_lock:
  mov w1, #1
  .L_loop:
  ldaxr w2, [x0]
  cbnz w2, .L_loop
  stxr w2, w1, [x0]
  cbnz w2, .L_loop
  dmb ish
  ret

.section .text
.type mcal_cpu_secure_release_spin_lock,@function
.align 3
.globl mcal_cpu_secure_release_spin_lock

mcal_cpu_secure_release_spin_lock:
  dmb ish
  stlr wzr, [x0]
  ret
