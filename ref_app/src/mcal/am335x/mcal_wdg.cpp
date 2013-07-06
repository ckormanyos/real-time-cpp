///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_cpu.h>
#include <mcal_wdg.h>
#include <mcal_reg_access.h>

namespace mcal
{
  namespace wdg
  {
    namespace detail
    {
      void wdg_stop()
      {
        mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wspr, 0x0000AAAAUL>::reg_set();
        while(std::uint32_t(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wwps>::reg_get() & std::uint32_t(0x3FUL)) != std::uint32_t(0UL)) { mcal::cpu::nop(); }

        mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wspr, 0x00005555UL>::reg_set();
        while(std::uint32_t(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wwps>::reg_get() & std::uint32_t(0x3FUL)) != std::uint32_t(0UL)) { mcal::cpu::nop(); }
      }

      void wdg_start()
      {
        mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wspr, 0x0000BBBBUL>::reg_set();
        while(std::uint32_t(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wwps>::reg_get() & std::uint32_t(0x3FUL)) != std::uint32_t(0UL)) { mcal::cpu::nop(); }

        mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wspr, 0x00004444UL>::reg_set();
        while(std::uint32_t(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wwps>::reg_get() & std::uint32_t(0x3FUL)) != std::uint32_t(0UL)) { mcal::cpu::nop(); }
      }
    }
  }
}

void mcal::wdg::init(const config_type*)
{
  // Stop the watchdog timer.
  detail::wdg_stop();

  // Select the watchdog timer clock source to be 32kHz from the 32K clock divider.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_dpll::clksel_wdt1_clk,
                    0UL>::bit_set();

  // Set the watchdog prescaler to 2^0 = 1.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt1::wclr,
                    0UL>::reg_msk<0x3CUL>();

  // Activate the watchdog prescaler.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt1::wclr,
                    5UL>::bit_set();

  // Set the watchdog delay register to zero.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt1::wdly,
                    0UL>::reg_set();

  // Set the watchdog counter register for a period of 100ms.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt1::wcrr,
                    0xFFFFFFFEUL - 3200UL>::reg_set();

  // Set the watchdog reload register for a period of 100ms.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt1::wldr,
                    0xFFFFFFFEUL - 3200UL>::reg_set();

  // Start the watchdog timer.
  detail::wdg_start();
}

void mcal::wdg::trigger()
{
  // Read the value of the watchdog trigger.
  const std::uint32_t this_trigger_value = mcal::reg::access<std::uint32_t,
                                                             std::uint32_t,
                                                             mcal::reg::wdt1::wtgr>::reg_get();

  // Write a different value to the watchdog trigger.
  // Here, we add 224,737 to the watchdog trigger,
  // where this is the value of the 20,000th prime number.
  const std::uint32_t next_trigger_value = std::uint32_t(this_trigger_value + std::uint32_t(224737UL));

  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt1::wtgr>::reg_set(next_trigger_value);
}
