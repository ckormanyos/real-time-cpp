///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_port.h>
#include <mcal_reg_access.h>
#include <am335x_hw_regs.h>

namespace
{
  constexpr std::uint32_t Port1_InitValue = static_cast<std::uint32_t>(0x00000000UL);
  constexpr std::uint32_t Port1_OE        = static_cast<std::uint32_t>(0xFE1FFFFFUL);
}

void mcal::port::init(const config_type*)
{
  // LED 1: A7 to GPIO1[21], fast slew, receiver disabled, pull-down enabled.
  CONTROL->CONF_GPMC_A5 = 0x07U;

  // LED 2: A7 to GPIO1[22], fast slew, receiver disabled, pull-down enabled.
  CONTROL->CONF_GPMC_A6 = 0x07U;

  // LED 3: A7 to GPIO1[23], fast slew, receiver disabled, pull-down enabled.
  CONTROL->CONF_GPMC_A7 = 0x07U;

  // LED 4: A7 to GPIO1[24], fast slew, receiver disabled, pull-down enabled.
  CONTROL->CONF_GPMC_A8 = 0x07U;

  // Enable the GPIO modules.
  // Clear the DISABLEMODULE bit in the Control(CTRL) register.
  // The gating ratio is 1:1.
  GPIO1->CTRL = 0U;

  // Reset the GPIO module: no-idle, no wakeup, soft-reset, ocp clock free running.
  GPIO1->SYSCONFIG = 0x0AU;

  // Wait until the GPIO Module is reset.
  while((GPIO1->SYSSTATUS & 1U) == 0U)
  {
    ;
  }

  GPIO1->OE = Port1_OE;
  GPIO1->DATAOUT = Port1_InitValue;
}
