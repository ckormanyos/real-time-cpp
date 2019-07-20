///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cmath>
#include <cstdint>
#include <vector>

#include <math/primes/primes.h>
#include <mcal_benchmark.h>
#include <mcal_cpu.h>
#include <util/memory/util_ring_allocator.h>
#include <util/utility/util_dynamic_bitset.h>

namespace app
{
  namespace prime
  {
    void task_init();
    void task_func();
  }
}

namespace
{
  using app_prime_port_type = mcal::benchmark::benchmark_port_type;

  using unsigned_integral_prime_type = std::uint_fast16_t;

  std::size_t upper_limit_of_number_of_primes;

  struct app_prime
  {
    static const unsigned_integral_prime_type maximum_value_of_primes = 542;
  };
}

void app::prime::task_init()
{
  // Set the port measurement pin to output
  app_prime_port_type::set_direction_output();

  // Calculate the upper limit of the number of primes expected.
  // Use an asymptotic expansion of the log_integral function li(x).

  // See also the article "Prime-counting function" at:
  // http://en.wikipedia.org/wiki/Prime-counting_function

  // Example:
  // N[LogIntegral[542]] = 108.5080795

  const float upper_limit_of_number_of_primes_as_float =
    math::primes::detail::log_integral_asym(static_cast<float>(app_prime::maximum_value_of_primes)) - 1.04516F;

  using std::floor;

  upper_limit_of_number_of_primes =
    static_cast<std::size_t>(upper_limit_of_number_of_primes_as_float);
}

void app::prime::task_func()
{
  using primes_container_type =
    std::vector<unsigned_integral_prime_type,
                util::ring_allocator<unsigned_integral_prime_type>>;

  primes_container_type primes(upper_limit_of_number_of_primes,
                               unsigned_integral_prime_type(0U));

  // Use a port pin to provide a real-time measurement.
  app_prime_port_type::set_pin_high();

  math::primes::compute_primes_via_sieve<app_prime::maximum_value_of_primes,
                                         typename primes_container_type::iterator,
                                         util::ring_allocator<void*>>(primes.begin());

  const auto prime_iterator =
    std::find_if(primes.crbegin(),
                 primes.crend(),
                 [](const unsigned_integral_prime_type& the_prime) -> bool
                 {
                   return (the_prime != unsigned_integral_prime_type(0U));
                 });

  // Potential improvement: Try to find a way to make
  // the following line independent of the number of primes.

  const bool result_is_ok =
    ((*prime_iterator) == unsigned_integral_prime_type(541U));

  if(result_is_ok)
  {
    app_prime_port_type::set_pin_low();
  }
  else
  {
    // The result of this prime number calculation is not OK.

    // Crash the system and toggle a port to provide an indication of failure.
    for(;;)
    {
      app_prime_port_type::toggle_pin();

      mcal::cpu::nop();
    }
  }
}
