///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter01_01-001_led_program.cpp

// The LED program (PC simulation).

#include <cstdint>
#include <iostream>

class led final
{
public:
  // The led class constructor.
  led() : is_on(false) { }

  ~led() = default;

  void toggle() const
  {
    // Toggle the LED in the PC simulation.
    is_on = (!is_on);

    std::cout << (is_on ? "LED is on" : "LED is off") << std::endl;
  }

private:
  // Private member variables of the class.
  mutable bool is_on;
};

namespace
{
  // Create led_b5 (simulated on a PC).
  const led led_b5;
}

int main()
{
  // Toggle led_b5 in a loop forever.
  for(;;)
  {
    led_b5.toggle();
  }
}
