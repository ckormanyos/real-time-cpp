///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter07_04-003_register_access_reg_map.cpp

#include <iomanip>
#include <iostream>
#include <cstdint>

typedef struct bit8_type
{
  std::uint8_t b0 : 1;
  std::uint8_t b1 : 1;
  std::uint8_t b2 : 1;
  std::uint8_t b3 : 1;
  std::uint8_t b4 : 1;
  std::uint8_t b5 : 1;
  std::uint8_t b6 : 1;
  std::uint8_t b7 : 1;
}
bit8_type;

template<typename addr_type,
         typename reg_type,
         typename bits_type>
struct reg_map_dynamic
{
  static reg_type& value(const addr_type addr)
  {
    return *reinterpret_cast<reg_type*>(addr);
  }

  static bits_type& bits(const addr_type addr)
  {
    return *reinterpret_cast<bits_type*>(addr);
  }
};

// The simulated portb.
std::uint8_t simulated_register_portb;

const std::uintptr_t address =
  reinterpret_cast<std::uintptr_t>(&simulated_register_portb);

void do_something()
{
  // Set portb to 0.
  reg_map_dynamic<std::uintptr_t,
                  std::uint8_t,
                  bit8_type>::value(address) = UINT8_C(0);

  // Set portb.5 to 1.
  reg_map_dynamic<std::uintptr_t,
                  std::uint8_t,
                  bit8_type>::bits(address).b5 = 1U;
}

int main()
{
  do_something();

  std::cout << "simulated_register_portb: "
            << std::hex
            << "0x"
            << std::setw(2)
            << unsigned(simulated_register_portb)
            << std::endl;
}
