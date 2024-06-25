///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#if ((defined(__GNUC__)  && (__GNUC__ > 10)) && defined(__riscv))
asm(".option arch, +zicsr");
#endif

#include <cstdint>

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>

extern "C"
{
  #if __riscv_xlen==32
  typedef std::uint32_t uint_xlen_t;
  typedef std::uint32_t uint_csr32_t;
  typedef std::uint32_t uint_csr64_t;
  #elif __riscv_xlen==64
  typedef std::uint64_t uint_xlen_t;
  typedef std::uint32_t uint_csr32_t;
  typedef std::uint64_t uint_csr64_t;
  #else
  #error "Unknown XLEN"
  #endif

  static inline void csr_write_mstatus(uint_xlen_t value)
  {
    asm volatile ("csrw    mstatus, %0" 
                  :             /* output: none */ 
                  : "r" (value) /* input : from register */
                  :             /* clobbers: none */);
  }
}

void mcal::cpu::init()
{
  /* Disable all PLIC interrupts */
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::plic_enable_0, static_cast<std::uint32_t>(UINT8_C(0))>::reg_set();
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::plic_enable_1, static_cast<std::uint32_t>(UINT8_C(0))>::reg_set();

  /* turn on the global interrupt enable flag */
  csr_write_mstatus(8);

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
