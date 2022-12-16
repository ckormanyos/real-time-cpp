/******************************************************************************************
  Filename    : boot.s
  
  Core        : RV32IMAC
  
  MCU         : FE310-G002 (SiFive)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 04.06.2021
  
  Description : boot routine 

******************************************************************************************/

.file "boot.s"

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .text
.type _start, @function
.align 4
.extern __STACK_TOP
.extern DirectModeInterruptHandler
.extern Startup_Init
.globl _start

_start:
        /* disable all interrupts flag */
        csrrs x0, mstatus, x0

        /* disable all specific interrupt sources */
        csrrs x0, mie, x0

        /* setup the stack pointer */
        la sp, __STACK_TOP
       
        /* setup the direct interrupt handler */
        la t0, DirectModeInterruptHandler
        csrrs x0, mtvec, t0

        jal   Startup_Init

.size _start, .-_start

