///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_11-001_scale_with_powers_of_two.cpp

#include <cstdint>
#include <iostream>

namespace
{
  std::uint_fast8_t prescaler;

  void do_something_at_01x_period() { std::cout << "prescaler: 1" << std::endl; }
  void do_something_at_02x_period() { std::cout << "prescaler: 2" << std::endl; }
  void do_something_at_04x_period() { std::cout << "prescaler: 4" << std::endl; }
  void do_something_at_08x_period() { std::cout << "prescaler: 8" << std::endl; }
}

void do_something()
{
  ++prescaler;

  do_something_at_01x_period();

  if((prescaler % 2U) == 0U)
  {
    do_something_at_02x_period();

    if((prescaler % 4U) == 0U)
    {
      do_something_at_04x_period();

      if((prescaler % 8U) == 0U)
      {
        do_something_at_08x_period();
      }
    }
  }
}

int main()
{
  for(;;)
  {
    do_something();
  }
}
