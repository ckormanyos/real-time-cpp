@///////////////////////////////////////////////////////////////////////////////
@//  Copyright Christopher Kormanyos 2013.
@//  Distributed under the Boost Software License,
@//  Version 1.0. (See accompanying file LICENSE_1_0.txt
@//  or copy at http://www.boost.org/LICENSE_1_0.txt)
@//

.global __irq_handler
.global __fiq_handler
.global __isr_vector

.set intc_sir_irq_activeirq, 0x0000007F
.set intc_control_newirqagr, 0x00000001
.set intc_sir_fiq_activefiq, 0x0000007F
.set intc_control_newfiqagr, 0x00000002
.set soc_aintc_regs,         0x48200000

.equ addr_sir_irq, soc_aintc_regs + 0x40
.equ addr_sir_fiq, soc_aintc_regs + 0x44
.equ addr_control, soc_aintc_regs + 0x48

.equ mask_active_irq, intc_sir_irq_activeirq
.equ mask_active_fiq, intc_sir_fiq_activefiq
.equ newirqagr, intc_control_newirqagr
.equ newfiqagr, intc_control_newfiqagr

.text

.code 32

@ The IRQ handler routes the ISR of highest priority in the IRQ
@ to its handler. The IRQ handler does not support nesting.

__irq_handler:
  stmfd  r13!, {r0-r3, r12, r14}    @ Save the context in the IRQ stack
  ldr    r0, =addr_sir_irq          @ Get the Active IRQ
  ldr    r1, [r0]
  and    r1, r1, #mask_active_irq   @ Mask the Active IRQ number
  ldr    r0, =__isr_vector          @ Load the base of the vector table
  add    r14, pc, #0                @ Save return address in LR 
  ldr    pc, [r0, r1, lsl #2]       @ Jump to the ISR
  mov    r0, #newirqagr             @ Acknowledge the current IRQ 
  ldr    r1, =addr_control
  str    r0, [r1]
  dmb                               @ Barrier to complete the data write
  ldmfd  r13!, {r0-r3, r12, r14}    @ Restore registers from IRQ stack
  subs   pc, r14, #0x4              @ Return to program before IRQ

@ The FIQ handler routes the ISR of highest priority in the FIQ
@ to its handler. The FIQ handler does not support nesting.

__fiq_handler:
  stmfd  r13!, {r0-r3, r12, r14}    @ Save the context in the FIQ stack
  ldr    r0, =addr_sir_fiq          @ Get the Active FIQ
  ldr    r1, [r0]
  and    r1, r1, #mask_active_fiq   @ Mask the Active IRQ number
  ldr    r0, =__isr_vector          @ Load the base of the vector table
  add    r14, pc, #0                @ Save return address in LR
  ldr    pc, [r0, r1, lsl #2]       @ Jump to the ISR
  mov    r0, #newfiqagr             @ Acknowledge the current FIQ
  ldr    r1, =addr_control
  str    r0, [r1]
  dmb                               @ Barrier to complete the data write
  ldmfd  r13!, {r0-r3, r12, r14}    @ Restore registers from IRQ stack
  subs   pc, r14, #0x4              @ Return to program before FIQ

.end
