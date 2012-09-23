.extern __ctors_start
.extern __ctors_end
.extern __tablejump__

.section .init6,"ax",@progbits
.weak  __do_global_ctors
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

.weak  __tablejump__
.func  __tablejump__

__tablejump__:

  lpm  r0, Z+
  lpm  r31, Z
  mov  r30, r0 
  ijmp

.endfunc
