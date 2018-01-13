#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <vector>

// chapter03_02-003_fixed_size_integer_prime_numbers.cpp

namespace
{
  template<typename unsigned_integral_type = std::uint32_t,
           const unsigned_integral_type maximum_value = UINT32_C(10006730)>
  void compute_primes_via_sieve(std::vector<unsigned_integral_type>& primes)
  {
    // Use a sieve algorithm to generate a uint8_t table representation
    // of the primes. In this sieve, the logic is inverted. In other words,
    // true means that the number is *not* prime.

    // Note for tiny embedded systems: Use a bit-stream for storing
    // the sieve information. The performance will suffer,
    // but the storage requirements will be significantly reduced.
    std::vector<std::uint_fast8_t> sieve(maximum_value, 0U);

    unsigned_integral_type i2;

    // Create the sieve of primes.
    for(unsigned_integral_type i = 2U; (i2 = unsigned_integral_type(i * i)) < maximum_value; ++i)
    {
      if(sieve[i] == 0U)
      {
        for(unsigned_integral_type j = i2; j < maximum_value; j += i)
        {
          sieve[j] = UINT8_C(1);
        }
      }
    }

    // Fill the prime numbers into the data table
    // by extracting them from the sieve of primes.
    std::uint32_t prime_number = UINT32_C(2);

    const float x = static_cast<float>(maximum_value);

    // Calculate the upper limit of the number of primes expected.

    // See Eq. 3.7 in: J. Barkley Rosser and Lowell Schoenfeld,
    // "Approximate formulas for some functions of prime numbers",
    // llinois J. Math. Volume 6, Issue 1 (1962), 64-94.
    // This states that pi(x) < ((5 * x) / (4 * log(x))).

    // See also "Prime-counting function" at
    // http://en.wikipedia.org/wiki/Prime-counting_function

    using std::log;

    const float upper_limit_of_number_of_primes = ((5.0F * x) / (4.0F * log(x)));

    using prime_index_type = std::vector<unsigned_integral_type>::size_type;

    primes.resize(static_cast<prime_index_type>(std::floor(upper_limit_of_number_of_primes)));

    prime_index_type prime_index = 0U;

    std::for_each(sieve.cbegin() + prime_index_type(2U),
                  sieve.cend(),
                  [&primes, &prime_number, &prime_index](const std::uint8_t& is_not_prime)
                  {
                    if(is_not_prime == 0U)
                    {
                      primes[prime_index] = prime_number;

                      ++prime_index;
                    }

                    ++prime_number;
                  });
  }
}

int main()
{
  using prime_integral_type = std::uint32_t;
  //using prime_integral_type = std::uint16_t;

  std::vector<prime_integral_type> primes;

  // For the prime number 10,006,721, see also
  // D.N. Lehmer, "List of prime numbers from 1 to 10,006,721"
  // (Carnegie Institution of Washington, Washington D.C. 1914).

  // Note for tiny embedded systems: The 500th prime number
  // is 3571. We can switch the number 10006730 to 3572
  // in order to obtain 500 prime numbers.

  compute_primes_via_sieve<prime_integral_type, UINT32_C(10006730)>(primes);
  //compute_primes_via_sieve<prime_integral_type, 3572U>(primes);

  std::for_each(primes.cbegin(),
                primes.cend(),
                [](const prime_integral_type& the_prime)
                {
                  if(the_prime != prime_integral_type(0U))
                  {
                    std::cout << the_prime << '\n';
                  }
                });
}
