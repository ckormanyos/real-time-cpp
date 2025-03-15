/******************************************************************************************
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from:
/******************************************************************************************
  Filename    : boot.S

  Core        : RISC-V

  MCU         : ESP32-S3

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 22.02.2025

  Description : boot routine for ULP-RISC-V Co-processor

******************************************************************************************/

/*******************************************************************************************
  \brief

  \param

  \return
********************************************************************************************/
.section .boot
.type _start, @function
.align 4
.extern __STACK_TOP
.extern __my_startup
.globl _start

_start:
  /* setup the stack pointer */
  la sp, __STACK_TOP

  /* setup C/C++ runtime environment */
  j  __my_startup

.size _start, .-_start
