/////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter16_08-001_random_engine.cpp

// See also https://godbolt.org/z/8c1v1rboh

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

  random_engine() = default;

  ~random_engine() = default;

  random_engine(const random_engine&) = delete;
  random_engine(random_engine&&) noexcept = delete;

  auto operator=(const random_engine&) -> random_engine& = delete;
  auto operator=(random_engine&&) noexcept -> random_engine& = delete;

  auto entropy() const noexcept -> std::uint_fast8_t
  {
    return 4U;
  }

  result_type operator()()
  {
    const auto time_stamp = static_cast<result_type>(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    const result_type basis_for_seed = static_cast<result_type>(time_stamp);

    return static_cast<result_type>(crc32_mpeg2(basis_for_seed));
  }

private:
  template<typename IntegralType>
  auto crc32_mpeg2(const IntegralType v) -> std::uint32_t
  {
    // Calculate a bitwise CRC32/MPEG-2 over the
    // individual bytes of the input parameter v.

    // Extract the bytes of v into an array.
    std::array<std::uint8_t,
               std::numeric_limits<IntegralType>::digits / 8U> data;

    for(auto i = static_cast<std::uint_fast8_t>(UINT8_C(0)); i < static_cast<std::uint_fast8_t>(data.size()); ++ i)
    {
      data[i] = std::uint8_t(v >> (i * 8U));
    }

    auto crc = static_cast<std::uint32_t>(UINT32_C(0xFFFFFFFF));

    // Perform modulo-2 division, one byte at a time.
    for(auto byte = static_cast<std::size_t>(UINT8_C(0)); byte < data.size(); ++byte)
    {
      {
        constexpr auto left_shift_amount =
          static_cast<unsigned>
          (
            std::numeric_limits<std::uint32_t>::digits - static_cast<int>(INT8_C(8))
          );

        // Bring the next byte into the result.
        crc ^= static_cast<std::uint32_t>(static_cast<std::uint32_t>(data[byte]) << left_shift_amount);
      }

      // Perform a modulo-2 division, one bit at a time.
      for(auto bit = static_cast<std::int_fast8_t>(INT8_C(8)); bit > static_cast<std::int_fast8_t>(INT8_C(0)); --bit)
      {
        const auto left_shift_amount =
          static_cast<unsigned>
          (
            std::numeric_limits<std::uint32_t>::digits - static_cast<int>(INT8_C(1))
          );

        constexpr auto mask =
          static_cast<std::uint32_t>(static_cast<std::uintmax_t>(UINT8_C(1)) << left_shift_amount);

        // Divide the current data bit.
        if(static_cast<std::uint32_t>(crc & mask) != static_cast<std::uint32_t>(UINT8_C(0)))
        {
          crc =
            static_cast<std::uint32_t>
            (
                static_cast<std::uint32_t>(crc << static_cast<unsigned>(UINT8_C(1)))
              ^ static_cast<std::uint32_t>(UINT32_C(0x04C11DB7))
            );
        }
        else
        {
          crc <<= static_cast<unsigned>(UINT8_C(1));
        }
      }
    }

    return static_cast<std::uint32_t>(crc);
  }
};

} } // namespace mcal::random

auto do_something() -> void;

auto do_something() -> void
{
        mcal::random::random_engine                       rng;
  const typename mcal::random::random_engine::result_type seed(rng());
        std::mt19937                                      generator(seed);

  std::uniform_int_distribution<unsigned>
    distribution
    {
      static_cast<unsigned>(UINT8_C(1)),
      static_cast<unsigned>(UINT16_C(1023))
    };

  const auto flg = std::cout.flags();

  // Print the seed.
  std::cout << "Seed is: 0x"
            << std::hex
            << std::setw(static_cast<std::streamsize>(INT8_C(8)))
            << std::setfill('0')
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
  std::cout << std::dec << std::setw(static_cast<std::streamsize>(INT8_C(5))) << std::setfill(' ') << random_numbers[static_cast<std::size_t>(UINT8_C(0))] << ", ";
  std::cout << std::dec << std::setw(static_cast<std::streamsize>(INT8_C(5))) << std::setfill(' ') << random_numbers[static_cast<std::size_t>(UINT8_C(1))] << ", ";
  std::cout << std::dec << std::setw(static_cast<std::streamsize>(INT8_C(5))) << std::setfill(' ') << random_numbers[static_cast<std::size_t>(UINT8_C(2))] << std::endl;

  std::cout.flags(flg);
}

auto main() -> int;

auto main() -> int
{
  // Generate 20 sequences of 3 pseudo-random numbers.
  for(auto i = static_cast<std::uint_fast8_t>(UINT8_C(0)); i < static_cast<std::uint_fast8_t>(UINT8_C(20)); ++i)
  {
    do_something();
  }
}
