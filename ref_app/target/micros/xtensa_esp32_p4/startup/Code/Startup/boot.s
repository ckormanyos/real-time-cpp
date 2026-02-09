/******************************************************************************************
  Filename    : boot.s
  
  Core        : RISC-V
  
  MCU         : ESP32-P4
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 06.01.2026
  
  Description : boot routine for HP cores

******************************************************************************************/

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .boot
.type _start, @function
.align 2
.globl _start

.set mtvt, 0x307
.set msip, 0x20000000

_start:
        /* setup the interrupt vector table (CLIC) */
        la t0, InterruptVectorTable
        csrw mtvt, t0

        /* setup the exception vector table (CLINT) */
        la t0, ExceptionVectorTable
        csrw mtvec, t0

        /* Enable FPU by setting FS bits in mstatus */
        li t0, 0x00006000
        csrs mstatus, t0
        fscsr x0

         /* Read machine hart ID */
         csrr a0, mhartid
         bnez a0, .L_core1
         la sp, __CORE0_STACK_TOP
         jal Startup_Init
         j .

.L_core1:
         /* note: - RISC-V has no WFE/SEV instructions to synchronize SMP system
                       so I'm using CLINT to synchronize both HP cores on ESP32-P4.
                  - Core0 will set the software interrupt pending flag in Core1's CLINT 
                      once the runtime environment setup is complete.
          */
         li a5, msip
         lw a0, 0(a5)
         beqz a0, .L_core1
         li a0, 0
         sw a0, 0(a5)
         la sp, __CORE1_STACK_TOP
         jal main
         j .

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .text
.type ExceptionVectorTable, @function
.align 6
.globl ExceptionVectorTable

ExceptionVectorTable:
                      j .

.size ExceptionVectorTable, .-ExceptionVectorTable

/*******************************************************************************************
  \brief  uint32_t osGetActiveCore(void)
  
  \param  void
  
  \return uint32_t : Active Core ID
********************************************************************************************/
.section ".text", "ax"
.align 2
.globl osGetActiveCore
.type  osGetActiveCore, @function


osGetActiveCore:
                  csrr a0, mhartid
                  ret

.size osGetActiveCore, .-osGetActiveCore

/*******************************************************************************************
  \brief  void osHwAcquireSpinLock(uint32* lock)
  
  \param  lock: pointer to the lock variable
  
  \return void
********************************************************************************************/
.section ".text", "ax"
.align 2
.globl osHwAcquireSpinLock
.type  osHwAcquireSpinLock, @function


osHwAcquireSpinLock:  lr.w a1, (a0)
                      bne zero, a1, osHwAcquireSpinLock
                      add a1, zero, 1
                      sc.w t0, a1, (a0)
                      bnez t0, osHwAcquireSpinLock
                      ret

.size osHwAcquireSpinLock, .-osHwAcquireSpinLock

/*******************************************************************************************
  \brief  uint32_t osHwTryToAcquireSpinLock(uint32_t* lock)
  
  \param  lock: pointer to the lock variable
  
  \return uint32_t  0 -> not acquired, 1 -> acquired
********************************************************************************************/
.section ".text", "ax"
.align 2
.globl osHwTryToAcquireSpinLock
.type  osHwTryToAcquireSpinLock, @function


osHwTryToAcquireSpinLock:  
                      lr.w a1, (a0)
                      bne zero, a1, .L_not_acquired
                      add a1, zero, 1
                      sc.w t0, a1, (a0)
                      bnez t0, .L_not_acquired
                      add a0, x0, 1
                      ret
.L_not_acquired:
                     mv a0, x0
                     ret

.size osHwTryToAcquireSpinLock, .-osHwTryToAcquireSpinLock

/*******************************************************************************************
  \brief  void osHwReleaseSpinLock(uint32_t* lock)
  
  \param  lock: pointer to the lock variable
  
  \return void
********************************************************************************************/
.section ".text", "ax"
.align 2
.globl osHwReleaseSpinLock
.type  osHwReleaseSpinLock, @function


osHwReleaseSpinLock: lr.w a1, (a0)
                     add a2, zero, 1
                     bne a2, a1, osHwReleaseSpinLock
                     sc.w t0, zero, (a0)
                     bnez t0, osHwReleaseSpinLock
                     ret

.size osHwReleaseSpinLock, .-osHwReleaseSpinLock

/*
-----------------------------------------------------------------
 Register | ABI Name | Description                      | Saver
-----------------------------------------------------------------
 x0       | zero     | Hard-wired zero                  | -
 x1       | ra       | Return address                   | Caller
 x2       | sp       | Stack pointer                    | Callee
 x3       | gp       | Global pointer                   | -
 x4       | tp       | Thread pointer                   | -
 x5-7     | t0-2     | Temporaries                      | Caller
 x8       | s0/fp    | Saved register/frame pointer     | Callee
 x9       | s1       | Saved register                   | Callee
 x10-11   | a0-1     | Function arguments/return values | Caller
 x12-17   | a2-7     | Function arguments               | Caller
 x18-27   | s2-11    | Saved registers                  | Callee
 x28-31   | t3-6     | Temporaries                      | Caller
 f0-7     | ft0-7    | FP temporaries                   | Caller
 f8-9     | fs0-1    | FP saved registers               | Callee
 f10-11   | fa0-1    | FP arguments/return values       | Caller
 f12-17   | fa2-7    | FP arguments                     | Caller
 f18-27   | fs2-11   | FP saved registers               | Callee
 f28-31   | ft8-11   | FP temporaries                   | Caller
-----------------------------------------------------------------
*/