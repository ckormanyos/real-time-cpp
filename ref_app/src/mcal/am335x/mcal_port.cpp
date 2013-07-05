///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_port.h>
#include <mcal_reg_access.h>

namespace
{
  constexpr std::uint32_t port1_initial_value = std::uint32_t(0x00000000UL);
  constexpr std::uint32_t port1_output_enable = std::uint32_t(0xFFFFFFFFUL);
}

void mcal::port::init(const config_type*)
{
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
    mcal::cpu::nop();
  }

  // Set the port1 output value and direction registers.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::gpio1_base + mcal::reg::gpiox::dataout,
                    port1_initial_value>::reg_set();

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::gpio1_base + mcal::reg::gpiox::oe,
                    port1_output_enable>::reg_set();
}
