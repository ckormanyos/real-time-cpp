///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_11-001_scale_with_powers_of_two.cpp

#include <cstdint>
#include <iostream>

namespace
{
  std::uint_fast8_t prescaler { };

  auto do_something_at_01x_period() -> void { std::cout << "prescaler: 1" << std::endl; }
  auto do_something_at_02x_period() -> void { std::cout << "prescaler: 2" << std::endl; }
  auto do_something_at_04x_period() -> void { std::cout << "prescaler: 4" << std::endl; }
  auto do_something_at_08x_period() -> void { std::cout << "prescaler: 8" << std::endl; }
}

auto do_something() -> void;

auto do_something() -> void
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

auto main() -> int;

auto main() -> int
{
  for(unsigned index { UINT8_C(0) }; index < unsigned { UINT8_C(128) }; ++index)
  {
    static_cast<void>(index);

    do_something();
  }
}
