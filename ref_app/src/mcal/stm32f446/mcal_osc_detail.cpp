///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <limits>
#include <mcal_osc_detail.h>

mcal::osc::detail::stm32f4xx_clock_settings::stm32f4xx_clock_settings(const std::uint16_t f_pll,
                                                                      const std::uint8_t  f_hsx)
{
  std::uint16_t f_vco           = UINT16_C(0);
  std::uint16_t delta_f_vco_min = (std::numeric_limits<std::uint16_t>::max)();

  // Initialize the parameter p.
  param_p = UINT8_C(2);

  // Use an iterative analysis to find the optimal value of f_vco in
  // relation to the specified range of the vco and the value of p.
  // Thereby select the optimal value of p.
  for(std::uint8_t param_p_this  = UINT8_C(2);
                   param_p_this <= UINT8_C(8);
                   param_p_this  = static_cast<std::uint8_t>(param_p_this + UINT8_C(2)))
  {
    const std::uint16_t       f_vco_this = static_cast<std::uint16_t>(f_pll * param_p_this);
    const std::uint16_t delta_f_vco_this = static_cast<std::uint16_t>(std::abs(static_cast<std::int32_t>(f_vco_this) - INT32_C(312)));

    const bool f_vco_is_within_range = ((f_vco_this >= UINT16_C(192)) && (f_vco_this <= UINT16_C(432)));

    if(f_vco_is_within_range)
    {
      if(delta_f_vco_this < delta_f_vco_min)
      {
        delta_f_vco_min = delta_f_vco_this;

        param_p = param_p_this;

        f_vco = f_vco_this;
      }
    }
  }

  clock_settings_are_valid = (f_vco != UINT16_C(0));

  f_usb_is_exactly_48 = false;
  param_q = UINT8_C(2);

  std::uint16_t f_usb           = UINT16_C(0);
  std::uint16_t delta_f_usb_min = (std::numeric_limits<std::uint16_t>::max)();

  // Use an iterative analysis to find the optimal value of f_usb in
  // relation to the value of f_vco and the value of param_q.
  // Thereby select the optimal value of param_q.
  for(std::uint8_t param_q_this = UINT8_C(2); param_q_this <= UINT8_C(15); ++param_q_this)
  {
    const std::uint16_t       f_usb_this = static_cast<std::uint16_t>(f_vco / param_q_this);
    const std::uint16_t delta_f_usb_this = static_cast<std::uint16_t>(std::abs(static_cast<std::int32_t>(f_usb_this) - INT32_C(48)));

    if(delta_f_usb_this < delta_f_usb_min)
    {
      delta_f_usb_min = delta_f_usb_this;

      param_q = param_q_this;

      f_usb = f_usb_this;

      f_usb_is_exactly_48 = (f_usb == UINT16_C(48));

      if(f_usb_is_exactly_48)
      {
        break;
      }
    }
  }

  clock_settings_are_valid = (clock_settings_are_valid && (f_usb != UINT16_C(0)));

  // TBD: Consider using more highly-refined integer mathematics in order to
  // calculate numbers that are more exact yet still within range.
  param_m = f_hsx;
  param_n = f_vco;
}

mcal::osc::detail::stm32f4xx_clock_settings::~stm32f4xx_clock_settings() { }
