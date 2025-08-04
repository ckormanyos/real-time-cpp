#ifndef _CORE_MACROS_H
#define _CORE_MACROS_H

#if defined(__GNUC__)
#pragma GCC system_header
#endif

#include <stdint.h>
#include <stdbool.h>

#define DSB __asm__ volatile("dsb sy" ::: "memory")
#define ISB __asm__ volatile("isb" ::: "memory")

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define ARM64_READ_SYSREG(reg) \
({ \
    uint64_t _val; \
    __asm__ volatile("mrs %0," TOSTRING(reg) : "=r" (_val)); \
    _val; \
})

#define ARM64_WRITE_SYSREG(reg, val) \
({ \
    __asm__ volatile("msr " TOSTRING(reg) ", %0" :: "r" (val)); \
    ISB; \
})

#define CF do { __asm__ volatile("" ::: "memory"); } while(0)

static inline void arch_enable_ints(void) {
    CF;
    __asm__ volatile("msr daifclr, #2" ::: "memory");
}

static inline void arch_disable_ints(void) {
    __asm__ volatile("msr daifset, #2" ::: "memory");
    CF;
}

static inline bool arch_ints_disabled(void) {
    unsigned long state;

    __asm__ volatile("mrs %0, daif" : "=r"(state));
    state &= (1<<7);

    return !!state;
}

static inline void arch_enable_fiqs(void) {
    CF;
    __asm__ volatile("msr daifclr, #1" ::: "memory");
}

static inline void arch_disable_fiqs(void) {
    __asm__ volatile("msr daifset, #1" ::: "memory");
    CF;
}

static inline bool arch_fiqs_disabled(void) {
    unsigned long state;

    __asm__ volatile("mrs %0, daif" : "=r"(state));
    state &= (1<<6);

    return !!state;
}



#endif /*_CORE_MACROS_H*/
