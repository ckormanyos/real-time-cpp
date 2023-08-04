///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <iostream>

// chapter08_03-001_static_constructor.cpp

class led
{
public:
  explicit led(const std::uintptr_t addr = static_cast<std::uintptr_t>(UINT8_C(0)),
               const std::uint8_t   bval = static_cast<std::uint8_t>  (UINT8_C(0)))
    : my_addr(addr),
      my_bval(bval)
  {
    static_cast<void>(my_addr);
    static_cast<void>(my_bval);

    std::cout << "in class led constructor" << std::endl;
  }

  ~led() = default;

  void toggle() const
  {
    std::cout << "in class led toggle" << std::endl;
  }

private:
  const std::uintptr_t my_addr { };
  const std::uint8_t   my_bval { };
};

// The simulated portb.
auto simulated_register_portb = std::uint8_t { };
auto bit5                     = static_cast<std::uint8_t>(UINT8_C(0x20));

const std::uintptr_t address =
  reinterpret_cast<std::uintptr_t>(&simulated_register_portb);

// Create led_b5 on portb.5.
const led led_b5
{
  address,
  bit5
};

void do_something()
{
  led_b5.toggle();
}

int main()
{
  do_something();
}
