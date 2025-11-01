///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_led/mcal_led_boolean_state_base.h>
#include <mcal_led.h>
#include <mcal_reg.h>
#include <util/utility/util_time.h>

namespace
{
  constexpr std::uint32_t GPIO_FUN_SDIO   { UINT32_C( 1) };
  constexpr std::uint32_t GPIO_FUN_FLASH  { UINT32_C( 2) };
  constexpr std::uint32_t GPIO_FUN_SPI    { UINT32_C( 4) };
  constexpr std::uint32_t GPIO_FUN_I2C    { UINT32_C( 6) };
  constexpr std::uint32_t GPIO_FUN_UART   { UINT32_C( 7) };
  constexpr std::uint32_t GPIO_FUN_PWM    { UINT32_C( 8) };
  constexpr std::uint32_t GPIO_FUN_EXT_PA { UINT32_C( 9) };
  constexpr std::uint32_t GPIO_FUN_ANALOG { UINT32_C(10) };
  constexpr std::uint32_t GPIO_FUN_SWGPIO { UINT32_C(11) };
  constexpr std::uint32_t GPIO_FUN_JTAG   { UINT32_C(14) };
} // anonymous namespace

class led_port_tmp_bl606 : public mcal::led::led_boolean_state_base
{
public:
  led_port_tmp_bl606() noexcept
  {
    // Configure IO3 as output, low.
    // glb->GPIO_CFGCTL1.bit.reg_gpio_3_func_sel = GPIO_FUN_SWGPIO;
    // glb->GPIO_CFGCTL1.bit.reg_gpio_3_ie       = 0ul;
    // glb->GPIO_CFGCTL1.bit.reg_gpio_3_smt      = 0ul;
    // glb->GPIO_CFGCTL1.bit.reg_gpio_3_drv      = 0ul;
    // glb->GPIO_CFGCTL34.bit.reg_gpio_3_oe      = 1ul;
    mcal::reg::reg_access_static<std::uintptr_t, std::uint32_t, mcal::reg::gpio_cfgctl1, static_cast<std::uint32_t>(GPIO_FUN_SWGPIO << 24U)>::template reg_msk<static_cast<std::uint32_t>(UINT32_C(0xF) << 24U)>();
    mcal::reg::reg_access_static<std::uintptr_t, std::uint32_t, mcal::reg::gpio_cfgctl1, UINT32_C(16)>::bit_clr();
    mcal::reg::reg_access_static<std::uintptr_t, std::uint32_t, mcal::reg::gpio_cfgctl1, UINT32_C(17)>::bit_clr();
    mcal::reg::reg_access_static<std::uintptr_t, std::uint32_t, mcal::reg::gpio_cfgctl1, UINT32_C(0) << 18U>::template reg_msk<UINT32_C(3) << 18U>();
    mcal::reg::reg_access_static<std::uintptr_t, std::uint32_t, mcal::reg::gpio_cfgctl34, UINT32_C(3)>::bit_set();
  }

  ~led_port_tmp_bl606() override = default;

  auto toggle() noexcept -> void override
  {
    // Toggle the IO3 pin.
    // glb->GPIO_CFGCTL32.bit.reg_gpio_3_o ^= 1ul;
    mcal::reg::reg_access_static<std::uintptr_t, std::uint32_t, mcal::reg::gpio_cfgctl32, UINT32_C(3)>::bit_not();

    using base_class_type = led_boolean_state_base;

    base_class_type::toggle();
  }
};

auto mcal::led::led0() -> mcal::led::led_base&
{
  using led0_led_type = led_port_tmp_bl606;

  static led0_led_type l0;

  return l0;
}

