///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

asm(".option arch, +zicsr");

#include <cstdint>

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>

extern "C"
{
  typedef std::uint32_t uint_xlen_t;
  typedef std::uint32_t uint_csr32_t;
  typedef std::uint32_t uint_csr64_t;

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
