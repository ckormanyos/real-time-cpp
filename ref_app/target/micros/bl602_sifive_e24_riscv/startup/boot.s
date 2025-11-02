/******************************************************************************************
  Filename    : boot.s
  
  Core        : RV32IMAFCB (SiFive E24 RISC-V)
  
  MCU         : BL602
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.10.2025
  
  Description : boot routine

******************************************************************************************/

.extern InterruptVectorTable
.extern __my_startup
.extern __initial_stack_pointer

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .boot
.type _start, @function
.align 2
.globl _start

_start:
        /* note: The system clock is set to 160MHz by the BL602 bootROM
                 RISC-V mtime clock (rtc_toggle signal) is set to 10MHz
        */

        /* setup the exception vector table (CLIC vectored) */
        la t0, ExceptionVectorTable
        addi t0, t0, 3
        csrw mtvec, t0

        /* setup the interrupt vector table (CLIC vectored) */
        la t0, InterruptVectorTable
        csrw 0x00000307, t0

        /* enable global interrupt flag */
        csrsi mstatus, (1ul << 3u)

        /* setup the stack pointer */
        la sp, __initial_stack_pointer

        /* setup the C/C++ runtime environment */
        j __my_startup


.size _start, .-_start

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .text.vivt
.type ExceptionVectorTable, @function
.align 6
.globl ExceptionVectorTable

ExceptionVectorTable:
                      j .

.size ExceptionVectorTable, .-ExceptionVectorTable
