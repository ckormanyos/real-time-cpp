@******************************************************************************
@
@ exceptionhandler.S - Definitions of exception handlers
@
@ Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/  
@ All rights reserved.
@
@******************************************************************************
@
@ Share header file with assembly source code
@
#include "hw_intc.h"
#include "soc_AM335x.h"

@************************** Global symbols ************************************
        .global IRQHandler
        .global FIQHandler
        .global AbortHandler
        .global SVCHandler
        .global UndefInstHandler
        .global CPUAbortHandler
        .global fnRAMVectors

        .set INTC_SIR_IRQ_ACTIVEIRQ, 0x0000007F
        .set INTC_CONTROL_NEWIRQAGR, 0x00000001
        .set INTC_SIR_FIQ_ACTIVEFIQ, 0x0000007F
        .set INTC_CONTROL_NEWFIQAGR, 0x00000002
        .set SOC_AINTC_REGS, 0x48200000
        .set INTC_SIR_IRQ, 0x40
        .set INTC_SIR_FIQ, 0x44
        .set INTC_CONTROL, 0x48

        .equ ADDR_SIR_IRQ, SOC_AINTC_REGS + INTC_SIR_IRQ
        .equ ADDR_SIR_FIQ, SOC_AINTC_REGS + INTC_SIR_FIQ
        .equ ADDR_CONTROL, SOC_AINTC_REGS + INTC_CONTROL

        .equ MASK_ACTIVE_IRQ, INTC_SIR_IRQ_ACTIVEIRQ
        .equ MASK_ACTIVE_FIQ, INTC_SIR_FIQ_ACTIVEFIQ
        .equ NEWIRQAGR, INTC_CONTROL_NEWIRQAGR
        .equ NEWFIQAGR, INTC_CONTROL_NEWFIQAGR

        .equ MASK_SVC_NUM, 0xFF000000

@**************************** Text Section ************************************
        .text

@ This source file is assembled for ARM instructions
        .code 32
@******************************************************************************
@*                  Function Definition of SWI Handler
@******************************************************************************    
@
@ The SVC Handler switches to system mode if the SVC number is 458752. If the
@ SVC number is different, no mode switching will be done. No other SVC are 
@ handled here
@
SVCHandler:
        STMFD    r13!, {r0-r1, r14}       @ Save context in SVC stack
        SUB      r13, r13, #0x4           @ Adjust the stack pointer
        LDR      r0, [r14, #-4]           @ R0 points to SWI instruction
        BIC      r0, r0, #MASK_SVC_NUM    @ Get the SWI number
        CMP      r0, #458752
        MRSEQ    r1, spsr                 @ Copy SPSR  
        ORREQ    r1, r1, #0x1F            @ Change the mode to System
        MSREQ    spsr_cf, r1              @ Restore SPSR
        ADD      r13, r13, #0x4           @ Adjust the stack pointer
        LDMFD    r13!, {r0-r1, pc}^       @ Restore registers from IRQ stack

@******************************************************************************
@*                  Function Definition of IRQ Handler
@******************************************************************************    
@
@ The IRQ handler jumps to the ISR of highest priority pending IRQ. 
@ This handler doesnot support nesting.
@
IRQHandler:
        STMFD    r13!, {r0-r3, r12, r14}  @ Save context in IRQ stack
        LDR      r0, =ADDR_SIR_IRQ        @ Get the Active IRQ
        LDR      r1, [r0]
        AND      r1, r1, #MASK_ACTIVE_IRQ @ Mask the Active IRQ number
        LDR      r0, =fnRAMVectors        @ Load the base of the vector table
        ADD      r14, pc, #0              @ Save return address in LR 
        LDR      pc, [r0, r1, lsl #2]     @ Jump to the ISR
        MOV      r0, #NEWIRQAGR           @ Acknowledge the current IRQ 
        LDR      r1, =ADDR_CONTROL        
        STR      r0, [r1]                 
        DMB                               @ Barrier to complete the data write
        LDMFD    r13!, {r0-r3, r12, r14}  @ Restore registers from IRQ stack
        SUBS     pc, r14, #0x4            @ Return to program before IRQ
        
@******************************************************************************
@*                  Function Definition of FIQ Handler
@******************************************************************************    
@
@ The FIQ Handler jumps to the ISR of the highest priority pending FIQ. The
@ pending FIQ. This handler doesnot support nesting
@
FIQHandler:
        STMFD    r13!, {r0-r3, r12, r14}  @ Save context in FIQ stack
        LDR      r0, =ADDR_SIR_FIQ        @ Get the Active FIQ
        LDR      r1, [r0]
        AND      r1, r1, #MASK_ACTIVE_FIQ @ Mask the Active IRQ number
        LDR      r0, =fnRAMVectors        @ Load the base of the vector table
        ADD      r14, pc, #0              @ Save return address in LR
        LDR      pc, [r0, r1, lsl #2]     @ Jump to the ISR
        MOV      r0, #NEWFIQAGR           @ Acknowledge the current FIQ
        LDR      r1, =ADDR_CONTROL
        STR      r0, [r1]
        DMB                               @ Barrier to complete the data write
        LDMFD    r13!, {r0-r3, r12, r14}  @ Restore registers from IRQ stack
        SUBS     pc, r14, #0x4            @ Return to program before FIQ

@******************************************************************************
@*             Function Definition of Abort/Undef Handler
@******************************************************************************    
@
@ The Abort handler goes to the C handler of abort mode. Note that the undefined
@ instruction is not handled separately.
@ if nothing is done in the abort mode, the execution enters infinite loop.
@
AbortHandler:
UndefInstHandler:
@
@ Disable all the interrupts
@
        MRS     r0, cpsr                  @ Read from CPSR
        ORR     r0, r0, #0xC0             @ Clear the IRQ and FIQ bits    
        MSR     cpsr, r0                  @ Write to CPSR
        ADD     r14, pc, #0               @ Store the return address
        LDR     pc, =CPUAbortHandler      @ Go to C handler
@
@ Go to infinite loop if returned from C handler
@
loop0:
        B       loop0

@*****************************************************************************
@
@ End of the file
@
    .end
