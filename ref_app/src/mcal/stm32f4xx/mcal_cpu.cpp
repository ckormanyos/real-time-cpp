///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg_access.h>
#include <mcal_wdg.h>

namespace
{
  constexpr std::uint32_t flash_acr_wait_state_calculator(const unsigned my_count)
  {
    return static_cast<std::uint32_t>(my_count);
  }

  void configure_the_flash()
  {
    // Configure the flash prefetch, the instruction cache,
    // the data cache, and the number of wait states.
    constexpr std::uint32_t flash_acr_prften = UINT32_C(0x00000100);
    constexpr std::uint32_t flash_acr_icen   = UINT32_C(0x00000200);
    constexpr std::uint32_t flash_acr_dcen   = UINT32_C(0x00000400);

    mcal::reg::access<std::uint32_t,
                      std::uint32_t,
                      mcal::reg::flash_acr,
                      static_cast<std::uint32_t>(  flash_acr_wait_state_calculator(5U)
                                                 | flash_acr_prften
                                                 | flash_acr_icen
                                                 | flash_acr_dcen
                                                )>::reg_set();
  }
}

void mcal::cpu::init()
{
  // Initialize the fpu.
  // Set cp10 and cp11 to full access.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::scb_cpacr,
                    static_cast<std::uint32_t>(  (UINT32_C(3) << (10 * 2))
                                               | (UINT32_C(3) << (11 * 2)))>::reg_or();

  // Reset the rcc clock configuration to the default reset state
  // Set the hsion bit.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::rcc_cr,
                    UINT32_C(0x00000001)>::reg_or();

  // Reset the rcc_cfgr register.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::rcc_cfgr,
                    UINT32_C(0)>::reg_set();

  // Clear the hseon, the csson, and the pllon bits.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::rcc_cr,
                    UINT32_C(0xFEF6FFFF)>::reg_and();

  // Reset the pllcfgr register.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::rcc_pllcfgr,
                    UINT32_C(0x24003010)>::reg_set();

  // Reset the hsebyp bit.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::rcc_cr,
                    UINT32_C(0xFFFBFFFF)>::reg_and();

  // Disable all interrupts.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::rcc_cir,
                    UINT32_C(0)>::reg_set();

  configure_the_flash();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
