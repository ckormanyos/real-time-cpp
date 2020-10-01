@///////////////////////////////////////////////////////////////////////////////
@//  Copyright Christopher Kormanyos 2014 - 2020.
@//  Distributed under the Boost Software License,
@//  Version 1.0. (See accompanying file LICENSE_1_0.txt
@//  or copy at http://www.boost.org/LICENSE_1_0.txt)
@//

.globl mcal_reg_access32_write
mcal_reg_access32_write:
  mov r2, #0
  mcr p15, 0, r2, c7, c10, 5
  str r1, [r0]
  bx lr

.globl mcal_reg_access32_read
mcal_reg_access32_read:
  mov r2, #0
  ldr r0, [r0]
  mcr p15, 0, r2, c7, c10, 5
  bx lr
