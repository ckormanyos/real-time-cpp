///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <vector>

// chapter03_02-002a_explore_prime_numbers.cpp

// In this code snippet, we explore the calculation
// of the prime numbers up to and including 10,006,721.
// A sieve method is used.

namespace
{
  template<typename unsigned_integral_type = std::uint32_t,
           const unsigned_integral_type maximum_value = static_cast<std::uint32_t>(UINT32_C(10006730))>
  auto compute_primes_via_sieve(std::vector<unsigned_integral_type>& primes) -> void
  {
    // Use a sieve algorithm to generate
    // a uint8 table of primes.
    // In this sieve, the logic is inverted.
    // In other words, true means that
    // the number is *not* prime.

    // Note for tiny embedded systems: Use a bit-stream for storing
    // the sieve information. The performance will suffer,
    // but the storage requirements will be significantly reduced.
    std::vector<std::uint_fast8_t> sieve(maximum_value, 0U);

    using std::sqrt;
    using std::floor;

    const unsigned_integral_type imax =
      static_cast<unsigned_integral_type>(floor(sqrt(static_cast<float>(maximum_value))));

    // Create the sieve of primes.
    for(unsigned_integral_type i = 2U; i < imax; ++i)
    {
      const unsigned_integral_type i2 = unsigned_integral_type(i * i);

      if(sieve[i] == 0U)
      {
        for(unsigned_integral_type j = i2; j < maximum_value; j += i)
        {
          sieve[j] = UINT8_C(1);
        }
      }
    }

    // Calculate the upper limit of the number of primes expected.
    // See Eq. 3.7 in: J. Barkley Rosser and Lowell Schoenfeld,
    // "Approximate formulas for some functions of prime numbers",
    // Illinois J. Math. Volume 6, Issue 1 (1962), 64-94.
    // This states that pi(x) < ((5 * x) / (4 * log(x))),
    // where pi(x) is the distribution of primes over
    // the real integral value x.

    // See also "Prime-counting function" at
    // http://en.wikipedia.org/wiki/Prime-counting_function

    using std::log;

    const float x = static_cast<float>(maximum_value);

    const float upper_limit_of_number_of_primes = ((5.0F * x) / (4.0F * log(x)));

    primes.clear();
    primes.resize(static_cast<unsigned_integral_type>(std::floor(upper_limit_of_number_of_primes)));

    // Fill the prime numbers into the data table
    // by extracting them from the sieve of primes.
    unsigned_integral_type prime_counter = 2U;

    // Fill the prime numbers into the data table
    // by extracting them from the sieve of primes.
    unsigned_integral_type running_number = 2U;

    std::for_each(sieve.cbegin() + unsigned_integral_type(2U),
                  sieve.cend(),
                  [&primes, &running_number, &prime_counter](const std::uint8_t& is_not_prime)
                  {
                    if(is_not_prime == 0U)
                    {
                      primes[prime_counter] = running_number;

                      ++prime_counter;
                    }

                    ++running_number;
                  });
  }
}

auto main() -> int
{
  using unsigned_integral_prime_type = std::uint32_t;

  std::vector<unsigned_integral_prime_type> primes;

  // For the prime number 10,006,721, see also
  // D.N. Lehmer, "List of prime numbers from 1 to 10,006,721"
  // (Carnegie Institution of Washington, Washington D.C. 1914).

  // Note for tiny embedded systems: The 500th prime number
  // is 3571. We can, therefore, switch the upper limit
  // from 10006730 to 3572 in order to obtain 500 prime numbers.

  compute_primes_via_sieve<unsigned_integral_prime_type,
                           unsigned_integral_prime_type(10006730ULL)>(primes);

  std::for_each(primes.cbegin(),
                primes.cend(),
                [](const unsigned_integral_prime_type& the_prime)
                {
                  if(the_prime != unsigned_integral_prime_type(0U))
                  {
                    std::cout << the_prime << '\n';
                  }
                });
}
