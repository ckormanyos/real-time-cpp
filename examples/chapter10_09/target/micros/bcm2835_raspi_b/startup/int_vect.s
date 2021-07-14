;///////////////////////////////////////////////////////////////////////////////
;//  Copyright Christopher Kormanyos 2013 - 2020.
;//  Distributed under the Boost Software License,
;//  Version 1.0. (See accompanying file LICENSE_1_0.txt
;//  or copy at http://www.boost.org/LICENSE_1_0.txt)
;//


.section .isr_vector, "ax"

b __my_startup
b __int_vect_undef_instr_handler
b __int_vect_sw_interrupt_handler
b __int_vect_prefetch_abort_handler
b __int_vect_data_abort_handler
b __int_vect_unused_05_handler
b __int_vect_irq_handler
b __int_vect_fiq_handler
