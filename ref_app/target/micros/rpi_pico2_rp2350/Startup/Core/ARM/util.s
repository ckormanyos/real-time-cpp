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

/*******************************************************************************************
  \brief  

  \param  
  
  \return 
********************************************************************************************/
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

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.thumb_func
.section ".text", "ax"
.align 8
.globl arch_spin_lock
.type  arch_spin_lock, % function


arch_spin_lock:
    mov     r1, #1              // Set r1 to 1 (lock acquired)
.L_loop:
    ldaex   r2, [r0]            // Load exclusive value
    cmp     r2, #0              // Check if lock is free
    bne     .L_loop                // Retry if not free
    strex   r2, r1, [r0]        // Try to acquire the lock
    cmp     r2, #0              // Check if successful
    bne     .L_loop                // Retry if not
    dmb                         // Ensure memory ordering after acquiring the lock
    bx      lr                  // Return if successful


.size arch_spin_lock, .-arch_spin_lock

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.thumb_func
.section ".text", "ax"
.align 8
.globl arch_spin_unlock
.type  arch_spin_unlock,  % function


arch_spin_unlock:
    dmb                         // Ensure memory operations before unlocking
    mov     r1, #0              // Clear the lock
    stl     r1, [r0]            // Store with release semantics
    bx      lr                  // Return


.size arch_spin_unlock, .-arch_spin_unlock
