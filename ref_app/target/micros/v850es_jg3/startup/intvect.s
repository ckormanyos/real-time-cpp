/******************************************************************************************
  Filename    : intvect.s

  Core        : V850ES/JG3-L

  Mcu         : uPD70F3793

  Author      : Chalandi Amine

  Owner       : Chalandi Amine

  Date        : 28.10.2026

  Description : Interrupt vector table for V850ES

******************************************************************************************/

.section .intvect
.type _start, @function
.align 2
.globl intvecttable

intvecttable:
    .balign 0x10
    vector_0x00:
        jr _start

    .balign 0x10
    vector_0x10:
        br .

    .balign 0x10
    vector_0x20:
        br .

    .balign 0x10
    vector_0x30:
        br .

    .balign 0x10
    vector_0x40:
        br .

    .balign 0x10
    vector_0x50:
        br .

    .balign 0x10
    vector_0x60:
        br .

    .balign 0x10
    vector_0x70:
        /* Security ID data (10 bytes) */
        .byte 0xFF
        .byte 0xFF
        .byte 0xFF
        .byte 0xFF
        .byte 0xFF
        .byte 0xFF
        .byte 0xFF
        .byte 0xFF
        .byte 0xFF
        .byte 0xFF /* enable the on-chip debug emulator */
        /* option bytes */
        .byte 0x01
        .byte 0x00
        .byte 0x00
        .byte 0x00
        .byte 0x00
        .byte 0x00

    .balign 0x10
    vector_0x80:
        br .

    .balign 0x10
    vector_0x90:
        br .

    .balign 0x10
    vector_0xa0:
        br .

    .balign 0x10
    vector_0xb0:
        br .

    .balign 0x10
    vector_0xc0:
        br .

    .balign 0x10
    vector_0xd0:
        br .

    .balign 0x10
    vector_0xe0:
        br .

    .balign 0x10
    vector_0xf0:
        br .

    .balign 0x10
    vector_0x100:
        br .

    .balign 0x10
    vector_0x110:
        br .

    .balign 0x10
    vector_0x120:
        br .

    .balign 0x10
    vector_0x130:
        br .

    .balign 0x10
    vector_0x140:
        br .

    .balign 0x10
    vector_0x150:
        br .

    .balign 0x10
    vector_0x160:
        br .

    .balign 0x10
    vector_0x170:
        br .

    .balign 0x10
    vector_0x180:
        br .

    .balign 0x10
    vector_0x190:
        br .

    .balign 0x10
    vector_0x1a0:
        br .

    .balign 0x10
    vector_0x1b0:
        br .

    .balign 0x10
    vector_0x1c0:
        br .

    .balign 0x10
    vector_0x1d0:
        br .

    .balign 0x10
    vector_0x1e0:
        br .

    .balign 0x10
    vector_0x1f0:
        br .

    .balign 0x10
    vector_0x200:
        br .

    .balign 0x10
    vector_0x210:
        br .

    .balign 0x10
    vector_0x220:
        br .

    .balign 0x10
    vector_0x230:
        br .

    .balign 0x10
    vector_0x240:
        br .

    .balign 0x10
    vector_0x250:
        br .

    .balign 0x10
    vector_0x260:
        br .

    .balign 0x10
    vector_0x270:
        br .

    .balign 0x10
    vector_0x280:
        jr _timer_isr

    .balign 0x10
    vector_0x290:
        br .

    .balign 0x10
    vector_0x2a0:
        br .

    .balign 0x10
    vector_0x2b0:
        br .

    .balign 0x10
    vector_0x2c0:
        br .

    .balign 0x10
    vector_0x2d0:
        br .

    .balign 0x10
    vector_0x2e0:
        br .

    .balign 0x10
    vector_0x2f0:
        br .

    .balign 0x10
    vector_0x300:
        br .

    .balign 0x10
    vector_0x310:
        br .

    .balign 0x10
    vector_0x320:
        br .

    .balign 0x10
    vector_0x330:
        br .

    .balign 0x10
    vector_0x340:
        br .

    .balign 0x10
    vector_0x350:
        br .

    .balign 0x10
    vector_0x360:
        br .

    .balign 0x10
    vector_0x370:
        br .

    .balign 0x10
    vector_0x380:
        br .

    .balign 0x10
    vector_0x390:
        br .

    .balign 0x10
    vector_0x3a0:
        br .

    .balign 0x10
    vector_0x3b0:
        br .

    .balign 0x10
    vector_0x3c0:
        br .

    .balign 0x10
    vector_0x3d0:
        br .

    .balign 0x10
    vector_0x3e0:
        br .

    .balign 0x10
    vector_0x3f0:
        br .

    .balign 0x10
    vector_0x400:
        br .

    .balign 0x10
    vector_0x410:
        br .

    .balign 0x10
    vector_0x420:
        br .

    .balign 0x10
    vector_0x430:
        br .

    .balign 0x10
    vector_0x440:
        br .

    .balign 0x10
    vector_0x450:
        br .

.size intvecttable, .-intvecttable
