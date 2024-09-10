// ***************************************************************************************
// Filename    : util.s
//
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 04.09.2024
// 
// Description : low-level utility functions
// 
// ***************************************************************************************

.file "util.s"

.syntax unified

.cpu cortex-m33


.thumb_func
.section ".text", "ax"
.align 8
.globl BlockingDelay
.type  BlockingDelay, % function


BlockingDelay:
                      subs r0, r0, #1
                      bne BlockingDelay
                      bx lr

.size BlockingDelay, .-BlockingDelay

