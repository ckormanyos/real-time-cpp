/////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter16_07-001_random_engine.cpp

#include <array>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>

namespace mcal { namespace random {

class random_engine
{
public:
  using result_type = std::uint32_t;

  random_engine() { }

  ~random_engine() = default;

  random_engine& operator=
    (const random_engine&) = delete;

  std::uint_fast8_t entropy() const
  {
    return 4U;
  }

  result_type operator()()
  {
    using clock_type =
      std::chrono::high_resolution_clock;

    const result_type basis_for_seed =
      result_type(
        clock_type::now().time_since_epoch().count());

    return result_type(crc32_mpeg2(basis_for_seed));
  }

private:
  template<typename IntegralType>
  std::uint32_t crc32_mpeg2(const IntegralType v)
  {
    // Calculate a bitwise CRC32/MPEG-2 over the
    // individual bytes of the input parameter v.

    // Extract the bytes of v into an array.
    std::array<std::uint8_t,
               std::numeric_limits<IntegralType>::digits / 8U> data;

    for(std::uint_fast8_t i = 0U; i < data.size(); ++ i)
    {
      data[i] = std::uint8_t(v >> (i * 8U));
    }

    std::uint32_t crc = UINT32_C(0xFFFFFFFF);

    // Perform modulo-2 division, one byte at a time.
    for(std::size_t byte = 0U; byte < data.size(); ++byte)
    {
      // Bring the next byte into the result.
      crc ^= (std::uint32_t(data[byte]) << (std::numeric_limits<std::uint32_t>::digits - 8U));

      // Perform a modulo-2 division, one bit at a time.
      for(std::int_fast8_t bit = 8; bit > 0; --bit)
      {
        // Divide the current data bit.
        if((crc & (std::uintmax_t(1U) << (std::numeric_limits<std::uint32_t>::digits - 1U))) != 0U)
        {
          crc = std::uint32_t(crc << 1) ^ UINT32_C(0x04C11DB7);
        }
        else
        {
          crc <<= 1;
        }
      }
    }

    return std::uint32_t(crc);
  }
};

} } // namespace mcal::random

void do_something()
{
        mcal::random::random_engine                       rng;
  const typename mcal::random::random_engine::result_type seed(rng());
        std::mt19937                                      generator(seed);
        std::uniform_int_distribution<unsigned> distribution(1U, 1023U);

  // Print the seed.
  std::cout << "Seed is: 0x"
            << std::hex
            << std::setw(8)
            << std::setfill(char('0'))
            << std::uppercase
            << seed
            << ". ";

  // Generate 3 pseudo-random numbers in [1, 1023].
  const unsigned random_numbers[3U] =
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
