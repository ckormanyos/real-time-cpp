
.extern __data_end
.extern __data_start
.extern __data_load_start

.extern __bss_start
.extern __bss_end


.section .init4,"ax",@progbits

.global __do_copy_data

.weak  __do_copy_data
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

.weak  __do_clear_bss
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
