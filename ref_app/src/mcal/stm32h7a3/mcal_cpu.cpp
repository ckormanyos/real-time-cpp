///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

extern "C"
{
  #include "STM32H7x3.h"

  #include "Cache.h"
}

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>

extern "C"
{
  extern unsigned long __INTVECT_BASE_ADDRESS;
}

namespace local
{
  auto system_init() -> void;

  auto system_init() -> void
  {
    /* Setup the VTOR */
    SCB->VTOR.reg = (unsigned long)&__INTVECT_BASE_ADDRESS;
  
    /* Initialize the FPU: Enable CP10 and CP11. */
    CPACR |= 0x00F00000UL;

    /* Enable ITCM and DTCM */
    ITCMCR |= 1UL;
    DTCMCR |= 1UL;

    __asm("DSB");
    __asm("ISB");
  }
} // namespace local

void mcal::cpu::init()
{
  local::system_init();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
