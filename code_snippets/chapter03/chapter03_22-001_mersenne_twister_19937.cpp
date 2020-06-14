///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_22-001_mersenne_twister_19937

#include <cstdint>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>

void do_something()
{
  using res_type =
    typename std::random_device::result_type;

  std::random_device  device;
  const res_type seed(device());
  std::mt19937        gtor(seed);
  const std::uniform_int_distribution<res_type>
   distribution(1U, 1023U);

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
