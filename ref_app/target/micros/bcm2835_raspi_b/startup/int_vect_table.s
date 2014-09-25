///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

.section ".text.vechi"

.global _int_vect_hi

_int_vect_hi:
  ldr pc, hi_my_startup                          // __my_startup
  ldr pc, hi_int_vect_undef_instr_handler        // __int_vect_undef_instr_handler
  ldr pc, hi_int_vect_sw_interrupt_handler       // __int_vect_sw_interrupt_handler
  ldr pc, hi_int_vect_prefetch_abort_handler     // __int_vect_prefetch_abort_handler
  ldr pc, hi_int_vect_data_abort_handler         // __int_vect_data_abort_handler
  ldr pc, hi_int_vect_unused_05_handler          // __int_vect_unused_05_handler
  ldr pc, hi_int_vect_irq_handler                // __int_vect_irq_handler
  ldr pc, hi_int_vect_fiq_handler                // __int_vect_fiq_handler

hi_my_startup                      :      .word     __my_startup
hi_int_vect_undef_instr_handler    :      .word     __int_vect_undef_instr_handler
hi_int_vect_sw_interrupt_handler   :      .word     __int_vect_sw_interrupt_handler
hi_int_vect_prefetch_abort_handler :      .word     __int_vect_prefetch_abort_handler
hi_int_vect_data_abort_handler     :      .word     __int_vect_data_abort_handler
hi_int_vect_unused_05_handler      :      .word     __int_vect_unused_05_handler
hi_int_vect_irq_handler            :      .word     __int_vect_irq_handler
hi_int_vect_fiq_handler            :      .word     __int_vect_fiq_handler

.section ".text.veclo"

.global _int_vect_lo

_int_vect_lo:
  ldr pc, lo_my_startup                          // __my_startup
  ldr pc, lo_int_vect_undef_instr_handler        // __int_vect_undef_instr_handler
  ldr pc, lo_int_vect_sw_interrupt_handler       // __int_vect_sw_interrupt_handler
  ldr pc, lo_int_vect_prefetch_abort_handler     // __int_vect_prefetch_abort_handler
  ldr pc, lo_int_vect_data_abort_handler         // __int_vect_data_abort_handler
  ldr pc, lo_int_vect_unused_05_handler          // __int_vect_unused_05_handler
  ldr pc, lo_int_vect_irq_handler                // __int_vect_irq_handler
  ldr pc, lo_int_vect_fiq_handler                // __int_vect_fiq_handler

lo_my_startup                      :      .word     __my_startup
lo_int_vect_undef_instr_handler    :      .word     __int_vect_undef_instr_handler
lo_int_vect_sw_interrupt_handler   :      .word     __int_vect_sw_interrupt_handler
lo_int_vect_prefetch_abort_handler :      .word     __int_vect_prefetch_abort_handler
lo_int_vect_data_abort_handler     :      .word     __int_vect_data_abort_handler
lo_int_vect_unused_05_handler      :      .word     __int_vect_unused_05_handler
lo_int_vect_irq_handler            :      .word     __int_vect_irq_handler
lo_int_vect_fiq_handler            :      .word     __int_vect_fiq_handler
