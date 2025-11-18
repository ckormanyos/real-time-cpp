///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_22-001_mersenne_twister_19937.cpp

// See also: https://godbolt.org/z/azW71ahfK

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>

template<typename EngineType>
auto do_something() -> void;

template<typename EngineType>
auto do_something() -> void
{
  using local_result_type = typename EngineType::result_type;

  using dist_type = std::uniform_int_distribution<local_result_type>;

  std::random_device dev { };

  const local_result_type seed(dev());
  EngineType eng { seed };

  dist_type
    distribution
    {
      static_cast<local_result_type>(UINT16_C(1)),
      static_cast<local_result_type>(UINT16_C(1023))
    };

  std::stringstream strm { };

  // Print the seed.
  strm << "Seed is: 0x"
       << std::hex
       << std::setw(8)
       << std::setfill('0')
       << std::uppercase
       << seed
       << ". ";

  // Generate 3 pseudo-random numbers in [1, 1023].
  const unsigned random_numbers[std::size_t { UINT8_C(3) }] =
  {
    static_cast<unsigned>(distribution(eng)),
    static_cast<unsigned>(distribution(eng)),
    static_cast<unsigned>(distribution(eng))
  };

  strm << "Random numbers in [1, 1023]: ";
  strm << std::dec << std::setw(5) << std::setfill(char(' ')) << random_numbers[0U] << ", ";
  strm << std::dec << std::setw(5) << std::setfill(char(' ')) << random_numbers[1U] << ", ";
  strm << std::dec << std::setw(5) << std::setfill(char(' ')) << random_numbers[2U];

  std::cout << strm.str() << std::endl;
}

auto main() -> int;

auto main() -> int
{
  // Generate 8 sequences of 3 pseudo-random numbers.
  for(std::uint_fast8_t i = { UINT8_C(0) }; i < std::uint_fast8_t { UINT8_C(8) }; ++i)
  {
    // For std::mt19937.
    using eng32_type = std::mt19937;

    do_something<eng32_type>();
  }

  std::cout << std::endl;

  // Generate 8 sequences of 3 pseudo-random numbers.
  for(std::uint_fast8_t i = { UINT8_C(0) }; i < std::uint_fast8_t { UINT8_C(8) }; ++i)
  {
    // For std::mt19937_64.
    using eng64_type = std::mt19937_64;

    do_something<eng64_type>();
  }
}
