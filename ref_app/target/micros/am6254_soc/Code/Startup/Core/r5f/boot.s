// ***************************************************************************************
// Filename    : boot.s
// 
// Core        : ARM Cortex-R5F
// 
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 26.07.2025
// 
// Description : boot code
// 
// ***************************************************************************************

//----------------------------------------------------------------------------------------
/// \brief  _start
///
/// \descr  boot manager
///
/// \param  void
///
/// \return void
//----------------------------------------------------------------------------------------
.section .boot,"ax"
.type _start, %function
.align 2
.globl _start

_start:
       /* The AM6254 SBL jumped to this code in System mode (thumb state) and with interrupt disabled */
       /* switch to ARM state */
        mrs     r0, cpsr
        bic     r1, r0, #0x20
        msr     cpsr, r1

      /* patch the exception vector table at address 0 (we cannot relocate it, on R5F the IVT @ is hard coded to 0).
         address 0x20 --> holds the address of the reset handler */
       ldr r0, =undefined_exception_handler
       mov r1, #0x24
       str r0, [r1, #0]
       ldr r0, =svc_exception_handler
       str r0, [r1, #4]
       ldr r0, =prefetch_abort_exception_handler
       str r0, [r1, #8]
       ldr r0, =data_abort_exception_handler
       str r0, [r1, #12]
       ldr r0, =reserved_exception_handler
       str r0, [r1, #16]
       ldr r0, =irq_exception_handler
       str r0, [r1, #20]
       ldr r0, =fiq_exception_handler
       str r0, [r1, #24]

       /* enable the vectored interrupt controller */
       mrc p15, #0, r0, c1, c0, #0
       orr r0, r0, #(1ul<<24)
       mcr p15, #0, r0, c1, c0, #0

       /* enable FPU */
       mrc p15, 0, r0, c1, c0, 2
       orr r1, r0, #(0xFul<<20)
       mcr p15, 0, r1, c1, c0, 2
       mov r0,#(1ul<<30)
       fmxr fpexc,r0

       /* Setup the stack pointer for the System mode */
       ldr r3, =__SYS_STACK_TOP
       mov sp, r3

       /* switch to Abort mode and setup the relevant stack pointer */
       cps #0x17
       ldr r3, =__ABT_STACK_TOP
       mov sp, r3

       /* switch to Undefined mode and setup the relevant stack pointer */
       cps #0x1b
       ldr r3, =__UND_STACK_TOP
       mov sp, r3

       /* switch to IRQ mode and setup the relevant stack pointer */
       cps #0x12
       ldr r3, =__IRQ_STACK_TOP
       mov sp, r3

       /* switch to FIQ mode and setup the relevant stack pointer */
       cps #0x11
       ldr r3, =__FIQ_STACK_TOP
       mov sp, r3

       /* switch to SVC mode and setup the relevant stack pointer */
       cps #0x1a
       ldr r3, =__SVC_STACK_TOP
       mov sp, r3

       /* switch back to SYS mode */
       cps #0x1f

       /* clear registers (for clean debugging) */
       mov r0, #0
       mov r1, #0
       mov r2, #0
       mov r3, #0
       mov r4, #0
       mov r5, #0
       mov r6, #0
       mov r7, #0
       mov r8, #0
       mov r9, #0
       mov r10, #0
       mov r11, #0
       mov r12, #0

       /* Jump to the C-Runtime Startup */
       b Startup_Init

.size _start, .-_start
