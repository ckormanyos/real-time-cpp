/******************************************************************************************
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from:
******************************************************************************************/

/******************************************************************************************
  Filename    : IntVectTable.S

  Core        : Xtensa LX7

  MCU         : ESP32-S3

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 22.02.2025

  Description : Interrupt vector tables for ESP32-S3

******************************************************************************************/

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.macro SaveCpuContext
    addi sp, sp, -4*15
    s32i.n a0,  sp, 0*4
    s32i.n a2,  sp, 1*4
    s32i.n a3,  sp, 2*4
    s32i.n a4,  sp, 3*4
    s32i.n a5,  sp, 4*4
    s32i.n a6,  sp, 5*4
    s32i.n a7,  sp, 6*4
    s32i.n a8,  sp, 7*4
    s32i.n a9,  sp, 8*4
    s32i.n a10,  sp, 9*4
    s32i.n a11,  sp, 10*4
    s32i.n a12,  sp, 11*4
    s32i.n a13,  sp, 12*4
    s32i.n a14,  sp, 13*4
    s32i.n a15,  sp, 14*4
.endm

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.macro RestoreCpuContext
    l32i.n a0,  sp, 0*4
    l32i.n a2,  sp, 1*4
    l32i.n a3,  sp, 2*4
    l32i.n a4,  sp, 3*4
    l32i.n a5,  sp, 4*4
    l32i.n a6,  sp, 5*4
    l32i.n a7,  sp, 6*4
    l32i.n a8,  sp, 7*4
    l32i.n a9,  sp, 8*4
    l32i.n a10,  sp, 9*4
    l32i.n a11,  sp, 10*4
    l32i.n a12,  sp, 11*4
    l32i.n a13,  sp, 12*4
    l32i.n a14,  sp, 13*4
    l32i.n a15,  sp, 14*4
    addi sp, sp, 4*15
.endm

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section  .vector,"ax"

.extern __system_tick_handler

.global _vector_table
.type _vector_table, @function
.align 1024

_vector_table:

  .org _vector_table + 0x00
  WindowVectors:
    j .

  .org _vector_table + 0x180
  Level2InterruptVector:
    j .

  .org _vector_table + 0x1c0
  Level3InterruptVector:
    j irq6_timer1

  .org _vector_table + 0x200
  Level4InterruptVector:
    j .

  .org _vector_table + 0x240
  Level5InterruptVector:
    j .

  .org _vector_table + 0x280
  DebugExceptionVector:
    j .

  .org _vector_table + 0x2c0
  NMIExceptionVector:
    j .

  .org _vector_table + 0x300
  Level1KernalInterruptVector:
    j .

  .org _vector_table + 0x340
  Level1UserInterruptVector:
    j .

  .org _vector_table + 0x3C0
  DoubleExceptionVector:
    j .

  .org _vector_table + 0x400
  InvalidExceptionVector:
    j .

  .org _vector_table + 0x404
  AlignmentDummy:
    nop
    nop

.size _vector_table, .-_vector_table

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section  .text,"ax"
.type irq6_timer1, @function
.align 4
irq6_timer1:
  SaveCpuContext
  call0 __system_tick_handler
  RestoreCpuContext
  rfi 3

.size irq6_timer1, .-irq6_timer1

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section  .text,"ax"
.type enable_irq, @function
.align 4
.global enable_irq

enable_irq:
  wsr a2, INTENABLE
  ret

.size enable_irq, .-enable_irq

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section  .text,"ax"
.type set_cpu_private_timer1, @function
.align 4
.global set_cpu_private_timer1

set_cpu_private_timer1:
  movi a11, 0
  wsr  a11, ccount
  esync
  wsr  a2, ccompare1
  esync
  ret

.size set_cpu_private_timer1, .-set_cpu_private_timer1

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section  .text,"ax"
.type get_cpu_private_timer1, @function
.align 4
.global get_cpu_private_timer1

get_cpu_private_timer1:
  rsr a2, ccount
  esync
  ret

.size get_cpu_private_timer1, .-get_cpu_private_timer1

  // software interrupt
  //movi a10, 0x80;
  //wsr.intset a10
  
  //RSIL --> read and set prio level

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section  .vector,"ax"
.global _dummy_vector_table
.type _dummy_vector_table, @function
.align 1024

_dummy_vector_table:

  .rept 20   // this loop create the full interrupt vector table (20 vectors of 0x40 each)
  .rept 12 // this loop create 0x40 bytes (5x12 + 4 = size of one interrupt vector)
  j .    // 3-byte op
  nop    // 2-byte op
  .endr
  nop      // 2-byte op
  nop      // 2-byte op
  .endr

.size _dummy_vector_table, .-_dummy_vector_table
