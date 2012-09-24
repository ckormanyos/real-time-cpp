
.extern __do_clear_bss
.extern __do_global_ctors
.extern mcal_wdg_trigger
.extern main

.equ RAMEND, 0x800800

.weak  __stack
.set   __stack, RAMEND

.section .init0,"ax",@progbits
.weak startup
.func startup

startup:

  eor  r1, r1
  out  0x3f, r1         ; SREG
  ldi  r28,lo8(__stack)
  ldi  r29,hi8(__stack)
  out  0x3E, r29        ; SPH
  out  0x3D, r28        ; SPL

  ; Initialize the ROM-to-RAM data.
  call __do_copy_data

  ; Zero-clear the bss section.
  call __do_clear_bss

  ; Call static constructors.
  call __do_global_ctors

  ; Jump to main, and never return.
  call main

  ; Catch an unexpected return from main
  ; using a loop with watchdog service.
  .L__unexpected_return_loop:
  call mcal_wdg_trigger
  rjmp .L__unexpected_return_loop

.endfunc

