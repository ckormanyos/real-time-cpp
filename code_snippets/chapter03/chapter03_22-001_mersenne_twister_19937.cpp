///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_22-001_mersenne_twister_19937.cpp

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>

namespace detail
{
  // Create a custom random device for seeding the pseudo-random number generator.
  class random_integral_device final
  {
  public:
    typedef std::uint64_t result_type;

    random_integral_device() { }

    ~random_integral_device() = default;

    static result_type (min)() { return (std::numeric_limits<result_type>::min)(); }
    static result_type (max)() { return (std::numeric_limits<result_type>::max)(); }

    result_type operator()()
    {
      // Use the high-resolution clock to create the basis for a seed.

      using clock_type = std::chrono::high_resolution_clock;

      const std::uint64_t previous_now = 
        static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(clock_type::now().time_since_epoch()).count());

      std::uint64_t current_now;

      // Wait for std::chrono::high_resolution_clock::now() to differ from the previous value.
      for(;;)
      {
        current_now =
          static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(clock_type::now().time_since_epoch()).count());

        if(current_now != previous_now)
        {
          break;
        }
      }

      // The high-resolution clock is basically a timer counting up.
      // As this could be slightly deterministic, it might have low entropy.
      // We therefore run a simple CRC (in this case a bitwise CRC-64/WE)
      // over current_now to create the seed.

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

      const result_type seed_result = crc64_we_value;

      // We now have a unique seed expressed as a 64-bit unsigned integral value.
      return seed_result;
    }

    random_integral_device(const random_integral_device&) = delete;
    void operator=(const random_integral_device&) = delete;
  };
}

void do_something()
{
        detail::random_integral_device               device;
  const std::uint32_t                                seed(static_cast<std::uint32_t>(device()));
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
  // Generate 20 sequences of 3 pseudo-random numbers.
  for(std::uint_fast8_t i = 0U; i < 20U; ++i)
  {
    do_something();
  }
}
