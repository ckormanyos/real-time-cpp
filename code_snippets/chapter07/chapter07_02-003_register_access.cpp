///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter07_02-003_register_access.cpp

#include <iostream>
#include <cstdint>

template<typename addr_type,
         typename reg_type>
struct reg_access_dynamic
{
  static void reg_set(const addr_type addr, const reg_type val)
  {
    *reinterpret_cast<volatile reg_type*>(addr) = val;
  }
};

// The simulated timer0 compare0 register.
auto simulated_register_tm0cmp0 = std::uint16_t { };

void do_something()
{
  const std::uintptr_t address_tm0cmp0 = reinterpret_cast<std::uintptr_t>(&simulated_register_tm0cmp0);

  // Set the simulated timer0 compare0 register
  // at address 0xFFFFF694UL to value (32,000 - 1).
  *reinterpret_cast<volatile std::uint16_t*>(address_tm0cmp0) =
    static_cast<std::uint16_t>
    (
      static_cast<std::uint16_t>(UINT16_C(32000)) - static_cast<std::uint16_t>(UINT8_C(1))
    );
}

auto main() -> int;

auto main() -> int
{
  do_something();

  std::cout << "simulated_register_tm0cmp0: "
            << static_cast<unsigned>(simulated_register_tm0cmp0)
            << std::endl;
}
