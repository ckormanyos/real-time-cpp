
.section .text
.type hw_acquire_spin_lock,@function
.align 3
.globl hw_acquire_spin_lock

hw_acquire_spin_lock:
  mov w1, #1
  .L_loop:
  ldaxr w2, [x0]
  cbnz w2, .L_loop
  stxr w2, w1, [x0]
  cbnz w2, .L_loop
  dmb ish
  ret

.section .text
.type hw_release_spin_lock,@function
.align 3
.globl hw_release_spin_lock

hw_release_spin_lock:
  dmb ish
  stlr wzr, [x0]
  ret
