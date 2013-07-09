///////////////////////////////////////////////////////////////////////////////
//  Copyright Michael Schnerr 2011 - 2013.
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_osc_detail.h>
#include <mcal_port.h>
#include <mcal_reg_access.h>
#include <mcal_wdg.h>

namespace mcal
{
  namespace port
  {
    namespace detail
    {
      void gpio1_clock_init();

      constexpr std::uint32_t port1_initial_value = std::uint32_t(0x00000000UL);
      constexpr std::uint32_t port1_output_enable = std::uint32_t(0xFFFFFFFFUL);
    }
  }
}

void mcal::port::detail::gpio1_clock_init()
{
  constexpr std::uint32_t optfclken_gpio_1_gdbclk   = 0x00040000UL;
  constexpr std::uint32_t clkactivity_gpio_1_gdbclk = 0x00080000UL;

  // Set the module field of the cm_per::gpio1_clkctrl register.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_per::gpio1_clkctrl,
                    mcal::osc::detail::modulemode_enable>::reg_msk<mcal::osc::detail::modulemode_mask>();
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::gpio1_clkctrl>::reg_get() & mcal::osc::detail::modulemode_mask) != mcal::osc::detail::modulemode_enable) { mcal::wdg::trigger(); }

  // Enable the optional function clock.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_per::gpio1_clkctrl,
                    optfclken_gpio_1_gdbclk>::reg_msk<optfclken_gpio_1_gdbclk>();

  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::gpio1_clkctrl>::reg_get()  & optfclken_gpio_1_gdbclk  )      != optfclken_gpio_1_gdbclk  )      { mcal::wdg::trigger(); }
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::gpio1_clkctrl>::reg_get()  & mcal::osc::detail::idlest_mask) != mcal::osc::detail::idlest_func) { mcal::wdg::trigger(); }
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l4ls_clkstctrl>::reg_get() & clkactivity_gpio_1_gdbclk)      != clkactivity_gpio_1_gdbclk)      { mcal::wdg::trigger(); }
}

void mcal::port::init(const config_type*)
{
  // Initialize the gpio1 clock.
  detail::gpio1_clock_init();

  // LED 1: A7 to gpio1[21], fast slew, receiver disabled, pull-down enabled.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::control::conf_gpmc_a5, 0x07UL>::reg_set();

  // LED 2: A7 to gpio1[22], fast slew, receiver disabled, pull-down enabled.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::control::conf_gpmc_a6, 0x07UL>::reg_set();

  // LED 3: A7 to gpio1[23], fast slew, receiver disabled, pull-down enabled.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::control::conf_gpmc_a7, 0x07UL>::reg_set();

  // LED 4: A7 to gpio1[24], fast slew, receiver disabled, pull-down enabled.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::control::conf_gpmc_a8, 0x07UL>::reg_set();

  // Enable the gpio1 modules.
  // Clear the disablemodule bit in the control register (ctrl).
  // Set the gating ratio to 1:1.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::gpio1_base + mcal::reg::gpiox::ctrl,
                    0x00UL>::reg_set();

  // Reset the gpio1 module: no-idle, no wakeup, soft-reset, ocp clock free running.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::gpio1_base + mcal::reg::gpiox::sysconfig,
                    0x0AUL>::reg_set();

  // Wait until the gpio1 Module is reset.
  while((mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::gpio1_base + mcal::reg::gpiox::sysstatus>::reg_get() & std::uint32_t(1UL)) == std::uint32_t(0UL))
  {
    mcal::wdg::trigger();
  }

  // Set the port1 output value and direction registers.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::gpio1_base + mcal::reg::gpiox::dataout,
                    detail::port1_initial_value>::reg_set();

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::gpio1_base + mcal::reg::gpiox::oe,
                    detail::port1_output_enable>::reg_set();
}
