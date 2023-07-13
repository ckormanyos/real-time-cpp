///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_reg.h>
#include <mcal_wdg.h>

void mcal::wdg::init(const config_type*)
{
  // Read the MCU status register.
  volatile const std::uint8_t mcu_status_register =
    mcal::reg::reg_access_static<std::uint8_t,
                                 std::uint8_t,
                                 mcal::reg::mcusr>::reg_get();

  // At the moment, we do not make use of the MCU status register.
  // In the future, for example, we could query the reset reason.
  static_cast<void>(mcu_status_register);

  // Clear the MCU status register.
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::mcusr,
                               std::uint8_t(0U)>::reg_set();

  // Reset the watchdog timer.
  asm volatile("wdr");

  // Set the watchdog timer period and activate the watchdog timer.
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::wdtcsr,
                               std::uint8_t(0x18U)>::reg_set();

  // See Chapter 11.9.2, Table 11-2: Watchdog Timer Prescale Select.
  // Select WDP3:WDP0 in WDTCSR to binary 0b0111, resulting
  // in a watchdog period of approximately 2s.
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::wdtcsr,
                               std::uint8_t(0x08U) | std::uint8_t(0x07U)>::reg_set();
}

void mcal::wdg::secure::trigger()
{
  asm volatile("wdr");
}

