///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2011 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_reg.h>

namespace local
{
  auto set_system_clock() -> bool;

  auto set_system_clock() -> bool
  {
    // See also:
    // https://github.com/ARMmbed/mbed-os/blob/master/targets/TARGET_STM/TARGET_STM32L4/TARGET_STM32L432xC/system_clock.c

    // Set HSION (HSI16 clock enable) enable bit.
    // RCC_CR |= (uint32_t)(1UL << 8U);
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_cr,
                                 UINT32_C(8)>::bit_set();


    // Wait until HSI16 clock is ready.
    // while (!(RCC_CR & (uint32_t)(1UL << 10UL))) { mcal::cpu::nop(); }
    while(!mcal::reg::reg_access_static<std::uint32_t,
                                        std::uint32_t,
                                        mcal::reg::rcc_cr,
                                        UINT32_C(10)>::bit_get()) { mcal::cpu::nop(); }

    // PWREN: Power interface clock enable.
    // RCC_APB1ENR1 |= (uint32_t)(1UL << 28);
    mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_apb1enr1,
                               UINT32_C(28)>::bit_set();

    // Enable the main PLL.
    // RCC_CR &= (uint32_t)(~(uint32_t)(1UL << 24));
    mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::rcc_cr,
                               UINT32_C(24)>::bit_clr();

    // Wait until main PLL is enabled.
    // while (RCC_CR & (uint32_t)(1UL << 25)) { mcal::cpu::nop(); }
    while(mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       mcal::reg::rcc_cr,
                                       UINT32_C(25)>::bit_get()) { mcal::cpu::nop(); }

    // PLL configuration for 80MHz system clock from 16MHz HSI.
    // f(VCO clock) = 16MHz * (40 / 4) = 160MHz.
    // f(System Clock) = f(VCO clock) / PLLR = 80MHz.

    constexpr std::uint32_t
      rcc_pllcfgr_value
      {
        static_cast<std::uint32_t>
        (
            static_cast<std::uint32_t>( 2UL <<  0U)  // Set PLL source to HSI.
          | static_cast<std::uint32_t>( 3UL <<  4U)  // Set PLLM to 4.
          | static_cast<std::uint32_t>(40UL <<  8U)  // Set PLLN to 40.
          | static_cast<std::uint32_t>( 0UL << 25U)  // Set PLLR to 2.
        )
     };

    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pllcfgr,
                                 rcc_pllcfgr_value>::reg_set();

    // Enable Main PLLCLK output for the system clock.
    // RCC_PLLCFGR |= (uint32_t)(1UL << 24);
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_pllcfgr,
                                 UINT32_C(24)>::bit_set();

    // Enable the main PLL.
    // RCC_CR |= (uint32_t)(1UL << 24);
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_cr,
                                 UINT32_C(24)>::bit_set();

    // Wait until main PLL is enabled.
    //while (!(RCC_CR & (uint32_t)(1UL << 25))) { mcal::cpu::nop(); }
    while(!mcal::reg::reg_access_static<std::uint32_t,
                                        std::uint32_t,
                                        mcal::reg::rcc_cr,
                                        UINT32_C(25)>::bit_get()) { mcal::cpu::nop(); }

    // Select the PLL as system clock source.
    // RCC_CFGR &= (uint32_t)(~(3UL << 0));
    // RCC_CFGR |= (uint32_t)(3UL << 0U);
    mcal::reg::reg_access_static<std::uint32_t,
                                 std::uint32_t,
                                 mcal::reg::rcc_cfgr,
                                 UINT32_C(3)>::template reg_msk<UINT32_C(3) << 0U>();

    // Wait until the main PLL is used as system clock source.
    // while ((RCC_CFGR & (uint32_t)(0x0CU << 0)) != (0x0CU << 0)) { mcal::cpu::nop(); }
    while
    (
      static_cast<std::uint32_t>
      (
        mcal::reg::reg_access_static<std::uint32_t,
                                     std::uint32_t,
                                     mcal::reg::rcc_cfgr>::reg_get() & static_cast<std::uint32_t>(0x0CUL << 0U)
      ) != static_cast<std::uint32_t>(0x0CUL << 0U)
    )
    {
      mcal::cpu::nop();
    }

    return true;
  }
} //  namespace local

auto mcal::osc::init(const config_type*) -> void
{
  // Configure the system clock for 80MHz using the hsi-pll.
  const bool result_system_clock_is_ok { local::set_system_clock() };

  static_cast<void>(result_system_clock_is_ok);
}
