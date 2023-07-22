///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_22-001_mersenne_twister_19937.cpp

#include <cstdint>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>

void do_something()
{
  using local_result_type = typename std::random_device::result_type;

        std::random_device                               device;
  const local_result_type                                seed(device());
        std::mt19937                                     gtor(seed);
        std::uniform_int_distribution<local_result_type> distribution
                                                         {
                                                           static_cast<local_result_type>(UINT16_C(1)),
                                                           static_cast<local_result_type>(UINT16_C(1023))
                                                         };

  // Print the seed.
  std::cout << "Seed is: 0x"
            << std::hex
            << std::setw(8)
            << std::setfill('0')
            << std::uppercase
            << seed
            << ". ";

  // Generate 3 pseudo-random numbers in [1, 1023].
  const unsigned random_numbers[3U] =
  {
    distribution(gtor),
    distribution(gtor),
    distribution(gtor)
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
