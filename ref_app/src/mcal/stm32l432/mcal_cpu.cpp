///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_irq.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>

namespace local
{
  auto cpu_init() -> void;

  auto cpu_init() -> void
  {
    // Set coprocessor access control register CP10 and CP11 Full Access.
    // Here we also enable the hardware floating-point unit (FPU).

    // SCB_CPACR |= (uint32_t)((uint32_t)(3UL << 20U) | (uint32_t)(3UL << 22U));
    constexpr std::uint32_t
      scb_cpacr_or_value
      {
        static_cast<std::uint32_t>
        (
            static_cast<std::uint32_t>(3UL << 20U)
          | static_cast<std::uint32_t>(3UL << 22U)
        )
      };

    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::scb_cpacr,
                                 scb_cpacr_or_value>::reg_or();

    // Reset (clear) the HSEON, CSSON, HSEBYP and PLLON bits.
    // RCC_CR &= (uint32_t)((~(1UL << 16)) | (~(1UL << 18))) | (~(1UL << 19)) | (~(1UL << 24));
    constexpr std::uint32_t
      rcc_cr_not_value
      {
        static_cast<std::uint32_t>
        (
            static_cast<std::uint32_t>(1UL << 16U)
          | static_cast<std::uint32_t>(1UL << 18U)
          | static_cast<std::uint32_t>(1UL << 19U)
          | static_cast<std::uint32_t>(1UL << 24U)
        )
      };

    mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::rcc_cr, rcc_cr_not_value>::reg_not();

    // Reset CFGR register.
    // RCC_CFGR = (uint32_t)0x40000000UL;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_cfgr,
                                 UINT32_C(0x40000000)>::reg_set();

    // Reset PLLCFGR register.
    // RCC_PLLCFGR = (uint32_t)0x00001000UL;
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pllcfgr,
                                 UINT32_C(0x00001000)>::reg_set();

    // Configure Flash prefetch, Instruction cache, Data cache
    // and wait states. Use flat 3 wait states at 80MHz.

    // FLASH_ACR = (uint32_t)((1UL << 9) | (1UL << 10) | (3UL << 0));
    constexpr std::uint32_t
      flash_acr_set_value
      {
        static_cast<std::uint32_t>
        (
            static_cast<std::uint32_t>(3UL <<  0U)
          | static_cast<std::uint32_t>(1UL <<  9U)
          | static_cast<std::uint32_t>(1UL << 10U)
        )
      };

    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::flash_acr,
                                 flash_acr_set_value>::reg_set();
  }
} // namespace local

auto mcal::cpu::init() -> void
{
  ::local::cpu_init();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
