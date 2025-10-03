///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_18-002_alignment.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

struct alignas(16) timer_register_type
{
  std::uint32_t tmr_ctrl1 { };
  std::uint32_t tmr_ctrl2 { };
  std::uint32_t tmr_cntr1 { };
  std::uint32_t tmr_cntr2 { };
};

volatile timer_register_type my_timer_registers =
{
  0U, 0U, 0U, 0U
};

auto main() -> int
{
  // The address of my_timer_registers should be evenly divisible by 16.
  std::cout << std::showbase
            << std::hex
            << std::uintmax_t(&my_timer_registers)
            << std::endl;

  // This should be 0.
  std::cout << std::hex
            << (std::uintmax_t(&my_timer_registers) % 16U)
            << std::endl;
}
