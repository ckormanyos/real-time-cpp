// ***************************************************************************************
// Filename    : intvect.s
// 
// Core        : ARM Cortex-A53
// 
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 16.05.2025
// 
// Description : multicore ARM Cortex-A53 (ARMv8-A) exception table
// 
// ***************************************************************************************

.section  .intvect,"ax"
.global vector_table
.type vector_table, @function
.align 11

vector_table:
                  /*********************************************************/
                  /* exception from the current EL using SP0 */
                  /*********************************************************/
                  .balign 0x80
                  curr_el_sp0_sync: b .

                  .balign 0x80
                  curr_el_sp0_irq: b .

                  .balign 0x80
                  curr_el_sp0_fiq: b .

                  .balign 0x80
                  curr_el_sp0_serror: b .

                  /*********************************************************/
                  /* exception from the current EL using the current SP */
                  /*********************************************************/
                  .balign 0x80
                  curr_el_spx_sync: b .

                  .balign 0x80
                  curr_el_spx_irq: b irq_handler

                  .balign 0x80
                  curr_el_spx_fiq: b .

                  .balign 0x80
                  curr_el_spx_serror: b .

                  /*********************************************************/
                  /* exception from a lower EL (AArch64) */
                  /*********************************************************/
                  .balign 0x80
                  lower_el_aarch64_sync: b .

                  .balign 0x80
                  lower_el_aarch64_irq: b .

                  .balign 0x80
                  lower_el_aarch64_fiq: b .

                  .balign 0x80
                  lower_el_aarch64_serror: b .

                  /*********************************************************/
                  /* exception from a lower EL (AArch32) */
                  /*********************************************************/
                   .balign 0x80
                   lower_el_aarch32_sync: b .

                   .balign 0x80
                   lower_el_aarch32_irq: b .

                   .balign 0x80
                   lower_el_aarch32_fiq: b .

                   .balign 0x80
                   lower_el_aarch32_serror: b .


.size vector_table, .-vector_table


.macro save_context
  add  sp, sp, #-16 * 17
  stp  x0, x1, [sp, #16 * 0]
  stp  x2, x3, [sp, #16 * 1]
  stp  x4, x5, [sp, #16 * 2]
  stp  x6, x7, [sp, #16 * 3]
  stp  x8, x9, [sp, #16 * 4]
  stp  x10, x11, [sp, #16 * 5]
  stp  x12, x13, [sp, #16 * 6]
  stp  x14, x15, [sp, #16 * 7]
  stp  x16, x17, [sp, #16 * 8]
  stp  x18, x19, [sp, #16 * 9]
  stp  x20, x21, [sp, #16 * 10]
  stp  x22, x23, [sp, #16 * 11]
  stp  x24, x25, [sp, #16 * 12]
  stp  x26, x27, [sp, #16 * 13]
  stp  x28, x29, [sp, #16 * 14]
  str  x30, [sp, #16 * 15]
  mrs  x0, ELR_EL3
  mrs  x1, SPSR_EL3
  stp  x0, x1, [sp, #16 * 16]
.endm

.macro restore_context
  ldp  x2, x3, [sp, #16 * 1]
  ldp  x4, x5, [sp, #16 * 2]
  ldp  x6, x7, [sp, #16 * 3]
  ldp  x8, x9, [sp, #16 * 4]
  ldp  x10, x11, [sp, #16 * 5]
  ldp  x12, x13, [sp, #16 * 6]
  ldp  x14, x15, [sp, #16 * 7]
  ldp  x16, x17, [sp, #16 * 8]
  ldp  x18, x19, [sp, #16 * 9]
  ldp  x20, x21, [sp, #16 * 10]
  ldp  x22, x23, [sp, #16 * 11]
  ldp  x24, x25, [sp, #16 * 12]
  ldp  x26, x27, [sp, #16 * 13]
  ldp  x28, x29, [sp, #16 * 14]
  ldr  x30, [sp, #16 * 15]
  ldp  x0, x1, [sp, #16 * 16]
  msr  ELR_EL3, x0
  msr  SPSR_EL3, x1
  ldp  x0, x1, [sp, #16 * 0]
  add  sp, sp, #16 * 17
  eret
.endm



.global irq_handler
.type irq_handler, @function
.align 2
irq_handler:
             save_context
             bl timer_isr
             restore_context

.size irq_handler, .-irq_handler
