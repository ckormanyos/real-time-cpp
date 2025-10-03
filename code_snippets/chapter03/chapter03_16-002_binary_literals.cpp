///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter03_16-002_binary_literals.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

// The simulated portb register.
static auto simulated_portb = std::uint8_t { };

auto do_something() -> void
{
  // Switch portb.5 from low to high.
  volatile auto pb { reinterpret_cast<volatile std::uint8_t*>(&simulated_portb) };

  *pb =
    static_cast<std::uint8_t>
    (
        static_cast<std::uint8_t>(*pb)
      | static_cast<std::uint8_t>(UINT8_C(0b0010'0000))
    );
}

auto main() -> int
{
  do_something();

  const auto flg = std::cout.flags();

  std::cout << "simulated portb is "
            << std::hex
            << std::showbase
            << unsigned(simulated_portb)
            << std::endl;

  std::cout.flags(flg);
}
