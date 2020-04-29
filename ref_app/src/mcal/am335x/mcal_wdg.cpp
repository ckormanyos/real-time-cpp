///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstdint>
#include <mcal_reg.h>
#include <mcal_wdg.h>

namespace
{
  struct wdg_detail
  {
  public:
    template<const std::uint32_t wdg_action_pattern_01,
             const std::uint32_t wdg_action_pattern_02>
    static void wdg_action()
    {
      mcal::reg::reg_access_static<std::uint32_t,
                                   std::uint32_t,
                                   mcal::reg::wdt1::wspr,
                                   wdg_action_pattern_01>::reg_set();

      wdg_wait_clock_stable();

      mcal::reg::reg_access_static<std::uint32_t,
                                   std::uint32_t,
                                   mcal::reg::wdt1::wspr,
                                   wdg_action_pattern_02>::reg_set();

      wdg_wait_clock_stable();
    }

  private:
    static void wdg_wait_clock_stable()
    {
      volatile std::uint32_t wwps_mask_value;

      do
      {
        wwps_mask_value = mcal::reg::reg_access_static<std::uint32_t,
                                            std::uint32_t,
                                            mcal::reg::wdt1::wwps>::reg_get();

        wwps_mask_value &= UINT32_C(0x3F);
      }
      while(wwps_mask_value != UINT32_C(0));
    }
  };
}

void mcal::wdg::init(const config_type*)
{
  // Stop the watchdog timer.
  wdg_detail::wdg_action<UINT32_C(0x0000AAAA),
                         UINT32_C(0x00005555)>();

  // Select the watchdog timer clock source to be 32kHz,
  // originating from the 32K clock divider.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::cm_dpll::clksel_wdt1_clk,
                               UINT32_C(0)>::bit_set();

  // Set the watchdog prescaler to 2^0 = 1.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::wdt1::wclr,
                               UINT32_C(0)>::reg_msk<0x3C>();

  // Activate the watchdog prescaler.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::wdt1::wclr,
                               UINT32_C(5)>::bit_set();

  // Set the watchdog delay register to zero.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::wdt1::wdly,
                               UINT32_C(0)>::reg_set();

  // Set the watchdog *counter* register for a period of 100ms.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::wdt1::wcrr,
                               std::uint32_t(UINT32_C(0xFFFFFFFE) - UINT32_C(3200))>::reg_set();

  // Set the watchdog *reload* register for a period of 100ms.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::wdt1::wldr,
                               std::uint32_t(UINT32_C(0xFFFFFFFE) - UINT32_C(3200))>::reg_set();

  // Initialize the watchdog trigger to zero.
  mcal::reg::reg_access_static<std::uint32_t,
                               std::uint32_t,
                               mcal::reg::wdt1::wtgr,
                               UINT32_C(0)>::reg_set();

  // Start the watchdog timer.
  wdg_detail::wdg_action<UINT32_C(0x0000BBBB),
                         UINT32_C(0x00004444)>();
}

void mcal::wdg::secure::trigger()
{
  // Generate a different trigger value each time the watchdog
  // trigger is set. In order to do this, we add a prime number
  // from a sequence of primes to the previous value of the
  // watchdog trigger. In this way, a unique new value for
  // the watchdog trigger is created in each call.

  constexpr std::size_t prime_sequence_size = std::size_t(8U);

  typedef std::array<std::uint32_t, prime_sequence_size> prime_sequence_type;

  // Generate a sequence containing the first eight primes at
  // equidistant stride of 10,000. In particular, this means the
  // 10,000'th, 20,000'th, ... 80,000'th primes. See, for example,
  // Mathematica(R) or Wolfram's Alpha, and use a command such as:
  // Table[Prime[n 10000], {n, 1, 8, 1}]

  constexpr prime_sequence_type prime_sequence =
  {{
      UINT32_C(104729), UINT32_C(224737), UINT32_C(350377), UINT32_C(479909),
      UINT32_C(611953), UINT32_C(746773), UINT32_C(882377), UINT32_C(1020379)
  }};

  static volatile prime_sequence_type::size_type prime_sequence_index;

  // Read from the hardware the watchdog trigger value for this cycle.
  const std::uint32_t this_watchdog_trigger_value = mcal::reg::reg_access_static<std::uint32_t,
                                                                      std::uint32_t,
                                                                      mcal::reg::wdt1::wtgr>::reg_get();

  // Calculate the prime number sequence index for the next cycle.
  const prime_sequence_type::size_type next_prime_sequence_index
    = prime_sequence_type::size_type(prime_sequence_index % prime_sequence.size());

  // Calculate the watchdog trigger value for the next cycle.
  const std::uint32_t next_watchdog_trigger_value = std::uint32_t(  this_watchdog_trigger_value
                                                                  + prime_sequence[next_prime_sequence_index]);

  // Set the watchdog trigger value for the next cycle.
  mcal::reg::reg_access_dynamic<std::uint32_t,
                            std::uint32_t>::reg_set(mcal::reg::wdt1::wtgr,
                                                    next_watchdog_trigger_value);

  // Increment the prime number sequence index for the following cycle.
  ++prime_sequence_index;
}
