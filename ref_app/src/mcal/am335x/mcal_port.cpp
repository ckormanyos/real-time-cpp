///////////////////////////////////////////////////////////////////////////////
//  Copyright Michael Schnerr 2011 - 2013.
//  Copyright Christopher Kormanyos 2013 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc_shared.h>
#include <mcal_port.h>
#include <mcal_reg.h>

namespace
{
  struct osc_detail
  {
    static constexpr std::uint32_t modulemode_enable = mcal::osc::mcal_osc_shared::modulemode_enable;
    static constexpr std::uint32_t modulemode_mask   = mcal::osc::mcal_osc_shared::modulemode_mask;

    static constexpr std::uint32_t idlest_func       = mcal::osc::mcal_osc_shared::idlest_func;
    static constexpr std::uint32_t idlest_mask       = mcal::osc::mcal_osc_shared::idlest_mask;
  };

  struct port_detail
  {
    static void gpio1_clock_init()
    {
      constexpr std::uint32_t optfclken_gpio_1_gdbclk   = UINT32_C(0x00040000);
      constexpr std::uint32_t clkactivity_gpio_1_gdbclk = UINT32_C(0x00080000);

      // Set the module field of the cm_per::gpio1_clkctrl register.
      mcal::reg::reg_access_static<std::uint32_t,
                                   std::uint32_t,
                                   mcal::reg::cm_per::gpio1_clkctrl,
                                   osc_detail::modulemode_enable>::template reg_msk<osc_detail::modulemode_mask>();
      while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::gpio1_clkctrl>::reg_get() & osc_detail::modulemode_mask) != osc_detail::modulemode_enable) { mcal::cpu::nop(); }

      // Enable the optional function clock.
      mcal::reg::reg_access_static<std::uint32_t,
                                   std::uint32_t,
                                   mcal::reg::cm_per::gpio1_clkctrl,
                                   optfclken_gpio_1_gdbclk>::template reg_msk<optfclken_gpio_1_gdbclk>();

      while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::gpio1_clkctrl>::reg_get()  & optfclken_gpio_1_gdbclk)   != optfclken_gpio_1_gdbclk  ) { mcal::cpu::nop(); }
      while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::gpio1_clkctrl>::reg_get()  & osc_detail::idlest_mask)   != osc_detail::idlest_func)   { mcal::cpu::nop(); }
      while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::cm_per::l4ls_clkstctrl>::reg_get() & clkactivity_gpio_1_gdbclk) != clkactivity_gpio_1_gdbclk) { mcal::cpu::nop(); }
    }

    static constexpr std::uint32_t port1_initial_value = UINT32_C(0x00000000);
    static constexpr std::uint32_t port1_output_enable = UINT32_C(0xFFFFFFFF);
  };
}

void mcal::port::init(const config_type*)
{
  // Initialize the gpio1 clock.
  port_detail::gpio1_clock_init();

  // LED 1: A7 to gpio1[21], fast slew, receiver disabled, pull-down enabled.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::control::conf_gpmc_a5, UINT32_C(0x07)>::reg_set();

  // LED 2: A7 to gpio1[22], fast slew, receiver disabled, pull-down enabled.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::control::conf_gpmc_a6, UINT32_C(0x07)>::reg_set();

  // LED 3: A7 to gpio1[23], fast slew, receiver disabled, pull-down enabled.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::control::conf_gpmc_a7, UINT32_C(0x07)>::reg_set();

  // LED 4: A7 to gpio1[24], fast slew, receiver disabled, pull-down enabled.
  mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::control::conf_gpmc_a8, UINT32_C(0x07)>::reg_set();

  // Enable the gpio1 modules.
  // Clear the disablemodule bit in the control register (ctrl).
  // Set the gating ratio to 1:1.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::gpio1_base + mcal::reg::gpiox::ctrl,
                               UINT32_C(0x00)>::reg_set();

  // Reset the gpio1 module: no-idle, no wakeup, soft-reset, ocp clock free running.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::gpio1_base + mcal::reg::gpiox::sysconfig,
                               UINT32_C(0x0A)>::reg_set();

  // Wait until the gpio1 Module is reset.
  while((mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::gpio1_base + mcal::reg::gpiox::sysstatus>::reg_get() & UINT32_C(1)) == UINT32_C(0))
  {
    mcal::cpu::nop();
  }

  // Set the port1 output value and direction registers.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::gpio1_base + mcal::reg::gpiox::dataout,
                               port_detail::port1_initial_value>::reg_set();

  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::gpio1_base + mcal::reg::gpiox::oe,
                               port_detail::port1_output_enable>::reg_set();
}
