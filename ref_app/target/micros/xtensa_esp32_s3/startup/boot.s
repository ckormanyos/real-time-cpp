/******************************************************************************************
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from:
******************************************************************************************/

/******************************************************************************************
  Filename    : boot.s
  
  Core        : Xtensa LX7
  
  MCU         : ESP32-S3
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.02.2025
  
  Description : low-level startup code for ESP32-S3
  
******************************************************************************************/

/*******************************************************************************************
  \brief

  \param

  \return
********************************************************************************************/
.section .text
.type _start, @function
.align 4
.extern __CORE0_STACK_TOP
.extern __CORE1_STACK_TOP
.extern __my_startup
.extern main_c1
.globl _start

.equ  core0_id, 0xcdcd
.equ  core1_id, 0xabab

_start:
  /* disable and clear all pending interrupts including cpu timer interrupts */
  movi a8, 0
  wsr a8, interrupt
  wsr a8, intenable
  movi a8, -1
  wsr a8, intclear
  wsr a8, ccompare0
  wsr a8, ccompare1
  wsr a8, ccompare2

  /* setup interrupt vector table */
  movi a10, _vector_table
  wsr a10, vecbase

  /* check which core is executing this code */
  movi a8, core1_id
  rsr.prid a2
  beq a2, a8, .L_boot_core1

  /* setup the stack pointer for core0 */
  movi a1, __CORE0_STACK_TOP

  /* setup the C/C++ runtime environment */
  j  __my_startup
  j .

.L_boot_core1:
  /* setup the stack pointer for core1 */
  movi a1, __CORE1_STACK_TOP

  /* jump to core1 main function */
  j  main_c1
  j .

.size _start, .-_start

/*******************************************************************************************
  \brief

  \param

  \return
********************************************************************************************/
.section .text
.type get_core_id, @function
.align 4
.globl get_core_id

get_core_id:
  rsr.prid a2
  movi a8, core1_id
  beq a2, a8, .L_core1
  movi a2, 0
  ret
.L_core1:
  movi a2, 1
  ret

.size get_core_id, .-get_core_id
