///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter07_01-002_register_address.cpp

// See also https://godbolt.org/z/MoK9q9qY5

#include <cstdint>
#include <iomanip>
#include <iostream>

static auto simulated_register_portb = std::uint8_t { };

namespace local
{
  auto print() -> void
  {
    const auto flg = std::cout.flags();

    std::cout << "simulated_register_portb: "
              << std::hex
              << "0x"
              << std::setw(static_cast<std::streamsize>(INT8_C(2)))
              << std::setfill('0')
              << static_cast<unsigned>(simulated_register_portb)
              << std::endl;

    std::cout.flags(flg);
  }
}

void do_something()
{
  // Set simulated portb to 0x55.
  *reinterpret_cast<volatile std::uint8_t*>(&simulated_register_portb) = static_cast<std::uint8_t>(UINT8_C(0x55));

  local::print();

  // Set simulated portb to 0x00.
  *reinterpret_cast<volatile std::uint8_t*>(&simulated_register_portb) = static_cast<std::uint8_t>(UINT8_C(0x00));

  local::print();
}

auto main() -> int;

auto main() -> int
{
  do_something();
}
