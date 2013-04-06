
.extern mcal_cpu_init
.extern mcal_wdg_trigger
.extern __do_clear_bss
.extern __do_global_ctors
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

  ; Initialize the chip: Watchdog, port, oscillator
  call mcal_cpu_init

  ; Initialize data
  call __do_copy_data

  ; Clear bss
  call mcal_wdg_trigger
  call __do_clear_bss

  call mcal_wdg_trigger
  call __do_global_ctors

  call mcal_wdg_trigger
  call main

  ; Catch an unexpected return from main
  ; using a loop with watchdog service.
  .L__unexpected_return_loop:
  call mcal_wdg_trigger
  rjmp .L__unexpected_return_loop

.endfunc

