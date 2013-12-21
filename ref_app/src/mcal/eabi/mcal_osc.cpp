///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg_access.h>

namespace
{
  void set_the_system_clock()
  {
    // Enable the hse.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::rcc_cr,
                      UINT32_C(0x00010000)>::reg_or();

    // Wait until the hse is ready.
    while(mcal::reg::access<std::uint32_t,
                            std::uint32_t,
                            mcal::reg::rcc_cr,
                            UINT32_C(17)>::bit_get() == false)
    {
      mcal::cpu::nop();
    }

    // Set the pll parameters.

    // The pll configuration is: = (hse / 2) * 6 = 24 MHz.
    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_cfgr, UINT32_C(0x00130000)>::reg_or();

    // Enable the pll.
    mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::rcc_cr, UINT32_C(0x01000000)>::reg_or();

    // Wait until the pll is locked.
    while(mcal::reg::access<std::uint32_t,
                            std::uint32_t,
                            mcal::reg::rcc_cr,
                            UINT32_C(25)>::bit_get() == false)
    {
      mcal::cpu::nop();
    }

    // Select the pll as the system clock source.
    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::rcc_cfgr,
                      UINT32_C(0x00000002)>::reg_msk<UINT32_C(0x00000003)>();

    std::uint32_t rcc_cfgr_sws_value = UINT32_C(0);

    // Wait until the pll is latched as the system clock source.
    while(rcc_cfgr_sws_value != UINT32_C(0x00000008))
    {
      rcc_cfgr_sws_value = mcal::reg::access<std::uint32_t,
                                             std::uint32_t,
                                             mcal::reg::rcc_cfgr>::reg_get() & UINT32_C(0x0000000C);
    }

    // Now we have:
    //   * The hse is ready.
    //   * The pll is locked.
    //   * The pll is the clock source.
  }
}

void mcal::osc::init(const config_type*)
{
  // Configure the system clock for 24MHz using the hse-pll.
  set_the_system_clock();
}
