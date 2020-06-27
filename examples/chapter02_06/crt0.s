;
;  Copyright Christopher Kormanyos 2007 - 2020.
;  Distributed under the Boost Software License,
;  Version 1.0. (See accompanying file LICENSE_1_0.txt
;  or copy at http://www.boost.org/LICENSE_1_0.txt)
;


.section .isr_vectors,"ax",@progbits
.global isr_vectors
.func isr_vectors
isr_vectors:
  call __my_startup
  .endfunc

.extern __do_clear_bss
.extern __do_global_ctors
.extern __initial_stack_pointer
.extern main

.section .startup,"ax",@progbits
.func __my_startup

__my_startup:

  eor  r1, r1
  out  0x3f, r1         ; sreg
  ldi  r28,lo8(__initial_stack_pointer)
  ldi  r29,hi8(__initial_stack_pointer)
  out  0x3e, r29        ; sph
  out  0x3d, r28        ; spl

  ; Initialize the rom-to-ram data
  call __do_copy_data

  ; Clear the bss
  call __do_clear_bss

  ; Call the static constructors.
  call __do_global_ctors

  call main

  ; Catch an unexpected return from main using an endless loop.
  .L__unexpected_return_loop:
  rjmp .L__unexpected_return_loop

.endfunc

.extern __data_end
.extern __data_start
.extern __data_load_start

.extern __bss_start
.extern __bss_end


.section .startup,"ax",@progbits

.global __do_copy_data

.func  __do_copy_data

__do_copy_data:

  ldi  r17, hi8(__data_end)
  ldi  r26, lo8(__data_start)
  ldi  r27, hi8(__data_start)
  ldi  r30, lo8(__data_load_start)
  ldi  r31, hi8(__data_load_start)

  rjmp  .L__do_copy_data_start

  .L__do_copy_data_loop:

  lpm  r0, Z+
  st  X+, r0

  .L__do_copy_data_start:

  cpi  r26, lo8(__data_end)
  cpc  r27, r17
  brne  .L__do_copy_data_loop

  ret
.endfunc

.global __do_clear_bss

.func  __do_clear_bss

__do_clear_bss:

  ldi r17, hi8(__bss_end)
  ldi r26, lo8(__bss_end)
  ldi r27, hi8(__bss_start)
  rjmp .L__do_clear_bss_start

  .L__do_clear_bss_loop:

  ST X+, R1

  .L__do_clear_bss_start:

  cpi r26, lo8(__bss_end)
  cpc r27, r17
  brne .L__do_clear_bss_loop

  ret
.endfunc

.extern __ctors_start
.extern __ctors_end
.extern __tablejump__

.section .startup,"ax",@progbits
.func  __do_global_ctors

__do_global_ctors:

  ldi r17, hi8(__ctors_start)
  ldi r28, lo8(__ctors_end)
  ldi r29, hi8(__ctors_end)
  rjmp .L__do_global_ctors_start

  .L__do_global_ctors_loop:

  sbiw  r28, 0x02
  movw  r30, r28
  call __tablejump__

  .L__do_global_ctors_start:

  cpi r28, lo8(__ctors_start)
  cpc r29, r17
  brne .L__do_global_ctors_loop

  ret
.endfunc


.section .text

.func  __tablejump__

__tablejump__:

  lpm  r0, Z+
  lpm  r31, Z
  mov  r30, r0 
  ijmp

.endfunc
