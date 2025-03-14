/******************************************************************************************
  Filename    : boot.S

  Core        : RISC-V

  MCU         : ESP32-S3

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 22.02.2025

  Description : boot routine for ULP-RISC-V Co-processor

******************************************************************************************/

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .boot
.type _start, @function
.align 4
.extern __STACK_TOP
.extern Startup_Init
.globl _start

_start:
  /* setup the stack pointer */
  la sp, __STACK_TOP

  /* setup C/C++ runtime environment */
  j  Startup_Init

.size _start, .-_start
