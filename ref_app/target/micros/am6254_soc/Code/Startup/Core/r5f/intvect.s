// ***************************************************************************************
// Filename    : intvect.s
// 
// Core        : ARM Cortex-R5F
// 
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 26.07.2025
// 
// Description : Exception vector table for ARM Cortex-R5
// 
// ***************************************************************************************

//----------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  
///
/// \return 
//----------------------------------------------------------------------------------------
.section .intvect,"ax"
.type exception_vector_table, %function
.align 2
.globl exception_vector_table
.globl undefined_exception_handler
.globl svc_exception_handler
.globl prefetch_abort_exception_handler
.globl data_abort_exception_handler
.globl reserved_exception_handler
.globl irq_exception_handler
.globl fiq_exception_handler
.extern _start

exception_vector_table:
               b _start                           // Reset
               b undefined_exception_handler      // Undefined Instruction
               b svc_exception_handler            // Software interrupt
               b prefetch_abort_exception_handler // Abort (prefetch)
               b data_abort_exception_handler     // Abort (data)
               b reserved_exception_handler       // rsvd
               b irq_exception_handler            // IRQ
               b fiq_exception_handler            // FIQ


undefined_exception_handler:       b .
svc_exception_handler:             b .
prefetch_abort_exception_handler:  b .
data_abort_exception_handler:      b .
reserved_exception_handler:        b .
irq_exception_handler:             b .
fiq_exception_handler:             b .


.size exception_vector_table, .-exception_vector_table

//----------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  
///
/// \return 
//----------------------------------------------------------------------------------------
.section .text,"ax"
.type vim_irq_handler, %function
.align 2
.global vim_irq_handler

vim_irq_handler:
                push {r0-r12, lr}
                bl timer_irq
                pop {r0-r12, lr}
                subs pc, lr, #4


.size vim_irq_handler, .-vim_irq_handler

//----------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  
///
/// \return 
//----------------------------------------------------------------------------------------
.section .text,"ax"
.type vim_fiq_handler, %function
.align 2
.global vim_fiq_handler

vim_fiq_handler:
                  push {r0-r12, lr}
                  bl timer_irq
                  pop {r0-r12, lr}
                  subs pc, lr, #4


.size vim_fiq_handler, .-vim_fiq_handler

//----------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  
///
/// \return 
//----------------------------------------------------------------------------------------
.section .text,"ax"
.type EnableFIQ, %function
.align 2
.globl EnableFIQ

EnableFIQ:
        mrs     r0, cpsr
        bic     r1, r0, #0x40
        msr     cpsr, r1
        bx      lr

.size EnableFIQ, .-EnableFIQ

//----------------------------------------------------------------------------------------
/// \brief  
///
/// \descr  
///
/// \param  
///
/// \return 
//----------------------------------------------------------------------------------------
.section .text,"ax"
.type EnableIRQ, %function
.align 2
.globl EnableIRQ

EnableIRQ:
        mrs     r0, cpsr
        bic     r1, r0, #0x80
        msr     cpsr, r1
        bx      lr

.size EnableIRQ, .-EnableIRQ
