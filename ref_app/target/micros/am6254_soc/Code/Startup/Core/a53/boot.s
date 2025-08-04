///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from:

// ***************************************************************************************
// Filename    : boot.s
// 
// Core        : ARM Cortex-A53
// 
// Author      : Chalandi Amine
//
// Owner       : Chalandi Amine
// 
// Date        : 16.05.2025
// 
// Description : multicore ARM Cortex-A53 (ARMv8-A) startup code
// 
// ***************************************************************************************

//----------------------------------------------------------------------------------------
/// \brief  _start
///
/// \descr  Multicore boot manager
///
/// \param  void
///
/// \return void
//----------------------------------------------------------------------------------------
.section .boot,"ax"
.type _start, @function
.align 2
.extern vector_table
.globl _start
.globl main_x

_start:
    /* clear all registers */
    mov x0 , #0
    mov x1 , #0
    mov x2 , #0
    mov x3 , #0
    mov x4 , #0
    mov x5 , #0
    mov x6 , #0
    mov x7 , #0
    mov x8 , #0
    mov x9 , #0
    mov x10, #0
    mov x11, #0
    mov x12, #0
    mov x13, #0
    mov x14, #0
    mov x15, #0
    mov x16, #0
    mov x17, #0
    mov x18, #0
    mov x19, #0
    mov x20, #0
    mov x21, #0
    mov x22, #0
    mov x23, #0
    mov x24, #0
    mov x25, #0
    mov x26, #0
    mov x27, #0
    mov x28, #0
    mov x29, #0
    mov x30, #0

    /* Set up secure configuration register (SCR) for EL3 */
    /* mainly to enable FIQ and IRQ to be trapped to EL3 */
    mov x0, #0x66
    msr SCR_EL3, x0

    /* enable FPU */
    mrs x0, CPACR_EL1
    orr x1, x0, #(0x3ul<<20)
    msr CPACR_EL1, x0

    /* Set up ACTLR */
    mov x0, #0x73
    msr ACTLR_EL3, x0

    /* Set up CNTFRQ_EL0 (200 MHz) */
    ldr x0, =0x0BEBC200
    msr CNTFRQ_EL0, x0

    /* Set up CNTVOFF_EL2 */
    msr CNTVOFF_EL2, xzr

    /* Enable FP and SIMD */
    mov x0, #0x33ff
    msr CPTR_EL3, x0

    /* setup the exception table */
    ldr x1, =vector_table
    msr vbar_el3, x1

    /* configure the MMU */
    bl mmu_init

    /* init the thread id register */
    msr tpidr_el3, xzr

    /* check which core is executing this code */
    mrs  x6, mpidr_el1
    and  x6, x6, #3

    /* configure the stack pointer register on all cores and for all exception levels */
    ldr  x10, = _stack_ptrs_lut
    lsl  x11, x6, #5
    add  x10, x10, x11

    ldr x12, [x10, #0]
    ldr x13, [x10, #8]
    ldr x14, [x10, #16]
    ldr x15, [x10, #24]

    msr  SP_EL0, x12
    msr  SP_EL1, x13
    msr  SP_EL2, x14
    mov  sp, x15

    /* jump to each core entry */
    ldr  x10, = _entries_lut
    ldr  x12, [x10, x6, lsl #3]
    cmp  x6, #0
    b.eq  .L_jump_to_entry
    wfe
.L_jump_to_entry:
    br x12
    b .

.size _start, .-_start



.section .rodata
.type _stack_ptrs_lut, @object
.align 3
.globl _stack_ptrs_lut
.globl _stack_ptrs_lut
_stack_ptrs_lut:
    .xword __CORE0_EL0_STACK_TOP
    .xword __CORE0_EL1_STACK_TOP
    .xword __CORE0_EL2_STACK_TOP
    .xword __CORE0_EL3_STACK_TOP
    .xword __CORE1_EL0_STACK_TOP
    .xword __CORE1_EL1_STACK_TOP
    .xword __CORE1_EL2_STACK_TOP
    .xword __CORE1_EL3_STACK_TOP
    .xword __CORE2_EL0_STACK_TOP
    .xword __CORE2_EL1_STACK_TOP
    .xword __CORE2_EL2_STACK_TOP
    .xword __CORE2_EL3_STACK_TOP
    .xword __CORE3_EL0_STACK_TOP
    .xword __CORE3_EL1_STACK_TOP
    .xword __CORE3_EL2_STACK_TOP
    .xword __CORE3_EL3_STACK_TOP
.size _stack_ptrs_lut, .-_stack_ptrs_lut


.section .rodata
.type _entries_lut, @object
.align 3
.globl _entries_lut
_entries_lut:
    .xword Startup_Init
    .xword main_x
    .xword main_x
    .xword main_x

.size _entries_lut, .-_entries_lut

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .text
.type GetActiveCoreId, @function
.align 3
.globl GetActiveCoreId

GetActiveCoreId:
             mrs  x0, mpidr_el1
             and  x0, x0, #15
             ret

.size GetActiveCoreId, .-GetActiveCoreId

/*******************************************************************************************
  \brief    Initializes and enables L1 Data and Instruction Cache in EL3 on Cortex-A53
  \param    None
  \return   None
********************************************************************************************/
.global EnableCaches_A53_EL3
.section .text
.type EnableCaches_A53_EL3, @function

EnableCaches_A53_EL3:

        // Invalidate entire instruction cache to PoU
        ic      iallu
        dsb     sy
        isb

        // Invalidate data cache (optional full clean/inval omitted here)

        // Enable SMP bit in CPUECTLR_EL3 (SMP bit = bit 6)
        mrs     x0, S3_1_C15_C2_1          // CPUECTLR_EL3
        orr     x0, x0, #(1 << 6)          // Set SMP bit for coherency
        msr     S3_1_C15_C2_1, x0
        isb

        // Enable instruction & data caches in SCTLR_EL3
       //mrs     x0, SCTLR_EL3
       //orr     x0, x0, #(1 << 12)         // I: Instruction cache enable
       //orr     x0, x0, #(1 << 2)          // C: Data cache enable
       //msr     SCTLR_EL3, x0
       //isb
        ret

.size EnableCaches_A53_EL3, .-EnableCaches_A53_EL3

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
/* FUNCTION DEF: void CacheP_enableSMP(void) */
        .global CacheP_enableSMP
        .section .text
        .type CacheP_enableSMP, @function

CacheP_enableSMP:
        mrs     x0, s3_1_c15_c2_1           /* Read CPUECTLR_EL1 */
        mov     x1, x0
        and     x1, x1, #0x40
        cmp     x1, #0x40
        beq     smp_enabled
        orr     x0, x0, #0x40
        msr     s3_1_c15_c2_1, x0           /* Enable data coherency with other cores */
        smp_enabled:
        ret

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.macro DCACHE_LINE_SIZE reg0, reg1
        mrs     \reg1, ctr_el0
        ubfm    \reg1, \reg1, #16, #19      /* extract cache line size bits */
        mov     \reg0, #4
        lsl     \reg0, \reg0, \reg1         /* compute cache line size */
.endm

/* FUNCTION DEF: void CacheP_wb(uintptr_t blockPtr, uint32_t byteCnt, uint32_t type) */
        .global CacheP_wb
        .section .text
        .type CacheP_wb, @function

CacheP_wb:
        add     x1, x0, x1               /* calculate last address */
        DCACHE_LINE_SIZE x3, x4
        sub     x4, x3, #1
        bic     x0, x0, x4               /* align blockPtr to cache line */
1:
        dc      cvac, x0                 /* clean single entry in DCache to
                                            PoC */
        add     x0, x0, x3               /* increment address by cache line
                                            size */
        cmp     x0, x1                   /* compare to last address */
        blo     1b                       /* loop if > 0 */
        dsb     sy
        ret

/*******************************************************************************************
  \brief    Clean and Invalidate Data Cache for a memory block
  \param    x0 = blockPtr (start address)
  \param    x1 = byteCnt  (number of bytes to clean + invalidate)
  \return   void
********************************************************************************************/
.global CacheP_cleanInvalidate
.section .text
.type CacheP_cleanInvalidate, @function

CacheP_cleanInvalidate:
        // Save end address: x1 = byteCnt
        add     x1, x0, x1                // x1 = end address

        // Get cache line size into x3
        mrs     x4, ctr_el0               // CTR_EL0 contains cache line size info
        ubfm    x4, x4, #16, #19          // Bits [19:16] = log2(words per cache line)
        mov     x3, #4                    // 4 bytes per word
        lsl     x3, x3, x4                // x3 = cache line size in bytes

        // Align x0 (start address) to cache line boundary
        sub     x4, x3, #1
        bic     x0, x0, x4                // align down

1:      // Clean + Invalidate loop
        dc      civac, x0                 // clean and invalidate D-cache to PoC
        add     x0, x0, x3                // next cache line
        cmp     x0, x1
        blo     1b                        // loop until x0 >= end

        dsb     sy                        // ensure completion
        ret

.size CacheP_cleanInvalidate, .-CacheP_cleanInvalidate


/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .text
.type mmu_init, @function
.align 2
.globl mmu_init

mmu_init:
            /*
            Set MAIR_EL3 with four memory types
            Index 0: Device-nGnRE                      -> 0x00
            Index 1: Normal Non-Cacheable              -> 0x44
            Index 2: Write-back + No Write Allocate    -> 0xAA
            Index 3: Write-back + Write Allocate       -> 0xFF
            Index 4: Write-through + Write Allocate    -> 0xBB
            */
             ldr x0, =0xbbffaa4400
             msr mair_el3, x0
             isb
             /*
             T0SZ  [5:0]   = 0x20 (32 --> 4GB VA space)
             IRGN0 [9:8]   = 0b01 (Inner Write-Back + Write-Allocate)
             ORGN0 [11:10] = 0b01 (Outer Write-Back + Write-Allocate)
             SH0   [13:12] = 0b11 (Inner Shareable)
             TG0   [15:14] = 0b00 (4KB granule)
             */
             mov x0, #0x3520
             msr tcr_el3, x0
             isb

             ldr x0, =mmu_level1_translation_table
             msr ttbr0_el3, x0
             isb

             // Invalidate entire instruction cache to PoU
             ic      iallu
             dsb     sy
             isb

             // Invalidate data cache (optional full clean/inval omitted here)

             // Enable SMP bit in CPUECTLR_EL3 (SMP bit = bit 6)
             mrs     x0, S3_1_C15_C2_1          // CPUECTLR_EL3
             orr     x0, x0, #(1 << 6)          // Set SMP bit for coherency
             msr     S3_1_C15_C2_1, x0
             isb

             mrs x0, sctlr_el3
             orr x0, x0, #(1 << 0)   // M = 1 (Enable MMU)
             orr x0, x0, #(1 << 2)   // C = 1 (Enable data cache)
             orr x0, x0, #(1 << 12)  // I = 1 (Enable instruction cache)
             msr sctlr_el3, x0
             isb
             ret

.size mmu_init, .-mmu_init

.section .rodata
.align 12
.globl mmu_level1_translation_table
mmu_level1_translation_table:
     /*
     Block descriptor format:
     [1:0]   = 0b01        -> Block descriptor
     [4:2]   = AttrIdx<<2  -> MAIR index (AttrIdx)
     [5]     = NS          -> Non-Secure
     [9:8]   = SH          -> Shareability = 0b11 (inner Shareable)
     [10]    = AF          -> Access Flag = 1
     [11]    = nG          -> Not Global = 0 (global)
     [47:30] = Output address (aligned 1GB block)
     [51]    = DBM         -> Dirty bit modifier
     [52]    = Contiguous  -> Translation table contiguous to the previous one for initial lookup
     [53]    = PXN         -> Priviledge eXecute Never
     [54]    = UXN/XN      -> Unpriviledge eXecute Never / eXecute Never
     [63:55] = RAZ
     */
    .xword ((mmu_level2_translation_table_0) + ( (0b1 << 53) | (0b11 << 8) | (1 << 10) | 3)) /* L1 entry pointing to mmu_level2_translation_table_0 */
    .xword ((mmu_level2_translation_table_1) + ( (0b1 << 53) | (0b11 << 8) | (1 << 10) | 3)) /* L1 entry pointing to mmu_level2_translation_table_1 */
    .xword ((mmu_level2_translation_table_2) + ( (0b1 << 53) | (0b11 << 8) | (1 << 10) | 3)) /* L1 entry pointing to mmu_level2_translation_table_2 */
    .xword ((mmu_level2_translation_table_3) + ( (0b1 << 53) | (0b11 << 8) | (1 << 10) | 3)) /* L1 entry pointing to mmu_level2_translation_table_3 */

.size mmu_level1_translation_table, .-mmu_level1_translation_table


.section .rodata
.align 12
.globl mmu_level2_translation_table_0
mmu_level2_translation_table_0:
    .xword (0x00000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x00000000 - 0x001fffff --> PA: 0x00000000 - 0x001fffff */
    .xword (0x00200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x00200000 - 0x003fffff --> PA: 0x00200000 - 0x003fffff */
    .xword (0x00400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x00400000 - 0x005fffff --> PA: 0x00400000 - 0x005fffff */
    .xword (0x00600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x00600000 - 0x007fffff --> PA: 0x00600000 - 0x007fffff */
    .xword (0x00800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x00800000 - 0x009fffff --> PA: 0x00800000 - 0x009fffff */
    .xword (0x00a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x00a00000 - 0x00bfffff --> PA: 0x00a00000 - 0x00bfffff */
    .xword (0x00c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x00c00000 - 0x00dfffff --> PA: 0x00c00000 - 0x00dfffff */
    .xword (0x00e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x00e00000 - 0x00ffffff --> PA: 0x00e00000 - 0x00ffffff */
    .xword (0x01000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x01000000 - 0x011fffff --> PA: 0x01000000 - 0x011fffff */
    .xword (0x01200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x01200000 - 0x013fffff --> PA: 0x01200000 - 0x013fffff */
    .xword (0x01400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x01400000 - 0x015fffff --> PA: 0x01400000 - 0x015fffff */
    .xword (0x01600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x01600000 - 0x017fffff --> PA: 0x01600000 - 0x017fffff */
    .xword (0x01800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x01800000 - 0x019fffff --> PA: 0x01800000 - 0x019fffff */
    .xword (0x01a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x01a00000 - 0x01bfffff --> PA: 0x01a00000 - 0x01bfffff */
    .xword (0x01c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x01c00000 - 0x01dfffff --> PA: 0x01c00000 - 0x01dfffff */
    .xword (0x01e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x01e00000 - 0x01ffffff --> PA: 0x01e00000 - 0x01ffffff */
    .xword (0x02000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x02000000 - 0x021fffff --> PA: 0x02000000 - 0x021fffff */
    .xword (0x02200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x02200000 - 0x023fffff --> PA: 0x02200000 - 0x023fffff */
    .xword (0x02400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x02400000 - 0x025fffff --> PA: 0x02400000 - 0x025fffff */
    .xword (0x02600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x02600000 - 0x027fffff --> PA: 0x02600000 - 0x027fffff */
    .xword (0x02800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x02800000 - 0x029fffff --> PA: 0x02800000 - 0x029fffff */
    .xword (0x02a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x02a00000 - 0x02bfffff --> PA: 0x02a00000 - 0x02bfffff */
    .xword (0x02c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x02c00000 - 0x02dfffff --> PA: 0x02c00000 - 0x02dfffff */
    .xword (0x02e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x02e00000 - 0x02ffffff --> PA: 0x02e00000 - 0x02ffffff */
    .xword (0x03000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x03000000 - 0x031fffff --> PA: 0x03000000 - 0x031fffff */
    .xword (0x03200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x03200000 - 0x033fffff --> PA: 0x03200000 - 0x033fffff */
    .xword (0x03400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x03400000 - 0x035fffff --> PA: 0x03400000 - 0x035fffff */
    .xword (0x03600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x03600000 - 0x037fffff --> PA: 0x03600000 - 0x037fffff */
    .xword (0x03800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x03800000 - 0x039fffff --> PA: 0x03800000 - 0x039fffff */
    .xword (0x03a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x03a00000 - 0x03bfffff --> PA: 0x03a00000 - 0x03bfffff */
    .xword (0x03c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x03c00000 - 0x03dfffff --> PA: 0x03c00000 - 0x03dfffff */
    .xword (0x03e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x03e00000 - 0x03ffffff --> PA: 0x03e00000 - 0x03ffffff */
    .xword (0x04000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x04000000 - 0x041fffff --> PA: 0x04000000 - 0x041fffff */
    .xword (0x04200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x04200000 - 0x043fffff --> PA: 0x04200000 - 0x043fffff */
    .xword (0x04400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x04400000 - 0x045fffff --> PA: 0x04400000 - 0x045fffff */
    .xword (0x04600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x04600000 - 0x047fffff --> PA: 0x04600000 - 0x047fffff */
    .xword (0x04800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x04800000 - 0x049fffff --> PA: 0x04800000 - 0x049fffff */
    .xword (0x04a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x04a00000 - 0x04bfffff --> PA: 0x04a00000 - 0x04bfffff */
    .xword (0x04c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x04c00000 - 0x04dfffff --> PA: 0x04c00000 - 0x04dfffff */
    .xword (0x04e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x04e00000 - 0x04ffffff --> PA: 0x04e00000 - 0x04ffffff */
    .xword (0x05000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x05000000 - 0x051fffff --> PA: 0x05000000 - 0x051fffff */
    .xword (0x05200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x05200000 - 0x053fffff --> PA: 0x05200000 - 0x053fffff */
    .xword (0x05400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x05400000 - 0x055fffff --> PA: 0x05400000 - 0x055fffff */
    .xword (0x05600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x05600000 - 0x057fffff --> PA: 0x05600000 - 0x057fffff */
    .xword (0x05800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x05800000 - 0x059fffff --> PA: 0x05800000 - 0x059fffff */
    .xword (0x05a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x05a00000 - 0x05bfffff --> PA: 0x05a00000 - 0x05bfffff */
    .xword (0x05c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x05c00000 - 0x05dfffff --> PA: 0x05c00000 - 0x05dfffff */
    .xword (0x05e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x05e00000 - 0x05ffffff --> PA: 0x05e00000 - 0x05ffffff */
    .xword (0x06000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x06000000 - 0x061fffff --> PA: 0x06000000 - 0x061fffff */
    .xword (0x06200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x06200000 - 0x063fffff --> PA: 0x06200000 - 0x063fffff */
    .xword (0x06400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x06400000 - 0x065fffff --> PA: 0x06400000 - 0x065fffff */
    .xword (0x06600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x06600000 - 0x067fffff --> PA: 0x06600000 - 0x067fffff */
    .xword (0x06800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x06800000 - 0x069fffff --> PA: 0x06800000 - 0x069fffff */
    .xword (0x06a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x06a00000 - 0x06bfffff --> PA: 0x06a00000 - 0x06bfffff */
    .xword (0x06c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x06c00000 - 0x06dfffff --> PA: 0x06c00000 - 0x06dfffff */
    .xword (0x06e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x06e00000 - 0x06ffffff --> PA: 0x06e00000 - 0x06ffffff */
    .xword (0x07000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x07000000 - 0x071fffff --> PA: 0x07000000 - 0x071fffff */
    .xword (0x07200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x07200000 - 0x073fffff --> PA: 0x07200000 - 0x073fffff */
    .xword (0x07400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x07400000 - 0x075fffff --> PA: 0x07400000 - 0x075fffff */
    .xword (0x07600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x07600000 - 0x077fffff --> PA: 0x07600000 - 0x077fffff */
    .xword (0x07800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x07800000 - 0x079fffff --> PA: 0x07800000 - 0x079fffff */
    .xword (0x07a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x07a00000 - 0x07bfffff --> PA: 0x07a00000 - 0x07bfffff */
    .xword (0x07c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x07c00000 - 0x07dfffff --> PA: 0x07c00000 - 0x07dfffff */
    .xword (0x07e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x07e00000 - 0x07ffffff --> PA: 0x07e00000 - 0x07ffffff */
    .xword (0x08000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x08000000 - 0x081fffff --> PA: 0x08000000 - 0x081fffff */
    .xword (0x08200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x08200000 - 0x083fffff --> PA: 0x08200000 - 0x083fffff */
    .xword (0x08400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x08400000 - 0x085fffff --> PA: 0x08400000 - 0x085fffff */
    .xword (0x08600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x08600000 - 0x087fffff --> PA: 0x08600000 - 0x087fffff */
    .xword (0x08800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x08800000 - 0x089fffff --> PA: 0x08800000 - 0x089fffff */
    .xword (0x08a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x08a00000 - 0x08bfffff --> PA: 0x08a00000 - 0x08bfffff */
    .xword (0x08c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x08c00000 - 0x08dfffff --> PA: 0x08c00000 - 0x08dfffff */
    .xword (0x08e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x08e00000 - 0x08ffffff --> PA: 0x08e00000 - 0x08ffffff */
    .xword (0x09000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x09000000 - 0x091fffff --> PA: 0x09000000 - 0x091fffff */
    .xword (0x09200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x09200000 - 0x093fffff --> PA: 0x09200000 - 0x093fffff */
    .xword (0x09400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x09400000 - 0x095fffff --> PA: 0x09400000 - 0x095fffff */
    .xword (0x09600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x09600000 - 0x097fffff --> PA: 0x09600000 - 0x097fffff */
    .xword (0x09800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x09800000 - 0x099fffff --> PA: 0x09800000 - 0x099fffff */
    .xword (0x09a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x09a00000 - 0x09bfffff --> PA: 0x09a00000 - 0x09bfffff */
    .xword (0x09c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x09c00000 - 0x09dfffff --> PA: 0x09c00000 - 0x09dfffff */
    .xword (0x09e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x09e00000 - 0x09ffffff --> PA: 0x09e00000 - 0x09ffffff */
    .xword (0x0a000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0a000000 - 0x0a1fffff --> PA: 0x0a000000 - 0x0a1fffff */
    .xword (0x0a200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0a200000 - 0x0a3fffff --> PA: 0x0a200000 - 0x0a3fffff */
    .xword (0x0a400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0a400000 - 0x0a5fffff --> PA: 0x0a400000 - 0x0a5fffff */
    .xword (0x0a600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0a600000 - 0x0a7fffff --> PA: 0x0a600000 - 0x0a7fffff */
    .xword (0x0a800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0a800000 - 0x0a9fffff --> PA: 0x0a800000 - 0x0a9fffff */
    .xword (0x0aa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0aa00000 - 0x0abfffff --> PA: 0x0aa00000 - 0x0abfffff */
    .xword (0x0ac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0ac00000 - 0x0adfffff --> PA: 0x0ac00000 - 0x0adfffff */
    .xword (0x0ae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0ae00000 - 0x0affffff --> PA: 0x0ae00000 - 0x0affffff */
    .xword (0x0b000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0b000000 - 0x0b1fffff --> PA: 0x0b000000 - 0x0b1fffff */
    .xword (0x0b200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0b200000 - 0x0b3fffff --> PA: 0x0b200000 - 0x0b3fffff */
    .xword (0x0b400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0b400000 - 0x0b5fffff --> PA: 0x0b400000 - 0x0b5fffff */
    .xword (0x0b600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0b600000 - 0x0b7fffff --> PA: 0x0b600000 - 0x0b7fffff */
    .xword (0x0b800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0b800000 - 0x0b9fffff --> PA: 0x0b800000 - 0x0b9fffff */
    .xword (0x0ba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0ba00000 - 0x0bbfffff --> PA: 0x0ba00000 - 0x0bbfffff */
    .xword (0x0bc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0bc00000 - 0x0bdfffff --> PA: 0x0bc00000 - 0x0bdfffff */
    .xword (0x0be00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0be00000 - 0x0bffffff --> PA: 0x0be00000 - 0x0bffffff */
    .xword (0x0c000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0c000000 - 0x0c1fffff --> PA: 0x0c000000 - 0x0c1fffff */
    .xword (0x0c200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0c200000 - 0x0c3fffff --> PA: 0x0c200000 - 0x0c3fffff */
    .xword (0x0c400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0c400000 - 0x0c5fffff --> PA: 0x0c400000 - 0x0c5fffff */
    .xword (0x0c600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0c600000 - 0x0c7fffff --> PA: 0x0c600000 - 0x0c7fffff */
    .xword (0x0c800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0c800000 - 0x0c9fffff --> PA: 0x0c800000 - 0x0c9fffff */
    .xword (0x0ca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0ca00000 - 0x0cbfffff --> PA: 0x0ca00000 - 0x0cbfffff */
    .xword (0x0cc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0cc00000 - 0x0cdfffff --> PA: 0x0cc00000 - 0x0cdfffff */
    .xword (0x0ce00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0ce00000 - 0x0cffffff --> PA: 0x0ce00000 - 0x0cffffff */
    .xword (0x0d000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0d000000 - 0x0d1fffff --> PA: 0x0d000000 - 0x0d1fffff */
    .xword (0x0d200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0d200000 - 0x0d3fffff --> PA: 0x0d200000 - 0x0d3fffff */
    .xword (0x0d400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0d400000 - 0x0d5fffff --> PA: 0x0d400000 - 0x0d5fffff */
    .xword (0x0d600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0d600000 - 0x0d7fffff --> PA: 0x0d600000 - 0x0d7fffff */
    .xword (0x0d800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0d800000 - 0x0d9fffff --> PA: 0x0d800000 - 0x0d9fffff */
    .xword (0x0da00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0da00000 - 0x0dbfffff --> PA: 0x0da00000 - 0x0dbfffff */
    .xword (0x0dc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0dc00000 - 0x0ddfffff --> PA: 0x0dc00000 - 0x0ddfffff */
    .xword (0x0de00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0de00000 - 0x0dffffff --> PA: 0x0de00000 - 0x0dffffff */
    .xword (0x0e000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0e000000 - 0x0e1fffff --> PA: 0x0e000000 - 0x0e1fffff */
    .xword (0x0e200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0e200000 - 0x0e3fffff --> PA: 0x0e200000 - 0x0e3fffff */
    .xword (0x0e400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0e400000 - 0x0e5fffff --> PA: 0x0e400000 - 0x0e5fffff */
    .xword (0x0e600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0e600000 - 0x0e7fffff --> PA: 0x0e600000 - 0x0e7fffff */
    .xword (0x0e800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0e800000 - 0x0e9fffff --> PA: 0x0e800000 - 0x0e9fffff */
    .xword (0x0ea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0ea00000 - 0x0ebfffff --> PA: 0x0ea00000 - 0x0ebfffff */
    .xword (0x0ec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0ec00000 - 0x0edfffff --> PA: 0x0ec00000 - 0x0edfffff */
    .xword (0x0ee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0ee00000 - 0x0effffff --> PA: 0x0ee00000 - 0x0effffff */
    .xword (0x0f000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0f000000 - 0x0f1fffff --> PA: 0x0f000000 - 0x0f1fffff */
    .xword (0x0f200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0f200000 - 0x0f3fffff --> PA: 0x0f200000 - 0x0f3fffff */
    .xword (0x0f400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0f400000 - 0x0f5fffff --> PA: 0x0f400000 - 0x0f5fffff */
    .xword (0x0f600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0f600000 - 0x0f7fffff --> PA: 0x0f600000 - 0x0f7fffff */
    .xword (0x0f800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0f800000 - 0x0f9fffff --> PA: 0x0f800000 - 0x0f9fffff */
    .xword (0x0fa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0fa00000 - 0x0fbfffff --> PA: 0x0fa00000 - 0x0fbfffff */
    .xword (0x0fc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0fc00000 - 0x0fdfffff --> PA: 0x0fc00000 - 0x0fdfffff */
    .xword (0x0fe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x0fe00000 - 0x0fffffff --> PA: 0x0fe00000 - 0x0fffffff */
    .xword (0x10000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x10000000 - 0x101fffff --> PA: 0x10000000 - 0x101fffff */
    .xword (0x10200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x10200000 - 0x103fffff --> PA: 0x10200000 - 0x103fffff */
    .xword (0x10400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x10400000 - 0x105fffff --> PA: 0x10400000 - 0x105fffff */
    .xword (0x10600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x10600000 - 0x107fffff --> PA: 0x10600000 - 0x107fffff */
    .xword (0x10800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x10800000 - 0x109fffff --> PA: 0x10800000 - 0x109fffff */
    .xword (0x10a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x10a00000 - 0x10bfffff --> PA: 0x10a00000 - 0x10bfffff */
    .xword (0x10c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x10c00000 - 0x10dfffff --> PA: 0x10c00000 - 0x10dfffff */
    .xword (0x10e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x10e00000 - 0x10ffffff --> PA: 0x10e00000 - 0x10ffffff */
    .xword (0x11000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x11000000 - 0x111fffff --> PA: 0x11000000 - 0x111fffff */
    .xword (0x11200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x11200000 - 0x113fffff --> PA: 0x11200000 - 0x113fffff */
    .xword (0x11400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x11400000 - 0x115fffff --> PA: 0x11400000 - 0x115fffff */
    .xword (0x11600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x11600000 - 0x117fffff --> PA: 0x11600000 - 0x117fffff */
    .xword (0x11800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x11800000 - 0x119fffff --> PA: 0x11800000 - 0x119fffff */
    .xword (0x11a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x11a00000 - 0x11bfffff --> PA: 0x11a00000 - 0x11bfffff */
    .xword (0x11c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x11c00000 - 0x11dfffff --> PA: 0x11c00000 - 0x11dfffff */
    .xword (0x11e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x11e00000 - 0x11ffffff --> PA: 0x11e00000 - 0x11ffffff */
    .xword (0x12000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x12000000 - 0x121fffff --> PA: 0x12000000 - 0x121fffff */
    .xword (0x12200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x12200000 - 0x123fffff --> PA: 0x12200000 - 0x123fffff */
    .xword (0x12400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x12400000 - 0x125fffff --> PA: 0x12400000 - 0x125fffff */
    .xword (0x12600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x12600000 - 0x127fffff --> PA: 0x12600000 - 0x127fffff */
    .xword (0x12800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x12800000 - 0x129fffff --> PA: 0x12800000 - 0x129fffff */
    .xword (0x12a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x12a00000 - 0x12bfffff --> PA: 0x12a00000 - 0x12bfffff */
    .xword (0x12c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x12c00000 - 0x12dfffff --> PA: 0x12c00000 - 0x12dfffff */
    .xword (0x12e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x12e00000 - 0x12ffffff --> PA: 0x12e00000 - 0x12ffffff */
    .xword (0x13000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x13000000 - 0x131fffff --> PA: 0x13000000 - 0x131fffff */
    .xword (0x13200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x13200000 - 0x133fffff --> PA: 0x13200000 - 0x133fffff */
    .xword (0x13400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x13400000 - 0x135fffff --> PA: 0x13400000 - 0x135fffff */
    .xword (0x13600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x13600000 - 0x137fffff --> PA: 0x13600000 - 0x137fffff */
    .xword (0x13800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x13800000 - 0x139fffff --> PA: 0x13800000 - 0x139fffff */
    .xword (0x13a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x13a00000 - 0x13bfffff --> PA: 0x13a00000 - 0x13bfffff */
    .xword (0x13c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x13c00000 - 0x13dfffff --> PA: 0x13c00000 - 0x13dfffff */
    .xword (0x13e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x13e00000 - 0x13ffffff --> PA: 0x13e00000 - 0x13ffffff */
    .xword (0x14000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x14000000 - 0x141fffff --> PA: 0x14000000 - 0x141fffff */
    .xword (0x14200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x14200000 - 0x143fffff --> PA: 0x14200000 - 0x143fffff */
    .xword (0x14400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x14400000 - 0x145fffff --> PA: 0x14400000 - 0x145fffff */
    .xword (0x14600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x14600000 - 0x147fffff --> PA: 0x14600000 - 0x147fffff */
    .xword (0x14800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x14800000 - 0x149fffff --> PA: 0x14800000 - 0x149fffff */
    .xword (0x14a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x14a00000 - 0x14bfffff --> PA: 0x14a00000 - 0x14bfffff */
    .xword (0x14c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x14c00000 - 0x14dfffff --> PA: 0x14c00000 - 0x14dfffff */
    .xword (0x14e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x14e00000 - 0x14ffffff --> PA: 0x14e00000 - 0x14ffffff */
    .xword (0x15000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x15000000 - 0x151fffff --> PA: 0x15000000 - 0x151fffff */
    .xword (0x15200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x15200000 - 0x153fffff --> PA: 0x15200000 - 0x153fffff */
    .xword (0x15400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x15400000 - 0x155fffff --> PA: 0x15400000 - 0x155fffff */
    .xword (0x15600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x15600000 - 0x157fffff --> PA: 0x15600000 - 0x157fffff */
    .xword (0x15800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x15800000 - 0x159fffff --> PA: 0x15800000 - 0x159fffff */
    .xword (0x15a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x15a00000 - 0x15bfffff --> PA: 0x15a00000 - 0x15bfffff */
    .xword (0x15c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x15c00000 - 0x15dfffff --> PA: 0x15c00000 - 0x15dfffff */
    .xword (0x15e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x15e00000 - 0x15ffffff --> PA: 0x15e00000 - 0x15ffffff */
    .xword (0x16000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x16000000 - 0x161fffff --> PA: 0x16000000 - 0x161fffff */
    .xword (0x16200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x16200000 - 0x163fffff --> PA: 0x16200000 - 0x163fffff */
    .xword (0x16400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x16400000 - 0x165fffff --> PA: 0x16400000 - 0x165fffff */
    .xword (0x16600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x16600000 - 0x167fffff --> PA: 0x16600000 - 0x167fffff */
    .xword (0x16800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x16800000 - 0x169fffff --> PA: 0x16800000 - 0x169fffff */
    .xword (0x16a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x16a00000 - 0x16bfffff --> PA: 0x16a00000 - 0x16bfffff */
    .xword (0x16c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x16c00000 - 0x16dfffff --> PA: 0x16c00000 - 0x16dfffff */
    .xword (0x16e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x16e00000 - 0x16ffffff --> PA: 0x16e00000 - 0x16ffffff */
    .xword (0x17000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x17000000 - 0x171fffff --> PA: 0x17000000 - 0x171fffff */
    .xword (0x17200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x17200000 - 0x173fffff --> PA: 0x17200000 - 0x173fffff */
    .xword (0x17400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x17400000 - 0x175fffff --> PA: 0x17400000 - 0x175fffff */
    .xword (0x17600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x17600000 - 0x177fffff --> PA: 0x17600000 - 0x177fffff */
    .xword (0x17800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x17800000 - 0x179fffff --> PA: 0x17800000 - 0x179fffff */
    .xword (0x17a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x17a00000 - 0x17bfffff --> PA: 0x17a00000 - 0x17bfffff */
    .xword (0x17c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x17c00000 - 0x17dfffff --> PA: 0x17c00000 - 0x17dfffff */
    .xword (0x17e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x17e00000 - 0x17ffffff --> PA: 0x17e00000 - 0x17ffffff */
    .xword (0x18000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x18000000 - 0x181fffff --> PA: 0x18000000 - 0x181fffff */
    .xword (0x18200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x18200000 - 0x183fffff --> PA: 0x18200000 - 0x183fffff */
    .xword (0x18400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x18400000 - 0x185fffff --> PA: 0x18400000 - 0x185fffff */
    .xword (0x18600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x18600000 - 0x187fffff --> PA: 0x18600000 - 0x187fffff */
    .xword (0x18800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x18800000 - 0x189fffff --> PA: 0x18800000 - 0x189fffff */
    .xword (0x18a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x18a00000 - 0x18bfffff --> PA: 0x18a00000 - 0x18bfffff */
    .xword (0x18c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x18c00000 - 0x18dfffff --> PA: 0x18c00000 - 0x18dfffff */
    .xword (0x18e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x18e00000 - 0x18ffffff --> PA: 0x18e00000 - 0x18ffffff */
    .xword (0x19000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x19000000 - 0x191fffff --> PA: 0x19000000 - 0x191fffff */
    .xword (0x19200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x19200000 - 0x193fffff --> PA: 0x19200000 - 0x193fffff */
    .xword (0x19400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x19400000 - 0x195fffff --> PA: 0x19400000 - 0x195fffff */
    .xword (0x19600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x19600000 - 0x197fffff --> PA: 0x19600000 - 0x197fffff */
    .xword (0x19800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x19800000 - 0x199fffff --> PA: 0x19800000 - 0x199fffff */
    .xword (0x19a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x19a00000 - 0x19bfffff --> PA: 0x19a00000 - 0x19bfffff */
    .xword (0x19c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x19c00000 - 0x19dfffff --> PA: 0x19c00000 - 0x19dfffff */
    .xword (0x19e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x19e00000 - 0x19ffffff --> PA: 0x19e00000 - 0x19ffffff */
    .xword (0x1a000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1a000000 - 0x1a1fffff --> PA: 0x1a000000 - 0x1a1fffff */
    .xword (0x1a200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1a200000 - 0x1a3fffff --> PA: 0x1a200000 - 0x1a3fffff */
    .xword (0x1a400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1a400000 - 0x1a5fffff --> PA: 0x1a400000 - 0x1a5fffff */
    .xword (0x1a600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1a600000 - 0x1a7fffff --> PA: 0x1a600000 - 0x1a7fffff */
    .xword (0x1a800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1a800000 - 0x1a9fffff --> PA: 0x1a800000 - 0x1a9fffff */
    .xword (0x1aa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1aa00000 - 0x1abfffff --> PA: 0x1aa00000 - 0x1abfffff */
    .xword (0x1ac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1ac00000 - 0x1adfffff --> PA: 0x1ac00000 - 0x1adfffff */
    .xword (0x1ae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1ae00000 - 0x1affffff --> PA: 0x1ae00000 - 0x1affffff */
    .xword (0x1b000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1b000000 - 0x1b1fffff --> PA: 0x1b000000 - 0x1b1fffff */
    .xword (0x1b200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1b200000 - 0x1b3fffff --> PA: 0x1b200000 - 0x1b3fffff */
    .xword (0x1b400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1b400000 - 0x1b5fffff --> PA: 0x1b400000 - 0x1b5fffff */
    .xword (0x1b600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1b600000 - 0x1b7fffff --> PA: 0x1b600000 - 0x1b7fffff */
    .xword (0x1b800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1b800000 - 0x1b9fffff --> PA: 0x1b800000 - 0x1b9fffff */
    .xword (0x1ba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1ba00000 - 0x1bbfffff --> PA: 0x1ba00000 - 0x1bbfffff */
    .xword (0x1bc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1bc00000 - 0x1bdfffff --> PA: 0x1bc00000 - 0x1bdfffff */
    .xword (0x1be00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1be00000 - 0x1bffffff --> PA: 0x1be00000 - 0x1bffffff */
    .xword (0x1c000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1c000000 - 0x1c1fffff --> PA: 0x1c000000 - 0x1c1fffff */
    .xword (0x1c200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1c200000 - 0x1c3fffff --> PA: 0x1c200000 - 0x1c3fffff */
    .xword (0x1c400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1c400000 - 0x1c5fffff --> PA: 0x1c400000 - 0x1c5fffff */
    .xword (0x1c600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1c600000 - 0x1c7fffff --> PA: 0x1c600000 - 0x1c7fffff */
    .xword (0x1c800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1c800000 - 0x1c9fffff --> PA: 0x1c800000 - 0x1c9fffff */
    .xword (0x1ca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1ca00000 - 0x1cbfffff --> PA: 0x1ca00000 - 0x1cbfffff */
    .xword (0x1cc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1cc00000 - 0x1cdfffff --> PA: 0x1cc00000 - 0x1cdfffff */
    .xword (0x1ce00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1ce00000 - 0x1cffffff --> PA: 0x1ce00000 - 0x1cffffff */
    .xword (0x1d000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1d000000 - 0x1d1fffff --> PA: 0x1d000000 - 0x1d1fffff */
    .xword (0x1d200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1d200000 - 0x1d3fffff --> PA: 0x1d200000 - 0x1d3fffff */
    .xword (0x1d400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1d400000 - 0x1d5fffff --> PA: 0x1d400000 - 0x1d5fffff */
    .xword (0x1d600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1d600000 - 0x1d7fffff --> PA: 0x1d600000 - 0x1d7fffff */
    .xword (0x1d800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1d800000 - 0x1d9fffff --> PA: 0x1d800000 - 0x1d9fffff */
    .xword (0x1da00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1da00000 - 0x1dbfffff --> PA: 0x1da00000 - 0x1dbfffff */
    .xword (0x1dc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1dc00000 - 0x1ddfffff --> PA: 0x1dc00000 - 0x1ddfffff */
    .xword (0x1de00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1de00000 - 0x1dffffff --> PA: 0x1de00000 - 0x1dffffff */
    .xword (0x1e000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1e000000 - 0x1e1fffff --> PA: 0x1e000000 - 0x1e1fffff */
    .xword (0x1e200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1e200000 - 0x1e3fffff --> PA: 0x1e200000 - 0x1e3fffff */
    .xword (0x1e400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1e400000 - 0x1e5fffff --> PA: 0x1e400000 - 0x1e5fffff */
    .xword (0x1e600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1e600000 - 0x1e7fffff --> PA: 0x1e600000 - 0x1e7fffff */
    .xword (0x1e800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1e800000 - 0x1e9fffff --> PA: 0x1e800000 - 0x1e9fffff */
    .xword (0x1ea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1ea00000 - 0x1ebfffff --> PA: 0x1ea00000 - 0x1ebfffff */
    .xword (0x1ec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1ec00000 - 0x1edfffff --> PA: 0x1ec00000 - 0x1edfffff */
    .xword (0x1ee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1ee00000 - 0x1effffff --> PA: 0x1ee00000 - 0x1effffff */
    .xword (0x1f000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1f000000 - 0x1f1fffff --> PA: 0x1f000000 - 0x1f1fffff */
    .xword (0x1f200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1f200000 - 0x1f3fffff --> PA: 0x1f200000 - 0x1f3fffff */
    .xword (0x1f400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1f400000 - 0x1f5fffff --> PA: 0x1f400000 - 0x1f5fffff */
    .xword (0x1f600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1f600000 - 0x1f7fffff --> PA: 0x1f600000 - 0x1f7fffff */
    .xword (0x1f800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1f800000 - 0x1f9fffff --> PA: 0x1f800000 - 0x1f9fffff */
    .xword (0x1fa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1fa00000 - 0x1fbfffff --> PA: 0x1fa00000 - 0x1fbfffff */
    .xword (0x1fc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1fc00000 - 0x1fdfffff --> PA: 0x1fc00000 - 0x1fdfffff */
    .xword (0x1fe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x1fe00000 - 0x1fffffff --> PA: 0x1fe00000 - 0x1fffffff */
    .xword (0x20000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x20000000 - 0x201fffff --> PA: 0x20000000 - 0x201fffff */
    .xword (0x20200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x20200000 - 0x203fffff --> PA: 0x20200000 - 0x203fffff */
    .xword (0x20400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x20400000 - 0x205fffff --> PA: 0x20400000 - 0x205fffff */
    .xword (0x20600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x20600000 - 0x207fffff --> PA: 0x20600000 - 0x207fffff */
    .xword (0x20800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x20800000 - 0x209fffff --> PA: 0x20800000 - 0x209fffff */
    .xword (0x20a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x20a00000 - 0x20bfffff --> PA: 0x20a00000 - 0x20bfffff */
    .xword (0x20c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x20c00000 - 0x20dfffff --> PA: 0x20c00000 - 0x20dfffff */
    .xword (0x20e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x20e00000 - 0x20ffffff --> PA: 0x20e00000 - 0x20ffffff */
    .xword (0x21000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x21000000 - 0x211fffff --> PA: 0x21000000 - 0x211fffff */
    .xword (0x21200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x21200000 - 0x213fffff --> PA: 0x21200000 - 0x213fffff */
    .xword (0x21400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x21400000 - 0x215fffff --> PA: 0x21400000 - 0x215fffff */
    .xword (0x21600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x21600000 - 0x217fffff --> PA: 0x21600000 - 0x217fffff */
    .xword (0x21800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x21800000 - 0x219fffff --> PA: 0x21800000 - 0x219fffff */
    .xword (0x21a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x21a00000 - 0x21bfffff --> PA: 0x21a00000 - 0x21bfffff */
    .xword (0x21c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x21c00000 - 0x21dfffff --> PA: 0x21c00000 - 0x21dfffff */
    .xword (0x21e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x21e00000 - 0x21ffffff --> PA: 0x21e00000 - 0x21ffffff */
    .xword (0x22000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x22000000 - 0x221fffff --> PA: 0x22000000 - 0x221fffff */
    .xword (0x22200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x22200000 - 0x223fffff --> PA: 0x22200000 - 0x223fffff */
    .xword (0x22400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x22400000 - 0x225fffff --> PA: 0x22400000 - 0x225fffff */
    .xword (0x22600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x22600000 - 0x227fffff --> PA: 0x22600000 - 0x227fffff */
    .xword (0x22800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x22800000 - 0x229fffff --> PA: 0x22800000 - 0x229fffff */
    .xword (0x22a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x22a00000 - 0x22bfffff --> PA: 0x22a00000 - 0x22bfffff */
    .xword (0x22c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x22c00000 - 0x22dfffff --> PA: 0x22c00000 - 0x22dfffff */
    .xword (0x22e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x22e00000 - 0x22ffffff --> PA: 0x22e00000 - 0x22ffffff */
    .xword (0x23000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x23000000 - 0x231fffff --> PA: 0x23000000 - 0x231fffff */
    .xword (0x23200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x23200000 - 0x233fffff --> PA: 0x23200000 - 0x233fffff */
    .xword (0x23400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x23400000 - 0x235fffff --> PA: 0x23400000 - 0x235fffff */
    .xword (0x23600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x23600000 - 0x237fffff --> PA: 0x23600000 - 0x237fffff */
    .xword (0x23800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x23800000 - 0x239fffff --> PA: 0x23800000 - 0x239fffff */
    .xword (0x23a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x23a00000 - 0x23bfffff --> PA: 0x23a00000 - 0x23bfffff */
    .xword (0x23c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x23c00000 - 0x23dfffff --> PA: 0x23c00000 - 0x23dfffff */
    .xword (0x23e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x23e00000 - 0x23ffffff --> PA: 0x23e00000 - 0x23ffffff */
    .xword (0x24000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x24000000 - 0x241fffff --> PA: 0x24000000 - 0x241fffff */
    .xword (0x24200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x24200000 - 0x243fffff --> PA: 0x24200000 - 0x243fffff */
    .xword (0x24400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x24400000 - 0x245fffff --> PA: 0x24400000 - 0x245fffff */
    .xword (0x24600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x24600000 - 0x247fffff --> PA: 0x24600000 - 0x247fffff */
    .xword (0x24800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x24800000 - 0x249fffff --> PA: 0x24800000 - 0x249fffff */
    .xword (0x24a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x24a00000 - 0x24bfffff --> PA: 0x24a00000 - 0x24bfffff */
    .xword (0x24c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x24c00000 - 0x24dfffff --> PA: 0x24c00000 - 0x24dfffff */
    .xword (0x24e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x24e00000 - 0x24ffffff --> PA: 0x24e00000 - 0x24ffffff */
    .xword (0x25000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x25000000 - 0x251fffff --> PA: 0x25000000 - 0x251fffff */
    .xword (0x25200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x25200000 - 0x253fffff --> PA: 0x25200000 - 0x253fffff */
    .xword (0x25400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x25400000 - 0x255fffff --> PA: 0x25400000 - 0x255fffff */
    .xword (0x25600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x25600000 - 0x257fffff --> PA: 0x25600000 - 0x257fffff */
    .xword (0x25800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x25800000 - 0x259fffff --> PA: 0x25800000 - 0x259fffff */
    .xword (0x25a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x25a00000 - 0x25bfffff --> PA: 0x25a00000 - 0x25bfffff */
    .xword (0x25c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x25c00000 - 0x25dfffff --> PA: 0x25c00000 - 0x25dfffff */
    .xword (0x25e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x25e00000 - 0x25ffffff --> PA: 0x25e00000 - 0x25ffffff */
    .xword (0x26000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x26000000 - 0x261fffff --> PA: 0x26000000 - 0x261fffff */
    .xword (0x26200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x26200000 - 0x263fffff --> PA: 0x26200000 - 0x263fffff */
    .xword (0x26400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x26400000 - 0x265fffff --> PA: 0x26400000 - 0x265fffff */
    .xword (0x26600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x26600000 - 0x267fffff --> PA: 0x26600000 - 0x267fffff */
    .xword (0x26800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x26800000 - 0x269fffff --> PA: 0x26800000 - 0x269fffff */
    .xword (0x26a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x26a00000 - 0x26bfffff --> PA: 0x26a00000 - 0x26bfffff */
    .xword (0x26c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x26c00000 - 0x26dfffff --> PA: 0x26c00000 - 0x26dfffff */
    .xword (0x26e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x26e00000 - 0x26ffffff --> PA: 0x26e00000 - 0x26ffffff */
    .xword (0x27000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x27000000 - 0x271fffff --> PA: 0x27000000 - 0x271fffff */
    .xword (0x27200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x27200000 - 0x273fffff --> PA: 0x27200000 - 0x273fffff */
    .xword (0x27400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x27400000 - 0x275fffff --> PA: 0x27400000 - 0x275fffff */
    .xword (0x27600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x27600000 - 0x277fffff --> PA: 0x27600000 - 0x277fffff */
    .xword (0x27800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x27800000 - 0x279fffff --> PA: 0x27800000 - 0x279fffff */
    .xword (0x27a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x27a00000 - 0x27bfffff --> PA: 0x27a00000 - 0x27bfffff */
    .xword (0x27c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x27c00000 - 0x27dfffff --> PA: 0x27c00000 - 0x27dfffff */
    .xword (0x27e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x27e00000 - 0x27ffffff --> PA: 0x27e00000 - 0x27ffffff */
    .xword (0x28000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x28000000 - 0x281fffff --> PA: 0x28000000 - 0x281fffff */
    .xword (0x28200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x28200000 - 0x283fffff --> PA: 0x28200000 - 0x283fffff */
    .xword (0x28400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x28400000 - 0x285fffff --> PA: 0x28400000 - 0x285fffff */
    .xword (0x28600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x28600000 - 0x287fffff --> PA: 0x28600000 - 0x287fffff */
    .xword (0x28800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x28800000 - 0x289fffff --> PA: 0x28800000 - 0x289fffff */
    .xword (0x28a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x28a00000 - 0x28bfffff --> PA: 0x28a00000 - 0x28bfffff */
    .xword (0x28c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x28c00000 - 0x28dfffff --> PA: 0x28c00000 - 0x28dfffff */
    .xword (0x28e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x28e00000 - 0x28ffffff --> PA: 0x28e00000 - 0x28ffffff */
    .xword (0x29000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x29000000 - 0x291fffff --> PA: 0x29000000 - 0x291fffff */
    .xword (0x29200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x29200000 - 0x293fffff --> PA: 0x29200000 - 0x293fffff */
    .xword (0x29400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x29400000 - 0x295fffff --> PA: 0x29400000 - 0x295fffff */
    .xword (0x29600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x29600000 - 0x297fffff --> PA: 0x29600000 - 0x297fffff */
    .xword (0x29800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x29800000 - 0x299fffff --> PA: 0x29800000 - 0x299fffff */
    .xword (0x29a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x29a00000 - 0x29bfffff --> PA: 0x29a00000 - 0x29bfffff */
    .xword (0x29c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x29c00000 - 0x29dfffff --> PA: 0x29c00000 - 0x29dfffff */
    .xword (0x29e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x29e00000 - 0x29ffffff --> PA: 0x29e00000 - 0x29ffffff */
    .xword (0x2a000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2a000000 - 0x2a1fffff --> PA: 0x2a000000 - 0x2a1fffff */
    .xword (0x2a200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2a200000 - 0x2a3fffff --> PA: 0x2a200000 - 0x2a3fffff */
    .xword (0x2a400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2a400000 - 0x2a5fffff --> PA: 0x2a400000 - 0x2a5fffff */
    .xword (0x2a600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2a600000 - 0x2a7fffff --> PA: 0x2a600000 - 0x2a7fffff */
    .xword (0x2a800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2a800000 - 0x2a9fffff --> PA: 0x2a800000 - 0x2a9fffff */
    .xword (0x2aa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2aa00000 - 0x2abfffff --> PA: 0x2aa00000 - 0x2abfffff */
    .xword (0x2ac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2ac00000 - 0x2adfffff --> PA: 0x2ac00000 - 0x2adfffff */
    .xword (0x2ae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2ae00000 - 0x2affffff --> PA: 0x2ae00000 - 0x2affffff */
    .xword (0x2b000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2b000000 - 0x2b1fffff --> PA: 0x2b000000 - 0x2b1fffff */
    .xword (0x2b200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2b200000 - 0x2b3fffff --> PA: 0x2b200000 - 0x2b3fffff */
    .xword (0x2b400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2b400000 - 0x2b5fffff --> PA: 0x2b400000 - 0x2b5fffff */
    .xword (0x2b600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2b600000 - 0x2b7fffff --> PA: 0x2b600000 - 0x2b7fffff */
    .xword (0x2b800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2b800000 - 0x2b9fffff --> PA: 0x2b800000 - 0x2b9fffff */
    .xword (0x2ba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2ba00000 - 0x2bbfffff --> PA: 0x2ba00000 - 0x2bbfffff */
    .xword (0x2bc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2bc00000 - 0x2bdfffff --> PA: 0x2bc00000 - 0x2bdfffff */
    .xword (0x2be00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2be00000 - 0x2bffffff --> PA: 0x2be00000 - 0x2bffffff */
    .xword (0x2c000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2c000000 - 0x2c1fffff --> PA: 0x2c000000 - 0x2c1fffff */
    .xword (0x2c200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2c200000 - 0x2c3fffff --> PA: 0x2c200000 - 0x2c3fffff */
    .xword (0x2c400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2c400000 - 0x2c5fffff --> PA: 0x2c400000 - 0x2c5fffff */
    .xword (0x2c600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2c600000 - 0x2c7fffff --> PA: 0x2c600000 - 0x2c7fffff */
    .xword (0x2c800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2c800000 - 0x2c9fffff --> PA: 0x2c800000 - 0x2c9fffff */
    .xword (0x2ca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2ca00000 - 0x2cbfffff --> PA: 0x2ca00000 - 0x2cbfffff */
    .xword (0x2cc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2cc00000 - 0x2cdfffff --> PA: 0x2cc00000 - 0x2cdfffff */
    .xword (0x2ce00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2ce00000 - 0x2cffffff --> PA: 0x2ce00000 - 0x2cffffff */
    .xword (0x2d000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2d000000 - 0x2d1fffff --> PA: 0x2d000000 - 0x2d1fffff */
    .xword (0x2d200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2d200000 - 0x2d3fffff --> PA: 0x2d200000 - 0x2d3fffff */
    .xword (0x2d400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2d400000 - 0x2d5fffff --> PA: 0x2d400000 - 0x2d5fffff */
    .xword (0x2d600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2d600000 - 0x2d7fffff --> PA: 0x2d600000 - 0x2d7fffff */
    .xword (0x2d800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2d800000 - 0x2d9fffff --> PA: 0x2d800000 - 0x2d9fffff */
    .xword (0x2da00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2da00000 - 0x2dbfffff --> PA: 0x2da00000 - 0x2dbfffff */
    .xword (0x2dc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2dc00000 - 0x2ddfffff --> PA: 0x2dc00000 - 0x2ddfffff */
    .xword (0x2de00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2de00000 - 0x2dffffff --> PA: 0x2de00000 - 0x2dffffff */
    .xword (0x2e000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2e000000 - 0x2e1fffff --> PA: 0x2e000000 - 0x2e1fffff */
    .xword (0x2e200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2e200000 - 0x2e3fffff --> PA: 0x2e200000 - 0x2e3fffff */
    .xword (0x2e400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2e400000 - 0x2e5fffff --> PA: 0x2e400000 - 0x2e5fffff */
    .xword (0x2e600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2e600000 - 0x2e7fffff --> PA: 0x2e600000 - 0x2e7fffff */
    .xword (0x2e800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2e800000 - 0x2e9fffff --> PA: 0x2e800000 - 0x2e9fffff */
    .xword (0x2ea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2ea00000 - 0x2ebfffff --> PA: 0x2ea00000 - 0x2ebfffff */
    .xword (0x2ec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2ec00000 - 0x2edfffff --> PA: 0x2ec00000 - 0x2edfffff */
    .xword (0x2ee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2ee00000 - 0x2effffff --> PA: 0x2ee00000 - 0x2effffff */
    .xword (0x2f000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2f000000 - 0x2f1fffff --> PA: 0x2f000000 - 0x2f1fffff */
    .xword (0x2f200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2f200000 - 0x2f3fffff --> PA: 0x2f200000 - 0x2f3fffff */
    .xword (0x2f400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2f400000 - 0x2f5fffff --> PA: 0x2f400000 - 0x2f5fffff */
    .xword (0x2f600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2f600000 - 0x2f7fffff --> PA: 0x2f600000 - 0x2f7fffff */
    .xword (0x2f800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2f800000 - 0x2f9fffff --> PA: 0x2f800000 - 0x2f9fffff */
    .xword (0x2fa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2fa00000 - 0x2fbfffff --> PA: 0x2fa00000 - 0x2fbfffff */
    .xword (0x2fc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2fc00000 - 0x2fdfffff --> PA: 0x2fc00000 - 0x2fdfffff */
    .xword (0x2fe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x2fe00000 - 0x2fffffff --> PA: 0x2fe00000 - 0x2fffffff */
    .xword (0x30000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x30000000 - 0x301fffff --> PA: 0x30000000 - 0x301fffff */
    .xword (0x30200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x30200000 - 0x303fffff --> PA: 0x30200000 - 0x303fffff */
    .xword (0x30400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x30400000 - 0x305fffff --> PA: 0x30400000 - 0x305fffff */
    .xword (0x30600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x30600000 - 0x307fffff --> PA: 0x30600000 - 0x307fffff */
    .xword (0x30800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x30800000 - 0x309fffff --> PA: 0x30800000 - 0x309fffff */
    .xword (0x30a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x30a00000 - 0x30bfffff --> PA: 0x30a00000 - 0x30bfffff */
    .xword (0x30c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x30c00000 - 0x30dfffff --> PA: 0x30c00000 - 0x30dfffff */
    .xword (0x30e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x30e00000 - 0x30ffffff --> PA: 0x30e00000 - 0x30ffffff */
    .xword (0x31000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x31000000 - 0x311fffff --> PA: 0x31000000 - 0x311fffff */
    .xword (0x31200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x31200000 - 0x313fffff --> PA: 0x31200000 - 0x313fffff */
    .xword (0x31400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x31400000 - 0x315fffff --> PA: 0x31400000 - 0x315fffff */
    .xword (0x31600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x31600000 - 0x317fffff --> PA: 0x31600000 - 0x317fffff */
    .xword (0x31800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x31800000 - 0x319fffff --> PA: 0x31800000 - 0x319fffff */
    .xword (0x31a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x31a00000 - 0x31bfffff --> PA: 0x31a00000 - 0x31bfffff */
    .xword (0x31c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x31c00000 - 0x31dfffff --> PA: 0x31c00000 - 0x31dfffff */
    .xword (0x31e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x31e00000 - 0x31ffffff --> PA: 0x31e00000 - 0x31ffffff */
    .xword (0x32000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x32000000 - 0x321fffff --> PA: 0x32000000 - 0x321fffff */
    .xword (0x32200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x32200000 - 0x323fffff --> PA: 0x32200000 - 0x323fffff */
    .xword (0x32400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x32400000 - 0x325fffff --> PA: 0x32400000 - 0x325fffff */
    .xword (0x32600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x32600000 - 0x327fffff --> PA: 0x32600000 - 0x327fffff */
    .xword (0x32800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x32800000 - 0x329fffff --> PA: 0x32800000 - 0x329fffff */
    .xword (0x32a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x32a00000 - 0x32bfffff --> PA: 0x32a00000 - 0x32bfffff */
    .xword (0x32c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x32c00000 - 0x32dfffff --> PA: 0x32c00000 - 0x32dfffff */
    .xword (0x32e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x32e00000 - 0x32ffffff --> PA: 0x32e00000 - 0x32ffffff */
    .xword (0x33000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x33000000 - 0x331fffff --> PA: 0x33000000 - 0x331fffff */
    .xword (0x33200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x33200000 - 0x333fffff --> PA: 0x33200000 - 0x333fffff */
    .xword (0x33400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x33400000 - 0x335fffff --> PA: 0x33400000 - 0x335fffff */
    .xword (0x33600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x33600000 - 0x337fffff --> PA: 0x33600000 - 0x337fffff */
    .xword (0x33800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x33800000 - 0x339fffff --> PA: 0x33800000 - 0x339fffff */
    .xword (0x33a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x33a00000 - 0x33bfffff --> PA: 0x33a00000 - 0x33bfffff */
    .xword (0x33c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x33c00000 - 0x33dfffff --> PA: 0x33c00000 - 0x33dfffff */
    .xword (0x33e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x33e00000 - 0x33ffffff --> PA: 0x33e00000 - 0x33ffffff */
    .xword (0x34000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x34000000 - 0x341fffff --> PA: 0x34000000 - 0x341fffff */
    .xword (0x34200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x34200000 - 0x343fffff --> PA: 0x34200000 - 0x343fffff */
    .xword (0x34400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x34400000 - 0x345fffff --> PA: 0x34400000 - 0x345fffff */
    .xword (0x34600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x34600000 - 0x347fffff --> PA: 0x34600000 - 0x347fffff */
    .xword (0x34800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x34800000 - 0x349fffff --> PA: 0x34800000 - 0x349fffff */
    .xword (0x34a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x34a00000 - 0x34bfffff --> PA: 0x34a00000 - 0x34bfffff */
    .xword (0x34c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x34c00000 - 0x34dfffff --> PA: 0x34c00000 - 0x34dfffff */
    .xword (0x34e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x34e00000 - 0x34ffffff --> PA: 0x34e00000 - 0x34ffffff */
    .xword (0x35000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x35000000 - 0x351fffff --> PA: 0x35000000 - 0x351fffff */
    .xword (0x35200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x35200000 - 0x353fffff --> PA: 0x35200000 - 0x353fffff */
    .xword (0x35400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x35400000 - 0x355fffff --> PA: 0x35400000 - 0x355fffff */
    .xword (0x35600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x35600000 - 0x357fffff --> PA: 0x35600000 - 0x357fffff */
    .xword (0x35800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x35800000 - 0x359fffff --> PA: 0x35800000 - 0x359fffff */
    .xword (0x35a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x35a00000 - 0x35bfffff --> PA: 0x35a00000 - 0x35bfffff */
    .xword (0x35c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x35c00000 - 0x35dfffff --> PA: 0x35c00000 - 0x35dfffff */
    .xword (0x35e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x35e00000 - 0x35ffffff --> PA: 0x35e00000 - 0x35ffffff */
    .xword (0x36000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x36000000 - 0x361fffff --> PA: 0x36000000 - 0x361fffff */
    .xword (0x36200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x36200000 - 0x363fffff --> PA: 0x36200000 - 0x363fffff */
    .xword (0x36400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x36400000 - 0x365fffff --> PA: 0x36400000 - 0x365fffff */
    .xword (0x36600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x36600000 - 0x367fffff --> PA: 0x36600000 - 0x367fffff */
    .xword (0x36800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x36800000 - 0x369fffff --> PA: 0x36800000 - 0x369fffff */
    .xword (0x36a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x36a00000 - 0x36bfffff --> PA: 0x36a00000 - 0x36bfffff */
    .xword (0x36c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x36c00000 - 0x36dfffff --> PA: 0x36c00000 - 0x36dfffff */
    .xword (0x36e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x36e00000 - 0x36ffffff --> PA: 0x36e00000 - 0x36ffffff */
    .xword (0x37000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x37000000 - 0x371fffff --> PA: 0x37000000 - 0x371fffff */
    .xword (0x37200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x37200000 - 0x373fffff --> PA: 0x37200000 - 0x373fffff */
    .xword (0x37400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x37400000 - 0x375fffff --> PA: 0x37400000 - 0x375fffff */
    .xword (0x37600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x37600000 - 0x377fffff --> PA: 0x37600000 - 0x377fffff */
    .xword (0x37800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x37800000 - 0x379fffff --> PA: 0x37800000 - 0x379fffff */
    .xword (0x37a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x37a00000 - 0x37bfffff --> PA: 0x37a00000 - 0x37bfffff */
    .xword (0x37c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x37c00000 - 0x37dfffff --> PA: 0x37c00000 - 0x37dfffff */
    .xword (0x37e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x37e00000 - 0x37ffffff --> PA: 0x37e00000 - 0x37ffffff */
    .xword (0x38000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x38000000 - 0x381fffff --> PA: 0x38000000 - 0x381fffff */
    .xword (0x38200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x38200000 - 0x383fffff --> PA: 0x38200000 - 0x383fffff */
    .xword (0x38400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x38400000 - 0x385fffff --> PA: 0x38400000 - 0x385fffff */
    .xword (0x38600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x38600000 - 0x387fffff --> PA: 0x38600000 - 0x387fffff */
    .xword (0x38800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x38800000 - 0x389fffff --> PA: 0x38800000 - 0x389fffff */
    .xword (0x38a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x38a00000 - 0x38bfffff --> PA: 0x38a00000 - 0x38bfffff */
    .xword (0x38c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x38c00000 - 0x38dfffff --> PA: 0x38c00000 - 0x38dfffff */
    .xword (0x38e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x38e00000 - 0x38ffffff --> PA: 0x38e00000 - 0x38ffffff */
    .xword (0x39000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x39000000 - 0x391fffff --> PA: 0x39000000 - 0x391fffff */
    .xword (0x39200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x39200000 - 0x393fffff --> PA: 0x39200000 - 0x393fffff */
    .xword (0x39400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x39400000 - 0x395fffff --> PA: 0x39400000 - 0x395fffff */
    .xword (0x39600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x39600000 - 0x397fffff --> PA: 0x39600000 - 0x397fffff */
    .xword (0x39800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x39800000 - 0x399fffff --> PA: 0x39800000 - 0x399fffff */
    .xword (0x39a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x39a00000 - 0x39bfffff --> PA: 0x39a00000 - 0x39bfffff */
    .xword (0x39c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x39c00000 - 0x39dfffff --> PA: 0x39c00000 - 0x39dfffff */
    .xword (0x39e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x39e00000 - 0x39ffffff --> PA: 0x39e00000 - 0x39ffffff */
    .xword (0x3a000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3a000000 - 0x3a1fffff --> PA: 0x3a000000 - 0x3a1fffff */
    .xword (0x3a200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3a200000 - 0x3a3fffff --> PA: 0x3a200000 - 0x3a3fffff */
    .xword (0x3a400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3a400000 - 0x3a5fffff --> PA: 0x3a400000 - 0x3a5fffff */
    .xword (0x3a600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3a600000 - 0x3a7fffff --> PA: 0x3a600000 - 0x3a7fffff */
    .xword (0x3a800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3a800000 - 0x3a9fffff --> PA: 0x3a800000 - 0x3a9fffff */
    .xword (0x3aa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3aa00000 - 0x3abfffff --> PA: 0x3aa00000 - 0x3abfffff */
    .xword (0x3ac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3ac00000 - 0x3adfffff --> PA: 0x3ac00000 - 0x3adfffff */
    .xword (0x3ae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3ae00000 - 0x3affffff --> PA: 0x3ae00000 - 0x3affffff */
    .xword (0x3b000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3b000000 - 0x3b1fffff --> PA: 0x3b000000 - 0x3b1fffff */
    .xword (0x3b200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3b200000 - 0x3b3fffff --> PA: 0x3b200000 - 0x3b3fffff */
    .xword (0x3b400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3b400000 - 0x3b5fffff --> PA: 0x3b400000 - 0x3b5fffff */
    .xword (0x3b600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3b600000 - 0x3b7fffff --> PA: 0x3b600000 - 0x3b7fffff */
    .xword (0x3b800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3b800000 - 0x3b9fffff --> PA: 0x3b800000 - 0x3b9fffff */
    .xword (0x3ba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3ba00000 - 0x3bbfffff --> PA: 0x3ba00000 - 0x3bbfffff */
    .xword (0x3bc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3bc00000 - 0x3bdfffff --> PA: 0x3bc00000 - 0x3bdfffff */
    .xword (0x3be00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3be00000 - 0x3bffffff --> PA: 0x3be00000 - 0x3bffffff */
    .xword (0x3c000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3c000000 - 0x3c1fffff --> PA: 0x3c000000 - 0x3c1fffff */
    .xword (0x3c200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3c200000 - 0x3c3fffff --> PA: 0x3c200000 - 0x3c3fffff */
    .xword (0x3c400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3c400000 - 0x3c5fffff --> PA: 0x3c400000 - 0x3c5fffff */
    .xword (0x3c600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3c600000 - 0x3c7fffff --> PA: 0x3c600000 - 0x3c7fffff */
    .xword (0x3c800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3c800000 - 0x3c9fffff --> PA: 0x3c800000 - 0x3c9fffff */
    .xword (0x3ca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3ca00000 - 0x3cbfffff --> PA: 0x3ca00000 - 0x3cbfffff */
    .xword (0x3cc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3cc00000 - 0x3cdfffff --> PA: 0x3cc00000 - 0x3cdfffff */
    .xword (0x3ce00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3ce00000 - 0x3cffffff --> PA: 0x3ce00000 - 0x3cffffff */
    .xword (0x3d000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3d000000 - 0x3d1fffff --> PA: 0x3d000000 - 0x3d1fffff */
    .xword (0x3d200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3d200000 - 0x3d3fffff --> PA: 0x3d200000 - 0x3d3fffff */
    .xword (0x3d400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3d400000 - 0x3d5fffff --> PA: 0x3d400000 - 0x3d5fffff */
    .xword (0x3d600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3d600000 - 0x3d7fffff --> PA: 0x3d600000 - 0x3d7fffff */
    .xword (0x3d800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3d800000 - 0x3d9fffff --> PA: 0x3d800000 - 0x3d9fffff */
    .xword (0x3da00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3da00000 - 0x3dbfffff --> PA: 0x3da00000 - 0x3dbfffff */
    .xword (0x3dc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3dc00000 - 0x3ddfffff --> PA: 0x3dc00000 - 0x3ddfffff */
    .xword (0x3de00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3de00000 - 0x3dffffff --> PA: 0x3de00000 - 0x3dffffff */
    .xword (0x3e000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3e000000 - 0x3e1fffff --> PA: 0x3e000000 - 0x3e1fffff */
    .xword (0x3e200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3e200000 - 0x3e3fffff --> PA: 0x3e200000 - 0x3e3fffff */
    .xword (0x3e400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3e400000 - 0x3e5fffff --> PA: 0x3e400000 - 0x3e5fffff */
    .xword (0x3e600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3e600000 - 0x3e7fffff --> PA: 0x3e600000 - 0x3e7fffff */
    .xword (0x3e800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3e800000 - 0x3e9fffff --> PA: 0x3e800000 - 0x3e9fffff */
    .xword (0x3ea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3ea00000 - 0x3ebfffff --> PA: 0x3ea00000 - 0x3ebfffff */
    .xword (0x3ec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3ec00000 - 0x3edfffff --> PA: 0x3ec00000 - 0x3edfffff */
    .xword (0x3ee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3ee00000 - 0x3effffff --> PA: 0x3ee00000 - 0x3effffff */
    .xword (0x3f000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3f000000 - 0x3f1fffff --> PA: 0x3f000000 - 0x3f1fffff */
    .xword (0x3f200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3f200000 - 0x3f3fffff --> PA: 0x3f200000 - 0x3f3fffff */
    .xword (0x3f400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3f400000 - 0x3f5fffff --> PA: 0x3f400000 - 0x3f5fffff */
    .xword (0x3f600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3f600000 - 0x3f7fffff --> PA: 0x3f600000 - 0x3f7fffff */
    .xword (0x3f800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3f800000 - 0x3f9fffff --> PA: 0x3f800000 - 0x3f9fffff */
    .xword (0x3fa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3fa00000 - 0x3fbfffff --> PA: 0x3fa00000 - 0x3fbfffff */
    .xword (0x3fc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3fc00000 - 0x3fdfffff --> PA: 0x3fc00000 - 0x3fdfffff */
    .xword (0x3fe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x3fe00000 - 0x3fffffff --> PA: 0x3fe00000 - 0x3fffffff */

.size mmu_level2_translation_table_0, .-mmu_level2_translation_table_0


.section .rodata
.align 12
.globl mmu_level2_translation_table_1
mmu_level2_translation_table_1:
    .xword (0x40000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x40000000 - 0x401fffff --> PA: 0x40000000 - 0x401fffff */
    .xword (0x40200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x40200000 - 0x403fffff --> PA: 0x40200000 - 0x403fffff */
    .xword (0x40400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x40400000 - 0x405fffff --> PA: 0x40400000 - 0x405fffff */
    .xword (0x40600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x40600000 - 0x407fffff --> PA: 0x40600000 - 0x407fffff */
    .xword (0x40800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x40800000 - 0x409fffff --> PA: 0x40800000 - 0x409fffff */
    .xword (0x40a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x40a00000 - 0x40bfffff --> PA: 0x40a00000 - 0x40bfffff */
    .xword (0x40c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x40c00000 - 0x40dfffff --> PA: 0x40c00000 - 0x40dfffff */
    .xword (0x40e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x40e00000 - 0x40ffffff --> PA: 0x40e00000 - 0x40ffffff */
    .xword (0x41000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x41000000 - 0x411fffff --> PA: 0x41000000 - 0x411fffff */
    .xword (0x41200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x41200000 - 0x413fffff --> PA: 0x41200000 - 0x413fffff */
    .xword (0x41400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x41400000 - 0x415fffff --> PA: 0x41400000 - 0x415fffff */
    .xword (0x41600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x41600000 - 0x417fffff --> PA: 0x41600000 - 0x417fffff */
    .xword (0x41800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x41800000 - 0x419fffff --> PA: 0x41800000 - 0x419fffff */
    .xword (0x41a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x41a00000 - 0x41bfffff --> PA: 0x41a00000 - 0x41bfffff */
    .xword (0x41c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x41c00000 - 0x41dfffff --> PA: 0x41c00000 - 0x41dfffff */
    .xword (0x41e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x41e00000 - 0x41ffffff --> PA: 0x41e00000 - 0x41ffffff */
    .xword (0x42000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x42000000 - 0x421fffff --> PA: 0x42000000 - 0x421fffff */
    .xword (0x42200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x42200000 - 0x423fffff --> PA: 0x42200000 - 0x423fffff */
    .xword (0x42400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x42400000 - 0x425fffff --> PA: 0x42400000 - 0x425fffff */
    .xword (0x42600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x42600000 - 0x427fffff --> PA: 0x42600000 - 0x427fffff */
    .xword (0x42800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x42800000 - 0x429fffff --> PA: 0x42800000 - 0x429fffff */
    .xword (0x42a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x42a00000 - 0x42bfffff --> PA: 0x42a00000 - 0x42bfffff */
    .xword (0x42c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x42c00000 - 0x42dfffff --> PA: 0x42c00000 - 0x42dfffff */
    .xword (0x42e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x42e00000 - 0x42ffffff --> PA: 0x42e00000 - 0x42ffffff */
    .xword (0x43000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x43000000 - 0x431fffff --> PA: 0x43000000 - 0x431fffff */
    .xword (0x43200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x43200000 - 0x433fffff --> PA: 0x43200000 - 0x433fffff */
    .xword (0x43400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x43400000 - 0x435fffff --> PA: 0x43400000 - 0x435fffff */
    .xword (0x43600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x43600000 - 0x437fffff --> PA: 0x43600000 - 0x437fffff */
    .xword (0x43800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x43800000 - 0x439fffff --> PA: 0x43800000 - 0x439fffff */
    .xword (0x43a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x43a00000 - 0x43bfffff --> PA: 0x43a00000 - 0x43bfffff */
    .xword (0x43c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x43c00000 - 0x43dfffff --> PA: 0x43c00000 - 0x43dfffff */
    .xword (0x43e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x43e00000 - 0x43ffffff --> PA: 0x43e00000 - 0x43ffffff */
    .xword (0x44000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x44000000 - 0x441fffff --> PA: 0x44000000 - 0x441fffff */
    .xword (0x44200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x44200000 - 0x443fffff --> PA: 0x44200000 - 0x443fffff */
    .xword (0x44400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x44400000 - 0x445fffff --> PA: 0x44400000 - 0x445fffff */
    .xword (0x44600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x44600000 - 0x447fffff --> PA: 0x44600000 - 0x447fffff */
    .xword (0x44800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x44800000 - 0x449fffff --> PA: 0x44800000 - 0x449fffff */
    .xword (0x44a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x44a00000 - 0x44bfffff --> PA: 0x44a00000 - 0x44bfffff */
    .xword (0x44c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x44c00000 - 0x44dfffff --> PA: 0x44c00000 - 0x44dfffff */
    .xword (0x44e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x44e00000 - 0x44ffffff --> PA: 0x44e00000 - 0x44ffffff */
    .xword (0x45000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x45000000 - 0x451fffff --> PA: 0x45000000 - 0x451fffff */
    .xword (0x45200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x45200000 - 0x453fffff --> PA: 0x45200000 - 0x453fffff */
    .xword (0x45400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x45400000 - 0x455fffff --> PA: 0x45400000 - 0x455fffff */
    .xword (0x45600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x45600000 - 0x457fffff --> PA: 0x45600000 - 0x457fffff */
    .xword (0x45800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x45800000 - 0x459fffff --> PA: 0x45800000 - 0x459fffff */
    .xword (0x45a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x45a00000 - 0x45bfffff --> PA: 0x45a00000 - 0x45bfffff */
    .xword (0x45c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x45c00000 - 0x45dfffff --> PA: 0x45c00000 - 0x45dfffff */
    .xword (0x45e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x45e00000 - 0x45ffffff --> PA: 0x45e00000 - 0x45ffffff */
    .xword (0x46000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x46000000 - 0x461fffff --> PA: 0x46000000 - 0x461fffff */
    .xword (0x46200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x46200000 - 0x463fffff --> PA: 0x46200000 - 0x463fffff */
    .xword (0x46400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x46400000 - 0x465fffff --> PA: 0x46400000 - 0x465fffff */
    .xword (0x46600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x46600000 - 0x467fffff --> PA: 0x46600000 - 0x467fffff */
    .xword (0x46800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x46800000 - 0x469fffff --> PA: 0x46800000 - 0x469fffff */
    .xword (0x46a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x46a00000 - 0x46bfffff --> PA: 0x46a00000 - 0x46bfffff */
    .xword (0x46c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x46c00000 - 0x46dfffff --> PA: 0x46c00000 - 0x46dfffff */
    .xword (0x46e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x46e00000 - 0x46ffffff --> PA: 0x46e00000 - 0x46ffffff */
    .xword (0x47000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x47000000 - 0x471fffff --> PA: 0x47000000 - 0x471fffff */
    .xword (0x47200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x47200000 - 0x473fffff --> PA: 0x47200000 - 0x473fffff */
    .xword (0x47400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x47400000 - 0x475fffff --> PA: 0x47400000 - 0x475fffff */
    .xword (0x47600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x47600000 - 0x477fffff --> PA: 0x47600000 - 0x477fffff */
    .xword (0x47800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x47800000 - 0x479fffff --> PA: 0x47800000 - 0x479fffff */
    .xword (0x47a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x47a00000 - 0x47bfffff --> PA: 0x47a00000 - 0x47bfffff */
    .xword (0x47c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x47c00000 - 0x47dfffff --> PA: 0x47c00000 - 0x47dfffff */
    .xword (0x47e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x47e00000 - 0x47ffffff --> PA: 0x47e00000 - 0x47ffffff */
    .xword (0x48000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x48000000 - 0x481fffff --> PA: 0x48000000 - 0x481fffff */
    .xword (0x48200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x48200000 - 0x483fffff --> PA: 0x48200000 - 0x483fffff */
    .xword (0x48400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x48400000 - 0x485fffff --> PA: 0x48400000 - 0x485fffff */
    .xword (0x48600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x48600000 - 0x487fffff --> PA: 0x48600000 - 0x487fffff */
    .xword (0x48800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x48800000 - 0x489fffff --> PA: 0x48800000 - 0x489fffff */
    .xword (0x48a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x48a00000 - 0x48bfffff --> PA: 0x48a00000 - 0x48bfffff */
    .xword (0x48c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x48c00000 - 0x48dfffff --> PA: 0x48c00000 - 0x48dfffff */
    .xword (0x48e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x48e00000 - 0x48ffffff --> PA: 0x48e00000 - 0x48ffffff */
    .xword (0x49000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x49000000 - 0x491fffff --> PA: 0x49000000 - 0x491fffff */
    .xword (0x49200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x49200000 - 0x493fffff --> PA: 0x49200000 - 0x493fffff */
    .xword (0x49400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x49400000 - 0x495fffff --> PA: 0x49400000 - 0x495fffff */
    .xword (0x49600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x49600000 - 0x497fffff --> PA: 0x49600000 - 0x497fffff */
    .xword (0x49800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x49800000 - 0x499fffff --> PA: 0x49800000 - 0x499fffff */
    .xword (0x49a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x49a00000 - 0x49bfffff --> PA: 0x49a00000 - 0x49bfffff */
    .xword (0x49c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x49c00000 - 0x49dfffff --> PA: 0x49c00000 - 0x49dfffff */
    .xword (0x49e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x49e00000 - 0x49ffffff --> PA: 0x49e00000 - 0x49ffffff */
    .xword (0x4a000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4a000000 - 0x4a1fffff --> PA: 0x4a000000 - 0x4a1fffff */
    .xword (0x4a200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4a200000 - 0x4a3fffff --> PA: 0x4a200000 - 0x4a3fffff */
    .xword (0x4a400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4a400000 - 0x4a5fffff --> PA: 0x4a400000 - 0x4a5fffff */
    .xword (0x4a600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4a600000 - 0x4a7fffff --> PA: 0x4a600000 - 0x4a7fffff */
    .xword (0x4a800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4a800000 - 0x4a9fffff --> PA: 0x4a800000 - 0x4a9fffff */
    .xword (0x4aa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4aa00000 - 0x4abfffff --> PA: 0x4aa00000 - 0x4abfffff */
    .xword (0x4ac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4ac00000 - 0x4adfffff --> PA: 0x4ac00000 - 0x4adfffff */
    .xword (0x4ae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4ae00000 - 0x4affffff --> PA: 0x4ae00000 - 0x4affffff */
    .xword (0x4b000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4b000000 - 0x4b1fffff --> PA: 0x4b000000 - 0x4b1fffff */
    .xword (0x4b200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4b200000 - 0x4b3fffff --> PA: 0x4b200000 - 0x4b3fffff */
    .xword (0x4b400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4b400000 - 0x4b5fffff --> PA: 0x4b400000 - 0x4b5fffff */
    .xword (0x4b600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4b600000 - 0x4b7fffff --> PA: 0x4b600000 - 0x4b7fffff */
    .xword (0x4b800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4b800000 - 0x4b9fffff --> PA: 0x4b800000 - 0x4b9fffff */
    .xword (0x4ba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4ba00000 - 0x4bbfffff --> PA: 0x4ba00000 - 0x4bbfffff */
    .xword (0x4bc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4bc00000 - 0x4bdfffff --> PA: 0x4bc00000 - 0x4bdfffff */
    .xword (0x4be00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4be00000 - 0x4bffffff --> PA: 0x4be00000 - 0x4bffffff */
    .xword (0x4c000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4c000000 - 0x4c1fffff --> PA: 0x4c000000 - 0x4c1fffff */
    .xword (0x4c200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4c200000 - 0x4c3fffff --> PA: 0x4c200000 - 0x4c3fffff */
    .xword (0x4c400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4c400000 - 0x4c5fffff --> PA: 0x4c400000 - 0x4c5fffff */
    .xword (0x4c600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4c600000 - 0x4c7fffff --> PA: 0x4c600000 - 0x4c7fffff */
    .xword (0x4c800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4c800000 - 0x4c9fffff --> PA: 0x4c800000 - 0x4c9fffff */
    .xword (0x4ca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4ca00000 - 0x4cbfffff --> PA: 0x4ca00000 - 0x4cbfffff */
    .xword (0x4cc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4cc00000 - 0x4cdfffff --> PA: 0x4cc00000 - 0x4cdfffff */
    .xword (0x4ce00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4ce00000 - 0x4cffffff --> PA: 0x4ce00000 - 0x4cffffff */
    .xword (0x4d000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4d000000 - 0x4d1fffff --> PA: 0x4d000000 - 0x4d1fffff */
    .xword (0x4d200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4d200000 - 0x4d3fffff --> PA: 0x4d200000 - 0x4d3fffff */
    .xword (0x4d400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4d400000 - 0x4d5fffff --> PA: 0x4d400000 - 0x4d5fffff */
    .xword (0x4d600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4d600000 - 0x4d7fffff --> PA: 0x4d600000 - 0x4d7fffff */
    .xword (0x4d800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4d800000 - 0x4d9fffff --> PA: 0x4d800000 - 0x4d9fffff */
    .xword (0x4da00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4da00000 - 0x4dbfffff --> PA: 0x4da00000 - 0x4dbfffff */
    .xword (0x4dc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4dc00000 - 0x4ddfffff --> PA: 0x4dc00000 - 0x4ddfffff */
    .xword (0x4de00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4de00000 - 0x4dffffff --> PA: 0x4de00000 - 0x4dffffff */
    .xword (0x4e000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4e000000 - 0x4e1fffff --> PA: 0x4e000000 - 0x4e1fffff */
    .xword (0x4e200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4e200000 - 0x4e3fffff --> PA: 0x4e200000 - 0x4e3fffff */
    .xword (0x4e400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4e400000 - 0x4e5fffff --> PA: 0x4e400000 - 0x4e5fffff */
    .xword (0x4e600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4e600000 - 0x4e7fffff --> PA: 0x4e600000 - 0x4e7fffff */
    .xword (0x4e800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4e800000 - 0x4e9fffff --> PA: 0x4e800000 - 0x4e9fffff */
    .xword (0x4ea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4ea00000 - 0x4ebfffff --> PA: 0x4ea00000 - 0x4ebfffff */
    .xword (0x4ec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4ec00000 - 0x4edfffff --> PA: 0x4ec00000 - 0x4edfffff */
    .xword (0x4ee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4ee00000 - 0x4effffff --> PA: 0x4ee00000 - 0x4effffff */
    .xword (0x4f000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4f000000 - 0x4f1fffff --> PA: 0x4f000000 - 0x4f1fffff */
    .xword (0x4f200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4f200000 - 0x4f3fffff --> PA: 0x4f200000 - 0x4f3fffff */
    .xword (0x4f400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4f400000 - 0x4f5fffff --> PA: 0x4f400000 - 0x4f5fffff */
    .xword (0x4f600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4f600000 - 0x4f7fffff --> PA: 0x4f600000 - 0x4f7fffff */
    .xword (0x4f800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4f800000 - 0x4f9fffff --> PA: 0x4f800000 - 0x4f9fffff */
    .xword (0x4fa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4fa00000 - 0x4fbfffff --> PA: 0x4fa00000 - 0x4fbfffff */
    .xword (0x4fc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4fc00000 - 0x4fdfffff --> PA: 0x4fc00000 - 0x4fdfffff */
    .xword (0x4fe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x4fe00000 - 0x4fffffff --> PA: 0x4fe00000 - 0x4fffffff */
    .xword (0x50000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x50000000 - 0x501fffff --> PA: 0x50000000 - 0x501fffff */
    .xword (0x50200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x50200000 - 0x503fffff --> PA: 0x50200000 - 0x503fffff */
    .xword (0x50400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x50400000 - 0x505fffff --> PA: 0x50400000 - 0x505fffff */
    .xword (0x50600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x50600000 - 0x507fffff --> PA: 0x50600000 - 0x507fffff */
    .xword (0x50800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x50800000 - 0x509fffff --> PA: 0x50800000 - 0x509fffff */
    .xword (0x50a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x50a00000 - 0x50bfffff --> PA: 0x50a00000 - 0x50bfffff */
    .xword (0x50c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x50c00000 - 0x50dfffff --> PA: 0x50c00000 - 0x50dfffff */
    .xword (0x50e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x50e00000 - 0x50ffffff --> PA: 0x50e00000 - 0x50ffffff */
    .xword (0x51000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x51000000 - 0x511fffff --> PA: 0x51000000 - 0x511fffff */
    .xword (0x51200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x51200000 - 0x513fffff --> PA: 0x51200000 - 0x513fffff */
    .xword (0x51400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x51400000 - 0x515fffff --> PA: 0x51400000 - 0x515fffff */
    .xword (0x51600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x51600000 - 0x517fffff --> PA: 0x51600000 - 0x517fffff */
    .xword (0x51800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x51800000 - 0x519fffff --> PA: 0x51800000 - 0x519fffff */
    .xword (0x51a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x51a00000 - 0x51bfffff --> PA: 0x51a00000 - 0x51bfffff */
    .xword (0x51c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x51c00000 - 0x51dfffff --> PA: 0x51c00000 - 0x51dfffff */
    .xword (0x51e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x51e00000 - 0x51ffffff --> PA: 0x51e00000 - 0x51ffffff */
    .xword (0x52000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x52000000 - 0x521fffff --> PA: 0x52000000 - 0x521fffff */
    .xword (0x52200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x52200000 - 0x523fffff --> PA: 0x52200000 - 0x523fffff */
    .xword (0x52400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x52400000 - 0x525fffff --> PA: 0x52400000 - 0x525fffff */
    .xword (0x52600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x52600000 - 0x527fffff --> PA: 0x52600000 - 0x527fffff */
    .xword (0x52800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x52800000 - 0x529fffff --> PA: 0x52800000 - 0x529fffff */
    .xword (0x52a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x52a00000 - 0x52bfffff --> PA: 0x52a00000 - 0x52bfffff */
    .xword (0x52c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x52c00000 - 0x52dfffff --> PA: 0x52c00000 - 0x52dfffff */
    .xword (0x52e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x52e00000 - 0x52ffffff --> PA: 0x52e00000 - 0x52ffffff */
    .xword (0x53000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x53000000 - 0x531fffff --> PA: 0x53000000 - 0x531fffff */
    .xword (0x53200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x53200000 - 0x533fffff --> PA: 0x53200000 - 0x533fffff */
    .xword (0x53400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x53400000 - 0x535fffff --> PA: 0x53400000 - 0x535fffff */
    .xword (0x53600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x53600000 - 0x537fffff --> PA: 0x53600000 - 0x537fffff */
    .xword (0x53800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x53800000 - 0x539fffff --> PA: 0x53800000 - 0x539fffff */
    .xword (0x53a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x53a00000 - 0x53bfffff --> PA: 0x53a00000 - 0x53bfffff */
    .xword (0x53c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x53c00000 - 0x53dfffff --> PA: 0x53c00000 - 0x53dfffff */
    .xword (0x53e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x53e00000 - 0x53ffffff --> PA: 0x53e00000 - 0x53ffffff */
    .xword (0x54000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x54000000 - 0x541fffff --> PA: 0x54000000 - 0x541fffff */
    .xword (0x54200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x54200000 - 0x543fffff --> PA: 0x54200000 - 0x543fffff */
    .xword (0x54400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x54400000 - 0x545fffff --> PA: 0x54400000 - 0x545fffff */
    .xword (0x54600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x54600000 - 0x547fffff --> PA: 0x54600000 - 0x547fffff */
    .xword (0x54800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x54800000 - 0x549fffff --> PA: 0x54800000 - 0x549fffff */
    .xword (0x54a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x54a00000 - 0x54bfffff --> PA: 0x54a00000 - 0x54bfffff */
    .xword (0x54c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x54c00000 - 0x54dfffff --> PA: 0x54c00000 - 0x54dfffff */
    .xword (0x54e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x54e00000 - 0x54ffffff --> PA: 0x54e00000 - 0x54ffffff */
    .xword (0x55000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x55000000 - 0x551fffff --> PA: 0x55000000 - 0x551fffff */
    .xword (0x55200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x55200000 - 0x553fffff --> PA: 0x55200000 - 0x553fffff */
    .xword (0x55400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x55400000 - 0x555fffff --> PA: 0x55400000 - 0x555fffff */
    .xword (0x55600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x55600000 - 0x557fffff --> PA: 0x55600000 - 0x557fffff */
    .xword (0x55800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x55800000 - 0x559fffff --> PA: 0x55800000 - 0x559fffff */
    .xword (0x55a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x55a00000 - 0x55bfffff --> PA: 0x55a00000 - 0x55bfffff */
    .xword (0x55c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x55c00000 - 0x55dfffff --> PA: 0x55c00000 - 0x55dfffff */
    .xword (0x55e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x55e00000 - 0x55ffffff --> PA: 0x55e00000 - 0x55ffffff */
    .xword (0x56000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x56000000 - 0x561fffff --> PA: 0x56000000 - 0x561fffff */
    .xword (0x56200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x56200000 - 0x563fffff --> PA: 0x56200000 - 0x563fffff */
    .xword (0x56400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x56400000 - 0x565fffff --> PA: 0x56400000 - 0x565fffff */
    .xword (0x56600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x56600000 - 0x567fffff --> PA: 0x56600000 - 0x567fffff */
    .xword (0x56800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x56800000 - 0x569fffff --> PA: 0x56800000 - 0x569fffff */
    .xword (0x56a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x56a00000 - 0x56bfffff --> PA: 0x56a00000 - 0x56bfffff */
    .xword (0x56c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x56c00000 - 0x56dfffff --> PA: 0x56c00000 - 0x56dfffff */
    .xword (0x56e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x56e00000 - 0x56ffffff --> PA: 0x56e00000 - 0x56ffffff */
    .xword (0x57000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x57000000 - 0x571fffff --> PA: 0x57000000 - 0x571fffff */
    .xword (0x57200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x57200000 - 0x573fffff --> PA: 0x57200000 - 0x573fffff */
    .xword (0x57400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x57400000 - 0x575fffff --> PA: 0x57400000 - 0x575fffff */
    .xword (0x57600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x57600000 - 0x577fffff --> PA: 0x57600000 - 0x577fffff */
    .xword (0x57800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x57800000 - 0x579fffff --> PA: 0x57800000 - 0x579fffff */
    .xword (0x57a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x57a00000 - 0x57bfffff --> PA: 0x57a00000 - 0x57bfffff */
    .xword (0x57c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x57c00000 - 0x57dfffff --> PA: 0x57c00000 - 0x57dfffff */
    .xword (0x57e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x57e00000 - 0x57ffffff --> PA: 0x57e00000 - 0x57ffffff */
    .xword (0x58000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x58000000 - 0x581fffff --> PA: 0x58000000 - 0x581fffff */
    .xword (0x58200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x58200000 - 0x583fffff --> PA: 0x58200000 - 0x583fffff */
    .xword (0x58400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x58400000 - 0x585fffff --> PA: 0x58400000 - 0x585fffff */
    .xword (0x58600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x58600000 - 0x587fffff --> PA: 0x58600000 - 0x587fffff */
    .xword (0x58800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x58800000 - 0x589fffff --> PA: 0x58800000 - 0x589fffff */
    .xword (0x58a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x58a00000 - 0x58bfffff --> PA: 0x58a00000 - 0x58bfffff */
    .xword (0x58c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x58c00000 - 0x58dfffff --> PA: 0x58c00000 - 0x58dfffff */
    .xword (0x58e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x58e00000 - 0x58ffffff --> PA: 0x58e00000 - 0x58ffffff */
    .xword (0x59000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x59000000 - 0x591fffff --> PA: 0x59000000 - 0x591fffff */
    .xword (0x59200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x59200000 - 0x593fffff --> PA: 0x59200000 - 0x593fffff */
    .xword (0x59400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x59400000 - 0x595fffff --> PA: 0x59400000 - 0x595fffff */
    .xword (0x59600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x59600000 - 0x597fffff --> PA: 0x59600000 - 0x597fffff */
    .xword (0x59800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x59800000 - 0x599fffff --> PA: 0x59800000 - 0x599fffff */
    .xword (0x59a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x59a00000 - 0x59bfffff --> PA: 0x59a00000 - 0x59bfffff */
    .xword (0x59c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x59c00000 - 0x59dfffff --> PA: 0x59c00000 - 0x59dfffff */
    .xword (0x59e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x59e00000 - 0x59ffffff --> PA: 0x59e00000 - 0x59ffffff */
    .xword (0x5a000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5a000000 - 0x5a1fffff --> PA: 0x5a000000 - 0x5a1fffff */
    .xword (0x5a200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5a200000 - 0x5a3fffff --> PA: 0x5a200000 - 0x5a3fffff */
    .xword (0x5a400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5a400000 - 0x5a5fffff --> PA: 0x5a400000 - 0x5a5fffff */
    .xword (0x5a600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5a600000 - 0x5a7fffff --> PA: 0x5a600000 - 0x5a7fffff */
    .xword (0x5a800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5a800000 - 0x5a9fffff --> PA: 0x5a800000 - 0x5a9fffff */
    .xword (0x5aa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5aa00000 - 0x5abfffff --> PA: 0x5aa00000 - 0x5abfffff */
    .xword (0x5ac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5ac00000 - 0x5adfffff --> PA: 0x5ac00000 - 0x5adfffff */
    .xword (0x5ae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5ae00000 - 0x5affffff --> PA: 0x5ae00000 - 0x5affffff */
    .xword (0x5b000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5b000000 - 0x5b1fffff --> PA: 0x5b000000 - 0x5b1fffff */
    .xword (0x5b200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5b200000 - 0x5b3fffff --> PA: 0x5b200000 - 0x5b3fffff */
    .xword (0x5b400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5b400000 - 0x5b5fffff --> PA: 0x5b400000 - 0x5b5fffff */
    .xword (0x5b600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5b600000 - 0x5b7fffff --> PA: 0x5b600000 - 0x5b7fffff */
    .xword (0x5b800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5b800000 - 0x5b9fffff --> PA: 0x5b800000 - 0x5b9fffff */
    .xword (0x5ba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5ba00000 - 0x5bbfffff --> PA: 0x5ba00000 - 0x5bbfffff */
    .xword (0x5bc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5bc00000 - 0x5bdfffff --> PA: 0x5bc00000 - 0x5bdfffff */
    .xword (0x5be00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5be00000 - 0x5bffffff --> PA: 0x5be00000 - 0x5bffffff */
    .xword (0x5c000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5c000000 - 0x5c1fffff --> PA: 0x5c000000 - 0x5c1fffff */
    .xword (0x5c200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5c200000 - 0x5c3fffff --> PA: 0x5c200000 - 0x5c3fffff */
    .xword (0x5c400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5c400000 - 0x5c5fffff --> PA: 0x5c400000 - 0x5c5fffff */
    .xword (0x5c600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5c600000 - 0x5c7fffff --> PA: 0x5c600000 - 0x5c7fffff */
    .xword (0x5c800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5c800000 - 0x5c9fffff --> PA: 0x5c800000 - 0x5c9fffff */
    .xword (0x5ca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5ca00000 - 0x5cbfffff --> PA: 0x5ca00000 - 0x5cbfffff */
    .xword (0x5cc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5cc00000 - 0x5cdfffff --> PA: 0x5cc00000 - 0x5cdfffff */
    .xword (0x5ce00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5ce00000 - 0x5cffffff --> PA: 0x5ce00000 - 0x5cffffff */
    .xword (0x5d000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5d000000 - 0x5d1fffff --> PA: 0x5d000000 - 0x5d1fffff */
    .xword (0x5d200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5d200000 - 0x5d3fffff --> PA: 0x5d200000 - 0x5d3fffff */
    .xword (0x5d400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5d400000 - 0x5d5fffff --> PA: 0x5d400000 - 0x5d5fffff */
    .xword (0x5d600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5d600000 - 0x5d7fffff --> PA: 0x5d600000 - 0x5d7fffff */
    .xword (0x5d800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5d800000 - 0x5d9fffff --> PA: 0x5d800000 - 0x5d9fffff */
    .xword (0x5da00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5da00000 - 0x5dbfffff --> PA: 0x5da00000 - 0x5dbfffff */
    .xword (0x5dc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5dc00000 - 0x5ddfffff --> PA: 0x5dc00000 - 0x5ddfffff */
    .xword (0x5de00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5de00000 - 0x5dffffff --> PA: 0x5de00000 - 0x5dffffff */
    .xword (0x5e000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5e000000 - 0x5e1fffff --> PA: 0x5e000000 - 0x5e1fffff */
    .xword (0x5e200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5e200000 - 0x5e3fffff --> PA: 0x5e200000 - 0x5e3fffff */
    .xword (0x5e400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5e400000 - 0x5e5fffff --> PA: 0x5e400000 - 0x5e5fffff */
    .xword (0x5e600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5e600000 - 0x5e7fffff --> PA: 0x5e600000 - 0x5e7fffff */
    .xword (0x5e800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5e800000 - 0x5e9fffff --> PA: 0x5e800000 - 0x5e9fffff */
    .xword (0x5ea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5ea00000 - 0x5ebfffff --> PA: 0x5ea00000 - 0x5ebfffff */
    .xword (0x5ec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5ec00000 - 0x5edfffff --> PA: 0x5ec00000 - 0x5edfffff */
    .xword (0x5ee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5ee00000 - 0x5effffff --> PA: 0x5ee00000 - 0x5effffff */
    .xword (0x5f000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5f000000 - 0x5f1fffff --> PA: 0x5f000000 - 0x5f1fffff */
    .xword (0x5f200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5f200000 - 0x5f3fffff --> PA: 0x5f200000 - 0x5f3fffff */
    .xword (0x5f400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5f400000 - 0x5f5fffff --> PA: 0x5f400000 - 0x5f5fffff */
    .xword (0x5f600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5f600000 - 0x5f7fffff --> PA: 0x5f600000 - 0x5f7fffff */
    .xword (0x5f800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5f800000 - 0x5f9fffff --> PA: 0x5f800000 - 0x5f9fffff */
    .xword (0x5fa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5fa00000 - 0x5fbfffff --> PA: 0x5fa00000 - 0x5fbfffff */
    .xword (0x5fc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5fc00000 - 0x5fdfffff --> PA: 0x5fc00000 - 0x5fdfffff */
    .xword (0x5fe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x5fe00000 - 0x5fffffff --> PA: 0x5fe00000 - 0x5fffffff */
    .xword (0x60000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x60000000 - 0x601fffff --> PA: 0x60000000 - 0x601fffff */
    .xword (0x60200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x60200000 - 0x603fffff --> PA: 0x60200000 - 0x603fffff */
    .xword (0x60400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x60400000 - 0x605fffff --> PA: 0x60400000 - 0x605fffff */
    .xword (0x60600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x60600000 - 0x607fffff --> PA: 0x60600000 - 0x607fffff */
    .xword (0x60800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x60800000 - 0x609fffff --> PA: 0x60800000 - 0x609fffff */
    .xword (0x60a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x60a00000 - 0x60bfffff --> PA: 0x60a00000 - 0x60bfffff */
    .xword (0x60c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x60c00000 - 0x60dfffff --> PA: 0x60c00000 - 0x60dfffff */
    .xword (0x60e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x60e00000 - 0x60ffffff --> PA: 0x60e00000 - 0x60ffffff */
    .xword (0x61000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x61000000 - 0x611fffff --> PA: 0x61000000 - 0x611fffff */
    .xword (0x61200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x61200000 - 0x613fffff --> PA: 0x61200000 - 0x613fffff */
    .xword (0x61400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x61400000 - 0x615fffff --> PA: 0x61400000 - 0x615fffff */
    .xword (0x61600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x61600000 - 0x617fffff --> PA: 0x61600000 - 0x617fffff */
    .xword (0x61800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x61800000 - 0x619fffff --> PA: 0x61800000 - 0x619fffff */
    .xword (0x61a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x61a00000 - 0x61bfffff --> PA: 0x61a00000 - 0x61bfffff */
    .xword (0x61c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x61c00000 - 0x61dfffff --> PA: 0x61c00000 - 0x61dfffff */
    .xword (0x61e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x61e00000 - 0x61ffffff --> PA: 0x61e00000 - 0x61ffffff */
    .xword (0x62000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x62000000 - 0x621fffff --> PA: 0x62000000 - 0x621fffff */
    .xword (0x62200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x62200000 - 0x623fffff --> PA: 0x62200000 - 0x623fffff */
    .xword (0x62400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x62400000 - 0x625fffff --> PA: 0x62400000 - 0x625fffff */
    .xword (0x62600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x62600000 - 0x627fffff --> PA: 0x62600000 - 0x627fffff */
    .xword (0x62800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x62800000 - 0x629fffff --> PA: 0x62800000 - 0x629fffff */
    .xword (0x62a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x62a00000 - 0x62bfffff --> PA: 0x62a00000 - 0x62bfffff */
    .xword (0x62c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x62c00000 - 0x62dfffff --> PA: 0x62c00000 - 0x62dfffff */
    .xword (0x62e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x62e00000 - 0x62ffffff --> PA: 0x62e00000 - 0x62ffffff */
    .xword (0x63000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x63000000 - 0x631fffff --> PA: 0x63000000 - 0x631fffff */
    .xword (0x63200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x63200000 - 0x633fffff --> PA: 0x63200000 - 0x633fffff */
    .xword (0x63400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x63400000 - 0x635fffff --> PA: 0x63400000 - 0x635fffff */
    .xword (0x63600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x63600000 - 0x637fffff --> PA: 0x63600000 - 0x637fffff */
    .xword (0x63800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x63800000 - 0x639fffff --> PA: 0x63800000 - 0x639fffff */
    .xword (0x63a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x63a00000 - 0x63bfffff --> PA: 0x63a00000 - 0x63bfffff */
    .xword (0x63c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x63c00000 - 0x63dfffff --> PA: 0x63c00000 - 0x63dfffff */
    .xword (0x63e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x63e00000 - 0x63ffffff --> PA: 0x63e00000 - 0x63ffffff */
    .xword (0x64000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x64000000 - 0x641fffff --> PA: 0x64000000 - 0x641fffff */
    .xword (0x64200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x64200000 - 0x643fffff --> PA: 0x64200000 - 0x643fffff */
    .xword (0x64400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x64400000 - 0x645fffff --> PA: 0x64400000 - 0x645fffff */
    .xword (0x64600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x64600000 - 0x647fffff --> PA: 0x64600000 - 0x647fffff */
    .xword (0x64800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x64800000 - 0x649fffff --> PA: 0x64800000 - 0x649fffff */
    .xword (0x64a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x64a00000 - 0x64bfffff --> PA: 0x64a00000 - 0x64bfffff */
    .xword (0x64c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x64c00000 - 0x64dfffff --> PA: 0x64c00000 - 0x64dfffff */
    .xword (0x64e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x64e00000 - 0x64ffffff --> PA: 0x64e00000 - 0x64ffffff */
    .xword (0x65000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x65000000 - 0x651fffff --> PA: 0x65000000 - 0x651fffff */
    .xword (0x65200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x65200000 - 0x653fffff --> PA: 0x65200000 - 0x653fffff */
    .xword (0x65400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x65400000 - 0x655fffff --> PA: 0x65400000 - 0x655fffff */
    .xword (0x65600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x65600000 - 0x657fffff --> PA: 0x65600000 - 0x657fffff */
    .xword (0x65800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x65800000 - 0x659fffff --> PA: 0x65800000 - 0x659fffff */
    .xword (0x65a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x65a00000 - 0x65bfffff --> PA: 0x65a00000 - 0x65bfffff */
    .xword (0x65c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x65c00000 - 0x65dfffff --> PA: 0x65c00000 - 0x65dfffff */
    .xword (0x65e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x65e00000 - 0x65ffffff --> PA: 0x65e00000 - 0x65ffffff */
    .xword (0x66000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x66000000 - 0x661fffff --> PA: 0x66000000 - 0x661fffff */
    .xword (0x66200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x66200000 - 0x663fffff --> PA: 0x66200000 - 0x663fffff */
    .xword (0x66400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x66400000 - 0x665fffff --> PA: 0x66400000 - 0x665fffff */
    .xword (0x66600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x66600000 - 0x667fffff --> PA: 0x66600000 - 0x667fffff */
    .xword (0x66800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x66800000 - 0x669fffff --> PA: 0x66800000 - 0x669fffff */
    .xword (0x66a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x66a00000 - 0x66bfffff --> PA: 0x66a00000 - 0x66bfffff */
    .xword (0x66c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x66c00000 - 0x66dfffff --> PA: 0x66c00000 - 0x66dfffff */
    .xword (0x66e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x66e00000 - 0x66ffffff --> PA: 0x66e00000 - 0x66ffffff */
    .xword (0x67000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x67000000 - 0x671fffff --> PA: 0x67000000 - 0x671fffff */
    .xword (0x67200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x67200000 - 0x673fffff --> PA: 0x67200000 - 0x673fffff */
    .xword (0x67400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x67400000 - 0x675fffff --> PA: 0x67400000 - 0x675fffff */
    .xword (0x67600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x67600000 - 0x677fffff --> PA: 0x67600000 - 0x677fffff */
    .xword (0x67800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x67800000 - 0x679fffff --> PA: 0x67800000 - 0x679fffff */
    .xword (0x67a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x67a00000 - 0x67bfffff --> PA: 0x67a00000 - 0x67bfffff */
    .xword (0x67c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x67c00000 - 0x67dfffff --> PA: 0x67c00000 - 0x67dfffff */
    .xword (0x67e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x67e00000 - 0x67ffffff --> PA: 0x67e00000 - 0x67ffffff */
    .xword (0x68000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x68000000 - 0x681fffff --> PA: 0x68000000 - 0x681fffff */
    .xword (0x68200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x68200000 - 0x683fffff --> PA: 0x68200000 - 0x683fffff */
    .xword (0x68400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x68400000 - 0x685fffff --> PA: 0x68400000 - 0x685fffff */
    .xword (0x68600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x68600000 - 0x687fffff --> PA: 0x68600000 - 0x687fffff */
    .xword (0x68800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x68800000 - 0x689fffff --> PA: 0x68800000 - 0x689fffff */
    .xword (0x68a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x68a00000 - 0x68bfffff --> PA: 0x68a00000 - 0x68bfffff */
    .xword (0x68c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x68c00000 - 0x68dfffff --> PA: 0x68c00000 - 0x68dfffff */
    .xword (0x68e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x68e00000 - 0x68ffffff --> PA: 0x68e00000 - 0x68ffffff */
    .xword (0x69000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x69000000 - 0x691fffff --> PA: 0x69000000 - 0x691fffff */
    .xword (0x69200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x69200000 - 0x693fffff --> PA: 0x69200000 - 0x693fffff */
    .xword (0x69400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x69400000 - 0x695fffff --> PA: 0x69400000 - 0x695fffff */
    .xword (0x69600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x69600000 - 0x697fffff --> PA: 0x69600000 - 0x697fffff */
    .xword (0x69800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x69800000 - 0x699fffff --> PA: 0x69800000 - 0x699fffff */
    .xword (0x69a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x69a00000 - 0x69bfffff --> PA: 0x69a00000 - 0x69bfffff */
    .xword (0x69c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x69c00000 - 0x69dfffff --> PA: 0x69c00000 - 0x69dfffff */
    .xword (0x69e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x69e00000 - 0x69ffffff --> PA: 0x69e00000 - 0x69ffffff */
    .xword (0x6a000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6a000000 - 0x6a1fffff --> PA: 0x6a000000 - 0x6a1fffff */
    .xword (0x6a200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6a200000 - 0x6a3fffff --> PA: 0x6a200000 - 0x6a3fffff */
    .xword (0x6a400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6a400000 - 0x6a5fffff --> PA: 0x6a400000 - 0x6a5fffff */
    .xword (0x6a600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6a600000 - 0x6a7fffff --> PA: 0x6a600000 - 0x6a7fffff */
    .xword (0x6a800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6a800000 - 0x6a9fffff --> PA: 0x6a800000 - 0x6a9fffff */
    .xword (0x6aa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6aa00000 - 0x6abfffff --> PA: 0x6aa00000 - 0x6abfffff */
    .xword (0x6ac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6ac00000 - 0x6adfffff --> PA: 0x6ac00000 - 0x6adfffff */
    .xword (0x6ae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6ae00000 - 0x6affffff --> PA: 0x6ae00000 - 0x6affffff */
    .xword (0x6b000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6b000000 - 0x6b1fffff --> PA: 0x6b000000 - 0x6b1fffff */
    .xword (0x6b200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6b200000 - 0x6b3fffff --> PA: 0x6b200000 - 0x6b3fffff */
    .xword (0x6b400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6b400000 - 0x6b5fffff --> PA: 0x6b400000 - 0x6b5fffff */
    .xword (0x6b600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6b600000 - 0x6b7fffff --> PA: 0x6b600000 - 0x6b7fffff */
    .xword (0x6b800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6b800000 - 0x6b9fffff --> PA: 0x6b800000 - 0x6b9fffff */
    .xword (0x6ba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6ba00000 - 0x6bbfffff --> PA: 0x6ba00000 - 0x6bbfffff */
    .xword (0x6bc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6bc00000 - 0x6bdfffff --> PA: 0x6bc00000 - 0x6bdfffff */
    .xword (0x6be00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6be00000 - 0x6bffffff --> PA: 0x6be00000 - 0x6bffffff */
    .xword (0x6c000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6c000000 - 0x6c1fffff --> PA: 0x6c000000 - 0x6c1fffff */
    .xword (0x6c200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6c200000 - 0x6c3fffff --> PA: 0x6c200000 - 0x6c3fffff */
    .xword (0x6c400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6c400000 - 0x6c5fffff --> PA: 0x6c400000 - 0x6c5fffff */
    .xword (0x6c600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6c600000 - 0x6c7fffff --> PA: 0x6c600000 - 0x6c7fffff */
    .xword (0x6c800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6c800000 - 0x6c9fffff --> PA: 0x6c800000 - 0x6c9fffff */
    .xword (0x6ca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6ca00000 - 0x6cbfffff --> PA: 0x6ca00000 - 0x6cbfffff */
    .xword (0x6cc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6cc00000 - 0x6cdfffff --> PA: 0x6cc00000 - 0x6cdfffff */
    .xword (0x6ce00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6ce00000 - 0x6cffffff --> PA: 0x6ce00000 - 0x6cffffff */
    .xword (0x6d000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6d000000 - 0x6d1fffff --> PA: 0x6d000000 - 0x6d1fffff */
    .xword (0x6d200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6d200000 - 0x6d3fffff --> PA: 0x6d200000 - 0x6d3fffff */
    .xword (0x6d400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6d400000 - 0x6d5fffff --> PA: 0x6d400000 - 0x6d5fffff */
    .xword (0x6d600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6d600000 - 0x6d7fffff --> PA: 0x6d600000 - 0x6d7fffff */
    .xword (0x6d800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6d800000 - 0x6d9fffff --> PA: 0x6d800000 - 0x6d9fffff */
    .xword (0x6da00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6da00000 - 0x6dbfffff --> PA: 0x6da00000 - 0x6dbfffff */
    .xword (0x6dc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6dc00000 - 0x6ddfffff --> PA: 0x6dc00000 - 0x6ddfffff */
    .xword (0x6de00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6de00000 - 0x6dffffff --> PA: 0x6de00000 - 0x6dffffff */
    .xword (0x6e000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6e000000 - 0x6e1fffff --> PA: 0x6e000000 - 0x6e1fffff */
    .xword (0x6e200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6e200000 - 0x6e3fffff --> PA: 0x6e200000 - 0x6e3fffff */
    .xword (0x6e400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6e400000 - 0x6e5fffff --> PA: 0x6e400000 - 0x6e5fffff */
    .xword (0x6e600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6e600000 - 0x6e7fffff --> PA: 0x6e600000 - 0x6e7fffff */
    .xword (0x6e800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6e800000 - 0x6e9fffff --> PA: 0x6e800000 - 0x6e9fffff */
    .xword (0x6ea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6ea00000 - 0x6ebfffff --> PA: 0x6ea00000 - 0x6ebfffff */
    .xword (0x6ec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6ec00000 - 0x6edfffff --> PA: 0x6ec00000 - 0x6edfffff */
    .xword (0x6ee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6ee00000 - 0x6effffff --> PA: 0x6ee00000 - 0x6effffff */
    .xword (0x6f000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6f000000 - 0x6f1fffff --> PA: 0x6f000000 - 0x6f1fffff */
    .xword (0x6f200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6f200000 - 0x6f3fffff --> PA: 0x6f200000 - 0x6f3fffff */
    .xword (0x6f400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6f400000 - 0x6f5fffff --> PA: 0x6f400000 - 0x6f5fffff */
    .xword (0x6f600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6f600000 - 0x6f7fffff --> PA: 0x6f600000 - 0x6f7fffff */
    .xword (0x6f800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6f800000 - 0x6f9fffff --> PA: 0x6f800000 - 0x6f9fffff */
    .xword (0x6fa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6fa00000 - 0x6fbfffff --> PA: 0x6fa00000 - 0x6fbfffff */
    .xword (0x6fc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6fc00000 - 0x6fdfffff --> PA: 0x6fc00000 - 0x6fdfffff */
    .xword (0x6fe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x6fe00000 - 0x6fffffff --> PA: 0x6fe00000 - 0x6fffffff */
    .xword (0x70000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x70000000 - 0x701fffff --> PA: 0x70000000 - 0x701fffff */
    .xword (0x70200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x70200000 - 0x703fffff --> PA: 0x70200000 - 0x703fffff */
    .xword (0x70400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x70400000 - 0x705fffff --> PA: 0x70400000 - 0x705fffff */
    .xword (0x70600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x70600000 - 0x707fffff --> PA: 0x70600000 - 0x707fffff */
    .xword (0x70800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x70800000 - 0x709fffff --> PA: 0x70800000 - 0x709fffff */
    .xword (0x70a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x70a00000 - 0x70bfffff --> PA: 0x70a00000 - 0x70bfffff */
    .xword (0x70c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x70c00000 - 0x70dfffff --> PA: 0x70c00000 - 0x70dfffff */
    .xword (0x70e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x70e00000 - 0x70ffffff --> PA: 0x70e00000 - 0x70ffffff */
    .xword (0x71000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x71000000 - 0x711fffff --> PA: 0x71000000 - 0x711fffff */
    .xword (0x71200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x71200000 - 0x713fffff --> PA: 0x71200000 - 0x713fffff */
    .xword (0x71400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x71400000 - 0x715fffff --> PA: 0x71400000 - 0x715fffff */
    .xword (0x71600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x71600000 - 0x717fffff --> PA: 0x71600000 - 0x717fffff */
    .xword (0x71800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x71800000 - 0x719fffff --> PA: 0x71800000 - 0x719fffff */
    .xword (0x71a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x71a00000 - 0x71bfffff --> PA: 0x71a00000 - 0x71bfffff */
    .xword (0x71c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x71c00000 - 0x71dfffff --> PA: 0x71c00000 - 0x71dfffff */
    .xword (0x71e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x71e00000 - 0x71ffffff --> PA: 0x71e00000 - 0x71ffffff */
    .xword (0x72000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x72000000 - 0x721fffff --> PA: 0x72000000 - 0x721fffff */
    .xword (0x72200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x72200000 - 0x723fffff --> PA: 0x72200000 - 0x723fffff */
    .xword (0x72400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x72400000 - 0x725fffff --> PA: 0x72400000 - 0x725fffff */
    .xword (0x72600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x72600000 - 0x727fffff --> PA: 0x72600000 - 0x727fffff */
    .xword (0x72800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x72800000 - 0x729fffff --> PA: 0x72800000 - 0x729fffff */
    .xword (0x72a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x72a00000 - 0x72bfffff --> PA: 0x72a00000 - 0x72bfffff */
    .xword (0x72c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x72c00000 - 0x72dfffff --> PA: 0x72c00000 - 0x72dfffff */
    .xword (0x72e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x72e00000 - 0x72ffffff --> PA: 0x72e00000 - 0x72ffffff */
    .xword (0x73000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x73000000 - 0x731fffff --> PA: 0x73000000 - 0x731fffff */
    .xword (0x73200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x73200000 - 0x733fffff --> PA: 0x73200000 - 0x733fffff */
    .xword (0x73400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x73400000 - 0x735fffff --> PA: 0x73400000 - 0x735fffff */
    .xword (0x73600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x73600000 - 0x737fffff --> PA: 0x73600000 - 0x737fffff */
    .xword (0x73800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x73800000 - 0x739fffff --> PA: 0x73800000 - 0x739fffff */
    .xword (0x73a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x73a00000 - 0x73bfffff --> PA: 0x73a00000 - 0x73bfffff */
    .xword (0x73c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x73c00000 - 0x73dfffff --> PA: 0x73c00000 - 0x73dfffff */
    .xword (0x73e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x73e00000 - 0x73ffffff --> PA: 0x73e00000 - 0x73ffffff */
    .xword (0x74000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x74000000 - 0x741fffff --> PA: 0x74000000 - 0x741fffff */
    .xword (0x74200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x74200000 - 0x743fffff --> PA: 0x74200000 - 0x743fffff */
    .xword (0x74400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x74400000 - 0x745fffff --> PA: 0x74400000 - 0x745fffff */
    .xword (0x74600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x74600000 - 0x747fffff --> PA: 0x74600000 - 0x747fffff */
    .xword (0x74800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x74800000 - 0x749fffff --> PA: 0x74800000 - 0x749fffff */
    .xword (0x74a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x74a00000 - 0x74bfffff --> PA: 0x74a00000 - 0x74bfffff */
    .xword (0x74c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x74c00000 - 0x74dfffff --> PA: 0x74c00000 - 0x74dfffff */
    .xword (0x74e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x74e00000 - 0x74ffffff --> PA: 0x74e00000 - 0x74ffffff */
    .xword (0x75000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x75000000 - 0x751fffff --> PA: 0x75000000 - 0x751fffff */
    .xword (0x75200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x75200000 - 0x753fffff --> PA: 0x75200000 - 0x753fffff */
    .xword (0x75400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x75400000 - 0x755fffff --> PA: 0x75400000 - 0x755fffff */
    .xword (0x75600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x75600000 - 0x757fffff --> PA: 0x75600000 - 0x757fffff */
    .xword (0x75800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x75800000 - 0x759fffff --> PA: 0x75800000 - 0x759fffff */
    .xword (0x75a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x75a00000 - 0x75bfffff --> PA: 0x75a00000 - 0x75bfffff */
    .xword (0x75c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x75c00000 - 0x75dfffff --> PA: 0x75c00000 - 0x75dfffff */
    .xword (0x75e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x75e00000 - 0x75ffffff --> PA: 0x75e00000 - 0x75ffffff */
    .xword (0x76000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x76000000 - 0x761fffff --> PA: 0x76000000 - 0x761fffff */
    .xword (0x76200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x76200000 - 0x763fffff --> PA: 0x76200000 - 0x763fffff */
    .xword (0x76400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x76400000 - 0x765fffff --> PA: 0x76400000 - 0x765fffff */
    .xword (0x76600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x76600000 - 0x767fffff --> PA: 0x76600000 - 0x767fffff */
    .xword (0x76800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x76800000 - 0x769fffff --> PA: 0x76800000 - 0x769fffff */
    .xword (0x76a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x76a00000 - 0x76bfffff --> PA: 0x76a00000 - 0x76bfffff */
    .xword (0x76c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x76c00000 - 0x76dfffff --> PA: 0x76c00000 - 0x76dfffff */
    .xword (0x76e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x76e00000 - 0x76ffffff --> PA: 0x76e00000 - 0x76ffffff */
    .xword (0x77000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x77000000 - 0x771fffff --> PA: 0x77000000 - 0x771fffff */
    .xword (0x77200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x77200000 - 0x773fffff --> PA: 0x77200000 - 0x773fffff */
    .xword (0x77400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x77400000 - 0x775fffff --> PA: 0x77400000 - 0x775fffff */
    .xword (0x77600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x77600000 - 0x777fffff --> PA: 0x77600000 - 0x777fffff */
    .xword (0x77800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x77800000 - 0x779fffff --> PA: 0x77800000 - 0x779fffff */
    .xword (0x77a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x77a00000 - 0x77bfffff --> PA: 0x77a00000 - 0x77bfffff */
    .xword (0x77c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x77c00000 - 0x77dfffff --> PA: 0x77c00000 - 0x77dfffff */
    .xword (0x77e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x77e00000 - 0x77ffffff --> PA: 0x77e00000 - 0x77ffffff */
    .xword (0x78000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x78000000 - 0x781fffff --> PA: 0x78000000 - 0x781fffff */
    .xword (0x78200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x78200000 - 0x783fffff --> PA: 0x78200000 - 0x783fffff */
    .xword (0x78400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x78400000 - 0x785fffff --> PA: 0x78400000 - 0x785fffff */
    .xword (0x78600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x78600000 - 0x787fffff --> PA: 0x78600000 - 0x787fffff */
    .xword (0x78800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x78800000 - 0x789fffff --> PA: 0x78800000 - 0x789fffff */
    .xword (0x78a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x78a00000 - 0x78bfffff --> PA: 0x78a00000 - 0x78bfffff */
    .xword (0x78c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x78c00000 - 0x78dfffff --> PA: 0x78c00000 - 0x78dfffff */
    .xword (0x78e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x78e00000 - 0x78ffffff --> PA: 0x78e00000 - 0x78ffffff */
    .xword (0x79000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x79000000 - 0x791fffff --> PA: 0x79000000 - 0x791fffff */
    .xword (0x79200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x79200000 - 0x793fffff --> PA: 0x79200000 - 0x793fffff */
    .xword (0x79400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x79400000 - 0x795fffff --> PA: 0x79400000 - 0x795fffff */
    .xword (0x79600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x79600000 - 0x797fffff --> PA: 0x79600000 - 0x797fffff */
    .xword (0x79800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x79800000 - 0x799fffff --> PA: 0x79800000 - 0x799fffff */
    .xword (0x79a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x79a00000 - 0x79bfffff --> PA: 0x79a00000 - 0x79bfffff */
    .xword (0x79c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x79c00000 - 0x79dfffff --> PA: 0x79c00000 - 0x79dfffff */
    .xword (0x79e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x79e00000 - 0x79ffffff --> PA: 0x79e00000 - 0x79ffffff */
    .xword (0x7a000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7a000000 - 0x7a1fffff --> PA: 0x7a000000 - 0x7a1fffff */
    .xword (0x7a200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7a200000 - 0x7a3fffff --> PA: 0x7a200000 - 0x7a3fffff */
    .xword (0x7a400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7a400000 - 0x7a5fffff --> PA: 0x7a400000 - 0x7a5fffff */
    .xword (0x7a600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7a600000 - 0x7a7fffff --> PA: 0x7a600000 - 0x7a7fffff */
    .xword (0x7a800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7a800000 - 0x7a9fffff --> PA: 0x7a800000 - 0x7a9fffff */
    .xword (0x7aa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7aa00000 - 0x7abfffff --> PA: 0x7aa00000 - 0x7abfffff */
    .xword (0x7ac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7ac00000 - 0x7adfffff --> PA: 0x7ac00000 - 0x7adfffff */
    .xword (0x7ae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7ae00000 - 0x7affffff --> PA: 0x7ae00000 - 0x7affffff */
    .xword (0x7b000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7b000000 - 0x7b1fffff --> PA: 0x7b000000 - 0x7b1fffff */
    .xword (0x7b200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7b200000 - 0x7b3fffff --> PA: 0x7b200000 - 0x7b3fffff */
    .xword (0x7b400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7b400000 - 0x7b5fffff --> PA: 0x7b400000 - 0x7b5fffff */
    .xword (0x7b600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7b600000 - 0x7b7fffff --> PA: 0x7b600000 - 0x7b7fffff */
    .xword (0x7b800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7b800000 - 0x7b9fffff --> PA: 0x7b800000 - 0x7b9fffff */
    .xword (0x7ba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7ba00000 - 0x7bbfffff --> PA: 0x7ba00000 - 0x7bbfffff */
    .xword (0x7bc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7bc00000 - 0x7bdfffff --> PA: 0x7bc00000 - 0x7bdfffff */
    .xword (0x7be00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7be00000 - 0x7bffffff --> PA: 0x7be00000 - 0x7bffffff */
    .xword (0x7c000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7c000000 - 0x7c1fffff --> PA: 0x7c000000 - 0x7c1fffff */
    .xword (0x7c200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7c200000 - 0x7c3fffff --> PA: 0x7c200000 - 0x7c3fffff */
    .xword (0x7c400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7c400000 - 0x7c5fffff --> PA: 0x7c400000 - 0x7c5fffff */
    .xword (0x7c600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7c600000 - 0x7c7fffff --> PA: 0x7c600000 - 0x7c7fffff */
    .xword (0x7c800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7c800000 - 0x7c9fffff --> PA: 0x7c800000 - 0x7c9fffff */
    .xword (0x7ca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7ca00000 - 0x7cbfffff --> PA: 0x7ca00000 - 0x7cbfffff */
    .xword (0x7cc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7cc00000 - 0x7cdfffff --> PA: 0x7cc00000 - 0x7cdfffff */
    .xword (0x7ce00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7ce00000 - 0x7cffffff --> PA: 0x7ce00000 - 0x7cffffff */
    .xword (0x7d000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7d000000 - 0x7d1fffff --> PA: 0x7d000000 - 0x7d1fffff */
    .xword (0x7d200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7d200000 - 0x7d3fffff --> PA: 0x7d200000 - 0x7d3fffff */
    .xword (0x7d400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7d400000 - 0x7d5fffff --> PA: 0x7d400000 - 0x7d5fffff */
    .xword (0x7d600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7d600000 - 0x7d7fffff --> PA: 0x7d600000 - 0x7d7fffff */
    .xword (0x7d800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7d800000 - 0x7d9fffff --> PA: 0x7d800000 - 0x7d9fffff */
    .xword (0x7da00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7da00000 - 0x7dbfffff --> PA: 0x7da00000 - 0x7dbfffff */
    .xword (0x7dc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7dc00000 - 0x7ddfffff --> PA: 0x7dc00000 - 0x7ddfffff */
    .xword (0x7de00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7de00000 - 0x7dffffff --> PA: 0x7de00000 - 0x7dffffff */
    .xword (0x7e000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7e000000 - 0x7e1fffff --> PA: 0x7e000000 - 0x7e1fffff */
    .xword (0x7e200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7e200000 - 0x7e3fffff --> PA: 0x7e200000 - 0x7e3fffff */
    .xword (0x7e400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7e400000 - 0x7e5fffff --> PA: 0x7e400000 - 0x7e5fffff */
    .xword (0x7e600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7e600000 - 0x7e7fffff --> PA: 0x7e600000 - 0x7e7fffff */
    .xword (0x7e800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7e800000 - 0x7e9fffff --> PA: 0x7e800000 - 0x7e9fffff */
    .xword (0x7ea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7ea00000 - 0x7ebfffff --> PA: 0x7ea00000 - 0x7ebfffff */
    .xword (0x7ec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7ec00000 - 0x7edfffff --> PA: 0x7ec00000 - 0x7edfffff */
    .xword (0x7ee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7ee00000 - 0x7effffff --> PA: 0x7ee00000 - 0x7effffff */
    .xword (0x7f000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7f000000 - 0x7f1fffff --> PA: 0x7f000000 - 0x7f1fffff */
    .xword (0x7f200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7f200000 - 0x7f3fffff --> PA: 0x7f200000 - 0x7f3fffff */
    .xword (0x7f400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7f400000 - 0x7f5fffff --> PA: 0x7f400000 - 0x7f5fffff */
    .xword (0x7f600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7f600000 - 0x7f7fffff --> PA: 0x7f600000 - 0x7f7fffff */
    .xword (0x7f800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7f800000 - 0x7f9fffff --> PA: 0x7f800000 - 0x7f9fffff */
    .xword (0x7fa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7fa00000 - 0x7fbfffff --> PA: 0x7fa00000 - 0x7fbfffff */
    .xword (0x7fc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7fc00000 - 0x7fdfffff --> PA: 0x7fc00000 - 0x7fdfffff */
    .xword (0x7fe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0x7fe00000 - 0x7fffffff --> PA: 0x7fe00000 - 0x7fffffff */

.size mmu_level2_translation_table_1, .-mmu_level2_translation_table_1


.section .rodata
.align 12
.globl mmu_level2_translation_table_2
mmu_level2_translation_table_2:
    .xword (0x80000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x80000000 - 0x801fffff --> PA: 0x80000000 - 0x801fffff */
    .xword (0x80200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x80200000 - 0x803fffff --> PA: 0x80200000 - 0x803fffff */
    .xword (0x80400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x80400000 - 0x805fffff --> PA: 0x80400000 - 0x805fffff */
    .xword (0x80600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x80600000 - 0x807fffff --> PA: 0x80600000 - 0x807fffff */
    .xword (0x80800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x80800000 - 0x809fffff --> PA: 0x80800000 - 0x809fffff */
    .xword (0x80a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x80a00000 - 0x80bfffff --> PA: 0x80a00000 - 0x80bfffff */
    .xword (0x80c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x80c00000 - 0x80dfffff --> PA: 0x80c00000 - 0x80dfffff */
    .xword (0x80e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x80e00000 - 0x80ffffff --> PA: 0x80e00000 - 0x80ffffff */
    .xword (0x81000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x81000000 - 0x811fffff --> PA: 0x81000000 - 0x811fffff */
    .xword (0x81200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x81200000 - 0x813fffff --> PA: 0x81200000 - 0x813fffff */
    .xword (0x81400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x81400000 - 0x815fffff --> PA: 0x81400000 - 0x815fffff */
    .xword (0x81600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x81600000 - 0x817fffff --> PA: 0x81600000 - 0x817fffff */
    .xword (0x81800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x81800000 - 0x819fffff --> PA: 0x81800000 - 0x819fffff */
    .xword (0x81a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x81a00000 - 0x81bfffff --> PA: 0x81a00000 - 0x81bfffff */
    .xword (0x81c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x81c00000 - 0x81dfffff --> PA: 0x81c00000 - 0x81dfffff */
    .xword (0x81e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x81e00000 - 0x81ffffff --> PA: 0x81e00000 - 0x81ffffff */
    .xword (0x82000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x82000000 - 0x821fffff --> PA: 0x82000000 - 0x821fffff */
    .xword (0x82200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x82200000 - 0x823fffff --> PA: 0x82200000 - 0x823fffff */
    .xword (0x82400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x82400000 - 0x825fffff --> PA: 0x82400000 - 0x825fffff */
    .xword (0x82600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x82600000 - 0x827fffff --> PA: 0x82600000 - 0x827fffff */
    .xword (0x82800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x82800000 - 0x829fffff --> PA: 0x82800000 - 0x829fffff */
    .xword (0x82a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x82a00000 - 0x82bfffff --> PA: 0x82a00000 - 0x82bfffff */
    .xword (0x82c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x82c00000 - 0x82dfffff --> PA: 0x82c00000 - 0x82dfffff */
    .xword (0x82e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x82e00000 - 0x82ffffff --> PA: 0x82e00000 - 0x82ffffff */
    .xword (0x83000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x83000000 - 0x831fffff --> PA: 0x83000000 - 0x831fffff */
    .xword (0x83200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x83200000 - 0x833fffff --> PA: 0x83200000 - 0x833fffff */
    .xword (0x83400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x83400000 - 0x835fffff --> PA: 0x83400000 - 0x835fffff */
    .xword (0x83600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x83600000 - 0x837fffff --> PA: 0x83600000 - 0x837fffff */
    .xword (0x83800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x83800000 - 0x839fffff --> PA: 0x83800000 - 0x839fffff */
    .xword (0x83a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x83a00000 - 0x83bfffff --> PA: 0x83a00000 - 0x83bfffff */
    .xword (0x83c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x83c00000 - 0x83dfffff --> PA: 0x83c00000 - 0x83dfffff */
    .xword (0x83e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x83e00000 - 0x83ffffff --> PA: 0x83e00000 - 0x83ffffff */
    .xword (0x84000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x84000000 - 0x841fffff --> PA: 0x84000000 - 0x841fffff */
    .xword (0x84200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x84200000 - 0x843fffff --> PA: 0x84200000 - 0x843fffff */
    .xword (0x84400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x84400000 - 0x845fffff --> PA: 0x84400000 - 0x845fffff */
    .xword (0x84600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x84600000 - 0x847fffff --> PA: 0x84600000 - 0x847fffff */
    .xword (0x84800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x84800000 - 0x849fffff --> PA: 0x84800000 - 0x849fffff */
    .xword (0x84a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x84a00000 - 0x84bfffff --> PA: 0x84a00000 - 0x84bfffff */
    .xword (0x84c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x84c00000 - 0x84dfffff --> PA: 0x84c00000 - 0x84dfffff */
    .xword (0x84e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x84e00000 - 0x84ffffff --> PA: 0x84e00000 - 0x84ffffff */
    .xword (0x85000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x85000000 - 0x851fffff --> PA: 0x85000000 - 0x851fffff */
    .xword (0x85200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x85200000 - 0x853fffff --> PA: 0x85200000 - 0x853fffff */
    .xword (0x85400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x85400000 - 0x855fffff --> PA: 0x85400000 - 0x855fffff */
    .xword (0x85600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x85600000 - 0x857fffff --> PA: 0x85600000 - 0x857fffff */
    .xword (0x85800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x85800000 - 0x859fffff --> PA: 0x85800000 - 0x859fffff */
    .xword (0x85a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x85a00000 - 0x85bfffff --> PA: 0x85a00000 - 0x85bfffff */
    .xword (0x85c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x85c00000 - 0x85dfffff --> PA: 0x85c00000 - 0x85dfffff */
    .xword (0x85e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x85e00000 - 0x85ffffff --> PA: 0x85e00000 - 0x85ffffff */
    .xword (0x86000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x86000000 - 0x861fffff --> PA: 0x86000000 - 0x861fffff */
    .xword (0x86200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x86200000 - 0x863fffff --> PA: 0x86200000 - 0x863fffff */
    .xword (0x86400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x86400000 - 0x865fffff --> PA: 0x86400000 - 0x865fffff */
    .xword (0x86600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x86600000 - 0x867fffff --> PA: 0x86600000 - 0x867fffff */
    .xword (0x86800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x86800000 - 0x869fffff --> PA: 0x86800000 - 0x869fffff */
    .xword (0x86a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x86a00000 - 0x86bfffff --> PA: 0x86a00000 - 0x86bfffff */
    .xword (0x86c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x86c00000 - 0x86dfffff --> PA: 0x86c00000 - 0x86dfffff */
    .xword (0x86e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x86e00000 - 0x86ffffff --> PA: 0x86e00000 - 0x86ffffff */
    .xword (0x87000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x87000000 - 0x871fffff --> PA: 0x87000000 - 0x871fffff */
    .xword (0x87200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x87200000 - 0x873fffff --> PA: 0x87200000 - 0x873fffff */
    .xword (0x87400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x87400000 - 0x875fffff --> PA: 0x87400000 - 0x875fffff */
    .xword (0x87600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x87600000 - 0x877fffff --> PA: 0x87600000 - 0x877fffff */
    .xword (0x87800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x87800000 - 0x879fffff --> PA: 0x87800000 - 0x879fffff */
    .xword (0x87a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x87a00000 - 0x87bfffff --> PA: 0x87a00000 - 0x87bfffff */
    .xword (0x87c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x87c00000 - 0x87dfffff --> PA: 0x87c00000 - 0x87dfffff */
    .xword (0x87e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x87e00000 - 0x87ffffff --> PA: 0x87e00000 - 0x87ffffff */
    .xword (0x88000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x88000000 - 0x881fffff --> PA: 0x88000000 - 0x881fffff */
    .xword (0x88200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x88200000 - 0x883fffff --> PA: 0x88200000 - 0x883fffff */
    .xword (0x88400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x88400000 - 0x885fffff --> PA: 0x88400000 - 0x885fffff */
    .xword (0x88600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x88600000 - 0x887fffff --> PA: 0x88600000 - 0x887fffff */
    .xword (0x88800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x88800000 - 0x889fffff --> PA: 0x88800000 - 0x889fffff */
    .xword (0x88a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x88a00000 - 0x88bfffff --> PA: 0x88a00000 - 0x88bfffff */
    .xword (0x88c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x88c00000 - 0x88dfffff --> PA: 0x88c00000 - 0x88dfffff */
    .xword (0x88e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x88e00000 - 0x88ffffff --> PA: 0x88e00000 - 0x88ffffff */
    .xword (0x89000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x89000000 - 0x891fffff --> PA: 0x89000000 - 0x891fffff */
    .xword (0x89200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x89200000 - 0x893fffff --> PA: 0x89200000 - 0x893fffff */
    .xword (0x89400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x89400000 - 0x895fffff --> PA: 0x89400000 - 0x895fffff */
    .xword (0x89600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x89600000 - 0x897fffff --> PA: 0x89600000 - 0x897fffff */
    .xword (0x89800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x89800000 - 0x899fffff --> PA: 0x89800000 - 0x899fffff */
    .xword (0x89a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x89a00000 - 0x89bfffff --> PA: 0x89a00000 - 0x89bfffff */
    .xword (0x89c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x89c00000 - 0x89dfffff --> PA: 0x89c00000 - 0x89dfffff */
    .xword (0x89e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x89e00000 - 0x89ffffff --> PA: 0x89e00000 - 0x89ffffff */
    .xword (0x8a000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8a000000 - 0x8a1fffff --> PA: 0x8a000000 - 0x8a1fffff */
    .xword (0x8a200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8a200000 - 0x8a3fffff --> PA: 0x8a200000 - 0x8a3fffff */
    .xword (0x8a400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8a400000 - 0x8a5fffff --> PA: 0x8a400000 - 0x8a5fffff */
    .xword (0x8a600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8a600000 - 0x8a7fffff --> PA: 0x8a600000 - 0x8a7fffff */
    .xword (0x8a800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8a800000 - 0x8a9fffff --> PA: 0x8a800000 - 0x8a9fffff */
    .xword (0x8aa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8aa00000 - 0x8abfffff --> PA: 0x8aa00000 - 0x8abfffff */
    .xword (0x8ac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8ac00000 - 0x8adfffff --> PA: 0x8ac00000 - 0x8adfffff */
    .xword (0x8ae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8ae00000 - 0x8affffff --> PA: 0x8ae00000 - 0x8affffff */
    .xword (0x8b000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8b000000 - 0x8b1fffff --> PA: 0x8b000000 - 0x8b1fffff */
    .xword (0x8b200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8b200000 - 0x8b3fffff --> PA: 0x8b200000 - 0x8b3fffff */
    .xword (0x8b400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8b400000 - 0x8b5fffff --> PA: 0x8b400000 - 0x8b5fffff */
    .xword (0x8b600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8b600000 - 0x8b7fffff --> PA: 0x8b600000 - 0x8b7fffff */
    .xword (0x8b800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8b800000 - 0x8b9fffff --> PA: 0x8b800000 - 0x8b9fffff */
    .xword (0x8ba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8ba00000 - 0x8bbfffff --> PA: 0x8ba00000 - 0x8bbfffff */
    .xword (0x8bc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8bc00000 - 0x8bdfffff --> PA: 0x8bc00000 - 0x8bdfffff */
    .xword (0x8be00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8be00000 - 0x8bffffff --> PA: 0x8be00000 - 0x8bffffff */
    .xword (0x8c000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8c000000 - 0x8c1fffff --> PA: 0x8c000000 - 0x8c1fffff */
    .xword (0x8c200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8c200000 - 0x8c3fffff --> PA: 0x8c200000 - 0x8c3fffff */
    .xword (0x8c400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8c400000 - 0x8c5fffff --> PA: 0x8c400000 - 0x8c5fffff */
    .xword (0x8c600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8c600000 - 0x8c7fffff --> PA: 0x8c600000 - 0x8c7fffff */
    .xword (0x8c800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8c800000 - 0x8c9fffff --> PA: 0x8c800000 - 0x8c9fffff */
    .xword (0x8ca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8ca00000 - 0x8cbfffff --> PA: 0x8ca00000 - 0x8cbfffff */
    .xword (0x8cc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8cc00000 - 0x8cdfffff --> PA: 0x8cc00000 - 0x8cdfffff */
    .xword (0x8ce00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8ce00000 - 0x8cffffff --> PA: 0x8ce00000 - 0x8cffffff */
    .xword (0x8d000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8d000000 - 0x8d1fffff --> PA: 0x8d000000 - 0x8d1fffff */
    .xword (0x8d200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8d200000 - 0x8d3fffff --> PA: 0x8d200000 - 0x8d3fffff */
    .xword (0x8d400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8d400000 - 0x8d5fffff --> PA: 0x8d400000 - 0x8d5fffff */
    .xword (0x8d600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8d600000 - 0x8d7fffff --> PA: 0x8d600000 - 0x8d7fffff */
    .xword (0x8d800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8d800000 - 0x8d9fffff --> PA: 0x8d800000 - 0x8d9fffff */
    .xword (0x8da00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8da00000 - 0x8dbfffff --> PA: 0x8da00000 - 0x8dbfffff */
    .xword (0x8dc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8dc00000 - 0x8ddfffff --> PA: 0x8dc00000 - 0x8ddfffff */
    .xword (0x8de00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8de00000 - 0x8dffffff --> PA: 0x8de00000 - 0x8dffffff */
    .xword (0x8e000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8e000000 - 0x8e1fffff --> PA: 0x8e000000 - 0x8e1fffff */
    .xword (0x8e200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8e200000 - 0x8e3fffff --> PA: 0x8e200000 - 0x8e3fffff */
    .xword (0x8e400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8e400000 - 0x8e5fffff --> PA: 0x8e400000 - 0x8e5fffff */
    .xword (0x8e600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8e600000 - 0x8e7fffff --> PA: 0x8e600000 - 0x8e7fffff */
    .xword (0x8e800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8e800000 - 0x8e9fffff --> PA: 0x8e800000 - 0x8e9fffff */
    .xword (0x8ea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8ea00000 - 0x8ebfffff --> PA: 0x8ea00000 - 0x8ebfffff */
    .xword (0x8ec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8ec00000 - 0x8edfffff --> PA: 0x8ec00000 - 0x8edfffff */
    .xword (0x8ee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8ee00000 - 0x8effffff --> PA: 0x8ee00000 - 0x8effffff */
    .xword (0x8f000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8f000000 - 0x8f1fffff --> PA: 0x8f000000 - 0x8f1fffff */
    .xword (0x8f200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8f200000 - 0x8f3fffff --> PA: 0x8f200000 - 0x8f3fffff */
    .xword (0x8f400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8f400000 - 0x8f5fffff --> PA: 0x8f400000 - 0x8f5fffff */
    .xword (0x8f600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8f600000 - 0x8f7fffff --> PA: 0x8f600000 - 0x8f7fffff */
    .xword (0x8f800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8f800000 - 0x8f9fffff --> PA: 0x8f800000 - 0x8f9fffff */
    .xword (0x8fa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8fa00000 - 0x8fbfffff --> PA: 0x8fa00000 - 0x8fbfffff */
    .xword (0x8fc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8fc00000 - 0x8fdfffff --> PA: 0x8fc00000 - 0x8fdfffff */
    .xword (0x8fe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x8fe00000 - 0x8fffffff --> PA: 0x8fe00000 - 0x8fffffff */
    .xword (0x90000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x90000000 - 0x901fffff --> PA: 0x90000000 - 0x901fffff */
    .xword (0x90200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x90200000 - 0x903fffff --> PA: 0x90200000 - 0x903fffff */
    .xword (0x90400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x90400000 - 0x905fffff --> PA: 0x90400000 - 0x905fffff */
    .xword (0x90600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x90600000 - 0x907fffff --> PA: 0x90600000 - 0x907fffff */
    .xword (0x90800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x90800000 - 0x909fffff --> PA: 0x90800000 - 0x909fffff */
    .xword (0x90a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x90a00000 - 0x90bfffff --> PA: 0x90a00000 - 0x90bfffff */
    .xword (0x90c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x90c00000 - 0x90dfffff --> PA: 0x90c00000 - 0x90dfffff */
    .xword (0x90e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x90e00000 - 0x90ffffff --> PA: 0x90e00000 - 0x90ffffff */
    .xword (0x91000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x91000000 - 0x911fffff --> PA: 0x91000000 - 0x911fffff */
    .xword (0x91200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x91200000 - 0x913fffff --> PA: 0x91200000 - 0x913fffff */
    .xword (0x91400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x91400000 - 0x915fffff --> PA: 0x91400000 - 0x915fffff */
    .xword (0x91600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x91600000 - 0x917fffff --> PA: 0x91600000 - 0x917fffff */
    .xword (0x91800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x91800000 - 0x919fffff --> PA: 0x91800000 - 0x919fffff */
    .xword (0x91a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x91a00000 - 0x91bfffff --> PA: 0x91a00000 - 0x91bfffff */
    .xword (0x91c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x91c00000 - 0x91dfffff --> PA: 0x91c00000 - 0x91dfffff */
    .xword (0x91e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x91e00000 - 0x91ffffff --> PA: 0x91e00000 - 0x91ffffff */
    .xword (0x92000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x92000000 - 0x921fffff --> PA: 0x92000000 - 0x921fffff */
    .xword (0x92200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x92200000 - 0x923fffff --> PA: 0x92200000 - 0x923fffff */
    .xword (0x92400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x92400000 - 0x925fffff --> PA: 0x92400000 - 0x925fffff */
    .xword (0x92600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x92600000 - 0x927fffff --> PA: 0x92600000 - 0x927fffff */
    .xword (0x92800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x92800000 - 0x929fffff --> PA: 0x92800000 - 0x929fffff */
    .xword (0x92a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x92a00000 - 0x92bfffff --> PA: 0x92a00000 - 0x92bfffff */
    .xword (0x92c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x92c00000 - 0x92dfffff --> PA: 0x92c00000 - 0x92dfffff */
    .xword (0x92e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x92e00000 - 0x92ffffff --> PA: 0x92e00000 - 0x92ffffff */
    .xword (0x93000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x93000000 - 0x931fffff --> PA: 0x93000000 - 0x931fffff */
    .xword (0x93200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x93200000 - 0x933fffff --> PA: 0x93200000 - 0x933fffff */
    .xword (0x93400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x93400000 - 0x935fffff --> PA: 0x93400000 - 0x935fffff */
    .xword (0x93600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x93600000 - 0x937fffff --> PA: 0x93600000 - 0x937fffff */
    .xword (0x93800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x93800000 - 0x939fffff --> PA: 0x93800000 - 0x939fffff */
    .xword (0x93a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x93a00000 - 0x93bfffff --> PA: 0x93a00000 - 0x93bfffff */
    .xword (0x93c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x93c00000 - 0x93dfffff --> PA: 0x93c00000 - 0x93dfffff */
    .xword (0x93e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x93e00000 - 0x93ffffff --> PA: 0x93e00000 - 0x93ffffff */
    .xword (0x94000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x94000000 - 0x941fffff --> PA: 0x94000000 - 0x941fffff */
    .xword (0x94200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x94200000 - 0x943fffff --> PA: 0x94200000 - 0x943fffff */
    .xword (0x94400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x94400000 - 0x945fffff --> PA: 0x94400000 - 0x945fffff */
    .xword (0x94600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x94600000 - 0x947fffff --> PA: 0x94600000 - 0x947fffff */
    .xword (0x94800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x94800000 - 0x949fffff --> PA: 0x94800000 - 0x949fffff */
    .xword (0x94a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x94a00000 - 0x94bfffff --> PA: 0x94a00000 - 0x94bfffff */
    .xword (0x94c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x94c00000 - 0x94dfffff --> PA: 0x94c00000 - 0x94dfffff */
    .xword (0x94e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x94e00000 - 0x94ffffff --> PA: 0x94e00000 - 0x94ffffff */
    .xword (0x95000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x95000000 - 0x951fffff --> PA: 0x95000000 - 0x951fffff */
    .xword (0x95200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x95200000 - 0x953fffff --> PA: 0x95200000 - 0x953fffff */
    .xword (0x95400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x95400000 - 0x955fffff --> PA: 0x95400000 - 0x955fffff */
    .xword (0x95600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x95600000 - 0x957fffff --> PA: 0x95600000 - 0x957fffff */
    .xword (0x95800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x95800000 - 0x959fffff --> PA: 0x95800000 - 0x959fffff */
    .xword (0x95a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x95a00000 - 0x95bfffff --> PA: 0x95a00000 - 0x95bfffff */
    .xword (0x95c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x95c00000 - 0x95dfffff --> PA: 0x95c00000 - 0x95dfffff */
    .xword (0x95e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x95e00000 - 0x95ffffff --> PA: 0x95e00000 - 0x95ffffff */
    .xword (0x96000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x96000000 - 0x961fffff --> PA: 0x96000000 - 0x961fffff */
    .xword (0x96200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x96200000 - 0x963fffff --> PA: 0x96200000 - 0x963fffff */
    .xword (0x96400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x96400000 - 0x965fffff --> PA: 0x96400000 - 0x965fffff */
    .xword (0x96600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x96600000 - 0x967fffff --> PA: 0x96600000 - 0x967fffff */
    .xword (0x96800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x96800000 - 0x969fffff --> PA: 0x96800000 - 0x969fffff */
    .xword (0x96a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x96a00000 - 0x96bfffff --> PA: 0x96a00000 - 0x96bfffff */
    .xword (0x96c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x96c00000 - 0x96dfffff --> PA: 0x96c00000 - 0x96dfffff */
    .xword (0x96e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x96e00000 - 0x96ffffff --> PA: 0x96e00000 - 0x96ffffff */
    .xword (0x97000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x97000000 - 0x971fffff --> PA: 0x97000000 - 0x971fffff */
    .xword (0x97200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x97200000 - 0x973fffff --> PA: 0x97200000 - 0x973fffff */
    .xword (0x97400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x97400000 - 0x975fffff --> PA: 0x97400000 - 0x975fffff */
    .xword (0x97600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x97600000 - 0x977fffff --> PA: 0x97600000 - 0x977fffff */
    .xword (0x97800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x97800000 - 0x979fffff --> PA: 0x97800000 - 0x979fffff */
    .xword (0x97a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x97a00000 - 0x97bfffff --> PA: 0x97a00000 - 0x97bfffff */
    .xword (0x97c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x97c00000 - 0x97dfffff --> PA: 0x97c00000 - 0x97dfffff */
    .xword (0x97e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x97e00000 - 0x97ffffff --> PA: 0x97e00000 - 0x97ffffff */
    .xword (0x98000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x98000000 - 0x981fffff --> PA: 0x98000000 - 0x981fffff */
    .xword (0x98200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x98200000 - 0x983fffff --> PA: 0x98200000 - 0x983fffff */
    .xword (0x98400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x98400000 - 0x985fffff --> PA: 0x98400000 - 0x985fffff */
    .xword (0x98600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x98600000 - 0x987fffff --> PA: 0x98600000 - 0x987fffff */
    .xword (0x98800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x98800000 - 0x989fffff --> PA: 0x98800000 - 0x989fffff */
    .xword (0x98a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x98a00000 - 0x98bfffff --> PA: 0x98a00000 - 0x98bfffff */
    .xword (0x98c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x98c00000 - 0x98dfffff --> PA: 0x98c00000 - 0x98dfffff */
    .xword (0x98e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x98e00000 - 0x98ffffff --> PA: 0x98e00000 - 0x98ffffff */
    .xword (0x99000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x99000000 - 0x991fffff --> PA: 0x99000000 - 0x991fffff */
    .xword (0x99200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x99200000 - 0x993fffff --> PA: 0x99200000 - 0x993fffff */
    .xword (0x99400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x99400000 - 0x995fffff --> PA: 0x99400000 - 0x995fffff */
    .xword (0x99600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x99600000 - 0x997fffff --> PA: 0x99600000 - 0x997fffff */
    .xword (0x99800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x99800000 - 0x999fffff --> PA: 0x99800000 - 0x999fffff */
    .xword (0x99a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x99a00000 - 0x99bfffff --> PA: 0x99a00000 - 0x99bfffff */
    .xword (0x99c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x99c00000 - 0x99dfffff --> PA: 0x99c00000 - 0x99dfffff */
    .xword (0x99e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x99e00000 - 0x99ffffff --> PA: 0x99e00000 - 0x99ffffff */
    .xword (0x9a000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9a000000 - 0x9a1fffff --> PA: 0x9a000000 - 0x9a1fffff */
    .xword (0x9a200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9a200000 - 0x9a3fffff --> PA: 0x9a200000 - 0x9a3fffff */
    .xword (0x9a400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9a400000 - 0x9a5fffff --> PA: 0x9a400000 - 0x9a5fffff */
    .xword (0x9a600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9a600000 - 0x9a7fffff --> PA: 0x9a600000 - 0x9a7fffff */
    .xword (0x9a800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9a800000 - 0x9a9fffff --> PA: 0x9a800000 - 0x9a9fffff */
    .xword (0x9aa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9aa00000 - 0x9abfffff --> PA: 0x9aa00000 - 0x9abfffff */
    .xword (0x9ac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9ac00000 - 0x9adfffff --> PA: 0x9ac00000 - 0x9adfffff */
    .xword (0x9ae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9ae00000 - 0x9affffff --> PA: 0x9ae00000 - 0x9affffff */
    .xword (0x9b000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9b000000 - 0x9b1fffff --> PA: 0x9b000000 - 0x9b1fffff */
    .xword (0x9b200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9b200000 - 0x9b3fffff --> PA: 0x9b200000 - 0x9b3fffff */
    .xword (0x9b400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9b400000 - 0x9b5fffff --> PA: 0x9b400000 - 0x9b5fffff */
    .xword (0x9b600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9b600000 - 0x9b7fffff --> PA: 0x9b600000 - 0x9b7fffff */
    .xword (0x9b800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9b800000 - 0x9b9fffff --> PA: 0x9b800000 - 0x9b9fffff */
    .xword (0x9ba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9ba00000 - 0x9bbfffff --> PA: 0x9ba00000 - 0x9bbfffff */
    .xword (0x9bc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9bc00000 - 0x9bdfffff --> PA: 0x9bc00000 - 0x9bdfffff */
    .xword (0x9be00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9be00000 - 0x9bffffff --> PA: 0x9be00000 - 0x9bffffff */
    .xword (0x9c000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9c000000 - 0x9c1fffff --> PA: 0x9c000000 - 0x9c1fffff */
    .xword (0x9c200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9c200000 - 0x9c3fffff --> PA: 0x9c200000 - 0x9c3fffff */
    .xword (0x9c400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9c400000 - 0x9c5fffff --> PA: 0x9c400000 - 0x9c5fffff */
    .xword (0x9c600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9c600000 - 0x9c7fffff --> PA: 0x9c600000 - 0x9c7fffff */
    .xword (0x9c800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9c800000 - 0x9c9fffff --> PA: 0x9c800000 - 0x9c9fffff */
    .xword (0x9ca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9ca00000 - 0x9cbfffff --> PA: 0x9ca00000 - 0x9cbfffff */
    .xword (0x9cc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9cc00000 - 0x9cdfffff --> PA: 0x9cc00000 - 0x9cdfffff */
    .xword (0x9ce00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9ce00000 - 0x9cffffff --> PA: 0x9ce00000 - 0x9cffffff */
    .xword (0x9d000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9d000000 - 0x9d1fffff --> PA: 0x9d000000 - 0x9d1fffff */
    .xword (0x9d200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9d200000 - 0x9d3fffff --> PA: 0x9d200000 - 0x9d3fffff */
    .xword (0x9d400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9d400000 - 0x9d5fffff --> PA: 0x9d400000 - 0x9d5fffff */
    .xword (0x9d600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9d600000 - 0x9d7fffff --> PA: 0x9d600000 - 0x9d7fffff */
    .xword (0x9d800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9d800000 - 0x9d9fffff --> PA: 0x9d800000 - 0x9d9fffff */
    .xword (0x9da00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9da00000 - 0x9dbfffff --> PA: 0x9da00000 - 0x9dbfffff */
    .xword (0x9dc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9dc00000 - 0x9ddfffff --> PA: 0x9dc00000 - 0x9ddfffff */
    .xword (0x9de00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9de00000 - 0x9dffffff --> PA: 0x9de00000 - 0x9dffffff */
    .xword (0x9e000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9e000000 - 0x9e1fffff --> PA: 0x9e000000 - 0x9e1fffff */
    .xword (0x9e200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9e200000 - 0x9e3fffff --> PA: 0x9e200000 - 0x9e3fffff */
    .xword (0x9e400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9e400000 - 0x9e5fffff --> PA: 0x9e400000 - 0x9e5fffff */
    .xword (0x9e600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9e600000 - 0x9e7fffff --> PA: 0x9e600000 - 0x9e7fffff */
    .xword (0x9e800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9e800000 - 0x9e9fffff --> PA: 0x9e800000 - 0x9e9fffff */
    .xword (0x9ea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9ea00000 - 0x9ebfffff --> PA: 0x9ea00000 - 0x9ebfffff */
    .xword (0x9ec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9ec00000 - 0x9edfffff --> PA: 0x9ec00000 - 0x9edfffff */
    .xword (0x9ee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9ee00000 - 0x9effffff --> PA: 0x9ee00000 - 0x9effffff */
    .xword (0x9f000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9f000000 - 0x9f1fffff --> PA: 0x9f000000 - 0x9f1fffff */
    .xword (0x9f200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9f200000 - 0x9f3fffff --> PA: 0x9f200000 - 0x9f3fffff */
    .xword (0x9f400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9f400000 - 0x9f5fffff --> PA: 0x9f400000 - 0x9f5fffff */
    .xword (0x9f600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9f600000 - 0x9f7fffff --> PA: 0x9f600000 - 0x9f7fffff */
    .xword (0x9f800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9f800000 - 0x9f9fffff --> PA: 0x9f800000 - 0x9f9fffff */
    .xword (0x9fa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9fa00000 - 0x9fbfffff --> PA: 0x9fa00000 - 0x9fbfffff */
    .xword (0x9fc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9fc00000 - 0x9fdfffff --> PA: 0x9fc00000 - 0x9fdfffff */
    .xword (0x9fe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0x9fe00000 - 0x9fffffff --> PA: 0x9fe00000 - 0x9fffffff */
    .xword (0xa0000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa0000000 - 0xa01fffff --> PA: 0xa0000000 - 0xa01fffff */
    .xword (0xa0200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa0200000 - 0xa03fffff --> PA: 0xa0200000 - 0xa03fffff */
    .xword (0xa0400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa0400000 - 0xa05fffff --> PA: 0xa0400000 - 0xa05fffff */
    .xword (0xa0600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa0600000 - 0xa07fffff --> PA: 0xa0600000 - 0xa07fffff */
    .xword (0xa0800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa0800000 - 0xa09fffff --> PA: 0xa0800000 - 0xa09fffff */
    .xword (0xa0a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa0a00000 - 0xa0bfffff --> PA: 0xa0a00000 - 0xa0bfffff */
    .xword (0xa0c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa0c00000 - 0xa0dfffff --> PA: 0xa0c00000 - 0xa0dfffff */
    .xword (0xa0e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa0e00000 - 0xa0ffffff --> PA: 0xa0e00000 - 0xa0ffffff */
    .xword (0xa1000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa1000000 - 0xa11fffff --> PA: 0xa1000000 - 0xa11fffff */
    .xword (0xa1200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa1200000 - 0xa13fffff --> PA: 0xa1200000 - 0xa13fffff */
    .xword (0xa1400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa1400000 - 0xa15fffff --> PA: 0xa1400000 - 0xa15fffff */
    .xword (0xa1600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa1600000 - 0xa17fffff --> PA: 0xa1600000 - 0xa17fffff */
    .xword (0xa1800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa1800000 - 0xa19fffff --> PA: 0xa1800000 - 0xa19fffff */
    .xword (0xa1a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa1a00000 - 0xa1bfffff --> PA: 0xa1a00000 - 0xa1bfffff */
    .xword (0xa1c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa1c00000 - 0xa1dfffff --> PA: 0xa1c00000 - 0xa1dfffff */
    .xword (0xa1e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa1e00000 - 0xa1ffffff --> PA: 0xa1e00000 - 0xa1ffffff */
    .xword (0xa2000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa2000000 - 0xa21fffff --> PA: 0xa2000000 - 0xa21fffff */
    .xword (0xa2200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa2200000 - 0xa23fffff --> PA: 0xa2200000 - 0xa23fffff */
    .xword (0xa2400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa2400000 - 0xa25fffff --> PA: 0xa2400000 - 0xa25fffff */
    .xword (0xa2600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa2600000 - 0xa27fffff --> PA: 0xa2600000 - 0xa27fffff */
    .xword (0xa2800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa2800000 - 0xa29fffff --> PA: 0xa2800000 - 0xa29fffff */
    .xword (0xa2a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa2a00000 - 0xa2bfffff --> PA: 0xa2a00000 - 0xa2bfffff */
    .xword (0xa2c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa2c00000 - 0xa2dfffff --> PA: 0xa2c00000 - 0xa2dfffff */
    .xword (0xa2e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa2e00000 - 0xa2ffffff --> PA: 0xa2e00000 - 0xa2ffffff */
    .xword (0xa3000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa3000000 - 0xa31fffff --> PA: 0xa3000000 - 0xa31fffff */
    .xword (0xa3200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa3200000 - 0xa33fffff --> PA: 0xa3200000 - 0xa33fffff */
    .xword (0xa3400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa3400000 - 0xa35fffff --> PA: 0xa3400000 - 0xa35fffff */
    .xword (0xa3600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa3600000 - 0xa37fffff --> PA: 0xa3600000 - 0xa37fffff */
    .xword (0xa3800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa3800000 - 0xa39fffff --> PA: 0xa3800000 - 0xa39fffff */
    .xword (0xa3a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa3a00000 - 0xa3bfffff --> PA: 0xa3a00000 - 0xa3bfffff */
    .xword (0xa3c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa3c00000 - 0xa3dfffff --> PA: 0xa3c00000 - 0xa3dfffff */
    .xword (0xa3e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa3e00000 - 0xa3ffffff --> PA: 0xa3e00000 - 0xa3ffffff */
    .xword (0xa4000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa4000000 - 0xa41fffff --> PA: 0xa4000000 - 0xa41fffff */
    .xword (0xa4200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa4200000 - 0xa43fffff --> PA: 0xa4200000 - 0xa43fffff */
    .xword (0xa4400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa4400000 - 0xa45fffff --> PA: 0xa4400000 - 0xa45fffff */
    .xword (0xa4600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa4600000 - 0xa47fffff --> PA: 0xa4600000 - 0xa47fffff */
    .xword (0xa4800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa4800000 - 0xa49fffff --> PA: 0xa4800000 - 0xa49fffff */
    .xword (0xa4a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa4a00000 - 0xa4bfffff --> PA: 0xa4a00000 - 0xa4bfffff */
    .xword (0xa4c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa4c00000 - 0xa4dfffff --> PA: 0xa4c00000 - 0xa4dfffff */
    .xword (0xa4e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa4e00000 - 0xa4ffffff --> PA: 0xa4e00000 - 0xa4ffffff */
    .xword (0xa5000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa5000000 - 0xa51fffff --> PA: 0xa5000000 - 0xa51fffff */
    .xword (0xa5200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa5200000 - 0xa53fffff --> PA: 0xa5200000 - 0xa53fffff */
    .xword (0xa5400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa5400000 - 0xa55fffff --> PA: 0xa5400000 - 0xa55fffff */
    .xword (0xa5600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa5600000 - 0xa57fffff --> PA: 0xa5600000 - 0xa57fffff */
    .xword (0xa5800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa5800000 - 0xa59fffff --> PA: 0xa5800000 - 0xa59fffff */
    .xword (0xa5a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa5a00000 - 0xa5bfffff --> PA: 0xa5a00000 - 0xa5bfffff */
    .xword (0xa5c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa5c00000 - 0xa5dfffff --> PA: 0xa5c00000 - 0xa5dfffff */
    .xword (0xa5e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa5e00000 - 0xa5ffffff --> PA: 0xa5e00000 - 0xa5ffffff */
    .xword (0xa6000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa6000000 - 0xa61fffff --> PA: 0xa6000000 - 0xa61fffff */
    .xword (0xa6200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa6200000 - 0xa63fffff --> PA: 0xa6200000 - 0xa63fffff */
    .xword (0xa6400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa6400000 - 0xa65fffff --> PA: 0xa6400000 - 0xa65fffff */
    .xword (0xa6600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa6600000 - 0xa67fffff --> PA: 0xa6600000 - 0xa67fffff */
    .xword (0xa6800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa6800000 - 0xa69fffff --> PA: 0xa6800000 - 0xa69fffff */
    .xword (0xa6a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa6a00000 - 0xa6bfffff --> PA: 0xa6a00000 - 0xa6bfffff */
    .xword (0xa6c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa6c00000 - 0xa6dfffff --> PA: 0xa6c00000 - 0xa6dfffff */
    .xword (0xa6e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa6e00000 - 0xa6ffffff --> PA: 0xa6e00000 - 0xa6ffffff */
    .xword (0xa7000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa7000000 - 0xa71fffff --> PA: 0xa7000000 - 0xa71fffff */
    .xword (0xa7200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa7200000 - 0xa73fffff --> PA: 0xa7200000 - 0xa73fffff */
    .xword (0xa7400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa7400000 - 0xa75fffff --> PA: 0xa7400000 - 0xa75fffff */
    .xword (0xa7600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa7600000 - 0xa77fffff --> PA: 0xa7600000 - 0xa77fffff */
    .xword (0xa7800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa7800000 - 0xa79fffff --> PA: 0xa7800000 - 0xa79fffff */
    .xword (0xa7a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa7a00000 - 0xa7bfffff --> PA: 0xa7a00000 - 0xa7bfffff */
    .xword (0xa7c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa7c00000 - 0xa7dfffff --> PA: 0xa7c00000 - 0xa7dfffff */
    .xword (0xa7e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa7e00000 - 0xa7ffffff --> PA: 0xa7e00000 - 0xa7ffffff */
    .xword (0xa8000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa8000000 - 0xa81fffff --> PA: 0xa8000000 - 0xa81fffff */
    .xword (0xa8200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa8200000 - 0xa83fffff --> PA: 0xa8200000 - 0xa83fffff */
    .xword (0xa8400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa8400000 - 0xa85fffff --> PA: 0xa8400000 - 0xa85fffff */
    .xword (0xa8600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa8600000 - 0xa87fffff --> PA: 0xa8600000 - 0xa87fffff */
    .xword (0xa8800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa8800000 - 0xa89fffff --> PA: 0xa8800000 - 0xa89fffff */
    .xword (0xa8a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa8a00000 - 0xa8bfffff --> PA: 0xa8a00000 - 0xa8bfffff */
    .xword (0xa8c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa8c00000 - 0xa8dfffff --> PA: 0xa8c00000 - 0xa8dfffff */
    .xword (0xa8e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa8e00000 - 0xa8ffffff --> PA: 0xa8e00000 - 0xa8ffffff */
    .xword (0xa9000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa9000000 - 0xa91fffff --> PA: 0xa9000000 - 0xa91fffff */
    .xword (0xa9200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa9200000 - 0xa93fffff --> PA: 0xa9200000 - 0xa93fffff */
    .xword (0xa9400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa9400000 - 0xa95fffff --> PA: 0xa9400000 - 0xa95fffff */
    .xword (0xa9600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa9600000 - 0xa97fffff --> PA: 0xa9600000 - 0xa97fffff */
    .xword (0xa9800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa9800000 - 0xa99fffff --> PA: 0xa9800000 - 0xa99fffff */
    .xword (0xa9a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa9a00000 - 0xa9bfffff --> PA: 0xa9a00000 - 0xa9bfffff */
    .xword (0xa9c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa9c00000 - 0xa9dfffff --> PA: 0xa9c00000 - 0xa9dfffff */
    .xword (0xa9e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xa9e00000 - 0xa9ffffff --> PA: 0xa9e00000 - 0xa9ffffff */
    .xword (0xaa000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaa000000 - 0xaa1fffff --> PA: 0xaa000000 - 0xaa1fffff */
    .xword (0xaa200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaa200000 - 0xaa3fffff --> PA: 0xaa200000 - 0xaa3fffff */
    .xword (0xaa400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaa400000 - 0xaa5fffff --> PA: 0xaa400000 - 0xaa5fffff */
    .xword (0xaa600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaa600000 - 0xaa7fffff --> PA: 0xaa600000 - 0xaa7fffff */
    .xword (0xaa800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaa800000 - 0xaa9fffff --> PA: 0xaa800000 - 0xaa9fffff */
    .xword (0xaaa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaaa00000 - 0xaabfffff --> PA: 0xaaa00000 - 0xaabfffff */
    .xword (0xaac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaac00000 - 0xaadfffff --> PA: 0xaac00000 - 0xaadfffff */
    .xword (0xaae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaae00000 - 0xaaffffff --> PA: 0xaae00000 - 0xaaffffff */
    .xword (0xab000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xab000000 - 0xab1fffff --> PA: 0xab000000 - 0xab1fffff */
    .xword (0xab200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xab200000 - 0xab3fffff --> PA: 0xab200000 - 0xab3fffff */
    .xword (0xab400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xab400000 - 0xab5fffff --> PA: 0xab400000 - 0xab5fffff */
    .xword (0xab600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xab600000 - 0xab7fffff --> PA: 0xab600000 - 0xab7fffff */
    .xword (0xab800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xab800000 - 0xab9fffff --> PA: 0xab800000 - 0xab9fffff */
    .xword (0xaba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaba00000 - 0xabbfffff --> PA: 0xaba00000 - 0xabbfffff */
    .xword (0xabc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xabc00000 - 0xabdfffff --> PA: 0xabc00000 - 0xabdfffff */
    .xword (0xabe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xabe00000 - 0xabffffff --> PA: 0xabe00000 - 0xabffffff */
    .xword (0xac000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xac000000 - 0xac1fffff --> PA: 0xac000000 - 0xac1fffff */
    .xword (0xac200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xac200000 - 0xac3fffff --> PA: 0xac200000 - 0xac3fffff */
    .xword (0xac400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xac400000 - 0xac5fffff --> PA: 0xac400000 - 0xac5fffff */
    .xword (0xac600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xac600000 - 0xac7fffff --> PA: 0xac600000 - 0xac7fffff */
    .xword (0xac800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xac800000 - 0xac9fffff --> PA: 0xac800000 - 0xac9fffff */
    .xword (0xaca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaca00000 - 0xacbfffff --> PA: 0xaca00000 - 0xacbfffff */
    .xword (0xacc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xacc00000 - 0xacdfffff --> PA: 0xacc00000 - 0xacdfffff */
    .xword (0xace00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xace00000 - 0xacffffff --> PA: 0xace00000 - 0xacffffff */
    .xword (0xad000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xad000000 - 0xad1fffff --> PA: 0xad000000 - 0xad1fffff */
    .xword (0xad200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xad200000 - 0xad3fffff --> PA: 0xad200000 - 0xad3fffff */
    .xword (0xad400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xad400000 - 0xad5fffff --> PA: 0xad400000 - 0xad5fffff */
    .xword (0xad600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xad600000 - 0xad7fffff --> PA: 0xad600000 - 0xad7fffff */
    .xword (0xad800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xad800000 - 0xad9fffff --> PA: 0xad800000 - 0xad9fffff */
    .xword (0xada00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xada00000 - 0xadbfffff --> PA: 0xada00000 - 0xadbfffff */
    .xword (0xadc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xadc00000 - 0xaddfffff --> PA: 0xadc00000 - 0xaddfffff */
    .xword (0xade00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xade00000 - 0xadffffff --> PA: 0xade00000 - 0xadffffff */
    .xword (0xae000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xae000000 - 0xae1fffff --> PA: 0xae000000 - 0xae1fffff */
    .xword (0xae200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xae200000 - 0xae3fffff --> PA: 0xae200000 - 0xae3fffff */
    .xword (0xae400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xae400000 - 0xae5fffff --> PA: 0xae400000 - 0xae5fffff */
    .xword (0xae600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xae600000 - 0xae7fffff --> PA: 0xae600000 - 0xae7fffff */
    .xword (0xae800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xae800000 - 0xae9fffff --> PA: 0xae800000 - 0xae9fffff */
    .xword (0xaea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaea00000 - 0xaebfffff --> PA: 0xaea00000 - 0xaebfffff */
    .xword (0xaec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaec00000 - 0xaedfffff --> PA: 0xaec00000 - 0xaedfffff */
    .xword (0xaee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaee00000 - 0xaeffffff --> PA: 0xaee00000 - 0xaeffffff */
    .xword (0xaf000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaf000000 - 0xaf1fffff --> PA: 0xaf000000 - 0xaf1fffff */
    .xword (0xaf200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaf200000 - 0xaf3fffff --> PA: 0xaf200000 - 0xaf3fffff */
    .xword (0xaf400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaf400000 - 0xaf5fffff --> PA: 0xaf400000 - 0xaf5fffff */
    .xword (0xaf600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaf600000 - 0xaf7fffff --> PA: 0xaf600000 - 0xaf7fffff */
    .xword (0xaf800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xaf800000 - 0xaf9fffff --> PA: 0xaf800000 - 0xaf9fffff */
    .xword (0xafa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xafa00000 - 0xafbfffff --> PA: 0xafa00000 - 0xafbfffff */
    .xword (0xafc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xafc00000 - 0xafdfffff --> PA: 0xafc00000 - 0xafdfffff */
    .xword (0xafe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xafe00000 - 0xafffffff --> PA: 0xafe00000 - 0xafffffff */
    .xword (0xb0000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb0000000 - 0xb01fffff --> PA: 0xb0000000 - 0xb01fffff */
    .xword (0xb0200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb0200000 - 0xb03fffff --> PA: 0xb0200000 - 0xb03fffff */
    .xword (0xb0400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb0400000 - 0xb05fffff --> PA: 0xb0400000 - 0xb05fffff */
    .xword (0xb0600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb0600000 - 0xb07fffff --> PA: 0xb0600000 - 0xb07fffff */
    .xword (0xb0800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb0800000 - 0xb09fffff --> PA: 0xb0800000 - 0xb09fffff */
    .xword (0xb0a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb0a00000 - 0xb0bfffff --> PA: 0xb0a00000 - 0xb0bfffff */
    .xword (0xb0c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb0c00000 - 0xb0dfffff --> PA: 0xb0c00000 - 0xb0dfffff */
    .xword (0xb0e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb0e00000 - 0xb0ffffff --> PA: 0xb0e00000 - 0xb0ffffff */
    .xword (0xb1000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb1000000 - 0xb11fffff --> PA: 0xb1000000 - 0xb11fffff */
    .xword (0xb1200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb1200000 - 0xb13fffff --> PA: 0xb1200000 - 0xb13fffff */
    .xword (0xb1400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb1400000 - 0xb15fffff --> PA: 0xb1400000 - 0xb15fffff */
    .xword (0xb1600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb1600000 - 0xb17fffff --> PA: 0xb1600000 - 0xb17fffff */
    .xword (0xb1800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb1800000 - 0xb19fffff --> PA: 0xb1800000 - 0xb19fffff */
    .xword (0xb1a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb1a00000 - 0xb1bfffff --> PA: 0xb1a00000 - 0xb1bfffff */
    .xword (0xb1c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb1c00000 - 0xb1dfffff --> PA: 0xb1c00000 - 0xb1dfffff */
    .xword (0xb1e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb1e00000 - 0xb1ffffff --> PA: 0xb1e00000 - 0xb1ffffff */
    .xword (0xb2000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb2000000 - 0xb21fffff --> PA: 0xb2000000 - 0xb21fffff */
    .xword (0xb2200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb2200000 - 0xb23fffff --> PA: 0xb2200000 - 0xb23fffff */
    .xword (0xb2400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb2400000 - 0xb25fffff --> PA: 0xb2400000 - 0xb25fffff */
    .xword (0xb2600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb2600000 - 0xb27fffff --> PA: 0xb2600000 - 0xb27fffff */
    .xword (0xb2800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb2800000 - 0xb29fffff --> PA: 0xb2800000 - 0xb29fffff */
    .xword (0xb2a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb2a00000 - 0xb2bfffff --> PA: 0xb2a00000 - 0xb2bfffff */
    .xword (0xb2c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb2c00000 - 0xb2dfffff --> PA: 0xb2c00000 - 0xb2dfffff */
    .xword (0xb2e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb2e00000 - 0xb2ffffff --> PA: 0xb2e00000 - 0xb2ffffff */
    .xword (0xb3000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb3000000 - 0xb31fffff --> PA: 0xb3000000 - 0xb31fffff */
    .xword (0xb3200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb3200000 - 0xb33fffff --> PA: 0xb3200000 - 0xb33fffff */
    .xword (0xb3400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb3400000 - 0xb35fffff --> PA: 0xb3400000 - 0xb35fffff */
    .xword (0xb3600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb3600000 - 0xb37fffff --> PA: 0xb3600000 - 0xb37fffff */
    .xword (0xb3800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb3800000 - 0xb39fffff --> PA: 0xb3800000 - 0xb39fffff */
    .xword (0xb3a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb3a00000 - 0xb3bfffff --> PA: 0xb3a00000 - 0xb3bfffff */
    .xword (0xb3c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb3c00000 - 0xb3dfffff --> PA: 0xb3c00000 - 0xb3dfffff */
    .xword (0xb3e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb3e00000 - 0xb3ffffff --> PA: 0xb3e00000 - 0xb3ffffff */
    .xword (0xb4000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb4000000 - 0xb41fffff --> PA: 0xb4000000 - 0xb41fffff */
    .xword (0xb4200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb4200000 - 0xb43fffff --> PA: 0xb4200000 - 0xb43fffff */
    .xword (0xb4400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb4400000 - 0xb45fffff --> PA: 0xb4400000 - 0xb45fffff */
    .xword (0xb4600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb4600000 - 0xb47fffff --> PA: 0xb4600000 - 0xb47fffff */
    .xword (0xb4800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb4800000 - 0xb49fffff --> PA: 0xb4800000 - 0xb49fffff */
    .xword (0xb4a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb4a00000 - 0xb4bfffff --> PA: 0xb4a00000 - 0xb4bfffff */
    .xword (0xb4c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb4c00000 - 0xb4dfffff --> PA: 0xb4c00000 - 0xb4dfffff */
    .xword (0xb4e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb4e00000 - 0xb4ffffff --> PA: 0xb4e00000 - 0xb4ffffff */
    .xword (0xb5000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb5000000 - 0xb51fffff --> PA: 0xb5000000 - 0xb51fffff */
    .xword (0xb5200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb5200000 - 0xb53fffff --> PA: 0xb5200000 - 0xb53fffff */
    .xword (0xb5400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb5400000 - 0xb55fffff --> PA: 0xb5400000 - 0xb55fffff */
    .xword (0xb5600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb5600000 - 0xb57fffff --> PA: 0xb5600000 - 0xb57fffff */
    .xword (0xb5800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb5800000 - 0xb59fffff --> PA: 0xb5800000 - 0xb59fffff */
    .xword (0xb5a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb5a00000 - 0xb5bfffff --> PA: 0xb5a00000 - 0xb5bfffff */
    .xword (0xb5c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb5c00000 - 0xb5dfffff --> PA: 0xb5c00000 - 0xb5dfffff */
    .xword (0xb5e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb5e00000 - 0xb5ffffff --> PA: 0xb5e00000 - 0xb5ffffff */
    .xword (0xb6000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb6000000 - 0xb61fffff --> PA: 0xb6000000 - 0xb61fffff */
    .xword (0xb6200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb6200000 - 0xb63fffff --> PA: 0xb6200000 - 0xb63fffff */
    .xword (0xb6400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb6400000 - 0xb65fffff --> PA: 0xb6400000 - 0xb65fffff */
    .xword (0xb6600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb6600000 - 0xb67fffff --> PA: 0xb6600000 - 0xb67fffff */
    .xword (0xb6800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb6800000 - 0xb69fffff --> PA: 0xb6800000 - 0xb69fffff */
    .xword (0xb6a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb6a00000 - 0xb6bfffff --> PA: 0xb6a00000 - 0xb6bfffff */
    .xword (0xb6c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb6c00000 - 0xb6dfffff --> PA: 0xb6c00000 - 0xb6dfffff */
    .xword (0xb6e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb6e00000 - 0xb6ffffff --> PA: 0xb6e00000 - 0xb6ffffff */
    .xword (0xb7000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb7000000 - 0xb71fffff --> PA: 0xb7000000 - 0xb71fffff */
    .xword (0xb7200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb7200000 - 0xb73fffff --> PA: 0xb7200000 - 0xb73fffff */
    .xword (0xb7400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb7400000 - 0xb75fffff --> PA: 0xb7400000 - 0xb75fffff */
    .xword (0xb7600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb7600000 - 0xb77fffff --> PA: 0xb7600000 - 0xb77fffff */
    .xword (0xb7800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb7800000 - 0xb79fffff --> PA: 0xb7800000 - 0xb79fffff */
    .xword (0xb7a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb7a00000 - 0xb7bfffff --> PA: 0xb7a00000 - 0xb7bfffff */
    .xword (0xb7c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb7c00000 - 0xb7dfffff --> PA: 0xb7c00000 - 0xb7dfffff */
    .xword (0xb7e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb7e00000 - 0xb7ffffff --> PA: 0xb7e00000 - 0xb7ffffff */
    .xword (0xb8000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb8000000 - 0xb81fffff --> PA: 0xb8000000 - 0xb81fffff */
    .xword (0xb8200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb8200000 - 0xb83fffff --> PA: 0xb8200000 - 0xb83fffff */
    .xword (0xb8400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb8400000 - 0xb85fffff --> PA: 0xb8400000 - 0xb85fffff */
    .xword (0xb8600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb8600000 - 0xb87fffff --> PA: 0xb8600000 - 0xb87fffff */
    .xword (0xb8800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb8800000 - 0xb89fffff --> PA: 0xb8800000 - 0xb89fffff */
    .xword (0xb8a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb8a00000 - 0xb8bfffff --> PA: 0xb8a00000 - 0xb8bfffff */
    .xword (0xb8c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb8c00000 - 0xb8dfffff --> PA: 0xb8c00000 - 0xb8dfffff */
    .xword (0xb8e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb8e00000 - 0xb8ffffff --> PA: 0xb8e00000 - 0xb8ffffff */
    .xword (0xb9000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb9000000 - 0xb91fffff --> PA: 0xb9000000 - 0xb91fffff */
    .xword (0xb9200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb9200000 - 0xb93fffff --> PA: 0xb9200000 - 0xb93fffff */
    .xword (0xb9400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb9400000 - 0xb95fffff --> PA: 0xb9400000 - 0xb95fffff */
    .xword (0xb9600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb9600000 - 0xb97fffff --> PA: 0xb9600000 - 0xb97fffff */
    .xword (0xb9800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb9800000 - 0xb99fffff --> PA: 0xb9800000 - 0xb99fffff */
    .xword (0xb9a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb9a00000 - 0xb9bfffff --> PA: 0xb9a00000 - 0xb9bfffff */
    .xword (0xb9c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb9c00000 - 0xb9dfffff --> PA: 0xb9c00000 - 0xb9dfffff */
    .xword (0xb9e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xb9e00000 - 0xb9ffffff --> PA: 0xb9e00000 - 0xb9ffffff */
    .xword (0xba000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xba000000 - 0xba1fffff --> PA: 0xba000000 - 0xba1fffff */
    .xword (0xba200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xba200000 - 0xba3fffff --> PA: 0xba200000 - 0xba3fffff */
    .xword (0xba400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xba400000 - 0xba5fffff --> PA: 0xba400000 - 0xba5fffff */
    .xword (0xba600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xba600000 - 0xba7fffff --> PA: 0xba600000 - 0xba7fffff */
    .xword (0xba800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xba800000 - 0xba9fffff --> PA: 0xba800000 - 0xba9fffff */
    .xword (0xbaa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbaa00000 - 0xbabfffff --> PA: 0xbaa00000 - 0xbabfffff */
    .xword (0xbac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbac00000 - 0xbadfffff --> PA: 0xbac00000 - 0xbadfffff */
    .xword (0xbae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbae00000 - 0xbaffffff --> PA: 0xbae00000 - 0xbaffffff */
    .xword (0xbb000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbb000000 - 0xbb1fffff --> PA: 0xbb000000 - 0xbb1fffff */
    .xword (0xbb200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbb200000 - 0xbb3fffff --> PA: 0xbb200000 - 0xbb3fffff */
    .xword (0xbb400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbb400000 - 0xbb5fffff --> PA: 0xbb400000 - 0xbb5fffff */
    .xword (0xbb600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbb600000 - 0xbb7fffff --> PA: 0xbb600000 - 0xbb7fffff */
    .xword (0xbb800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbb800000 - 0xbb9fffff --> PA: 0xbb800000 - 0xbb9fffff */
    .xword (0xbba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbba00000 - 0xbbbfffff --> PA: 0xbba00000 - 0xbbbfffff */
    .xword (0xbbc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbbc00000 - 0xbbdfffff --> PA: 0xbbc00000 - 0xbbdfffff */
    .xword (0xbbe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbbe00000 - 0xbbffffff --> PA: 0xbbe00000 - 0xbbffffff */
    .xword (0xbc000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbc000000 - 0xbc1fffff --> PA: 0xbc000000 - 0xbc1fffff */
    .xword (0xbc200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbc200000 - 0xbc3fffff --> PA: 0xbc200000 - 0xbc3fffff */
    .xword (0xbc400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbc400000 - 0xbc5fffff --> PA: 0xbc400000 - 0xbc5fffff */
    .xword (0xbc600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbc600000 - 0xbc7fffff --> PA: 0xbc600000 - 0xbc7fffff */
    .xword (0xbc800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbc800000 - 0xbc9fffff --> PA: 0xbc800000 - 0xbc9fffff */
    .xword (0xbca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbca00000 - 0xbcbfffff --> PA: 0xbca00000 - 0xbcbfffff */
    .xword (0xbcc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbcc00000 - 0xbcdfffff --> PA: 0xbcc00000 - 0xbcdfffff */
    .xword (0xbce00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbce00000 - 0xbcffffff --> PA: 0xbce00000 - 0xbcffffff */
    .xword (0xbd000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbd000000 - 0xbd1fffff --> PA: 0xbd000000 - 0xbd1fffff */
    .xword (0xbd200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbd200000 - 0xbd3fffff --> PA: 0xbd200000 - 0xbd3fffff */
    .xword (0xbd400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbd400000 - 0xbd5fffff --> PA: 0xbd400000 - 0xbd5fffff */
    .xword (0xbd600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbd600000 - 0xbd7fffff --> PA: 0xbd600000 - 0xbd7fffff */
    .xword (0xbd800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbd800000 - 0xbd9fffff --> PA: 0xbd800000 - 0xbd9fffff */
    .xword (0xbda00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbda00000 - 0xbdbfffff --> PA: 0xbda00000 - 0xbdbfffff */
    .xword (0xbdc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbdc00000 - 0xbddfffff --> PA: 0xbdc00000 - 0xbddfffff */
    .xword (0xbde00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbde00000 - 0xbdffffff --> PA: 0xbde00000 - 0xbdffffff */
    .xword (0xbe000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbe000000 - 0xbe1fffff --> PA: 0xbe000000 - 0xbe1fffff */
    .xword (0xbe200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbe200000 - 0xbe3fffff --> PA: 0xbe200000 - 0xbe3fffff */
    .xword (0xbe400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbe400000 - 0xbe5fffff --> PA: 0xbe400000 - 0xbe5fffff */
    .xword (0xbe600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbe600000 - 0xbe7fffff --> PA: 0xbe600000 - 0xbe7fffff */
    .xword (0xbe800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbe800000 - 0xbe9fffff --> PA: 0xbe800000 - 0xbe9fffff */
    .xword (0xbea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbea00000 - 0xbebfffff --> PA: 0xbea00000 - 0xbebfffff */
    .xword (0xbec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbec00000 - 0xbedfffff --> PA: 0xbec00000 - 0xbedfffff */
    .xword (0xbee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbee00000 - 0xbeffffff --> PA: 0xbee00000 - 0xbeffffff */
    .xword (0xbf000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbf000000 - 0xbf1fffff --> PA: 0xbf000000 - 0xbf1fffff */
    .xword (0xbf200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbf200000 - 0xbf3fffff --> PA: 0xbf200000 - 0xbf3fffff */
    .xword (0xbf400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbf400000 - 0xbf5fffff --> PA: 0xbf400000 - 0xbf5fffff */
    .xword (0xbf600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbf600000 - 0xbf7fffff --> PA: 0xbf600000 - 0xbf7fffff */
    .xword (0xbf800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbf800000 - 0xbf9fffff --> PA: 0xbf800000 - 0xbf9fffff */
    .xword (0xbfa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbfa00000 - 0xbfbfffff --> PA: 0xbfa00000 - 0xbfbfffff */
    .xword (0xbfc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbfc00000 - 0xbfdfffff --> PA: 0xbfc00000 - 0xbfdfffff */
    .xword (0xbfe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x03 << 2) | 1) /* VA: 0xbfe00000 - 0xbfffffff --> PA: 0xbfe00000 - 0xbfffffff */

.size mmu_level2_translation_table_2, .-mmu_level2_translation_table_2


.section .rodata
.align 12
.globl mmu_level2_translation_table_3
mmu_level2_translation_table_3:
    .xword (0xc0000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc0000000 - 0xc01fffff --> PA: 0xc0000000 - 0xc01fffff */
    .xword (0xc0200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc0200000 - 0xc03fffff --> PA: 0xc0200000 - 0xc03fffff */
    .xword (0xc0400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc0400000 - 0xc05fffff --> PA: 0xc0400000 - 0xc05fffff */
    .xword (0xc0600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc0600000 - 0xc07fffff --> PA: 0xc0600000 - 0xc07fffff */
    .xword (0xc0800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc0800000 - 0xc09fffff --> PA: 0xc0800000 - 0xc09fffff */
    .xword (0xc0a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc0a00000 - 0xc0bfffff --> PA: 0xc0a00000 - 0xc0bfffff */
    .xword (0xc0c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc0c00000 - 0xc0dfffff --> PA: 0xc0c00000 - 0xc0dfffff */
    .xword (0xc0e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc0e00000 - 0xc0ffffff --> PA: 0xc0e00000 - 0xc0ffffff */
    .xword (0xc1000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc1000000 - 0xc11fffff --> PA: 0xc1000000 - 0xc11fffff */
    .xword (0xc1200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc1200000 - 0xc13fffff --> PA: 0xc1200000 - 0xc13fffff */
    .xword (0xc1400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc1400000 - 0xc15fffff --> PA: 0xc1400000 - 0xc15fffff */
    .xword (0xc1600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc1600000 - 0xc17fffff --> PA: 0xc1600000 - 0xc17fffff */
    .xword (0xc1800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc1800000 - 0xc19fffff --> PA: 0xc1800000 - 0xc19fffff */
    .xword (0xc1a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc1a00000 - 0xc1bfffff --> PA: 0xc1a00000 - 0xc1bfffff */
    .xword (0xc1c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc1c00000 - 0xc1dfffff --> PA: 0xc1c00000 - 0xc1dfffff */
    .xword (0xc1e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc1e00000 - 0xc1ffffff --> PA: 0xc1e00000 - 0xc1ffffff */
    .xword (0xc2000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc2000000 - 0xc21fffff --> PA: 0xc2000000 - 0xc21fffff */
    .xword (0xc2200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc2200000 - 0xc23fffff --> PA: 0xc2200000 - 0xc23fffff */
    .xword (0xc2400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc2400000 - 0xc25fffff --> PA: 0xc2400000 - 0xc25fffff */
    .xword (0xc2600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc2600000 - 0xc27fffff --> PA: 0xc2600000 - 0xc27fffff */
    .xword (0xc2800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc2800000 - 0xc29fffff --> PA: 0xc2800000 - 0xc29fffff */
    .xword (0xc2a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc2a00000 - 0xc2bfffff --> PA: 0xc2a00000 - 0xc2bfffff */
    .xword (0xc2c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc2c00000 - 0xc2dfffff --> PA: 0xc2c00000 - 0xc2dfffff */
    .xword (0xc2e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc2e00000 - 0xc2ffffff --> PA: 0xc2e00000 - 0xc2ffffff */
    .xword (0xc3000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc3000000 - 0xc31fffff --> PA: 0xc3000000 - 0xc31fffff */
    .xword (0xc3200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc3200000 - 0xc33fffff --> PA: 0xc3200000 - 0xc33fffff */
    .xword (0xc3400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc3400000 - 0xc35fffff --> PA: 0xc3400000 - 0xc35fffff */
    .xword (0xc3600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc3600000 - 0xc37fffff --> PA: 0xc3600000 - 0xc37fffff */
    .xword (0xc3800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc3800000 - 0xc39fffff --> PA: 0xc3800000 - 0xc39fffff */
    .xword (0xc3a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc3a00000 - 0xc3bfffff --> PA: 0xc3a00000 - 0xc3bfffff */
    .xword (0xc3c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc3c00000 - 0xc3dfffff --> PA: 0xc3c00000 - 0xc3dfffff */
    .xword (0xc3e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc3e00000 - 0xc3ffffff --> PA: 0xc3e00000 - 0xc3ffffff */
    .xword (0xc4000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc4000000 - 0xc41fffff --> PA: 0xc4000000 - 0xc41fffff */
    .xword (0xc4200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc4200000 - 0xc43fffff --> PA: 0xc4200000 - 0xc43fffff */
    .xword (0xc4400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc4400000 - 0xc45fffff --> PA: 0xc4400000 - 0xc45fffff */
    .xword (0xc4600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc4600000 - 0xc47fffff --> PA: 0xc4600000 - 0xc47fffff */
    .xword (0xc4800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc4800000 - 0xc49fffff --> PA: 0xc4800000 - 0xc49fffff */
    .xword (0xc4a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc4a00000 - 0xc4bfffff --> PA: 0xc4a00000 - 0xc4bfffff */
    .xword (0xc4c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc4c00000 - 0xc4dfffff --> PA: 0xc4c00000 - 0xc4dfffff */
    .xword (0xc4e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc4e00000 - 0xc4ffffff --> PA: 0xc4e00000 - 0xc4ffffff */
    .xword (0xc5000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc5000000 - 0xc51fffff --> PA: 0xc5000000 - 0xc51fffff */
    .xword (0xc5200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc5200000 - 0xc53fffff --> PA: 0xc5200000 - 0xc53fffff */
    .xword (0xc5400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc5400000 - 0xc55fffff --> PA: 0xc5400000 - 0xc55fffff */
    .xword (0xc5600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc5600000 - 0xc57fffff --> PA: 0xc5600000 - 0xc57fffff */
    .xword (0xc5800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc5800000 - 0xc59fffff --> PA: 0xc5800000 - 0xc59fffff */
    .xword (0xc5a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc5a00000 - 0xc5bfffff --> PA: 0xc5a00000 - 0xc5bfffff */
    .xword (0xc5c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc5c00000 - 0xc5dfffff --> PA: 0xc5c00000 - 0xc5dfffff */
    .xword (0xc5e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc5e00000 - 0xc5ffffff --> PA: 0xc5e00000 - 0xc5ffffff */
    .xword (0xc6000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc6000000 - 0xc61fffff --> PA: 0xc6000000 - 0xc61fffff */
    .xword (0xc6200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc6200000 - 0xc63fffff --> PA: 0xc6200000 - 0xc63fffff */
    .xword (0xc6400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc6400000 - 0xc65fffff --> PA: 0xc6400000 - 0xc65fffff */
    .xword (0xc6600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc6600000 - 0xc67fffff --> PA: 0xc6600000 - 0xc67fffff */
    .xword (0xc6800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc6800000 - 0xc69fffff --> PA: 0xc6800000 - 0xc69fffff */
    .xword (0xc6a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc6a00000 - 0xc6bfffff --> PA: 0xc6a00000 - 0xc6bfffff */
    .xword (0xc6c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc6c00000 - 0xc6dfffff --> PA: 0xc6c00000 - 0xc6dfffff */
    .xword (0xc6e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc6e00000 - 0xc6ffffff --> PA: 0xc6e00000 - 0xc6ffffff */
    .xword (0xc7000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc7000000 - 0xc71fffff --> PA: 0xc7000000 - 0xc71fffff */
    .xword (0xc7200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc7200000 - 0xc73fffff --> PA: 0xc7200000 - 0xc73fffff */
    .xword (0xc7400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc7400000 - 0xc75fffff --> PA: 0xc7400000 - 0xc75fffff */
    .xword (0xc7600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc7600000 - 0xc77fffff --> PA: 0xc7600000 - 0xc77fffff */
    .xword (0xc7800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc7800000 - 0xc79fffff --> PA: 0xc7800000 - 0xc79fffff */
    .xword (0xc7a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc7a00000 - 0xc7bfffff --> PA: 0xc7a00000 - 0xc7bfffff */
    .xword (0xc7c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc7c00000 - 0xc7dfffff --> PA: 0xc7c00000 - 0xc7dfffff */
    .xword (0xc7e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc7e00000 - 0xc7ffffff --> PA: 0xc7e00000 - 0xc7ffffff */
    .xword (0xc8000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc8000000 - 0xc81fffff --> PA: 0xc8000000 - 0xc81fffff */
    .xword (0xc8200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc8200000 - 0xc83fffff --> PA: 0xc8200000 - 0xc83fffff */
    .xword (0xc8400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc8400000 - 0xc85fffff --> PA: 0xc8400000 - 0xc85fffff */
    .xword (0xc8600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc8600000 - 0xc87fffff --> PA: 0xc8600000 - 0xc87fffff */
    .xword (0xc8800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc8800000 - 0xc89fffff --> PA: 0xc8800000 - 0xc89fffff */
    .xword (0xc8a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc8a00000 - 0xc8bfffff --> PA: 0xc8a00000 - 0xc8bfffff */
    .xword (0xc8c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc8c00000 - 0xc8dfffff --> PA: 0xc8c00000 - 0xc8dfffff */
    .xword (0xc8e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc8e00000 - 0xc8ffffff --> PA: 0xc8e00000 - 0xc8ffffff */
    .xword (0xc9000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc9000000 - 0xc91fffff --> PA: 0xc9000000 - 0xc91fffff */
    .xword (0xc9200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc9200000 - 0xc93fffff --> PA: 0xc9200000 - 0xc93fffff */
    .xword (0xc9400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc9400000 - 0xc95fffff --> PA: 0xc9400000 - 0xc95fffff */
    .xword (0xc9600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc9600000 - 0xc97fffff --> PA: 0xc9600000 - 0xc97fffff */
    .xword (0xc9800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc9800000 - 0xc99fffff --> PA: 0xc9800000 - 0xc99fffff */
    .xword (0xc9a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc9a00000 - 0xc9bfffff --> PA: 0xc9a00000 - 0xc9bfffff */
    .xword (0xc9c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc9c00000 - 0xc9dfffff --> PA: 0xc9c00000 - 0xc9dfffff */
    .xword (0xc9e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xc9e00000 - 0xc9ffffff --> PA: 0xc9e00000 - 0xc9ffffff */
    .xword (0xca000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xca000000 - 0xca1fffff --> PA: 0xca000000 - 0xca1fffff */
    .xword (0xca200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xca200000 - 0xca3fffff --> PA: 0xca200000 - 0xca3fffff */
    .xword (0xca400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xca400000 - 0xca5fffff --> PA: 0xca400000 - 0xca5fffff */
    .xword (0xca600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xca600000 - 0xca7fffff --> PA: 0xca600000 - 0xca7fffff */
    .xword (0xca800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xca800000 - 0xca9fffff --> PA: 0xca800000 - 0xca9fffff */
    .xword (0xcaa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcaa00000 - 0xcabfffff --> PA: 0xcaa00000 - 0xcabfffff */
    .xword (0xcac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcac00000 - 0xcadfffff --> PA: 0xcac00000 - 0xcadfffff */
    .xword (0xcae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcae00000 - 0xcaffffff --> PA: 0xcae00000 - 0xcaffffff */
    .xword (0xcb000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcb000000 - 0xcb1fffff --> PA: 0xcb000000 - 0xcb1fffff */
    .xword (0xcb200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcb200000 - 0xcb3fffff --> PA: 0xcb200000 - 0xcb3fffff */
    .xword (0xcb400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcb400000 - 0xcb5fffff --> PA: 0xcb400000 - 0xcb5fffff */
    .xword (0xcb600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcb600000 - 0xcb7fffff --> PA: 0xcb600000 - 0xcb7fffff */
    .xword (0xcb800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcb800000 - 0xcb9fffff --> PA: 0xcb800000 - 0xcb9fffff */
    .xword (0xcba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcba00000 - 0xcbbfffff --> PA: 0xcba00000 - 0xcbbfffff */
    .xword (0xcbc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcbc00000 - 0xcbdfffff --> PA: 0xcbc00000 - 0xcbdfffff */
    .xword (0xcbe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcbe00000 - 0xcbffffff --> PA: 0xcbe00000 - 0xcbffffff */
    .xword (0xcc000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcc000000 - 0xcc1fffff --> PA: 0xcc000000 - 0xcc1fffff */
    .xword (0xcc200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcc200000 - 0xcc3fffff --> PA: 0xcc200000 - 0xcc3fffff */
    .xword (0xcc400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcc400000 - 0xcc5fffff --> PA: 0xcc400000 - 0xcc5fffff */
    .xword (0xcc600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcc600000 - 0xcc7fffff --> PA: 0xcc600000 - 0xcc7fffff */
    .xword (0xcc800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcc800000 - 0xcc9fffff --> PA: 0xcc800000 - 0xcc9fffff */
    .xword (0xcca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcca00000 - 0xccbfffff --> PA: 0xcca00000 - 0xccbfffff */
    .xword (0xccc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xccc00000 - 0xccdfffff --> PA: 0xccc00000 - 0xccdfffff */
    .xword (0xcce00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcce00000 - 0xccffffff --> PA: 0xcce00000 - 0xccffffff */
    .xword (0xcd000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcd000000 - 0xcd1fffff --> PA: 0xcd000000 - 0xcd1fffff */
    .xword (0xcd200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcd200000 - 0xcd3fffff --> PA: 0xcd200000 - 0xcd3fffff */
    .xword (0xcd400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcd400000 - 0xcd5fffff --> PA: 0xcd400000 - 0xcd5fffff */
    .xword (0xcd600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcd600000 - 0xcd7fffff --> PA: 0xcd600000 - 0xcd7fffff */
    .xword (0xcd800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcd800000 - 0xcd9fffff --> PA: 0xcd800000 - 0xcd9fffff */
    .xword (0xcda00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcda00000 - 0xcdbfffff --> PA: 0xcda00000 - 0xcdbfffff */
    .xword (0xcdc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcdc00000 - 0xcddfffff --> PA: 0xcdc00000 - 0xcddfffff */
    .xword (0xcde00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcde00000 - 0xcdffffff --> PA: 0xcde00000 - 0xcdffffff */
    .xword (0xce000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xce000000 - 0xce1fffff --> PA: 0xce000000 - 0xce1fffff */
    .xword (0xce200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xce200000 - 0xce3fffff --> PA: 0xce200000 - 0xce3fffff */
    .xword (0xce400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xce400000 - 0xce5fffff --> PA: 0xce400000 - 0xce5fffff */
    .xword (0xce600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xce600000 - 0xce7fffff --> PA: 0xce600000 - 0xce7fffff */
    .xword (0xce800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xce800000 - 0xce9fffff --> PA: 0xce800000 - 0xce9fffff */
    .xword (0xcea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcea00000 - 0xcebfffff --> PA: 0xcea00000 - 0xcebfffff */
    .xword (0xcec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcec00000 - 0xcedfffff --> PA: 0xcec00000 - 0xcedfffff */
    .xword (0xcee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcee00000 - 0xceffffff --> PA: 0xcee00000 - 0xceffffff */
    .xword (0xcf000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcf000000 - 0xcf1fffff --> PA: 0xcf000000 - 0xcf1fffff */
    .xword (0xcf200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcf200000 - 0xcf3fffff --> PA: 0xcf200000 - 0xcf3fffff */
    .xword (0xcf400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcf400000 - 0xcf5fffff --> PA: 0xcf400000 - 0xcf5fffff */
    .xword (0xcf600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcf600000 - 0xcf7fffff --> PA: 0xcf600000 - 0xcf7fffff */
    .xword (0xcf800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcf800000 - 0xcf9fffff --> PA: 0xcf800000 - 0xcf9fffff */
    .xword (0xcfa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcfa00000 - 0xcfbfffff --> PA: 0xcfa00000 - 0xcfbfffff */
    .xword (0xcfc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcfc00000 - 0xcfdfffff --> PA: 0xcfc00000 - 0xcfdfffff */
    .xword (0xcfe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xcfe00000 - 0xcfffffff --> PA: 0xcfe00000 - 0xcfffffff */
    .xword (0xd0000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd0000000 - 0xd01fffff --> PA: 0xd0000000 - 0xd01fffff */
    .xword (0xd0200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd0200000 - 0xd03fffff --> PA: 0xd0200000 - 0xd03fffff */
    .xword (0xd0400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd0400000 - 0xd05fffff --> PA: 0xd0400000 - 0xd05fffff */
    .xword (0xd0600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd0600000 - 0xd07fffff --> PA: 0xd0600000 - 0xd07fffff */
    .xword (0xd0800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd0800000 - 0xd09fffff --> PA: 0xd0800000 - 0xd09fffff */
    .xword (0xd0a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd0a00000 - 0xd0bfffff --> PA: 0xd0a00000 - 0xd0bfffff */
    .xword (0xd0c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd0c00000 - 0xd0dfffff --> PA: 0xd0c00000 - 0xd0dfffff */
    .xword (0xd0e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd0e00000 - 0xd0ffffff --> PA: 0xd0e00000 - 0xd0ffffff */
    .xword (0xd1000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd1000000 - 0xd11fffff --> PA: 0xd1000000 - 0xd11fffff */
    .xword (0xd1200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd1200000 - 0xd13fffff --> PA: 0xd1200000 - 0xd13fffff */
    .xword (0xd1400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd1400000 - 0xd15fffff --> PA: 0xd1400000 - 0xd15fffff */
    .xword (0xd1600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd1600000 - 0xd17fffff --> PA: 0xd1600000 - 0xd17fffff */
    .xword (0xd1800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd1800000 - 0xd19fffff --> PA: 0xd1800000 - 0xd19fffff */
    .xword (0xd1a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd1a00000 - 0xd1bfffff --> PA: 0xd1a00000 - 0xd1bfffff */
    .xword (0xd1c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd1c00000 - 0xd1dfffff --> PA: 0xd1c00000 - 0xd1dfffff */
    .xword (0xd1e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd1e00000 - 0xd1ffffff --> PA: 0xd1e00000 - 0xd1ffffff */
    .xword (0xd2000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd2000000 - 0xd21fffff --> PA: 0xd2000000 - 0xd21fffff */
    .xword (0xd2200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd2200000 - 0xd23fffff --> PA: 0xd2200000 - 0xd23fffff */
    .xword (0xd2400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd2400000 - 0xd25fffff --> PA: 0xd2400000 - 0xd25fffff */
    .xword (0xd2600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd2600000 - 0xd27fffff --> PA: 0xd2600000 - 0xd27fffff */
    .xword (0xd2800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd2800000 - 0xd29fffff --> PA: 0xd2800000 - 0xd29fffff */
    .xword (0xd2a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd2a00000 - 0xd2bfffff --> PA: 0xd2a00000 - 0xd2bfffff */
    .xword (0xd2c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd2c00000 - 0xd2dfffff --> PA: 0xd2c00000 - 0xd2dfffff */
    .xword (0xd2e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd2e00000 - 0xd2ffffff --> PA: 0xd2e00000 - 0xd2ffffff */
    .xword (0xd3000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd3000000 - 0xd31fffff --> PA: 0xd3000000 - 0xd31fffff */
    .xword (0xd3200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd3200000 - 0xd33fffff --> PA: 0xd3200000 - 0xd33fffff */
    .xword (0xd3400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd3400000 - 0xd35fffff --> PA: 0xd3400000 - 0xd35fffff */
    .xword (0xd3600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd3600000 - 0xd37fffff --> PA: 0xd3600000 - 0xd37fffff */
    .xword (0xd3800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd3800000 - 0xd39fffff --> PA: 0xd3800000 - 0xd39fffff */
    .xword (0xd3a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd3a00000 - 0xd3bfffff --> PA: 0xd3a00000 - 0xd3bfffff */
    .xword (0xd3c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd3c00000 - 0xd3dfffff --> PA: 0xd3c00000 - 0xd3dfffff */
    .xword (0xd3e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd3e00000 - 0xd3ffffff --> PA: 0xd3e00000 - 0xd3ffffff */
    .xword (0xd4000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd4000000 - 0xd41fffff --> PA: 0xd4000000 - 0xd41fffff */
    .xword (0xd4200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd4200000 - 0xd43fffff --> PA: 0xd4200000 - 0xd43fffff */
    .xword (0xd4400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd4400000 - 0xd45fffff --> PA: 0xd4400000 - 0xd45fffff */
    .xword (0xd4600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd4600000 - 0xd47fffff --> PA: 0xd4600000 - 0xd47fffff */
    .xword (0xd4800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd4800000 - 0xd49fffff --> PA: 0xd4800000 - 0xd49fffff */
    .xword (0xd4a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd4a00000 - 0xd4bfffff --> PA: 0xd4a00000 - 0xd4bfffff */
    .xword (0xd4c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd4c00000 - 0xd4dfffff --> PA: 0xd4c00000 - 0xd4dfffff */
    .xword (0xd4e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd4e00000 - 0xd4ffffff --> PA: 0xd4e00000 - 0xd4ffffff */
    .xword (0xd5000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd5000000 - 0xd51fffff --> PA: 0xd5000000 - 0xd51fffff */
    .xword (0xd5200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd5200000 - 0xd53fffff --> PA: 0xd5200000 - 0xd53fffff */
    .xword (0xd5400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd5400000 - 0xd55fffff --> PA: 0xd5400000 - 0xd55fffff */
    .xword (0xd5600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd5600000 - 0xd57fffff --> PA: 0xd5600000 - 0xd57fffff */
    .xword (0xd5800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd5800000 - 0xd59fffff --> PA: 0xd5800000 - 0xd59fffff */
    .xword (0xd5a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd5a00000 - 0xd5bfffff --> PA: 0xd5a00000 - 0xd5bfffff */
    .xword (0xd5c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd5c00000 - 0xd5dfffff --> PA: 0xd5c00000 - 0xd5dfffff */
    .xword (0xd5e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd5e00000 - 0xd5ffffff --> PA: 0xd5e00000 - 0xd5ffffff */
    .xword (0xd6000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd6000000 - 0xd61fffff --> PA: 0xd6000000 - 0xd61fffff */
    .xword (0xd6200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd6200000 - 0xd63fffff --> PA: 0xd6200000 - 0xd63fffff */
    .xword (0xd6400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd6400000 - 0xd65fffff --> PA: 0xd6400000 - 0xd65fffff */
    .xword (0xd6600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd6600000 - 0xd67fffff --> PA: 0xd6600000 - 0xd67fffff */
    .xword (0xd6800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd6800000 - 0xd69fffff --> PA: 0xd6800000 - 0xd69fffff */
    .xword (0xd6a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd6a00000 - 0xd6bfffff --> PA: 0xd6a00000 - 0xd6bfffff */
    .xword (0xd6c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd6c00000 - 0xd6dfffff --> PA: 0xd6c00000 - 0xd6dfffff */
    .xword (0xd6e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd6e00000 - 0xd6ffffff --> PA: 0xd6e00000 - 0xd6ffffff */
    .xword (0xd7000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd7000000 - 0xd71fffff --> PA: 0xd7000000 - 0xd71fffff */
    .xword (0xd7200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd7200000 - 0xd73fffff --> PA: 0xd7200000 - 0xd73fffff */
    .xword (0xd7400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd7400000 - 0xd75fffff --> PA: 0xd7400000 - 0xd75fffff */
    .xword (0xd7600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd7600000 - 0xd77fffff --> PA: 0xd7600000 - 0xd77fffff */
    .xword (0xd7800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd7800000 - 0xd79fffff --> PA: 0xd7800000 - 0xd79fffff */
    .xword (0xd7a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd7a00000 - 0xd7bfffff --> PA: 0xd7a00000 - 0xd7bfffff */
    .xword (0xd7c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd7c00000 - 0xd7dfffff --> PA: 0xd7c00000 - 0xd7dfffff */
    .xword (0xd7e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd7e00000 - 0xd7ffffff --> PA: 0xd7e00000 - 0xd7ffffff */
    .xword (0xd8000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd8000000 - 0xd81fffff --> PA: 0xd8000000 - 0xd81fffff */
    .xword (0xd8200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd8200000 - 0xd83fffff --> PA: 0xd8200000 - 0xd83fffff */
    .xword (0xd8400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd8400000 - 0xd85fffff --> PA: 0xd8400000 - 0xd85fffff */
    .xword (0xd8600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd8600000 - 0xd87fffff --> PA: 0xd8600000 - 0xd87fffff */
    .xword (0xd8800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd8800000 - 0xd89fffff --> PA: 0xd8800000 - 0xd89fffff */
    .xword (0xd8a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd8a00000 - 0xd8bfffff --> PA: 0xd8a00000 - 0xd8bfffff */
    .xword (0xd8c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd8c00000 - 0xd8dfffff --> PA: 0xd8c00000 - 0xd8dfffff */
    .xword (0xd8e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd8e00000 - 0xd8ffffff --> PA: 0xd8e00000 - 0xd8ffffff */
    .xword (0xd9000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd9000000 - 0xd91fffff --> PA: 0xd9000000 - 0xd91fffff */
    .xword (0xd9200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd9200000 - 0xd93fffff --> PA: 0xd9200000 - 0xd93fffff */
    .xword (0xd9400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd9400000 - 0xd95fffff --> PA: 0xd9400000 - 0xd95fffff */
    .xword (0xd9600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd9600000 - 0xd97fffff --> PA: 0xd9600000 - 0xd97fffff */
    .xword (0xd9800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd9800000 - 0xd99fffff --> PA: 0xd9800000 - 0xd99fffff */
    .xword (0xd9a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd9a00000 - 0xd9bfffff --> PA: 0xd9a00000 - 0xd9bfffff */
    .xword (0xd9c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd9c00000 - 0xd9dfffff --> PA: 0xd9c00000 - 0xd9dfffff */
    .xword (0xd9e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xd9e00000 - 0xd9ffffff --> PA: 0xd9e00000 - 0xd9ffffff */
    .xword (0xda000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xda000000 - 0xda1fffff --> PA: 0xda000000 - 0xda1fffff */
    .xword (0xda200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xda200000 - 0xda3fffff --> PA: 0xda200000 - 0xda3fffff */
    .xword (0xda400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xda400000 - 0xda5fffff --> PA: 0xda400000 - 0xda5fffff */
    .xword (0xda600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xda600000 - 0xda7fffff --> PA: 0xda600000 - 0xda7fffff */
    .xword (0xda800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xda800000 - 0xda9fffff --> PA: 0xda800000 - 0xda9fffff */
    .xword (0xdaa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdaa00000 - 0xdabfffff --> PA: 0xdaa00000 - 0xdabfffff */
    .xword (0xdac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdac00000 - 0xdadfffff --> PA: 0xdac00000 - 0xdadfffff */
    .xword (0xdae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdae00000 - 0xdaffffff --> PA: 0xdae00000 - 0xdaffffff */
    .xword (0xdb000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdb000000 - 0xdb1fffff --> PA: 0xdb000000 - 0xdb1fffff */
    .xword (0xdb200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdb200000 - 0xdb3fffff --> PA: 0xdb200000 - 0xdb3fffff */
    .xword (0xdb400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdb400000 - 0xdb5fffff --> PA: 0xdb400000 - 0xdb5fffff */
    .xword (0xdb600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdb600000 - 0xdb7fffff --> PA: 0xdb600000 - 0xdb7fffff */
    .xword (0xdb800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdb800000 - 0xdb9fffff --> PA: 0xdb800000 - 0xdb9fffff */
    .xword (0xdba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdba00000 - 0xdbbfffff --> PA: 0xdba00000 - 0xdbbfffff */
    .xword (0xdbc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdbc00000 - 0xdbdfffff --> PA: 0xdbc00000 - 0xdbdfffff */
    .xword (0xdbe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdbe00000 - 0xdbffffff --> PA: 0xdbe00000 - 0xdbffffff */
    .xword (0xdc000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdc000000 - 0xdc1fffff --> PA: 0xdc000000 - 0xdc1fffff */
    .xword (0xdc200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdc200000 - 0xdc3fffff --> PA: 0xdc200000 - 0xdc3fffff */
    .xword (0xdc400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdc400000 - 0xdc5fffff --> PA: 0xdc400000 - 0xdc5fffff */
    .xword (0xdc600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdc600000 - 0xdc7fffff --> PA: 0xdc600000 - 0xdc7fffff */
    .xword (0xdc800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdc800000 - 0xdc9fffff --> PA: 0xdc800000 - 0xdc9fffff */
    .xword (0xdca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdca00000 - 0xdcbfffff --> PA: 0xdca00000 - 0xdcbfffff */
    .xword (0xdcc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdcc00000 - 0xdcdfffff --> PA: 0xdcc00000 - 0xdcdfffff */
    .xword (0xdce00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdce00000 - 0xdcffffff --> PA: 0xdce00000 - 0xdcffffff */
    .xword (0xdd000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdd000000 - 0xdd1fffff --> PA: 0xdd000000 - 0xdd1fffff */
    .xword (0xdd200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdd200000 - 0xdd3fffff --> PA: 0xdd200000 - 0xdd3fffff */
    .xword (0xdd400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdd400000 - 0xdd5fffff --> PA: 0xdd400000 - 0xdd5fffff */
    .xword (0xdd600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdd600000 - 0xdd7fffff --> PA: 0xdd600000 - 0xdd7fffff */
    .xword (0xdd800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdd800000 - 0xdd9fffff --> PA: 0xdd800000 - 0xdd9fffff */
    .xword (0xdda00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdda00000 - 0xddbfffff --> PA: 0xdda00000 - 0xddbfffff */
    .xword (0xddc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xddc00000 - 0xdddfffff --> PA: 0xddc00000 - 0xdddfffff */
    .xword (0xdde00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdde00000 - 0xddffffff --> PA: 0xdde00000 - 0xddffffff */
    .xword (0xde000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xde000000 - 0xde1fffff --> PA: 0xde000000 - 0xde1fffff */
    .xword (0xde200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xde200000 - 0xde3fffff --> PA: 0xde200000 - 0xde3fffff */
    .xword (0xde400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xde400000 - 0xde5fffff --> PA: 0xde400000 - 0xde5fffff */
    .xword (0xde600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xde600000 - 0xde7fffff --> PA: 0xde600000 - 0xde7fffff */
    .xword (0xde800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xde800000 - 0xde9fffff --> PA: 0xde800000 - 0xde9fffff */
    .xword (0xdea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdea00000 - 0xdebfffff --> PA: 0xdea00000 - 0xdebfffff */
    .xword (0xdec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdec00000 - 0xdedfffff --> PA: 0xdec00000 - 0xdedfffff */
    .xword (0xdee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdee00000 - 0xdeffffff --> PA: 0xdee00000 - 0xdeffffff */
    .xword (0xdf000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdf000000 - 0xdf1fffff --> PA: 0xdf000000 - 0xdf1fffff */
    .xword (0xdf200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdf200000 - 0xdf3fffff --> PA: 0xdf200000 - 0xdf3fffff */
    .xword (0xdf400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdf400000 - 0xdf5fffff --> PA: 0xdf400000 - 0xdf5fffff */
    .xword (0xdf600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdf600000 - 0xdf7fffff --> PA: 0xdf600000 - 0xdf7fffff */
    .xword (0xdf800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdf800000 - 0xdf9fffff --> PA: 0xdf800000 - 0xdf9fffff */
    .xword (0xdfa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdfa00000 - 0xdfbfffff --> PA: 0xdfa00000 - 0xdfbfffff */
    .xword (0xdfc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdfc00000 - 0xdfdfffff --> PA: 0xdfc00000 - 0xdfdfffff */
    .xword (0xdfe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xdfe00000 - 0xdfffffff --> PA: 0xdfe00000 - 0xdfffffff */
    .xword (0xe0000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe0000000 - 0xe01fffff --> PA: 0xe0000000 - 0xe01fffff */
    .xword (0xe0200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe0200000 - 0xe03fffff --> PA: 0xe0200000 - 0xe03fffff */
    .xword (0xe0400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe0400000 - 0xe05fffff --> PA: 0xe0400000 - 0xe05fffff */
    .xword (0xe0600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe0600000 - 0xe07fffff --> PA: 0xe0600000 - 0xe07fffff */
    .xword (0xe0800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe0800000 - 0xe09fffff --> PA: 0xe0800000 - 0xe09fffff */
    .xword (0xe0a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe0a00000 - 0xe0bfffff --> PA: 0xe0a00000 - 0xe0bfffff */
    .xword (0xe0c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe0c00000 - 0xe0dfffff --> PA: 0xe0c00000 - 0xe0dfffff */
    .xword (0xe0e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe0e00000 - 0xe0ffffff --> PA: 0xe0e00000 - 0xe0ffffff */
    .xword (0xe1000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe1000000 - 0xe11fffff --> PA: 0xe1000000 - 0xe11fffff */
    .xword (0xe1200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe1200000 - 0xe13fffff --> PA: 0xe1200000 - 0xe13fffff */
    .xword (0xe1400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe1400000 - 0xe15fffff --> PA: 0xe1400000 - 0xe15fffff */
    .xword (0xe1600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe1600000 - 0xe17fffff --> PA: 0xe1600000 - 0xe17fffff */
    .xword (0xe1800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe1800000 - 0xe19fffff --> PA: 0xe1800000 - 0xe19fffff */
    .xword (0xe1a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe1a00000 - 0xe1bfffff --> PA: 0xe1a00000 - 0xe1bfffff */
    .xword (0xe1c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe1c00000 - 0xe1dfffff --> PA: 0xe1c00000 - 0xe1dfffff */
    .xword (0xe1e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe1e00000 - 0xe1ffffff --> PA: 0xe1e00000 - 0xe1ffffff */
    .xword (0xe2000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe2000000 - 0xe21fffff --> PA: 0xe2000000 - 0xe21fffff */
    .xword (0xe2200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe2200000 - 0xe23fffff --> PA: 0xe2200000 - 0xe23fffff */
    .xword (0xe2400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe2400000 - 0xe25fffff --> PA: 0xe2400000 - 0xe25fffff */
    .xword (0xe2600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe2600000 - 0xe27fffff --> PA: 0xe2600000 - 0xe27fffff */
    .xword (0xe2800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe2800000 - 0xe29fffff --> PA: 0xe2800000 - 0xe29fffff */
    .xword (0xe2a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe2a00000 - 0xe2bfffff --> PA: 0xe2a00000 - 0xe2bfffff */
    .xword (0xe2c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe2c00000 - 0xe2dfffff --> PA: 0xe2c00000 - 0xe2dfffff */
    .xword (0xe2e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe2e00000 - 0xe2ffffff --> PA: 0xe2e00000 - 0xe2ffffff */
    .xword (0xe3000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe3000000 - 0xe31fffff --> PA: 0xe3000000 - 0xe31fffff */
    .xword (0xe3200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe3200000 - 0xe33fffff --> PA: 0xe3200000 - 0xe33fffff */
    .xword (0xe3400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe3400000 - 0xe35fffff --> PA: 0xe3400000 - 0xe35fffff */
    .xword (0xe3600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe3600000 - 0xe37fffff --> PA: 0xe3600000 - 0xe37fffff */
    .xword (0xe3800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe3800000 - 0xe39fffff --> PA: 0xe3800000 - 0xe39fffff */
    .xword (0xe3a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe3a00000 - 0xe3bfffff --> PA: 0xe3a00000 - 0xe3bfffff */
    .xword (0xe3c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe3c00000 - 0xe3dfffff --> PA: 0xe3c00000 - 0xe3dfffff */
    .xword (0xe3e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe3e00000 - 0xe3ffffff --> PA: 0xe3e00000 - 0xe3ffffff */
    .xword (0xe4000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe4000000 - 0xe41fffff --> PA: 0xe4000000 - 0xe41fffff */
    .xword (0xe4200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe4200000 - 0xe43fffff --> PA: 0xe4200000 - 0xe43fffff */
    .xword (0xe4400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe4400000 - 0xe45fffff --> PA: 0xe4400000 - 0xe45fffff */
    .xword (0xe4600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe4600000 - 0xe47fffff --> PA: 0xe4600000 - 0xe47fffff */
    .xword (0xe4800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe4800000 - 0xe49fffff --> PA: 0xe4800000 - 0xe49fffff */
    .xword (0xe4a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe4a00000 - 0xe4bfffff --> PA: 0xe4a00000 - 0xe4bfffff */
    .xword (0xe4c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe4c00000 - 0xe4dfffff --> PA: 0xe4c00000 - 0xe4dfffff */
    .xword (0xe4e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe4e00000 - 0xe4ffffff --> PA: 0xe4e00000 - 0xe4ffffff */
    .xword (0xe5000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe5000000 - 0xe51fffff --> PA: 0xe5000000 - 0xe51fffff */
    .xword (0xe5200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe5200000 - 0xe53fffff --> PA: 0xe5200000 - 0xe53fffff */
    .xword (0xe5400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe5400000 - 0xe55fffff --> PA: 0xe5400000 - 0xe55fffff */
    .xword (0xe5600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe5600000 - 0xe57fffff --> PA: 0xe5600000 - 0xe57fffff */
    .xword (0xe5800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe5800000 - 0xe59fffff --> PA: 0xe5800000 - 0xe59fffff */
    .xword (0xe5a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe5a00000 - 0xe5bfffff --> PA: 0xe5a00000 - 0xe5bfffff */
    .xword (0xe5c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe5c00000 - 0xe5dfffff --> PA: 0xe5c00000 - 0xe5dfffff */
    .xword (0xe5e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe5e00000 - 0xe5ffffff --> PA: 0xe5e00000 - 0xe5ffffff */
    .xword (0xe6000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe6000000 - 0xe61fffff --> PA: 0xe6000000 - 0xe61fffff */
    .xword (0xe6200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe6200000 - 0xe63fffff --> PA: 0xe6200000 - 0xe63fffff */
    .xword (0xe6400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe6400000 - 0xe65fffff --> PA: 0xe6400000 - 0xe65fffff */
    .xword (0xe6600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe6600000 - 0xe67fffff --> PA: 0xe6600000 - 0xe67fffff */
    .xword (0xe6800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe6800000 - 0xe69fffff --> PA: 0xe6800000 - 0xe69fffff */
    .xword (0xe6a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe6a00000 - 0xe6bfffff --> PA: 0xe6a00000 - 0xe6bfffff */
    .xword (0xe6c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe6c00000 - 0xe6dfffff --> PA: 0xe6c00000 - 0xe6dfffff */
    .xword (0xe6e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe6e00000 - 0xe6ffffff --> PA: 0xe6e00000 - 0xe6ffffff */
    .xword (0xe7000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe7000000 - 0xe71fffff --> PA: 0xe7000000 - 0xe71fffff */
    .xword (0xe7200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe7200000 - 0xe73fffff --> PA: 0xe7200000 - 0xe73fffff */
    .xword (0xe7400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe7400000 - 0xe75fffff --> PA: 0xe7400000 - 0xe75fffff */
    .xword (0xe7600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe7600000 - 0xe77fffff --> PA: 0xe7600000 - 0xe77fffff */
    .xword (0xe7800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe7800000 - 0xe79fffff --> PA: 0xe7800000 - 0xe79fffff */
    .xword (0xe7a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe7a00000 - 0xe7bfffff --> PA: 0xe7a00000 - 0xe7bfffff */
    .xword (0xe7c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe7c00000 - 0xe7dfffff --> PA: 0xe7c00000 - 0xe7dfffff */
    .xword (0xe7e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe7e00000 - 0xe7ffffff --> PA: 0xe7e00000 - 0xe7ffffff */
    .xword (0xe8000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe8000000 - 0xe81fffff --> PA: 0xe8000000 - 0xe81fffff */
    .xword (0xe8200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe8200000 - 0xe83fffff --> PA: 0xe8200000 - 0xe83fffff */
    .xword (0xe8400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe8400000 - 0xe85fffff --> PA: 0xe8400000 - 0xe85fffff */
    .xword (0xe8600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe8600000 - 0xe87fffff --> PA: 0xe8600000 - 0xe87fffff */
    .xword (0xe8800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe8800000 - 0xe89fffff --> PA: 0xe8800000 - 0xe89fffff */
    .xword (0xe8a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe8a00000 - 0xe8bfffff --> PA: 0xe8a00000 - 0xe8bfffff */
    .xword (0xe8c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe8c00000 - 0xe8dfffff --> PA: 0xe8c00000 - 0xe8dfffff */
    .xword (0xe8e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe8e00000 - 0xe8ffffff --> PA: 0xe8e00000 - 0xe8ffffff */
    .xword (0xe9000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe9000000 - 0xe91fffff --> PA: 0xe9000000 - 0xe91fffff */
    .xword (0xe9200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe9200000 - 0xe93fffff --> PA: 0xe9200000 - 0xe93fffff */
    .xword (0xe9400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe9400000 - 0xe95fffff --> PA: 0xe9400000 - 0xe95fffff */
    .xword (0xe9600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe9600000 - 0xe97fffff --> PA: 0xe9600000 - 0xe97fffff */
    .xword (0xe9800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe9800000 - 0xe99fffff --> PA: 0xe9800000 - 0xe99fffff */
    .xword (0xe9a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe9a00000 - 0xe9bfffff --> PA: 0xe9a00000 - 0xe9bfffff */
    .xword (0xe9c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe9c00000 - 0xe9dfffff --> PA: 0xe9c00000 - 0xe9dfffff */
    .xword (0xe9e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xe9e00000 - 0xe9ffffff --> PA: 0xe9e00000 - 0xe9ffffff */
    .xword (0xea000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xea000000 - 0xea1fffff --> PA: 0xea000000 - 0xea1fffff */
    .xword (0xea200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xea200000 - 0xea3fffff --> PA: 0xea200000 - 0xea3fffff */
    .xword (0xea400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xea400000 - 0xea5fffff --> PA: 0xea400000 - 0xea5fffff */
    .xword (0xea600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xea600000 - 0xea7fffff --> PA: 0xea600000 - 0xea7fffff */
    .xword (0xea800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xea800000 - 0xea9fffff --> PA: 0xea800000 - 0xea9fffff */
    .xword (0xeaa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xeaa00000 - 0xeabfffff --> PA: 0xeaa00000 - 0xeabfffff */
    .xword (0xeac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xeac00000 - 0xeadfffff --> PA: 0xeac00000 - 0xeadfffff */
    .xword (0xeae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xeae00000 - 0xeaffffff --> PA: 0xeae00000 - 0xeaffffff */
    .xword (0xeb000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xeb000000 - 0xeb1fffff --> PA: 0xeb000000 - 0xeb1fffff */
    .xword (0xeb200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xeb200000 - 0xeb3fffff --> PA: 0xeb200000 - 0xeb3fffff */
    .xword (0xeb400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xeb400000 - 0xeb5fffff --> PA: 0xeb400000 - 0xeb5fffff */
    .xword (0xeb600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xeb600000 - 0xeb7fffff --> PA: 0xeb600000 - 0xeb7fffff */
    .xword (0xeb800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xeb800000 - 0xeb9fffff --> PA: 0xeb800000 - 0xeb9fffff */
    .xword (0xeba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xeba00000 - 0xebbfffff --> PA: 0xeba00000 - 0xebbfffff */
    .xword (0xebc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xebc00000 - 0xebdfffff --> PA: 0xebc00000 - 0xebdfffff */
    .xword (0xebe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xebe00000 - 0xebffffff --> PA: 0xebe00000 - 0xebffffff */
    .xword (0xec000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xec000000 - 0xec1fffff --> PA: 0xec000000 - 0xec1fffff */
    .xword (0xec200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xec200000 - 0xec3fffff --> PA: 0xec200000 - 0xec3fffff */
    .xword (0xec400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xec400000 - 0xec5fffff --> PA: 0xec400000 - 0xec5fffff */
    .xword (0xec600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xec600000 - 0xec7fffff --> PA: 0xec600000 - 0xec7fffff */
    .xword (0xec800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xec800000 - 0xec9fffff --> PA: 0xec800000 - 0xec9fffff */
    .xword (0xeca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xeca00000 - 0xecbfffff --> PA: 0xeca00000 - 0xecbfffff */
    .xword (0xecc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xecc00000 - 0xecdfffff --> PA: 0xecc00000 - 0xecdfffff */
    .xword (0xece00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xece00000 - 0xecffffff --> PA: 0xece00000 - 0xecffffff */
    .xword (0xed000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xed000000 - 0xed1fffff --> PA: 0xed000000 - 0xed1fffff */
    .xword (0xed200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xed200000 - 0xed3fffff --> PA: 0xed200000 - 0xed3fffff */
    .xword (0xed400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xed400000 - 0xed5fffff --> PA: 0xed400000 - 0xed5fffff */
    .xword (0xed600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xed600000 - 0xed7fffff --> PA: 0xed600000 - 0xed7fffff */
    .xword (0xed800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xed800000 - 0xed9fffff --> PA: 0xed800000 - 0xed9fffff */
    .xword (0xeda00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xeda00000 - 0xedbfffff --> PA: 0xeda00000 - 0xedbfffff */
    .xword (0xedc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xedc00000 - 0xeddfffff --> PA: 0xedc00000 - 0xeddfffff */
    .xword (0xede00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xede00000 - 0xedffffff --> PA: 0xede00000 - 0xedffffff */
    .xword (0xee000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xee000000 - 0xee1fffff --> PA: 0xee000000 - 0xee1fffff */
    .xword (0xee200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xee200000 - 0xee3fffff --> PA: 0xee200000 - 0xee3fffff */
    .xword (0xee400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xee400000 - 0xee5fffff --> PA: 0xee400000 - 0xee5fffff */
    .xword (0xee600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xee600000 - 0xee7fffff --> PA: 0xee600000 - 0xee7fffff */
    .xword (0xee800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xee800000 - 0xee9fffff --> PA: 0xee800000 - 0xee9fffff */
    .xword (0xeea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xeea00000 - 0xeebfffff --> PA: 0xeea00000 - 0xeebfffff */
    .xword (0xeec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xeec00000 - 0xeedfffff --> PA: 0xeec00000 - 0xeedfffff */
    .xword (0xeee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xeee00000 - 0xeeffffff --> PA: 0xeee00000 - 0xeeffffff */
    .xword (0xef000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xef000000 - 0xef1fffff --> PA: 0xef000000 - 0xef1fffff */
    .xword (0xef200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xef200000 - 0xef3fffff --> PA: 0xef200000 - 0xef3fffff */
    .xword (0xef400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xef400000 - 0xef5fffff --> PA: 0xef400000 - 0xef5fffff */
    .xword (0xef600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xef600000 - 0xef7fffff --> PA: 0xef600000 - 0xef7fffff */
    .xword (0xef800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xef800000 - 0xef9fffff --> PA: 0xef800000 - 0xef9fffff */
    .xword (0xefa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xefa00000 - 0xefbfffff --> PA: 0xefa00000 - 0xefbfffff */
    .xword (0xefc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xefc00000 - 0xefdfffff --> PA: 0xefc00000 - 0xefdfffff */
    .xword (0xefe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xefe00000 - 0xefffffff --> PA: 0xefe00000 - 0xefffffff */
    .xword (0xf0000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf0000000 - 0xf01fffff --> PA: 0xf0000000 - 0xf01fffff */
    .xword (0xf0200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf0200000 - 0xf03fffff --> PA: 0xf0200000 - 0xf03fffff */
    .xword (0xf0400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf0400000 - 0xf05fffff --> PA: 0xf0400000 - 0xf05fffff */
    .xword (0xf0600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf0600000 - 0xf07fffff --> PA: 0xf0600000 - 0xf07fffff */
    .xword (0xf0800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf0800000 - 0xf09fffff --> PA: 0xf0800000 - 0xf09fffff */
    .xword (0xf0a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf0a00000 - 0xf0bfffff --> PA: 0xf0a00000 - 0xf0bfffff */
    .xword (0xf0c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf0c00000 - 0xf0dfffff --> PA: 0xf0c00000 - 0xf0dfffff */
    .xword (0xf0e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf0e00000 - 0xf0ffffff --> PA: 0xf0e00000 - 0xf0ffffff */
    .xword (0xf1000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf1000000 - 0xf11fffff --> PA: 0xf1000000 - 0xf11fffff */
    .xword (0xf1200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf1200000 - 0xf13fffff --> PA: 0xf1200000 - 0xf13fffff */
    .xword (0xf1400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf1400000 - 0xf15fffff --> PA: 0xf1400000 - 0xf15fffff */
    .xword (0xf1600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf1600000 - 0xf17fffff --> PA: 0xf1600000 - 0xf17fffff */
    .xword (0xf1800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf1800000 - 0xf19fffff --> PA: 0xf1800000 - 0xf19fffff */
    .xword (0xf1a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf1a00000 - 0xf1bfffff --> PA: 0xf1a00000 - 0xf1bfffff */
    .xword (0xf1c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf1c00000 - 0xf1dfffff --> PA: 0xf1c00000 - 0xf1dfffff */
    .xword (0xf1e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf1e00000 - 0xf1ffffff --> PA: 0xf1e00000 - 0xf1ffffff */
    .xword (0xf2000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf2000000 - 0xf21fffff --> PA: 0xf2000000 - 0xf21fffff */
    .xword (0xf2200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf2200000 - 0xf23fffff --> PA: 0xf2200000 - 0xf23fffff */
    .xword (0xf2400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf2400000 - 0xf25fffff --> PA: 0xf2400000 - 0xf25fffff */
    .xword (0xf2600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf2600000 - 0xf27fffff --> PA: 0xf2600000 - 0xf27fffff */
    .xword (0xf2800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf2800000 - 0xf29fffff --> PA: 0xf2800000 - 0xf29fffff */
    .xword (0xf2a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf2a00000 - 0xf2bfffff --> PA: 0xf2a00000 - 0xf2bfffff */
    .xword (0xf2c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf2c00000 - 0xf2dfffff --> PA: 0xf2c00000 - 0xf2dfffff */
    .xword (0xf2e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf2e00000 - 0xf2ffffff --> PA: 0xf2e00000 - 0xf2ffffff */
    .xword (0xf3000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf3000000 - 0xf31fffff --> PA: 0xf3000000 - 0xf31fffff */
    .xword (0xf3200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf3200000 - 0xf33fffff --> PA: 0xf3200000 - 0xf33fffff */
    .xword (0xf3400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf3400000 - 0xf35fffff --> PA: 0xf3400000 - 0xf35fffff */
    .xword (0xf3600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf3600000 - 0xf37fffff --> PA: 0xf3600000 - 0xf37fffff */
    .xword (0xf3800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf3800000 - 0xf39fffff --> PA: 0xf3800000 - 0xf39fffff */
    .xword (0xf3a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf3a00000 - 0xf3bfffff --> PA: 0xf3a00000 - 0xf3bfffff */
    .xword (0xf3c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf3c00000 - 0xf3dfffff --> PA: 0xf3c00000 - 0xf3dfffff */
    .xword (0xf3e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf3e00000 - 0xf3ffffff --> PA: 0xf3e00000 - 0xf3ffffff */
    .xword (0xf4000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf4000000 - 0xf41fffff --> PA: 0xf4000000 - 0xf41fffff */
    .xword (0xf4200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf4200000 - 0xf43fffff --> PA: 0xf4200000 - 0xf43fffff */
    .xword (0xf4400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf4400000 - 0xf45fffff --> PA: 0xf4400000 - 0xf45fffff */
    .xword (0xf4600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf4600000 - 0xf47fffff --> PA: 0xf4600000 - 0xf47fffff */
    .xword (0xf4800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf4800000 - 0xf49fffff --> PA: 0xf4800000 - 0xf49fffff */
    .xword (0xf4a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf4a00000 - 0xf4bfffff --> PA: 0xf4a00000 - 0xf4bfffff */
    .xword (0xf4c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf4c00000 - 0xf4dfffff --> PA: 0xf4c00000 - 0xf4dfffff */
    .xword (0xf4e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf4e00000 - 0xf4ffffff --> PA: 0xf4e00000 - 0xf4ffffff */
    .xword (0xf5000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf5000000 - 0xf51fffff --> PA: 0xf5000000 - 0xf51fffff */
    .xword (0xf5200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf5200000 - 0xf53fffff --> PA: 0xf5200000 - 0xf53fffff */
    .xword (0xf5400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf5400000 - 0xf55fffff --> PA: 0xf5400000 - 0xf55fffff */
    .xword (0xf5600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf5600000 - 0xf57fffff --> PA: 0xf5600000 - 0xf57fffff */
    .xword (0xf5800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf5800000 - 0xf59fffff --> PA: 0xf5800000 - 0xf59fffff */
    .xword (0xf5a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf5a00000 - 0xf5bfffff --> PA: 0xf5a00000 - 0xf5bfffff */
    .xword (0xf5c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf5c00000 - 0xf5dfffff --> PA: 0xf5c00000 - 0xf5dfffff */
    .xword (0xf5e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf5e00000 - 0xf5ffffff --> PA: 0xf5e00000 - 0xf5ffffff */
    .xword (0xf6000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf6000000 - 0xf61fffff --> PA: 0xf6000000 - 0xf61fffff */
    .xword (0xf6200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf6200000 - 0xf63fffff --> PA: 0xf6200000 - 0xf63fffff */
    .xword (0xf6400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf6400000 - 0xf65fffff --> PA: 0xf6400000 - 0xf65fffff */
    .xword (0xf6600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf6600000 - 0xf67fffff --> PA: 0xf6600000 - 0xf67fffff */
    .xword (0xf6800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf6800000 - 0xf69fffff --> PA: 0xf6800000 - 0xf69fffff */
    .xword (0xf6a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf6a00000 - 0xf6bfffff --> PA: 0xf6a00000 - 0xf6bfffff */
    .xword (0xf6c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf6c00000 - 0xf6dfffff --> PA: 0xf6c00000 - 0xf6dfffff */
    .xword (0xf6e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf6e00000 - 0xf6ffffff --> PA: 0xf6e00000 - 0xf6ffffff */
    .xword (0xf7000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf7000000 - 0xf71fffff --> PA: 0xf7000000 - 0xf71fffff */
    .xword (0xf7200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf7200000 - 0xf73fffff --> PA: 0xf7200000 - 0xf73fffff */
    .xword (0xf7400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf7400000 - 0xf75fffff --> PA: 0xf7400000 - 0xf75fffff */
    .xword (0xf7600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf7600000 - 0xf77fffff --> PA: 0xf7600000 - 0xf77fffff */
    .xword (0xf7800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf7800000 - 0xf79fffff --> PA: 0xf7800000 - 0xf79fffff */
    .xword (0xf7a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf7a00000 - 0xf7bfffff --> PA: 0xf7a00000 - 0xf7bfffff */
    .xword (0xf7c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf7c00000 - 0xf7dfffff --> PA: 0xf7c00000 - 0xf7dfffff */
    .xword (0xf7e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf7e00000 - 0xf7ffffff --> PA: 0xf7e00000 - 0xf7ffffff */
    .xword (0xf8000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf8000000 - 0xf81fffff --> PA: 0xf8000000 - 0xf81fffff */
    .xword (0xf8200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf8200000 - 0xf83fffff --> PA: 0xf8200000 - 0xf83fffff */
    .xword (0xf8400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf8400000 - 0xf85fffff --> PA: 0xf8400000 - 0xf85fffff */
    .xword (0xf8600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf8600000 - 0xf87fffff --> PA: 0xf8600000 - 0xf87fffff */
    .xword (0xf8800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf8800000 - 0xf89fffff --> PA: 0xf8800000 - 0xf89fffff */
    .xword (0xf8a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf8a00000 - 0xf8bfffff --> PA: 0xf8a00000 - 0xf8bfffff */
    .xword (0xf8c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf8c00000 - 0xf8dfffff --> PA: 0xf8c00000 - 0xf8dfffff */
    .xword (0xf8e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf8e00000 - 0xf8ffffff --> PA: 0xf8e00000 - 0xf8ffffff */
    .xword (0xf9000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf9000000 - 0xf91fffff --> PA: 0xf9000000 - 0xf91fffff */
    .xword (0xf9200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf9200000 - 0xf93fffff --> PA: 0xf9200000 - 0xf93fffff */
    .xword (0xf9400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf9400000 - 0xf95fffff --> PA: 0xf9400000 - 0xf95fffff */
    .xword (0xf9600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf9600000 - 0xf97fffff --> PA: 0xf9600000 - 0xf97fffff */
    .xword (0xf9800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf9800000 - 0xf99fffff --> PA: 0xf9800000 - 0xf99fffff */
    .xword (0xf9a00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf9a00000 - 0xf9bfffff --> PA: 0xf9a00000 - 0xf9bfffff */
    .xword (0xf9c00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf9c00000 - 0xf9dfffff --> PA: 0xf9c00000 - 0xf9dfffff */
    .xword (0xf9e00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xf9e00000 - 0xf9ffffff --> PA: 0xf9e00000 - 0xf9ffffff */
    .xword (0xfa000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfa000000 - 0xfa1fffff --> PA: 0xfa000000 - 0xfa1fffff */
    .xword (0xfa200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfa200000 - 0xfa3fffff --> PA: 0xfa200000 - 0xfa3fffff */
    .xword (0xfa400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfa400000 - 0xfa5fffff --> PA: 0xfa400000 - 0xfa5fffff */
    .xword (0xfa600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfa600000 - 0xfa7fffff --> PA: 0xfa600000 - 0xfa7fffff */
    .xword (0xfa800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfa800000 - 0xfa9fffff --> PA: 0xfa800000 - 0xfa9fffff */
    .xword (0xfaa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfaa00000 - 0xfabfffff --> PA: 0xfaa00000 - 0xfabfffff */
    .xword (0xfac00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfac00000 - 0xfadfffff --> PA: 0xfac00000 - 0xfadfffff */
    .xword (0xfae00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfae00000 - 0xfaffffff --> PA: 0xfae00000 - 0xfaffffff */
    .xword (0xfb000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfb000000 - 0xfb1fffff --> PA: 0xfb000000 - 0xfb1fffff */
    .xword (0xfb200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfb200000 - 0xfb3fffff --> PA: 0xfb200000 - 0xfb3fffff */
    .xword (0xfb400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfb400000 - 0xfb5fffff --> PA: 0xfb400000 - 0xfb5fffff */
    .xword (0xfb600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfb600000 - 0xfb7fffff --> PA: 0xfb600000 - 0xfb7fffff */
    .xword (0xfb800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfb800000 - 0xfb9fffff --> PA: 0xfb800000 - 0xfb9fffff */
    .xword (0xfba00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfba00000 - 0xfbbfffff --> PA: 0xfba00000 - 0xfbbfffff */
    .xword (0xfbc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfbc00000 - 0xfbdfffff --> PA: 0xfbc00000 - 0xfbdfffff */
    .xword (0xfbe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfbe00000 - 0xfbffffff --> PA: 0xfbe00000 - 0xfbffffff */
    .xword (0xfc000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfc000000 - 0xfc1fffff --> PA: 0xfc000000 - 0xfc1fffff */
    .xword (0xfc200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfc200000 - 0xfc3fffff --> PA: 0xfc200000 - 0xfc3fffff */
    .xword (0xfc400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfc400000 - 0xfc5fffff --> PA: 0xfc400000 - 0xfc5fffff */
    .xword (0xfc600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfc600000 - 0xfc7fffff --> PA: 0xfc600000 - 0xfc7fffff */
    .xword (0xfc800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfc800000 - 0xfc9fffff --> PA: 0xfc800000 - 0xfc9fffff */
    .xword (0xfca00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfca00000 - 0xfcbfffff --> PA: 0xfca00000 - 0xfcbfffff */
    .xword (0xfcc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfcc00000 - 0xfcdfffff --> PA: 0xfcc00000 - 0xfcdfffff */
    .xword (0xfce00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfce00000 - 0xfcffffff --> PA: 0xfce00000 - 0xfcffffff */
    .xword (0xfd000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfd000000 - 0xfd1fffff --> PA: 0xfd000000 - 0xfd1fffff */
    .xword (0xfd200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfd200000 - 0xfd3fffff --> PA: 0xfd200000 - 0xfd3fffff */
    .xword (0xfd400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfd400000 - 0xfd5fffff --> PA: 0xfd400000 - 0xfd5fffff */
    .xword (0xfd600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfd600000 - 0xfd7fffff --> PA: 0xfd600000 - 0xfd7fffff */
    .xword (0xfd800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfd800000 - 0xfd9fffff --> PA: 0xfd800000 - 0xfd9fffff */
    .xword (0xfda00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfda00000 - 0xfdbfffff --> PA: 0xfda00000 - 0xfdbfffff */
    .xword (0xfdc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfdc00000 - 0xfddfffff --> PA: 0xfdc00000 - 0xfddfffff */
    .xword (0xfde00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfde00000 - 0xfdffffff --> PA: 0xfde00000 - 0xfdffffff */
    .xword (0xfe000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfe000000 - 0xfe1fffff --> PA: 0xfe000000 - 0xfe1fffff */
    .xword (0xfe200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfe200000 - 0xfe3fffff --> PA: 0xfe200000 - 0xfe3fffff */
    .xword (0xfe400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfe400000 - 0xfe5fffff --> PA: 0xfe400000 - 0xfe5fffff */
    .xword (0xfe600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfe600000 - 0xfe7fffff --> PA: 0xfe600000 - 0xfe7fffff */
    .xword (0xfe800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfe800000 - 0xfe9fffff --> PA: 0xfe800000 - 0xfe9fffff */
    .xword (0xfea00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfea00000 - 0xfebfffff --> PA: 0xfea00000 - 0xfebfffff */
    .xword (0xfec00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfec00000 - 0xfedfffff --> PA: 0xfec00000 - 0xfedfffff */
    .xword (0xfee00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xfee00000 - 0xfeffffff --> PA: 0xfee00000 - 0xfeffffff */
    .xword (0xff000000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xff000000 - 0xff1fffff --> PA: 0xff000000 - 0xff1fffff */
    .xword (0xff200000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xff200000 - 0xff3fffff --> PA: 0xff200000 - 0xff3fffff */
    .xword (0xff400000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xff400000 - 0xff5fffff --> PA: 0xff400000 - 0xff5fffff */
    .xword (0xff600000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xff600000 - 0xff7fffff --> PA: 0xff600000 - 0xff7fffff */
    .xword (0xff800000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xff800000 - 0xff9fffff --> PA: 0xff800000 - 0xff9fffff */
    .xword (0xffa00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xffa00000 - 0xffbfffff --> PA: 0xffa00000 - 0xffbfffff */
    .xword (0xffc00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xffc00000 - 0xffdfffff --> PA: 0xffc00000 - 0xffdfffff */
    .xword (0xffe00000 | (0b1 << 53) | (0b11 << 8) | (1 << 10) | (0x00 << 2) | 1) /* VA: 0xffe00000 - 0xffffffff --> PA: 0xffe00000 - 0xffffffff */

.size mmu_level2_translation_table_3, .-mmu_level2_translation_table_3
