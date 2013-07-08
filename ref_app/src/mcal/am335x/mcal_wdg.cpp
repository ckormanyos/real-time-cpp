///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
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
      void wdg_stop ();
      void wdg_start();
    }
  }
}

void mcal::wdg::detail::wdg_stop()
{
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wspr, 0x0000AAAAUL>::reg_set();
  while(std::uint32_t(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wwps>::reg_get() & std::uint32_t(0x3FUL)) != std::uint32_t(0UL)) { mcal::cpu::nop(); }

  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wspr, 0x00005555UL>::reg_set();
  while(std::uint32_t(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wwps>::reg_get() & std::uint32_t(0x3FUL)) != std::uint32_t(0UL)) { mcal::cpu::nop(); }
}

void mcal::wdg::detail::wdg_start()
{
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wspr, 0x0000BBBBUL>::reg_set();
  while(std::uint32_t(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wwps>::reg_get() & std::uint32_t(0x3FUL)) != std::uint32_t(0UL)) { mcal::cpu::nop(); }

  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wspr, 0x00004444UL>::reg_set();
  while(std::uint32_t(mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::wdt1::wwps>::reg_get() & std::uint32_t(0x3FUL)) != std::uint32_t(0UL)) { mcal::cpu::nop(); }
}

void mcal::wdg::init(const config_type*)
{
  // Stop the watchdog timer.
  detail::wdg_stop();

  // Select the watchdog timer clock source to be 32kHz,
  // originating from the 32K clock divider.
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

  // Initialize the watchdog trigger to zero.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt1::wtgr,
                    0UL>::reg_set();

  // Start the watchdog timer.
  detail::wdg_start();
}

void mcal::wdg::trigger()
{
  typedef std::array<std::uint32_t, 4U> prime_sequence_type;

  // Table[Prime[1000 n], {n, 1, 4, 1}]
  constexpr prime_sequence_type prime_sequence =
  {{
     7919UL, 17389UL, 27449UL, 37813UL
  }};

  static prime_sequence_type::size_type prime_index;

  // Read the value of the watchdog trigger.
  const std::uint32_t this_trigger_value = mcal::reg::access<std::uint32_t,
                                                             std::uint32_t,
                                                             mcal::reg::wdt1::wtgr>::reg_get();

  // Generate a different value for the watchdog trigger.
  // Here, we add a prime number from a sequence of primes
  // to the previous value of the watchdog trigger in order
  // to create a unique new value.
  const std::uint32_t next_trigger_value = std::uint32_t(this_trigger_value + prime_sequence[prime_index]);

  // Set the next watchdog trigger value.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt1::wtgr>::reg_set(next_trigger_value);

  ++prime_index;

  if(prime_index >= prime_sequence.size())
  {
    prime_index = prime_sequence_type::size_type(0U);
  }
}
