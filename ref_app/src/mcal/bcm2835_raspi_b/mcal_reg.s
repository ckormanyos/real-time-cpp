@///////////////////////////////////////////////////////////////////////////////
@//  Copyright Christopher Kormanyos 2014 - 2023.
@//  Distributed under the Boost Software License,
@//  Version 1.0. (See accompanying file LICENSE_1_0.txt
@//  or copy at http://www.boost.org/LICENSE_1_0.txt)
@//

.globl Mcu_WriteBcm2835Register
Mcu_WriteBcm2835Register:
  mov r2, #0
  mcr p15, 0, r2, c7, c10, 5
  str r1, [r0]
  bx lr

.globl Mcu_ReadBcm2835Register
Mcu_ReadBcm2835Register:
  mov r2, #0
  ldr r0, [r0]
  mcr p15, 0, r2, c7, c10, 5
  bx lr
