/******************************************************************************************
  Filename    : boot.s

  Core        : V850ES/JG3-L

  Mcu         : uPD70F3793

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 28.10.2026

  Description : boot routine for V850ES

******************************************************************************************/

.section .boot
.type _start, @function
.align 2
.globl _start

_start:
    # enable the PLL (20MHz)
    jarl _pll_init, lp

    # set System wait control register (VSWC) to 1
    movhi 0xFFFF, r0, r2
    movea 0xF06E, r2, r2
    mov 1, r1
    st.b r1, 0[r2]

    # disable watchdog timer 2
    jarl _wdg_init, lp

    # setup the stack pointer
    movhi hi(__STACK_TOP), r0, sp
    movea lo(__STACK_TOP), sp, sp

    # call C/C++ runtime initialization
    jr _Startup_Init


.size _start, .-_start
