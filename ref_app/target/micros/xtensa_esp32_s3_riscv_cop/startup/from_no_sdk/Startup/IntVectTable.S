/******************************************************************************************
  Filename    : IntVectTable.S
  
  Core        : RISC-V
  
  MCU         : ESP32-S3
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.02.2025
  
  Description : interrupt vector table implementation for ULP-RISC-V Co-processor
  
******************************************************************************************/

#include "custom_ops.h"

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .vector
.type _InterruptVectorTable, @function
.align 4
.extern _IRQ_VECTORS
.globl _InterruptVectorTable

_InterruptVectorTable:
          /* reset vector */
          j _start
          
          /* irq vector  */
          .org  _InterruptVectorTable + 0x10
          j _IRQ_VECTORS

.size _InterruptVectorTable, .-_InterruptVectorTable

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .text
.type _IRQ_VECTORS, @function
.align 4
.extern irq_vector
.globl _IRQ_VECTORS


_IRQ_VECTORS:
          addi sp, sp, -(17*4)
          sw   ra, 0(sp)
          sw   tp, 4(sp)
          sw   t0, 8(sp)
          sw   t1, 12(sp)
          sw   t2, 16(sp)
          sw   a0, 20(sp)
          sw   a1, 24(sp)
          sw   a2, 28(sp)
          sw   a3, 32(sp)
          sw   a4, 36(sp)
          sw   a5, 40(sp)
          sw   a6, 44(sp)
          sw   a7, 48(sp)
          sw   t3, 52(sp)
          sw   t4, 56(sp)
          sw   t5, 60(sp)
          sw   t6, 64(sp)
          picorv32_getq_insn(a0,q1)
          jal irq_vector
          lw   ra, 0(sp)
          lw   tp, 4(sp)
          lw   t0, 8(sp)
          lw   t1, 12(sp)
          lw   t2, 16(sp)
          lw   a0, 20(sp)
          lw   a1, 24(sp)
          lw   a2, 28(sp)
          lw   a3, 32(sp)
          lw   a4, 36(sp)
          lw   a5, 40(sp)
          lw   a6, 44(sp)
          lw   a7, 48(sp)
          lw   t3, 52(sp)
          lw   t4, 56(sp)
          lw   t5, 60(sp)
          lw   t6, 64(sp)
          addi sp,sp, (17*4)
          picorv32_retirq_insn()


.size _IRQ_VECTORS, .-_IRQ_VECTORS

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .text
.type set_timer_counter, @function
.align 4
.globl set_timer_counter

set_timer_counter:
                  /* custom instruction to set the timer counter */
                  picorv32_timer_insn(zero, a0)
                  ret

.size set_timer_counter, .-set_timer_counter
