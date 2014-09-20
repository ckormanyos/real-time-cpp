
///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Adapted from: "Part of the Raspberry-Pi Bare Metal Tutorials"
//  See the original copyright notice below.

//  Part of the Raspberry-Pi Bare Metal Tutorials
//  Copyright (c) 2013, Brian Sidebotham
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice,
//      this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.


.section ".text.startup"

.global _start

.equ    CPSR_MODE_USER,         0x10
.equ    CPSR_MODE_FIQ,          0x11
.equ    CPSR_MODE_IRQ,          0x12
.equ    CPSR_MODE_SVR,          0x13
.equ    CPSR_MODE_ABORT,        0x17
.equ    CPSR_MODE_UNDEFINED,    0x1B
.equ    CPSR_MODE_SYSTEM,       0x1F

.equ    CPSR_THUMB,             0x20
.equ    CPSR_FIQ_INHIBIT,       0x40
.equ    CPSR_IRQ_INHIBIT,       0x80


_start:
  ldr pc, _reset_h
  ldr pc, _undefined_instruction_vector_h
  ldr pc, _software_interrupt_vector_h
  ldr pc, _prefetch_abort_vector_h
  ldr pc, _data_abort_vector_h
  ldr pc, _unused_handler_h
  ldr pc, _the_one_and_only_interrupt_vector_h
  ldr pc, _the_one_and_only_fast_interrupt_vector_h

_reset_h:                                  .word   _reset_
_undefined_instruction_vector_h:           .word   undefined_instruction_vector
_software_interrupt_vector_h:              .word   software_interrupt_vector
_prefetch_abort_vector_h:                  .word   prefetch_abort_vector
_data_abort_vector_h:                      .word   data_abort_vector
_unused_handler_h:                         .word   _reset_
_the_one_and_only_interrupt_vector_h:      .word   the_one_and_only_interrupt_vector
_the_one_and_only_fast_interrupt_vector_h: .word   the_one_and_only_fast_interrupt_vector


_reset_:

  // Copy the interrupt vector table.
  // TBD: Can the same be accomplished in C++?
  mov     r0, #0x8000
  mov     r1, #0x0000
  ldmia   r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
  stmia   r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
  ldmia   r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
  stmia   r1!, {r2, r3, r4, r5, r6, r7, r8, r9}

  // Setup the interrupt stack (with 1kB stack size),
  // and switch to irq mode.
  ldr r3, =__initial_stack_pointer
  msr cpsr_c, #(CPSR_MODE_IRQ | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT)
  mov sp, r3
  sub r3, r3, #0x0400

  // Setup the user/system stack (with 3kB stack size),
  // and switch back to system mode.
  msr cpsr_c, #(CPSR_MODE_SVR | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT)
  mov sp, r3

  // Jump to the startup function and never return.
  bl __my_startup
