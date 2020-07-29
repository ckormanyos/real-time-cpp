///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_irq.h>

/*
void __my_startup                     ();                                                                    // Position 00 : This is implemented in crt0.cpp.
*/
void __int_vect_undef_instr_handler   () { mcal::irq::secure::int_vect_undef_instr_handler_callback   (); }  // Position 01
void __int_vect_sw_interrupt_handler  () { mcal::irq::secure::int_vect_sw_interrupt_handler_callback  (); }  // Position 02
void __int_vect_prefetch_abort_handler() { mcal::irq::secure::int_vect_prefetch_abort_handler_callback(); }  // Position 03
void __int_vect_data_abort_handler    () { mcal::irq::secure::int_vect_data_abort_handler_callback    (); }  // Position 04
void __int_vect_unused_05_handler     () { mcal::irq::secure::int_vect_unused_05_handler_callback     (); }  // Position 05
void __int_vect_irq_handler           () { mcal::irq::secure::int_vect_irq_handler_callback           (); }  // Position 06
void __int_vect_fiq_handler           () { mcal::irq::secure::int_vect_fiq_handler_callback           (); }  // Position 07
