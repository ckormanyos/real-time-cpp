///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// The Led Program (with template LED class)

#include "mcal_reg.h"
#include <cstdint>

template<typename port_type,
         typename bval_type,
         const port_type port,
         const bval_type bval>
class led_template
{
public:
  led_template()
  {
    // Set the port pin value to low.
    *reinterpret_cast<volatile bval_type*>(port) &= static_cast<bval_type>(~bval);

    // Set the port pin direction to output.
    *reinterpret_cast<volatile bval_type*>(port - 1U) |= bval;
  }

  auto toggle() const -> void
  {
    // Toggle the LED via direct memory access.
    *reinterpret_cast<volatile bval_type*>(port) ^= bval;
  }
};

namespace
{
  // Create led_b5 at port B, bit position 0.
  const led_template<std::uint8_t,
                     std::uint8_t,
                     mcal::reg::portb,
                     mcal::reg::bval5> led_b5;
}

auto main() -> int
{
  // Toggle led_b5 in a loop forever.
  for (;;)
  {
    led_b5.toggle();
  }
}
