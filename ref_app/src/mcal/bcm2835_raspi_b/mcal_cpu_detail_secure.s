@;///////////////////////////////////////////////////////////////////////////////
@;//  Copyright Christopher Kormanyos 2013 - 2021.
@;//  Distributed under the Boost Software License,
@;//  Version 1.0. (See accompanying file LICENSE_1_0.txt
@;//  or copy at http://www.boost.org/LICENSE_1_0.txt)
@;//

.section .startup, "ax"

.globl mcal_cpu_detail_secure_start_mmu
mcal_cpu_detail_secure_start_mmu:
  mov r2, #0
  mcr p15, 0, r2, c7, c7, 0  @; invalidate caches
  mcr p15, 0, r2, c8, c7, 0  @; invalidate tlb
  mcr p15, 0, r2, c7, c10, 5 @; DSB (barrier instruction)

  mvn r2, #0
  bic r2, #0xC
  mcr p15, 0, r2, c3, c0, 0  @; domain

  mcr p15, 0, r0, c2, c0, 0  @; tlb base
  mcr p15, 0, r0, c2, c0, 1  @; tlb base

  mrc p15, 0, r2, c1, c0, 0
  orr r2, r2, r1
  mcr p15, 0, r2, c1, c0, 0

  bx lr
