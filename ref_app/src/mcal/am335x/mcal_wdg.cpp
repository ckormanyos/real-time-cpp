///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstdint>
#include <mcal_reg_access.h>
#include <mcal_wdg.h>

namespace
{
  struct wdg_detail
  {
  public:
    template<const std::uint32_t pattern_01,
             const std::uint32_t pattern_02>
    static void wdg_action()
    {
      mcal::reg::access<std::uint32_t,
                        std::uint32_t,
                        mcal::reg::wdt1::wspr,
                        pattern_01>::reg_set();

      wdg_wait_clock_stable();

      mcal::reg::access<std::uint32_t,
                        std::uint32_t,
                        mcal::reg::wdt1::wspr,
                        pattern_02>::reg_set();

      wdg_wait_clock_stable();
    }

  private:
    static void wdg_wait_clock_stable()
    {
      volatile std::uint32_t wwps_mask_value;

      do
      {
        wwps_mask_value = std::uint32_t(  mcal::reg::access<std::uint32_t,
                                                            std::uint32_t,
                                                            mcal::reg::wdt1::wwps>::reg_get()
                                        & std::uint32_t(0x3FUL));
      }
      while(wwps_mask_value != std::uint32_t(0UL));
    }
  };
}

void mcal::wdg::init(const config_type*)
{
  // Stop the watchdog timer.
  wdg_detail::wdg_action<std::uint32_t(0x0000AAAAUL),
                         std::uint32_t(0x00005555UL)>();

  // Select the watchdog timer clock source to be 32kHz,
  // originating from the 32K clock divider.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::cm_dpll::clksel_wdt1_clk,
                    std::uint32_t(0UL)>::bit_set();

  // Set the watchdog prescaler to 2^0 = 1.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt1::wclr,
                    std::uint32_t(0UL)>::reg_msk<0x3CUL>();

  // Activate the watchdog prescaler.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt1::wclr,
                    std::uint32_t(5UL)>::bit_set();

  // Set the watchdog delay register to zero.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt1::wdly,
                    std::uint32_t(0UL)>::reg_set();

  // Set the watchdog *counter* register for a period of 100ms.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt1::wcrr,
                    std::uint32_t(0xFFFFFFFEUL - 3200UL)>::reg_set();

  // Set the watchdog *reload* register for a period of 100ms.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt1::wldr,
                    std::uint32_t(0xFFFFFFFEUL - 3200UL)>::reg_set();

  // Initialize the watchdog trigger to zero.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt1::wtgr,
                    std::uint32_t(0UL)>::reg_set();

  // Start the watchdog timer.
  wdg_detail::wdg_action<std::uint32_t(0x0000BBBBUL),
                         std::uint32_t(0x00004444UL)>();
}

void mcal::wdg::trigger()
{
  // Generate a different trigger value for each time that
  // the watchdog trigger is set.
  // Here, we add a prime number from a sequence of primes
  // to the previous value of the watchdog trigger in order
  // to create a unique new value.

  constexpr std::size_t prime_sequence_size = 8U;

  typedef std::array<std::uint32_t, prime_sequence_size> prime_sequence_type;

  // Generate sequence the thousand'th primes, in particular the
  // 1000'th, 2000'th, ... 8000'th primes. See Mathematica(R) or
  // Wolfram's Alpha.
  // Table[Prime[1000 n], {n, 1, 8, 1}]
  constexpr prime_sequence_type prime_sequence =
  {{
      UINT32_C( 7919), UINT32_C(17389), UINT32_C(27449), UINT32_C(37813),
      UINT32_C(48611), UINT32_C(59359), UINT32_C(70657), UINT32_C(81799)
  }};

  static prime_sequence_type::size_type prime_sequence_index;

  // Read the watchdog trigger value from the hardware.
  const std::uint32_t wdt_trigger_value = mcal::reg::access<std::uint32_t,
                                                            std::uint32_t,
                                                            mcal::reg::wdt1::wtgr>::reg_get();

  // Calculate the prime number sequence index of this cycle.
  const prime_sequence_type::size_type this_prime_sequence_index
    = prime_sequence_type::size_type(prime_sequence_index % prime_sequence.size());

  // Calculate the watchdog trigger value of this cycle.
  const std::uint32_t this_trigger_value = std::uint32_t(  wdt_trigger_value
                                                         + prime_sequence[this_prime_sequence_index]);

  // Set the watchdog trigger value of this cycle.
  mcal::reg::access<std::uint32_t,
                    std::uint32_t,
                    mcal::reg::wdt1::wtgr>::reg_set(this_trigger_value);

  // Increment the prime number sequence index for the next cycle.
  ++prime_sequence_index;
}
