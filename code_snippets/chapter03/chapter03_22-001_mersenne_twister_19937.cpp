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

namespace local
{
  // Create a custom random device for seeding the pseudo-random number generator.
  // Use a custom random device because the default is allowed to repeat values.
  class my_custom_random_device
  {
  public:
    typedef std::uint32_t result_type;

    my_custom_random_device()
    {
      operator()();
    }

    static result_type (min)() { return (std::numeric_limits<result_type>::min)(); }
    static result_type (max)() { return (std::numeric_limits<result_type>::max)(); }

    result_type operator()()
    {
      // Use the high-resolution clock to create the basis for a seed.

      static std::uint64_t previous_now_as_integral_value;

      using clock_type = std::chrono::high_resolution_clock;

      std::uint64_t current_now_as_integral_value;

      // Wait for std::chrono::high_resolution_clock::now()
      // to differ from the last call of the seed.
      for(;;)
      {
        current_now_as_integral_value = 
          std::chrono::duration_cast<std::chrono::nanoseconds>(clock_type::now().time_since_epoch()).count();

        if(previous_now_as_integral_value != current_now_as_integral_value)
        {
          break;
        }
      }

      previous_now_as_integral_value = current_now_as_integral_value;

      // The high-resolution clock is basically a timer counting up.
      // It could be somewhat deterministic and might suffer from entropy loss.
      // We therefore run a simple CRC (in this case a bitwise CRC64 / WE)
      // over current_now_as_integral_value to create the seed.

      // Run CRC64 / WE over current_now_as_integral_value.

      // CRC64 / WE
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
        std::uint8_t(current_now_as_integral_value >>  0),
        std::uint8_t(current_now_as_integral_value >>  8),
        std::uint8_t(current_now_as_integral_value >> 16),
        std::uint8_t(current_now_as_integral_value >> 24),
        std::uint8_t(current_now_as_integral_value >> 32),
        std::uint8_t(current_now_as_integral_value >> 40),
        std::uint8_t(current_now_as_integral_value >> 48),
        std::uint8_t(current_now_as_integral_value >> 56),
      };

      // Initialize the CRC.
      std::uint64_t crc64_we_value = UINT64_C(0xFFFFFFFFFFFFFFFF);

      // Calculate the CRC, one byte and one bit at a time.
      for(std::size_t i = 0U; i < 8U; ++i)
      {
        crc64_we_value ^= (std::uint64_t(data[i]) << (64 - 8));

        for(std::uint_fast8_t bit = 8U; bit > 0U; --bit)
        {
          if(std::uint64_t(crc64_we_value & (1ULL << 63)) != 0U)
          {
            crc64_we_value = (crc64_we_value << 1) ^ UINT64_C(0x42F0E1EBA9EA3693);
          }
          else
          {
            crc64_we_value <<= 1;
          }
        }
      }

      // Finalize the CRC.
      crc64_we_value ^= UINT64_C(0xFFFFFFFFFFFFFFFF);

      const result_type seed32 = static_cast<result_type>(crc64_we_value);

      std::cout << "Seed is: 0x"
                << std::hex
                << std::setw(8)
                << std::setfill(char('0'))
                << std::uppercase
                << seed32
                << std::endl;

      // We now have a unique seed expressed as an integral value.
      return seed32;
    }

    my_custom_random_device(const my_custom_random_device&) = delete;
    void operator=(const my_custom_random_device&) = delete;
  };
}

void do_something()
{
  local::my_custom_random_device               my_random_device;
  std::mt19937                                 my_generator(my_random_device());
  std::uniform_int_distribution<std::uint16_t> my_distribution(1, 1023);

  // Generate 3 pseudo-random numbers.
  const std::uint16_t random_numbers[3U] =
  {
    my_distribution(my_generator),
    my_distribution(my_generator),
    my_distribution(my_generator)
  };

  std::cout << "Random numbers in [1...1023): ";
  std::cout << std::dec << std::setw(5) << std::setfill(char(' ')) << random_numbers[0U] << ", ";
  std::cout << std::dec << std::setw(5) << std::setfill(char(' ')) << random_numbers[1U] << ", ";
  std::cout << std::dec << std::setw(5) << std::setfill(char(' ')) << random_numbers[2U] << std::endl;
  std::cout << std::endl;
}

int main()
{
  // Generate 10 sequences of 3 pseudo-random numbers.
  for(std::uint_fast8_t i = 0U; i < 10U; ++i)
  {
    do_something();
  }
}
