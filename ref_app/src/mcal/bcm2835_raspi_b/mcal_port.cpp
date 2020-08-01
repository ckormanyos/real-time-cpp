///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_port.h>
#include <mcal_reg.h>

namespace
{
  constexpr std::uint32_t GPFSEL0_ADDR         = UINT32_C(0x20200000);

  constexpr std::uint32_t GPIO_PIN_X_INPUT     = UINT32_C(0);
  constexpr std::uint32_t GPIO_PIN_X_OUTPUT    = UINT32_C(1);

  constexpr std::uint32_t GPCLR0_ADDR          = UINT32_C(0x20200028);
  constexpr std::uint32_t GPCLR1_ADDR          = UINT32_C(0x2020002C);

  constexpr std::uint32_t GPSET0_ADDR          = UINT32_C(0x2020001C);
  constexpr std::uint32_t GPSET1_ADDR          = UINT32_C(0x20200020);

  constexpr std::uint32_t GPIO_NO_EFFECT       = UINT32_C(0);
  constexpr std::uint32_t GPIO_SET_GPIO_PIN_X  = UINT32_C(1);
}

void mcal::port::init(const config_type*)
{
}

extern "C"
void mcal_port_pin_clr(uint8_t PortPin)
{
  const std::uint32_t port    = (std::uint32_t) ((PortPin & 0xF0U) >> 4U);
  const std::uint32_t pin     = (std::uint32_t) (PortPin & 0x0FU);
  const std::uint32_t pos     = (std::uint32_t) ((port * 10U) + pin);
  const std::uint32_t addfsel = (std::uint32_t) (GPFSEL0_ADDR + (std::uint32_t) (4U * port));
  const std::uint32_t valfsel = (std::uint32_t) (GPIO_PIN_X_OUTPUT << (pin * 3U));
  const std::uint32_t addclr  = (std::uint32_t) ((PortPin < 0x32U) ? GPCLR0_ADDR : GPCLR1_ADDR);
  const std::uint32_t valclr  = (std::uint32_t) ((std::uint32_t) GPIO_SET_GPIO_PIN_X << ((pos < 32U) ? (pos) : (pos - 32U)));

  /* Set GPIO mode */
  mcal_reg_access32_reg_or(addfsel, valfsel);

  /* set the gpio low */
  mcal_reg_access32_reg_or(addclr, valclr);
}

extern "C"
void mcal_port_pin_set(uint8_t PortPin)
{
  const std::uint32_t port    = (std::uint32_t) ((PortPin & 0xF0U) >> 4u);
  const std::uint32_t pin     = (std::uint32_t) (PortPin & 0x0FU);
  const std::uint32_t pos     = (std::uint32_t) ((port * 10U) + pin);
  const std::uint32_t addfsel = (std::uint32_t) (GPFSEL0_ADDR + (std::uint32_t) (4U * port));
  const std::uint32_t valfsel = (std::uint32_t) GPIO_PIN_X_OUTPUT << (pin * 3U);
  const std::uint32_t addset  = (std::uint32_t) ((PortPin < 0x32U) ? GPSET0_ADDR : GPSET1_ADDR);
  const std::uint32_t valset  = (std::uint32_t) ((std::uint32_t) GPIO_SET_GPIO_PIN_X << ((pos < 32u) ? (pos) : (pos - 32u)));

  /* Set GPIO mode */
  mcal_reg_access32_reg_or(addfsel, valfsel);

  /* set the gpio high */
  mcal_reg_access32_reg_or(addset, valset);
}
