///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_21-001_mersenne_twister_19937.cpp

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <random>

void do_something()
{
  std::random_device my_device;
  std::mt19937       my_generator(my_device());
  std::uniform_int_distribution<std::uint16_t>
                     my_distribution(1, 1023);

  const std::uint16_t random_numbers[3U] =
  {
    my_distribution(my_generator),
    my_distribution(my_generator),
    my_distribution(my_generator)
  };

  std::copy(random_numbers,
            random_numbers + 3U,
            std::ostream_iterator<std::uint16_t>(std::cout, ". "));

  std::cout << std::endl;
}

int main()
{
  do_something();
}
