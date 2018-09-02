///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter16_07-001_rand_device_and_mt19937.cpp

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>

// Create a random unsigned custom device
// for seeding a random number generator.

namespace detail
{
  template<typename unsigned_integral_type>
  class random_unsigned_custom_device final
  {
  public:
    // Use std::numeric_limits for these static asserts instead of
    // type_traits because potential UDTs are more likely to support
    // numeric_limits rather than type_traits.
    static_assert(std::numeric_limits<unsigned_integral_type>::is_specialized == true,
                  "Error: The unsigned_integral_type parameter must support a template specialization of std::numeric_limits.");

    static_assert((   (std::numeric_limits<unsigned_integral_type>::is_integer == true)
                   && (std::numeric_limits<unsigned_integral_type>::is_signed  == false)),
                  "Error: The unsigned_integral_type parameter must be an unsigned integral type.");

    static_assert(std::numeric_limits<unsigned_integral_type>::digits < 512,
                  "Error: The unsigned_integral_type parameter must have 512 digits or less.");

    using value_type = unsigned_integral_type;

    random_unsigned_custom_device() = default;

    ~random_unsigned_custom_device() = default;

    static value_type (min)() { return (std::numeric_limits<value_type>::min)(); }
    static value_type (max)() { return (std::numeric_limits<value_type>::max)(); }

    double entropy() const
    {
      // This device uses an algorithmic scheme to produce a seed.
      // As such it can be considered somewhat deterministic since
      // the algorithm could be known or possibly guessed.

      // We therefore assign an empirically estimated entropy of 4.0.
      return 4.0;
    }

    value_type operator()()
    {
      // Use the high-resolution clock as a starting point
      // for creating a unique seed. It will also be hashed
      // further below.

      using clock_type = std::chrono::high_resolution_clock;

      // Obtain an initial value of std::chrono::high_resolution_clock::now().
      const std::uintmax_t previous_now = 
        static_cast<std::uintmax_t>(std::chrono::duration_cast<std::chrono::nanoseconds>
          (clock_type::now().time_since_epoch()).count());

      std::uintmax_t current_now;

      for(;;)
      {
        // Wait for std::chrono::high_resolution_clock::now()
        // to differ from the initial value previously obtained.

        current_now =
          static_cast<std::uintmax_t>(std::chrono::duration_cast<std::chrono::nanoseconds>
            (clock_type::now().time_since_epoch()).count());

        if(current_now != previous_now)
        {
          break;
        }
      }

      // Finally perform a logical xor of current_now
      // with the value of all bits set.
      current_now ^= (std::numeric_limits<std::uintmax_t>::max)();

      // The high-resolution clock is basically a timer counting up.
      // As this could be slightly deterministic, it might have low entropy.
      // We therefore attempt to improve entropy by running
      // a simple CRC over the individual bytes of current_now
      // in order to create a more unique seed.

      // Run CRC-64/WE over the data bytes of current_now_as_integral_value.

      // CRC-64/WE
      // width   : 64
      // poly    : 0x42F0E1EBA9EA3693
      // init    : 0xFFFFFFFFFFFFFFFF
      // refin   : false
      // refout  : false
      // xorout  : 0xFFFFFFFFFFFFFFFF
      // check   : 0x62EC59E3F1A4F00A
      // residue : 0xFCACBEBD5931A992
      // name    : CRC-64/WE

      const std::uint64_t data[8U] =
      {
        static_cast<std::uint8_t>(current_now >>  0),
        static_cast<std::uint8_t>(current_now >>  8),
        static_cast<std::uint8_t>(current_now >> 16),
        static_cast<std::uint8_t>(current_now >> 24),
        static_cast<std::uint8_t>(current_now >> 32),
        static_cast<std::uint8_t>(current_now >> 40),
        static_cast<std::uint8_t>(current_now >> 48),
        static_cast<std::uint8_t>(current_now >> 56),
      };

      // Initialize the CRC-64/WE.
      std::uint64_t crc64_we_value = UINT64_C(0xFFFFFFFFFFFFFFFF);

      // Calculate the CRC-64/WE using a slow algorithm,
      // one byte at a time with one bit at a time.
      for(std::size_t i = 0U; i < 8U; ++i)
      {
        crc64_we_value ^= (std::uint64_t(data[i]) << (64 - 8));

        for(std::uint_fast8_t bit = 8U; bit > 0U; --bit)
        {
          if(std::uint64_t(crc64_we_value & (UINT64_C(1) << 63)) != 0U)
          {
            crc64_we_value = (crc64_we_value << 1) ^ UINT64_C(0x42F0E1EBA9EA3693);
          }
          else
          {
            crc64_we_value <<= 1;
          }
        }
      }

      // Finalize the CRC-64/WE.
      crc64_we_value ^= UINT64_C(0xFFFFFFFFFFFFFFFF);

      const value_type seed_result = static_cast<value_type>(crc64_we_value);

      // We now have a relatively unique seed expressed
      // as an unsigned integral value.
      return seed_result;
    }

    random_unsigned_custom_device(const random_unsigned_custom_device&) = delete;
    void operator=(const random_unsigned_custom_device&) = delete;
  };
}

void do_something()
{
  detail::random_unsigned_custom_device<std::uint32_t> device;
  const std::uint32_t seed(static_cast<std::uint32_t>(device()));

  std::mt19937                                 generator(seed);
  std::uniform_int_distribution<std::uint16_t> distribution(1, 1023);

  // Print the seed.
  std::cout << "Seed is: 0x"
            << std::hex
            << std::setw(8)
            << std::setfill(char('0'))
            << std::uppercase
            << seed
            << ". ";

  // Generate 3 pseudo-random numbers in [1, 1023].
  const std::uint16_t random_numbers[3U] =
  {
    distribution(generator),
    distribution(generator),
    distribution(generator)
  };

  std::cout << "Random numbers in [1, 1023]: ";
  std::cout << std::dec << std::setw(5) << std::setfill(char(' ')) << random_numbers[0U] << ", ";
  std::cout << std::dec << std::setw(5) << std::setfill(char(' ')) << random_numbers[1U] << ", ";
  std::cout << std::dec << std::setw(5) << std::setfill(char(' ')) << random_numbers[2U] << std::endl;
}

int main()
{
  for(std::uint_fast8_t i = 0U; i < 20U; ++i)
  {
    // Generate 20 sequences of 3 pseudo-random numbers.
    // Here we also generate a new seed in each function call.
    // In other use cases, a seed might only be generated
    // once during initialization.

    do_something();
  }
}
