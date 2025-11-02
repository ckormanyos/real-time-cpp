///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_reg.h>
#include <mcal_wdg.h>

auto mcal::wdg::init(const config_type*) -> void
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

  // Start timed sequence in order to set the watchdog
  // timer period and activate the watchdog timer.
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::wdtcsr,
                               std::uint8_t(0x18U)>::reg_set();

  // In "Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf",
  // see Chapter 10.9.2, Table 10-3: Watchdog Timer Prescale Select.
  // Set WDP3 (bit 5) and clear WDP2:WDP0 (bits 0, 1 and 2) in WDTCSR
  // (i.e., set to hex 0x20). This results in a watchdog period
  // of approximately 4s.
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::wdtcsr,
                               std::uint8_t(0x20U)>::reg_set();

  // Set WDRF in the MCU status register.
  mcal::reg::reg_access_static<std::uint8_t,
                               std::uint8_t,
                               mcal::reg::mcusr,
                               std::uint8_t(3U)>::bit_set();
}

auto mcal::wdg::secure::trigger() -> void
{
  asm volatile("wdr");
}

