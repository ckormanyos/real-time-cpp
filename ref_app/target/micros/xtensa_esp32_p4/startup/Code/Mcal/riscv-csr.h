/*
   Register access functions for RISC-V system registers.
   SPDX-License-Identifier: Unlicense

   https://five-embeddev.com/

*/

#ifndef RISCV_CSR_H
#define RISCV_CSR_H

#include <stdint.h>

#if __riscv_xlen==32
typedef uint32_t uint_xlen_t;
typedef uint32_t uint_csr32_t;
typedef uint32_t uint_csr64_t;
#elif __riscv_xlen==64
typedef uint64_t uint_xlen_t;
typedef uint32_t uint_csr32_t;
typedef uint64_t uint_csr64_t;
#else
#error "Unknown XLEN"
#endif

// Test for Zicsr extension, if relevant
#if defined(__riscv_arch_test)
#if !defined(__riscv_zicsr)
#error "-march must include zicsr to access CSRs" 
#endif
#endif

/*******************************************
 * misa - MRW - Machine ISA 
 */
static inline uint_xlen_t csr_read_misa(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, misa" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_misa(uint_xlen_t value) {
    __asm__ volatile ("csrw    misa, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_misa(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, misa, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mvendorid - MRO - Machine Vendor ID 
 */
static inline uint32_t csr_read_mvendorid(void) {
    uint_csr32_t value;        
    __asm__ volatile ("csrr    %0, mvendorid" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * marchid - MRO - Machine Architecture ID 
 */
static inline uint_xlen_t csr_read_marchid(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, marchid" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * mimpid - MRO - Machine Implementation ID 
 */
static inline uint_xlen_t csr_read_mimpid(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mimpid" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * mhartid - MRO - Hardware Thread ID 
 */
static inline uint_xlen_t csr_read_mhartid(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mhartid" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * mstatus - MRW - Machine Status 
 */
static inline uint_xlen_t csr_read_mstatus(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mstatus" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mstatus(uint_xlen_t value) {
    __asm__ volatile ("csrw    mstatus, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mstatus(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mstatus, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_mstatus(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, mstatus, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_mstatus(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, mstatus, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_mstatus(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, mstatus, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_mstatus(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, mstatus, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* mstatus, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_MSTATUS(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, mstatus, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mstatus, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_MSTATUS(MASK)                 \
    __asm__ volatile ("csrrsi    zero, mstatus, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mstatus, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_MSTATUS(MASK)               \
    __asm__ volatile ("csrrci    zero, mstatus, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define MSTATUS_MIE_BIT_OFFSET   3
#define MSTATUS_MIE_BIT_WIDTH    1
#define MSTATUS_MIE_BIT_MASK     0x8
#define MSTATUS_MIE_ALL_SET_MASK 0x1
#define MSTATUS_SIE_BIT_OFFSET   2
#define MSTATUS_SIE_BIT_WIDTH    1
#define MSTATUS_SIE_BIT_MASK     0x4
#define MSTATUS_SIE_ALL_SET_MASK 0x1
#define MSTATUS_MPIE_BIT_OFFSET   7
#define MSTATUS_MPIE_BIT_WIDTH    1
#define MSTATUS_MPIE_BIT_MASK     0x80
#define MSTATUS_MPIE_ALL_SET_MASK 0x1
#define MSTATUS_SPIE_BIT_OFFSET   5
#define MSTATUS_SPIE_BIT_WIDTH    1
#define MSTATUS_SPIE_BIT_MASK     0x20
#define MSTATUS_SPIE_ALL_SET_MASK 0x1
#define MSTATUS_MPRV_BIT_OFFSET   17
#define MSTATUS_MPRV_BIT_WIDTH    1
#define MSTATUS_MPRV_BIT_MASK     0x20000
#define MSTATUS_MPRV_ALL_SET_MASK 0x1
#define MSTATUS_MPP_BIT_OFFSET   11
#define MSTATUS_MPP_BIT_WIDTH    2
#define MSTATUS_MPP_BIT_MASK     0x1800
#define MSTATUS_MPP_ALL_SET_MASK 0x3
#define MSTATUS_SPP_BIT_OFFSET   8
#define MSTATUS_SPP_BIT_WIDTH    1
#define MSTATUS_SPP_BIT_MASK     0x100
#define MSTATUS_SPP_ALL_SET_MASK 0x1

/*******************************************
 * mstatush - MRW - Additional machine status register, RV32 only. 
 */
static inline uint_xlen_t csr_read_mstatush(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mstatush" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mstatush(uint_xlen_t value) {
    __asm__ volatile ("csrw    mstatush, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mstatush(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mstatush, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mtvec - MRW - Machine Trap Vector Base Address 
 */
static inline uint_xlen_t csr_read_mtvec(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mtvec" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mtvec(uint_xlen_t value) {
    __asm__ volatile ("csrw    mtvec, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mtvec(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mtvec, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_mtvec(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, mtvec, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_mtvec(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, mtvec, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_mtvec(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, mtvec, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_mtvec(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, mtvec, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* mtvec, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_MTVEC(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, mtvec, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mtvec, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_MTVEC(MASK)                 \
    __asm__ volatile ("csrrsi    zero, mtvec, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mtvec, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_MTVEC(MASK)               \
    __asm__ volatile ("csrrci    zero, mtvec, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define MTVEC_BASE_BIT_OFFSET   2
#define MTVEC_BASE_BIT_WIDTH    ((__riscv_xlen-1)-(2) + 1)
#define MTVEC_BASE_BIT_MASK     ((1UL<<(((__riscv_xlen-1)-(2) + 1)-1)) << (2))
#define MTVEC_BASE_ALL_SET_MASK ((1UL<<(((__riscv_xlen-1)-(2) + 1)-1)) << (0))
#define MTVEC_MODE_BIT_OFFSET   0
#define MTVEC_MODE_BIT_WIDTH    2
#define MTVEC_MODE_BIT_MASK     0x3
#define MTVEC_MODE_ALL_SET_MASK 0x3

/*******************************************
 * medeleg - MRW - Machine Exception Delegation 
 */
static inline uint_xlen_t csr_read_medeleg(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, medeleg" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_medeleg(uint_xlen_t value) {
    __asm__ volatile ("csrw    medeleg, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_medeleg(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, medeleg, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mideleg - MRW - Machine Interrupt Delegation 
 */
static inline uint_xlen_t csr_read_mideleg(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mideleg" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mideleg(uint_xlen_t value) {
    __asm__ volatile ("csrw    mideleg, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mideleg(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mideleg, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mip - MRW - Machine Interrupt Pending 
 */
static inline uint_xlen_t csr_read_mip(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mip" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mip(uint_xlen_t value) {
    __asm__ volatile ("csrw    mip, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mip(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mip, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_mip(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, mip, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_mip(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, mip, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_mip(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, mip, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_mip(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, mip, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* mip, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_MIP(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, mip, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mip, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_MIP(MASK)                 \
    __asm__ volatile ("csrrsi    zero, mip, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mip, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_MIP(MASK)               \
    __asm__ volatile ("csrrci    zero, mip, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define MIP_MSI_BIT_OFFSET   3
#define MIP_MSI_BIT_WIDTH    1
#define MIP_MSI_BIT_MASK     0x8
#define MIP_MSI_ALL_SET_MASK 0x1
#define MIP_MTI_BIT_OFFSET   7
#define MIP_MTI_BIT_WIDTH    1
#define MIP_MTI_BIT_MASK     0x80
#define MIP_MTI_ALL_SET_MASK 0x1
#define MIP_MEI_BIT_OFFSET   11
#define MIP_MEI_BIT_WIDTH    1
#define MIP_MEI_BIT_MASK     0x800
#define MIP_MEI_ALL_SET_MASK 0x1
#define MIP_SSI_BIT_OFFSET   1
#define MIP_SSI_BIT_WIDTH    1
#define MIP_SSI_BIT_MASK     0x2
#define MIP_SSI_ALL_SET_MASK 0x1
#define MIP_STI_BIT_OFFSET   5
#define MIP_STI_BIT_WIDTH    1
#define MIP_STI_BIT_MASK     0x20
#define MIP_STI_ALL_SET_MASK 0x1
#define MIP_SEI_BIT_OFFSET   9
#define MIP_SEI_BIT_WIDTH    1
#define MIP_SEI_BIT_MASK     0x200
#define MIP_SEI_ALL_SET_MASK 0x1
#define MIP_USI_BIT_OFFSET   0
#define MIP_USI_BIT_WIDTH    1
#define MIP_USI_BIT_MASK     0x1
#define MIP_USI_ALL_SET_MASK 0x1
#define MIP_UTI_BIT_OFFSET   4
#define MIP_UTI_BIT_WIDTH    1
#define MIP_UTI_BIT_MASK     0x10
#define MIP_UTI_ALL_SET_MASK 0x1
#define MIP_UEI_BIT_OFFSET   8
#define MIP_UEI_BIT_WIDTH    1
#define MIP_UEI_BIT_MASK     0x100
#define MIP_UEI_ALL_SET_MASK 0x1
#define MIP_PLATFORM_DEFINED_BIT_OFFSET   16
#define MIP_PLATFORM_DEFINED_BIT_WIDTH    ((__riscv_xlen)-(16) + 1)
#define MIP_PLATFORM_DEFINED_BIT_MASK     ((1UL<<(((__riscv_xlen)-(16) + 1)-1)) << (16))
#define MIP_PLATFORM_DEFINED_ALL_SET_MASK ((1UL<<(((__riscv_xlen)-(16) + 1)-1)) << (0))

/*******************************************
 * mie - MRW - Machine Interrupt Enable 
 */
static inline uint_xlen_t csr_read_mie(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mie" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mie(uint_xlen_t value) {
    __asm__ volatile ("csrw    mie, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mie(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mie, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_mie(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, mie, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_mie(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, mie, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_mie(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, mie, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_mie(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, mie, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* mie, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_MIE(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, mie, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mie, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_MIE(MASK)                 \
    __asm__ volatile ("csrrsi    zero, mie, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mie, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_MIE(MASK)               \
    __asm__ volatile ("csrrci    zero, mie, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define MIE_MSI_BIT_OFFSET   3
#define MIE_MSI_BIT_WIDTH    1
#define MIE_MSI_BIT_MASK     0x8
#define MIE_MSI_ALL_SET_MASK 0x1
#define MIE_MTI_BIT_OFFSET   7
#define MIE_MTI_BIT_WIDTH    1
#define MIE_MTI_BIT_MASK     0x80
#define MIE_MTI_ALL_SET_MASK 0x1
#define MIE_MEI_BIT_OFFSET   11
#define MIE_MEI_BIT_WIDTH    1
#define MIE_MEI_BIT_MASK     0x800
#define MIE_MEI_ALL_SET_MASK 0x1
#define MIE_SSI_BIT_OFFSET   1
#define MIE_SSI_BIT_WIDTH    1
#define MIE_SSI_BIT_MASK     0x2
#define MIE_SSI_ALL_SET_MASK 0x1
#define MIE_STI_BIT_OFFSET   5
#define MIE_STI_BIT_WIDTH    1
#define MIE_STI_BIT_MASK     0x20
#define MIE_STI_ALL_SET_MASK 0x1
#define MIE_SEI_BIT_OFFSET   9
#define MIE_SEI_BIT_WIDTH    1
#define MIE_SEI_BIT_MASK     0x200
#define MIE_SEI_ALL_SET_MASK 0x1
#define MIE_USI_BIT_OFFSET   0
#define MIE_USI_BIT_WIDTH    1
#define MIE_USI_BIT_MASK     0x1
#define MIE_USI_ALL_SET_MASK 0x1
#define MIE_UTI_BIT_OFFSET   4
#define MIE_UTI_BIT_WIDTH    1
#define MIE_UTI_BIT_MASK     0x10
#define MIE_UTI_ALL_SET_MASK 0x1
#define MIE_UEI_BIT_OFFSET   8
#define MIE_UEI_BIT_WIDTH    1
#define MIE_UEI_BIT_MASK     0x100
#define MIE_UEI_ALL_SET_MASK 0x1
#define MIE_PLATFORM_DEFINED_BIT_OFFSET   16
#define MIE_PLATFORM_DEFINED_BIT_WIDTH    ((__riscv_xlen)-(16) + 1)
#define MIE_PLATFORM_DEFINED_BIT_MASK     ((1UL<<(((__riscv_xlen)-(16) + 1)-1)) << (16))
#define MIE_PLATFORM_DEFINED_ALL_SET_MASK ((1UL<<(((__riscv_xlen)-(16) + 1)-1)) << (0))

/*******************************************
 * mcountinhibit - MRW - Machine Counter Inhibit 
 */
static inline uint32_t csr_read_mcountinhibit(void) {
    uint_csr32_t value;        
    __asm__ volatile ("csrr    %0, mcountinhibit" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mcountinhibit(uint_csr32_t value) {
    __asm__ volatile ("csrw    mcountinhibit, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint32_t csr_read_write_mcountinhibit(uint32_t new_value) {
    uint_csr32_t prev_value;
    __asm__ volatile ("csrrw    %0, mcountinhibit, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_mcountinhibit(uint32_t mask) {
    __asm__ volatile ("csrrs    zero, mcountinhibit, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_mcountinhibit(uint32_t mask) {
    __asm__ volatile ("csrrc    zero, mcountinhibit, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint32_t csr_read_set_bits_mcountinhibit(uint32_t mask) {
    uint_csr32_t value;
    __asm__ volatile ("csrrs    %0, mcountinhibit, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint32_t csr_read_clr_bits_mcountinhibit(uint32_t mask) {
    uint_csr32_t value;
    __asm__ volatile ("csrrc    %0, mcountinhibit, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* mcountinhibit, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_MCOUNTINHIBIT(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, mcountinhibit, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mcountinhibit, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_MCOUNTINHIBIT(MASK)                 \
    __asm__ volatile ("csrrsi    zero, mcountinhibit, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mcountinhibit, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_MCOUNTINHIBIT(MASK)               \
    __asm__ volatile ("csrrci    zero, mcountinhibit, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define MCOUNTINHIBIT_CY_BIT_OFFSET   0
#define MCOUNTINHIBIT_CY_BIT_WIDTH    1
#define MCOUNTINHIBIT_CY_BIT_MASK     0x1
#define MCOUNTINHIBIT_CY_ALL_SET_MASK 0x1
#define MCOUNTINHIBIT_IR_BIT_OFFSET   2
#define MCOUNTINHIBIT_IR_BIT_WIDTH    1
#define MCOUNTINHIBIT_IR_BIT_MASK     0x4
#define MCOUNTINHIBIT_IR_ALL_SET_MASK 0x1
#define MCOUNTINHIBIT_HPM_BIT_OFFSET   3
#define MCOUNTINHIBIT_HPM_BIT_WIDTH    29
#define MCOUNTINHIBIT_HPM_BIT_MASK     0xfffffff8
#define MCOUNTINHIBIT_HPM_ALL_SET_MASK 0x1fffffff

/*******************************************
 * mcycle - MRW - Clock Cycles Executed Counter 
 */
static inline uint64_t csr_read_mcycle(void) {
    uint_csr64_t value;        
    __asm__ volatile ("csrr    %0, mcycle" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mcycle(uint_csr64_t value) {
    __asm__ volatile ("csrw    mcycle, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mcycle(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mcycle, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * minstret - MRW - Number of Instructions Retired Counter 
 */
static inline uint64_t csr_read_minstret(void) {
    uint_csr64_t value;        
    __asm__ volatile ("csrr    %0, minstret" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_minstret(uint_csr64_t value) {
    __asm__ volatile ("csrw    minstret, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_minstret(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, minstret, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter3 - MRW - Event Counters 
 */
static inline uint64_t csr_read_mhpmcounter3(void) {
    uint_csr64_t value;        
    __asm__ volatile ("csrr    %0, mhpmcounter3" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter3(uint_csr64_t value) {
    __asm__ volatile ("csrw    mhpmcounter3, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint64_t csr_read_write_mhpmcounter3(uint64_t new_value) {
    uint_csr64_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter3, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmevent3 - MRW - Event Counter Event Select 
 */
static inline uint_xlen_t csr_read_mhpmevent3(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mhpmevent3" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmevent3(uint_xlen_t value) {
    __asm__ volatile ("csrw    mhpmevent3, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mhpmevent3(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmevent3, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mcounteren - MRW - Counter Enable 
 */
static inline uint32_t csr_read_mcounteren(void) {
    uint_csr32_t value;        
    __asm__ volatile ("csrr    %0, mcounteren" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mcounteren(uint_csr32_t value) {
    __asm__ volatile ("csrw    mcounteren, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint32_t csr_read_write_mcounteren(uint32_t new_value) {
    uint_csr32_t prev_value;
    __asm__ volatile ("csrrw    %0, mcounteren, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_mcounteren(uint32_t mask) {
    __asm__ volatile ("csrrs    zero, mcounteren, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_mcounteren(uint32_t mask) {
    __asm__ volatile ("csrrc    zero, mcounteren, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint32_t csr_read_set_bits_mcounteren(uint32_t mask) {
    uint_csr32_t value;
    __asm__ volatile ("csrrs    %0, mcounteren, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint32_t csr_read_clr_bits_mcounteren(uint32_t mask) {
    uint_csr32_t value;
    __asm__ volatile ("csrrc    %0, mcounteren, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* mcounteren, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_MCOUNTEREN(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, mcounteren, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mcounteren, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_MCOUNTEREN(MASK)                 \
    __asm__ volatile ("csrrsi    zero, mcounteren, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mcounteren, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_MCOUNTEREN(MASK)               \
    __asm__ volatile ("csrrci    zero, mcounteren, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define MCOUNTEREN_CY_BIT_OFFSET   0
#define MCOUNTEREN_CY_BIT_WIDTH    1
#define MCOUNTEREN_CY_BIT_MASK     0x1
#define MCOUNTEREN_CY_ALL_SET_MASK 0x1
#define MCOUNTEREN_TM_BIT_OFFSET   1
#define MCOUNTEREN_TM_BIT_WIDTH    1
#define MCOUNTEREN_TM_BIT_MASK     0x2
#define MCOUNTEREN_TM_ALL_SET_MASK 0x1
#define MCOUNTEREN_IR_BIT_OFFSET   2
#define MCOUNTEREN_IR_BIT_WIDTH    1
#define MCOUNTEREN_IR_BIT_MASK     0x4
#define MCOUNTEREN_IR_ALL_SET_MASK 0x1
#define MCOUNTEREN_HPM_BIT_OFFSET   3
#define MCOUNTEREN_HPM_BIT_WIDTH    29
#define MCOUNTEREN_HPM_BIT_MASK     0xfffffff8
#define MCOUNTEREN_HPM_ALL_SET_MASK 0x1fffffff

/*******************************************
 * scounteren - SRW - Counter Enable 
 */
static inline uint_xlen_t csr_read_scounteren(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, scounteren" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_scounteren(uint_xlen_t value) {
    __asm__ volatile ("csrw    scounteren, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_scounteren(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, scounteren, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mscratch - MRW - Machine Mode Scratch Register 
 */
static inline uint_xlen_t csr_read_mscratch(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mscratch" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mscratch(uint_xlen_t value) {
    __asm__ volatile ("csrw    mscratch, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mscratch(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mscratch, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mepc - MRW - Machine Exception Program Counter 
 */
static inline uint_xlen_t csr_read_mepc(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mepc" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mepc(uint_xlen_t value) {
    __asm__ volatile ("csrw    mepc, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mepc(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mepc, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mcause - MRW - Machine Exception Cause 
 */
static inline uint_xlen_t csr_read_mcause(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mcause" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mcause(uint_xlen_t value) {
    __asm__ volatile ("csrw    mcause, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mcause(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mcause, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_mcause(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, mcause, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_mcause(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, mcause, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_mcause(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, mcause, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_mcause(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, mcause, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* mcause, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_MCAUSE(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, mcause, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mcause, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_MCAUSE(MASK)                 \
    __asm__ volatile ("csrrsi    zero, mcause, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* mcause, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_MCAUSE(MASK)               \
    __asm__ volatile ("csrrci    zero, mcause, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define MCAUSE_INTERRUPT_BIT_OFFSET   (__riscv_xlen-1)
#define MCAUSE_INTERRUPT_BIT_WIDTH    1
#define MCAUSE_INTERRUPT_BIT_MASK     (0x1UL << ((__riscv_xlen-1)))
#define MCAUSE_INTERRUPT_ALL_SET_MASK 0x1
#define MCAUSE_EXCEPTION_CODE_BIT_OFFSET   0
#define MCAUSE_EXCEPTION_CODE_BIT_WIDTH    ((__riscv_xlen-2)-(0) + 1)
#define MCAUSE_EXCEPTION_CODE_BIT_MASK     ((1UL<<(((__riscv_xlen-2)-(0) + 1)-1)) << (0))
#define MCAUSE_EXCEPTION_CODE_ALL_SET_MASK ((1UL<<(((__riscv_xlen-2)-(0) + 1)-1)) << (0))

/*******************************************
 * mtval - MRW - Machine Trap Value 
 */
static inline uint_xlen_t csr_read_mtval(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mtval" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mtval(uint_xlen_t value) {
    __asm__ volatile ("csrw    mtval, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mtval(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mtval, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * sscratch - SRW - Supervisor Mode Scratch Register 
 */
static inline uint_xlen_t csr_read_sscratch(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, sscratch" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_sscratch(uint_xlen_t value) {
    __asm__ volatile ("csrw    sscratch, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_sscratch(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, sscratch, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * sepc - SRW - Supervisor Exception Program Counter 
 */
static inline uint_xlen_t csr_read_sepc(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, sepc" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_sepc(uint_xlen_t value) {
    __asm__ volatile ("csrw    sepc, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_sepc(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, sepc, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * scause - SRW - Supervisor Exception Cause 
 */
static inline uint_xlen_t csr_read_scause(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, scause" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_scause(uint_xlen_t value) {
    __asm__ volatile ("csrw    scause, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_scause(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, scause, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_scause(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, scause, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_scause(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, scause, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_scause(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, scause, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_scause(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, scause, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* scause, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_SCAUSE(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, scause, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* scause, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_SCAUSE(MASK)                 \
    __asm__ volatile ("csrrsi    zero, scause, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* scause, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_SCAUSE(MASK)               \
    __asm__ volatile ("csrrci    zero, scause, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define SCAUSE_INTERRUPT_BIT_OFFSET   (__riscv_xlen-1)
#define SCAUSE_INTERRUPT_BIT_WIDTH    1
#define SCAUSE_INTERRUPT_BIT_MASK     (0x1UL << ((__riscv_xlen-1)))
#define SCAUSE_INTERRUPT_ALL_SET_MASK 0x1
#define SCAUSE_EXCEPTION_CODE_BIT_OFFSET   0
#define SCAUSE_EXCEPTION_CODE_BIT_WIDTH    ((__riscv_xlen-2)-(0) + 1)
#define SCAUSE_EXCEPTION_CODE_BIT_MASK     ((1UL<<(((__riscv_xlen-2)-(0) + 1)-1)) << (0))
#define SCAUSE_EXCEPTION_CODE_ALL_SET_MASK ((1UL<<(((__riscv_xlen-2)-(0) + 1)-1)) << (0))

/*******************************************
 * sstatus - SRW - Supervisor Status 
 */
static inline uint_xlen_t csr_read_sstatus(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, sstatus" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_sstatus(uint_xlen_t value) {
    __asm__ volatile ("csrw    sstatus, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_sstatus(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, sstatus, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_sstatus(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, sstatus, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_sstatus(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, sstatus, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_sstatus(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, sstatus, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_sstatus(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, sstatus, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* sstatus, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_SSTATUS(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, sstatus, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* sstatus, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_SSTATUS(MASK)                 \
    __asm__ volatile ("csrrsi    zero, sstatus, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* sstatus, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_SSTATUS(MASK)               \
    __asm__ volatile ("csrrci    zero, sstatus, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define SSTATUS_SIE_BIT_OFFSET   2
#define SSTATUS_SIE_BIT_WIDTH    1
#define SSTATUS_SIE_BIT_MASK     0x4
#define SSTATUS_SIE_ALL_SET_MASK 0x1
#define SSTATUS_SPIE_BIT_OFFSET   5
#define SSTATUS_SPIE_BIT_WIDTH    1
#define SSTATUS_SPIE_BIT_MASK     0x20
#define SSTATUS_SPIE_ALL_SET_MASK 0x1
#define SSTATUS_SPP_BIT_OFFSET   8
#define SSTATUS_SPP_BIT_WIDTH    1
#define SSTATUS_SPP_BIT_MASK     0x100
#define SSTATUS_SPP_ALL_SET_MASK 0x1

/*******************************************
 * stvec - SRW - Supervisor Trap Vector Base Address 
 */
static inline uint_xlen_t csr_read_stvec(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, stvec" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_stvec(uint_xlen_t value) {
    __asm__ volatile ("csrw    stvec, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_stvec(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, stvec, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_stvec(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, stvec, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_stvec(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, stvec, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_stvec(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, stvec, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_stvec(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, stvec, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* stvec, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_STVEC(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, stvec, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* stvec, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_STVEC(MASK)                 \
    __asm__ volatile ("csrrsi    zero, stvec, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* stvec, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_STVEC(MASK)               \
    __asm__ volatile ("csrrci    zero, stvec, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define STVEC_BASE_BIT_OFFSET   2
#define STVEC_BASE_BIT_WIDTH    ((__riscv_xlen-1)-(2) + 1)
#define STVEC_BASE_BIT_MASK     ((1UL<<(((__riscv_xlen-1)-(2) + 1)-1)) << (2))
#define STVEC_BASE_ALL_SET_MASK ((1UL<<(((__riscv_xlen-1)-(2) + 1)-1)) << (0))
#define STVEC_MODE_BIT_OFFSET   0
#define STVEC_MODE_BIT_WIDTH    2
#define STVEC_MODE_BIT_MASK     0x3
#define STVEC_MODE_ALL_SET_MASK 0x3

/*******************************************
 * sideleg - SRW - Supervisor Interrupt Delegation 
 */
static inline uint_xlen_t csr_read_sideleg(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, sideleg" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_sideleg(uint_xlen_t value) {
    __asm__ volatile ("csrw    sideleg, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_sideleg(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, sideleg, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * sedeleg - SRW - Supervisor Exception Delegation 
 */
static inline uint_xlen_t csr_read_sedeleg(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, sedeleg" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_sedeleg(uint_xlen_t value) {
    __asm__ volatile ("csrw    sedeleg, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_sedeleg(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, sedeleg, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * sip - SRW - Supervisor Interrupt Pending 
 */
static inline uint_xlen_t csr_read_sip(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, sip" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_sip(uint_xlen_t value) {
    __asm__ volatile ("csrw    sip, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_sip(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, sip, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_sip(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, sip, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_sip(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, sip, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_sip(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, sip, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_sip(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, sip, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* sip, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_SIP(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, sip, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* sip, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_SIP(MASK)                 \
    __asm__ volatile ("csrrsi    zero, sip, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* sip, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_SIP(MASK)               \
    __asm__ volatile ("csrrci    zero, sip, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define SIP_SSI_BIT_OFFSET   1
#define SIP_SSI_BIT_WIDTH    1
#define SIP_SSI_BIT_MASK     0x2
#define SIP_SSI_ALL_SET_MASK 0x1
#define SIP_STI_BIT_OFFSET   5
#define SIP_STI_BIT_WIDTH    1
#define SIP_STI_BIT_MASK     0x20
#define SIP_STI_ALL_SET_MASK 0x1
#define SIP_SEI_BIT_OFFSET   9
#define SIP_SEI_BIT_WIDTH    1
#define SIP_SEI_BIT_MASK     0x200
#define SIP_SEI_ALL_SET_MASK 0x1
#define SIP_USI_BIT_OFFSET   0
#define SIP_USI_BIT_WIDTH    1
#define SIP_USI_BIT_MASK     0x1
#define SIP_USI_ALL_SET_MASK 0x1
#define SIP_UTI_BIT_OFFSET   4
#define SIP_UTI_BIT_WIDTH    1
#define SIP_UTI_BIT_MASK     0x10
#define SIP_UTI_ALL_SET_MASK 0x1
#define SIP_UEI_BIT_OFFSET   8
#define SIP_UEI_BIT_WIDTH    1
#define SIP_UEI_BIT_MASK     0x100
#define SIP_UEI_ALL_SET_MASK 0x1

/*******************************************
 * sie - SRW - Supervisor Interrupt Enable 
 */
static inline uint_xlen_t csr_read_sie(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, sie" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_sie(uint_xlen_t value) {
    __asm__ volatile ("csrw    sie, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_sie(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, sie, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_sie(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, sie, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_sie(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, sie, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_sie(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, sie, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_sie(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, sie, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* sie, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_SIE(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, sie, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* sie, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_SIE(MASK)                 \
    __asm__ volatile ("csrrsi    zero, sie, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* sie, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_SIE(MASK)               \
    __asm__ volatile ("csrrci    zero, sie, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define SIE_SSI_BIT_OFFSET   1
#define SIE_SSI_BIT_WIDTH    1
#define SIE_SSI_BIT_MASK     0x2
#define SIE_SSI_ALL_SET_MASK 0x1
#define SIE_STI_BIT_OFFSET   5
#define SIE_STI_BIT_WIDTH    1
#define SIE_STI_BIT_MASK     0x20
#define SIE_STI_ALL_SET_MASK 0x1
#define SIE_SEI_BIT_OFFSET   9
#define SIE_SEI_BIT_WIDTH    1
#define SIE_SEI_BIT_MASK     0x200
#define SIE_SEI_ALL_SET_MASK 0x1
#define SIE_USI_BIT_OFFSET   0
#define SIE_USI_BIT_WIDTH    1
#define SIE_USI_BIT_MASK     0x1
#define SIE_USI_ALL_SET_MASK 0x1
#define SIE_UTI_BIT_OFFSET   4
#define SIE_UTI_BIT_WIDTH    1
#define SIE_UTI_BIT_MASK     0x10
#define SIE_UTI_ALL_SET_MASK 0x1
#define SIE_UEI_BIT_OFFSET   8
#define SIE_UEI_BIT_WIDTH    1
#define SIE_UEI_BIT_MASK     0x100
#define SIE_UEI_ALL_SET_MASK 0x1

/*******************************************
 * ustatus - URW - User mode restricted view of mstatus 
 */
static inline uint_xlen_t csr_read_ustatus(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, ustatus" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_ustatus(uint_xlen_t value) {
    __asm__ volatile ("csrw    ustatus, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_ustatus(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, ustatus, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_ustatus(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, ustatus, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_ustatus(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, ustatus, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_ustatus(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, ustatus, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_ustatus(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, ustatus, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* ustatus, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_USTATUS(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, ustatus, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* ustatus, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_USTATUS(MASK)                 \
    __asm__ volatile ("csrrsi    zero, ustatus, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* ustatus, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_USTATUS(MASK)               \
    __asm__ volatile ("csrrci    zero, ustatus, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define USTATUS_UIE_BIT_OFFSET   1
#define USTATUS_UIE_BIT_WIDTH    1
#define USTATUS_UIE_BIT_MASK     0x2
#define USTATUS_UIE_ALL_SET_MASK 0x1
#define USTATUS_UPIE_BIT_OFFSET   3
#define USTATUS_UPIE_BIT_WIDTH    1
#define USTATUS_UPIE_BIT_MASK     0x8
#define USTATUS_UPIE_ALL_SET_MASK 0x1

/*******************************************
 * uip - URW - User Interrupt Pending 
 */
static inline uint_xlen_t csr_read_uip(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, uip" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_uip(uint_xlen_t value) {
    __asm__ volatile ("csrw    uip, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_uip(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, uip, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_uip(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, uip, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_uip(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, uip, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_uip(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, uip, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_uip(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, uip, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* uip, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_UIP(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, uip, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* uip, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_UIP(MASK)                 \
    __asm__ volatile ("csrrsi    zero, uip, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* uip, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_UIP(MASK)               \
    __asm__ volatile ("csrrci    zero, uip, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define UIP_USI_BIT_OFFSET   0
#define UIP_USI_BIT_WIDTH    1
#define UIP_USI_BIT_MASK     0x1
#define UIP_USI_ALL_SET_MASK 0x1
#define UIP_UTI_BIT_OFFSET   4
#define UIP_UTI_BIT_WIDTH    1
#define UIP_UTI_BIT_MASK     0x10
#define UIP_UTI_ALL_SET_MASK 0x1
#define UIP_UEI_BIT_OFFSET   8
#define UIP_UEI_BIT_WIDTH    1
#define UIP_UEI_BIT_MASK     0x100
#define UIP_UEI_ALL_SET_MASK 0x1

/*******************************************
 * uie - URW - User Interrupt Enable 
 */
static inline uint_xlen_t csr_read_uie(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, uie" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_uie(uint_xlen_t value) {
    __asm__ volatile ("csrw    uie, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_uie(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, uie, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_uie(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, uie, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_uie(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, uie, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_uie(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, uie, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_uie(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, uie, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* uie, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_UIE(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, uie, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* uie, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_UIE(MASK)                 \
    __asm__ volatile ("csrrsi    zero, uie, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* uie, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_UIE(MASK)               \
    __asm__ volatile ("csrrci    zero, uie, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define UIE_USI_BIT_OFFSET   0
#define UIE_USI_BIT_WIDTH    1
#define UIE_USI_BIT_MASK     0x1
#define UIE_USI_ALL_SET_MASK 0x1
#define UIE_UTI_BIT_OFFSET   4
#define UIE_UTI_BIT_WIDTH    1
#define UIE_UTI_BIT_MASK     0x10
#define UIE_UTI_ALL_SET_MASK 0x1
#define UIE_UEI_BIT_OFFSET   8
#define UIE_UEI_BIT_WIDTH    1
#define UIE_UEI_BIT_MASK     0x100
#define UIE_UEI_ALL_SET_MASK 0x1

/*******************************************
 * uscratch - URW - User Mode Scratch Register 
 */
static inline uint_xlen_t csr_read_uscratch(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, uscratch" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_uscratch(uint_xlen_t value) {
    __asm__ volatile ("csrw    uscratch, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_uscratch(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, uscratch, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * uepc - URW - User Exception Program Counter 
 */
static inline uint_xlen_t csr_read_uepc(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, uepc" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_uepc(uint_xlen_t value) {
    __asm__ volatile ("csrw    uepc, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_uepc(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, uepc, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * ucause - URW - User Exception Cause 
 */
static inline uint_xlen_t csr_read_ucause(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, ucause" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_ucause(uint_xlen_t value) {
    __asm__ volatile ("csrw    ucause, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_ucause(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, ucause, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_ucause(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, ucause, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_ucause(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, ucause, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_ucause(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, ucause, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_ucause(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, ucause, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* ucause, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_UCAUSE(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, ucause, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* ucause, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_UCAUSE(MASK)                 \
    __asm__ volatile ("csrrsi    zero, ucause, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* ucause, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_UCAUSE(MASK)               \
    __asm__ volatile ("csrrci    zero, ucause, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define UCAUSE_INTERRUPT_BIT_OFFSET   (__riscv_xlen-1)
#define UCAUSE_INTERRUPT_BIT_WIDTH    1
#define UCAUSE_INTERRUPT_BIT_MASK     (0x1UL << ((__riscv_xlen-1)))
#define UCAUSE_INTERRUPT_ALL_SET_MASK 0x1
#define UCAUSE_EXCEPTION_CODE_BIT_OFFSET   0
#define UCAUSE_EXCEPTION_CODE_BIT_WIDTH    ((__riscv_xlen-2)-(0) + 1)
#define UCAUSE_EXCEPTION_CODE_BIT_MASK     ((1UL<<(((__riscv_xlen-2)-(0) + 1)-1)) << (0))
#define UCAUSE_EXCEPTION_CODE_ALL_SET_MASK ((1UL<<(((__riscv_xlen-2)-(0) + 1)-1)) << (0))

/*******************************************
 * utvec - URW - User Trap Vector Base Address 
 */
static inline uint_xlen_t csr_read_utvec(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, utvec" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_utvec(uint_xlen_t value) {
    __asm__ volatile ("csrw    utvec, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_utvec(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, utvec, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}
/* Register CSR bit set and clear instructions */
static inline void csr_set_bits_utvec(uint_xlen_t mask) {
    __asm__ volatile ("csrrs    zero, utvec, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline void csr_clr_bits_utvec(uint_xlen_t mask) {
    __asm__ volatile ("csrrc    zero, utvec, %0"  
                      : /* output: none */ 
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_set_bits_utvec(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrs    %0, utvec, %1"  
                      : "=r" (value) /* output: register %0 */
                      : "r" (mask)  /* input : register */
                      : /* clobbers: none */);
    return value;
}
static inline uint_xlen_t csr_read_clr_bits_utvec(uint_xlen_t mask) {
    uint_xlen_t value;
    __asm__ volatile ("csrrc    %0, utvec, %1"  
                                  : "=r" (value) /* output: register %0 */
                                  : "r" (mask)  /* input : register */
                                  : /* clobbers: none */);
    return value;
}
/* utvec, CSR write value via immediate value (only up to 5 bits) */
#define CSR_WRITE_IMM_UTVEC(VALUE)                    \
    __asm__ volatile ("csrrwi    zero, utvec, %0"           \
                      : /* output: none */                         \
                      : "i" (VALUE)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* utvec, CSR set bits via immediate value mask (only up to 5 bits) */
#define CSR_SET_BITS_IMM_UTVEC(MASK)                 \
    __asm__ volatile ("csrrsi    zero, utvec, %0"          \
                      : /* output: none */                        \
                      : "i" (MASK)  /* input : immediate  */      \
                      : /* clobbers: none */)

/* utvec, CSR clear bits via immediate value mask (only up to 5 bits) */
#define CSR_CLR_BITS_IMM_UTVEC(MASK)               \
    __asm__ volatile ("csrrci    zero, utvec, %0"        \
                      : /* output: none */                      \
                      : "i" (MASK)  /* input : immediate */     \
                      : /* clobbers: none */)
#define UTVEC_BASE_BIT_OFFSET   2
#define UTVEC_BASE_BIT_WIDTH    ((__riscv_xlen-1)-(2) + 1)
#define UTVEC_BASE_BIT_MASK     ((1UL<<(((__riscv_xlen-1)-(2) + 1)-1)) << (2))
#define UTVEC_BASE_ALL_SET_MASK ((1UL<<(((__riscv_xlen-1)-(2) + 1)-1)) << (0))
#define UTVEC_MODE_BIT_OFFSET   0
#define UTVEC_MODE_BIT_WIDTH    2
#define UTVEC_MODE_BIT_MASK     0x3
#define UTVEC_MODE_ALL_SET_MASK 0x3

/*******************************************
 * utval - URW - User Trap Value 
 */
static inline uint_xlen_t csr_read_utval(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, utval" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_utval(uint_xlen_t value) {
    __asm__ volatile ("csrw    utval, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_utval(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, utval, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * fflags - URW - Floating-Point Accrued Exceptions. 
 */
static inline uint_xlen_t csr_read_fflags(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, fflags" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_fflags(uint_xlen_t value) {
    __asm__ volatile ("csrw    fflags, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_fflags(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, fflags, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * frm - URW - Floating-Point Dynamic Rounding Mode. 
 */
static inline uint_xlen_t csr_read_frm(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, frm" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_frm(uint_xlen_t value) {
    __asm__ volatile ("csrw    frm, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_frm(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, frm, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * fcsr - URW - Floating-Point Control and Status 
 */
static inline uint_xlen_t csr_read_fcsr(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, fcsr" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_fcsr(uint_xlen_t value) {
    __asm__ volatile ("csrw    fcsr, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_fcsr(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, fcsr, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * cycle - URO - Cycle counter for RDCYCLE instruction. 
 */
static inline uint_xlen_t csr_read_cycle(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, cycle" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * time - URO - Timer for RDTIME instruction. 
 */
static inline uint_xlen_t csr_read_time(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, time" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * instret - URO - Instructions-retired counter for RDINSTRET instruction. 
 */
static inline uint_xlen_t csr_read_instret(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, instret" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * hpmcounter3 - URO - Performance-monitoring counter. 
 */
static inline uint_xlen_t csr_read_hpmcounter3(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, hpmcounter3" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * hpmcounter4 - URO - Performance-monitoring counter. 
 */
static inline uint_xlen_t csr_read_hpmcounter4(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, hpmcounter4" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * hpmcounter31 - URO - Performance-monitoring counter. 
 */
static inline uint_xlen_t csr_read_hpmcounter31(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, hpmcounter31" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * cycleh - URO - Upper 32 bits of  cycle, RV32I only. 
 */
static inline uint_xlen_t csr_read_cycleh(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, cycleh" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * timeh - URO - Upper 32 bits of  time, RV32I only. 
 */
static inline uint_xlen_t csr_read_timeh(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, timeh" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * instreth - URO - Upper 32 bits of  instret, RV32I only. 
 */
static inline uint_xlen_t csr_read_instreth(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, instreth" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * hpmcounter3h - URO - Upper 32 bits of  hpmcounter3, RV32I only. 
 */
static inline uint_xlen_t csr_read_hpmcounter3h(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, hpmcounter3h" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * hpmcounter4h - URO - Upper 32 bits of  hpmcounter4, RV32I only. 
 */
static inline uint_xlen_t csr_read_hpmcounter4h(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, hpmcounter4h" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * hpmcounter31h - URO - Upper 32 bits of  hpmcounter31, RV32I only. 
 */
static inline uint_xlen_t csr_read_hpmcounter31h(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, hpmcounter31h" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * stval - SRW - Supervisor bad address or instruction. 
 */
static inline uint_xlen_t csr_read_stval(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, stval" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_stval(uint_xlen_t value) {
    __asm__ volatile ("csrw    stval, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_stval(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, stval, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * satp - SRW - Supervisor address translation and protection. 
 */
static inline uint_xlen_t csr_read_satp(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, satp" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_satp(uint_xlen_t value) {
    __asm__ volatile ("csrw    satp, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_satp(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, satp, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * hstatus - HRW - Hypervisor status register. 
 */
static inline uint_xlen_t csr_read_hstatus(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, hstatus" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_hstatus(uint_xlen_t value) {
    __asm__ volatile ("csrw    hstatus, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_hstatus(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, hstatus, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * hedeleg - HRW - Hypervisor exception delegation register. 
 */
static inline uint_xlen_t csr_read_hedeleg(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, hedeleg" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_hedeleg(uint_xlen_t value) {
    __asm__ volatile ("csrw    hedeleg, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_hedeleg(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, hedeleg, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * hideleg - HRW - Hypervisor interrupt delegation register. 
 */
static inline uint_xlen_t csr_read_hideleg(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, hideleg" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_hideleg(uint_xlen_t value) {
    __asm__ volatile ("csrw    hideleg, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_hideleg(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, hideleg, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * hcounteren - HRW - Hypervisor counter enable. 
 */
static inline uint_xlen_t csr_read_hcounteren(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, hcounteren" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_hcounteren(uint_xlen_t value) {
    __asm__ volatile ("csrw    hcounteren, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_hcounteren(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, hcounteren, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * hgatp - HRW - Hypervisor guest address translation and protection. 
 */
static inline uint_xlen_t csr_read_hgatp(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, hgatp" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_hgatp(uint_xlen_t value) {
    __asm__ volatile ("csrw    hgatp, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_hgatp(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, hgatp, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * htimedelta - HRW - Delta for VS/VU-mode timer. 
 */
static inline uint_xlen_t csr_read_htimedelta(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, htimedelta" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_htimedelta(uint_xlen_t value) {
    __asm__ volatile ("csrw    htimedelta, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_htimedelta(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, htimedelta, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * htimedeltah - HRW - Upper 32 bits of  htimedelta, RV32I only. 
 */
static inline uint_xlen_t csr_read_htimedeltah(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, htimedeltah" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_htimedeltah(uint_xlen_t value) {
    __asm__ volatile ("csrw    htimedeltah, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_htimedeltah(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, htimedeltah, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * vsstatus - HRW - Virtual supervisor status register. 
 */
static inline uint_xlen_t csr_read_vsstatus(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, vsstatus" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_vsstatus(uint_xlen_t value) {
    __asm__ volatile ("csrw    vsstatus, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_vsstatus(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, vsstatus, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * vsie - HRW - Virtual supervisor interrupt-enable register. 
 */
static inline uint_xlen_t csr_read_vsie(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, vsie" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_vsie(uint_xlen_t value) {
    __asm__ volatile ("csrw    vsie, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_vsie(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, vsie, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * vstvec - HRW - Virtual supervisor trap handler base address. 
 */
static inline uint_xlen_t csr_read_vstvec(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, vstvec" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_vstvec(uint_xlen_t value) {
    __asm__ volatile ("csrw    vstvec, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_vstvec(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, vstvec, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * vsscratch - HRW - Virtual supervisor scratch register. 
 */
static inline uint_xlen_t csr_read_vsscratch(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, vsscratch" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_vsscratch(uint_xlen_t value) {
    __asm__ volatile ("csrw    vsscratch, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_vsscratch(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, vsscratch, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * vsepc - HRW - Virtual supervisor exception program counter. 
 */
static inline uint_xlen_t csr_read_vsepc(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, vsepc" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_vsepc(uint_xlen_t value) {
    __asm__ volatile ("csrw    vsepc, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_vsepc(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, vsepc, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * vscause - HRW - Virtual supervisor trap cause. 
 */
static inline uint_xlen_t csr_read_vscause(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, vscause" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_vscause(uint_xlen_t value) {
    __asm__ volatile ("csrw    vscause, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_vscause(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, vscause, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * vstval - HRW - Virtual supervisor bad address or instruction. 
 */
static inline uint_xlen_t csr_read_vstval(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, vstval" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_vstval(uint_xlen_t value) {
    __asm__ volatile ("csrw    vstval, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_vstval(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, vstval, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * vsip - HRW - Virtual supervisor interrupt pending. 
 */
static inline uint_xlen_t csr_read_vsip(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, vsip" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_vsip(uint_xlen_t value) {
    __asm__ volatile ("csrw    vsip, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_vsip(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, vsip, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * vsatp - HRW - Virtual supervisor address translation and protection. 
 */
static inline uint_xlen_t csr_read_vsatp(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, vsatp" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_vsatp(uint_xlen_t value) {
    __asm__ volatile ("csrw    vsatp, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_vsatp(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, vsatp, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mbase - MRW - Base register. 
 */
static inline uint_xlen_t csr_read_mbase(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mbase" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mbase(uint_xlen_t value) {
    __asm__ volatile ("csrw    mbase, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mbase(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mbase, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mbound - MRW - Bound register. 
 */
static inline uint_xlen_t csr_read_mbound(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mbound" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mbound(uint_xlen_t value) {
    __asm__ volatile ("csrw    mbound, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mbound(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mbound, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mibase - MRW - Instruction base register. 
 */
static inline uint_xlen_t csr_read_mibase(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mibase" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mibase(uint_xlen_t value) {
    __asm__ volatile ("csrw    mibase, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mibase(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mibase, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mibound - MRW - Instruction bound register. 
 */
static inline uint_xlen_t csr_read_mibound(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mibound" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mibound(uint_xlen_t value) {
    __asm__ volatile ("csrw    mibound, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mibound(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mibound, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mdbase - MRW - Data base register. 
 */
static inline uint_xlen_t csr_read_mdbase(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mdbase" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mdbase(uint_xlen_t value) {
    __asm__ volatile ("csrw    mdbase, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mdbase(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mdbase, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mdbound - MRW - Data bound register. 
 */
static inline uint_xlen_t csr_read_mdbound(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mdbound" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mdbound(uint_xlen_t value) {
    __asm__ volatile ("csrw    mdbound, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mdbound(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mdbound, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * pmpcfg0 - MRW - Physical memory protection configuration. 
 */
static inline uint_xlen_t csr_read_pmpcfg0(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, pmpcfg0" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_pmpcfg0(uint_xlen_t value) {
    __asm__ volatile ("csrw    pmpcfg0, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_pmpcfg0(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, pmpcfg0, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * pmpcfg1 - MRW - Physical memory protection configuration, RV32 only. 
 */
static inline uint_xlen_t csr_read_pmpcfg1(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, pmpcfg1" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_pmpcfg1(uint_xlen_t value) {
    __asm__ volatile ("csrw    pmpcfg1, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_pmpcfg1(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, pmpcfg1, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * pmpcfg2 - MRW - Physical memory protection configuration. 
 */
static inline uint_xlen_t csr_read_pmpcfg2(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, pmpcfg2" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_pmpcfg2(uint_xlen_t value) {
    __asm__ volatile ("csrw    pmpcfg2, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_pmpcfg2(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, pmpcfg2, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * pmpcfg3 - MRW - Physical memory protection configuration, RV32 only. 
 */
static inline uint_xlen_t csr_read_pmpcfg3(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, pmpcfg3" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_pmpcfg3(uint_xlen_t value) {
    __asm__ volatile ("csrw    pmpcfg3, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_pmpcfg3(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, pmpcfg3, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * pmpaddr0 - MRW - Physical memory protection address register. 
 */
static inline uint_xlen_t csr_read_pmpaddr0(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, pmpaddr0" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_pmpaddr0(uint_xlen_t value) {
    __asm__ volatile ("csrw    pmpaddr0, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_pmpaddr0(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, pmpaddr0, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * pmpaddr1 - MRW - Physical memory protection address register. 
 */
static inline uint_xlen_t csr_read_pmpaddr1(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, pmpaddr1" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_pmpaddr1(uint_xlen_t value) {
    __asm__ volatile ("csrw    pmpaddr1, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_pmpaddr1(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, pmpaddr1, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * pmpaddr15 - MRW - Physical memory protection address register. 
 */
static inline uint_xlen_t csr_read_pmpaddr15(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, pmpaddr15" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_pmpaddr15(uint_xlen_t value) {
    __asm__ volatile ("csrw    pmpaddr15, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_pmpaddr15(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, pmpaddr15, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter4 - MRW - Machine performance-monitoring counter. 
 */
static inline uint_xlen_t csr_read_mhpmcounter4(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mhpmcounter4" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter4(uint_xlen_t value) {
    __asm__ volatile ("csrw    mhpmcounter4, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mhpmcounter4(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter4, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter31 - MRW - Machine performance-monitoring counter. 
 */
static inline uint_xlen_t csr_read_mhpmcounter31(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mhpmcounter31" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter31(uint_xlen_t value) {
    __asm__ volatile ("csrw    mhpmcounter31, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mhpmcounter31(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter31, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mcycleh - MRW - Upper 32 bits of  mcycle, RV32I only. 
 */
static inline uint32_t csr_read_mcycleh(void) {
    uint_csr32_t value;        
    __asm__ volatile ("csrr    %0, mcycleh" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mcycleh(uint_csr32_t value) {
    __asm__ volatile ("csrw    mcycleh, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint32_t csr_read_write_mcycleh(uint32_t new_value) {
    uint_csr32_t prev_value;
    __asm__ volatile ("csrrw    %0, mcycleh, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * minstreth - MRW - Upper 32 bits of  minstret, RV32I only. 
 */
static inline uint32_t csr_read_minstreth(void) {
    uint_csr32_t value;        
    __asm__ volatile ("csrr    %0, minstreth" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_minstreth(uint_csr32_t value) {
    __asm__ volatile ("csrw    minstreth, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint32_t csr_read_write_minstreth(uint32_t new_value) {
    uint_csr32_t prev_value;
    __asm__ volatile ("csrrw    %0, minstreth, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter3h - MRW - Upper 32 bits of  mhpmcounter3, RV32I only. 
 */
static inline uint32_t csr_read_mhpmcounter3h(void) {
    uint_csr32_t value;        
    __asm__ volatile ("csrr    %0, mhpmcounter3h" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter3h(uint_csr32_t value) {
    __asm__ volatile ("csrw    mhpmcounter3h, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint32_t csr_read_write_mhpmcounter3h(uint32_t new_value) {
    uint_csr32_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter3h, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter4h - MRW - Upper 32 bits of  mhpmcounter4, RV32I only. 
 */
static inline uint32_t csr_read_mhpmcounter4h(void) {
    uint_csr32_t value;        
    __asm__ volatile ("csrr    %0, mhpmcounter4h" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter4h(uint_csr32_t value) {
    __asm__ volatile ("csrw    mhpmcounter4h, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint32_t csr_read_write_mhpmcounter4h(uint32_t new_value) {
    uint_csr32_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter4h, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmcounter31h - MRW - Upper 32 bits of  mhpmcounter31, RV32I only. 
 */
static inline uint32_t csr_read_mhpmcounter31h(void) {
    uint_csr32_t value;        
    __asm__ volatile ("csrr    %0, mhpmcounter31h" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmcounter31h(uint_csr32_t value) {
    __asm__ volatile ("csrw    mhpmcounter31h, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint32_t csr_read_write_mhpmcounter31h(uint32_t new_value) {
    uint_csr32_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmcounter31h, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmevent4 - MRW - Machine performance-monitoring event selector. 
 */
static inline uint_xlen_t csr_read_mhpmevent4(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mhpmevent4" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmevent4(uint_xlen_t value) {
    __asm__ volatile ("csrw    mhpmevent4, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mhpmevent4(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmevent4, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mhpmevent31 - MRW - Machine performance-monitoring event selector. 
 */
static inline uint_xlen_t csr_read_mhpmevent31(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mhpmevent31" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mhpmevent31(uint_xlen_t value) {
    __asm__ volatile ("csrw    mhpmevent31, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mhpmevent31(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mhpmevent31, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * tselect - MRW - Debug/Trace trigger register select. 
 */
static inline uint_xlen_t csr_read_tselect(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, tselect" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_tselect(uint_xlen_t value) {
    __asm__ volatile ("csrw    tselect, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_tselect(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, tselect, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * tdata1 - MRW - First Debug/Trace trigger data register. 
 */
static inline uint_xlen_t csr_read_tdata1(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, tdata1" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_tdata1(uint_xlen_t value) {
    __asm__ volatile ("csrw    tdata1, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_tdata1(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, tdata1, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * tdata2 - MRW - Second Debug/Trace trigger data register. 
 */
static inline uint_xlen_t csr_read_tdata2(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, tdata2" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_tdata2(uint_xlen_t value) {
    __asm__ volatile ("csrw    tdata2, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_tdata2(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, tdata2, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * tdata3 - MRW - Third Debug/Trace trigger data register. 
 */
static inline uint_xlen_t csr_read_tdata3(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, tdata3" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_tdata3(uint_xlen_t value) {
    __asm__ volatile ("csrw    tdata3, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_tdata3(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, tdata3, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * dcsr - DRW - Debug control and status register. 
 */
static inline uint_xlen_t csr_read_dcsr(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, dcsr" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_dcsr(uint_xlen_t value) {
    __asm__ volatile ("csrw    dcsr, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_dcsr(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, dcsr, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * dpc - DRW - Debug PC. 
 */
static inline uint_xlen_t csr_read_dpc(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, dpc" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_dpc(uint_xlen_t value) {
    __asm__ volatile ("csrw    dpc, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_dpc(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, dpc, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * dscratch0 - DRW - Debug scratch register 0. 
 */
static inline uint_xlen_t csr_read_dscratch0(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, dscratch0" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_dscratch0(uint_xlen_t value) {
    __asm__ volatile ("csrw    dscratch0, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_dscratch0(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, dscratch0, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * dscratch1 - DRW - Debug scratch register 1. 
 */
static inline uint_xlen_t csr_read_dscratch1(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, dscratch1" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_dscratch1(uint_xlen_t value) {
    __asm__ volatile ("csrw    dscratch1, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_dscratch1(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, dscratch1, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * hie - HRW - Hypervisor interrupt-enable register. 
 */
static inline uint_xlen_t csr_read_hie(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, hie" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_hie(uint_xlen_t value) {
    __asm__ volatile ("csrw    hie, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_hie(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, hie, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * hgeie - HRW - Hypervisor guest external interrupt-enable register. 
 */
static inline uint_xlen_t csr_read_hgeie(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, hgeie" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_hgeie(uint_xlen_t value) {
    __asm__ volatile ("csrw    hgeie, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_hgeie(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, hgeie, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * htval - HRW - Hypervisor bad guest physical address. 
 */
static inline uint_xlen_t csr_read_htval(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, htval" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_htval(uint_xlen_t value) {
    __asm__ volatile ("csrw    htval, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_htval(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, htval, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * hip - HRW - Hypervisor interrupt pending. 
 */
static inline uint_xlen_t csr_read_hip(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, hip" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_hip(uint_xlen_t value) {
    __asm__ volatile ("csrw    hip, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_hip(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, hip, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * htinst - HRW - Hypervisor trap instruction (transformed). 
 */
static inline uint_xlen_t csr_read_htinst(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, htinst" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_htinst(uint_xlen_t value) {
    __asm__ volatile ("csrw    htinst, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_htinst(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, htinst, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * hgeip - HRO - Hypervisor guest external interrupt pending. 
 */
static inline uint_xlen_t csr_read_hgeip(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, hgeip" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}

/*******************************************
 * mtinst - MRW - Machine trap instruction (transformed). 
 */
static inline uint_xlen_t csr_read_mtinst(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mtinst" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mtinst(uint_xlen_t value) {
    __asm__ volatile ("csrw    mtinst, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mtinst(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mtinst, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}

/*******************************************
 * mtval2 - MRW - Machine bad guest physical address. 
 */
static inline uint_xlen_t csr_read_mtval2(void) {
    uint_xlen_t value;        
    __asm__ volatile ("csrr    %0, mtval2" 
                      : "=r" (value)  /* output : register */
                      : /* input : none */
                      : /* clobbers: none */);
    return value;
}
static inline void csr_write_mtval2(uint_xlen_t value) {
    __asm__ volatile ("csrw    mtval2, %0" 
                      : /* output: none */ 
                      : "r" (value) /* input : from register */
                      : /* clobbers: none */);
}
static inline uint_xlen_t csr_read_write_mtval2(uint_xlen_t new_value) {
    uint_xlen_t prev_value;
    __asm__ volatile ("csrrw    %0, mtval2, %1"  
                      : "=r" (prev_value) /* output: register %0 */
                      : "r" (new_value)  /* input : register */
                      : /* clobbers: none */);
    return prev_value;
}


#endif // #define RISCV_CSR_H
