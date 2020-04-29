///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_reg.h>
#include <mcal_wdg.h>

// This following function is not used.
// It is, however, kept as an example of *turning off*
// the wdt if wdton is set in the fuse bits.
void mcal_wdg_turn_off_wdt_if_wdton_is_set();

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
  // Select WDP3:WDP0 in WDTCSR to binary 0011, resulting in a watchdog
  // period of approximately 125ms.
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::wdtcsr,
                               std::uint8_t(0x0BU)>::reg_set();
}

void mcal::wdg::secure::trigger()
{
  asm volatile("wdr");
}

void mcal_wdg_turn_off_wdt_if_wdton_is_set()
{
  asm volatile("wdr");

  // Clear WDRF in the MCU status register.
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::mcusr,
                               std::uint8_t(3U)>::bit_clr();

  // Set WDCE and WDE.
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::wdtcsr,
                               std::uint8_t(0x18U)>::reg_or();

  // Turn off the WDT.
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::wdtcsr,
                               std::uint8_t(0U)>::reg_set();
}
