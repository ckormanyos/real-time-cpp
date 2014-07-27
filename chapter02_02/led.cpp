///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// The LED program.

#include <cstdint>
#include "mcal_reg.h"

class led
{
public:
  // Use convenient class-specific typedefs.
  typedef std::uint8_t port_type;
  typedef std::uint8_t bval_type;

  // The led class constructor.
  led(const port_type p,
      const bval_type b) : port(p),
                           bval(b)
  {
    // Set the port pin to low.
    *reinterpret_cast<volatile bval_type*>(port) &= static_cast<bval_type>(~bval);

    const bval_type pdir = port - 1U;

    // Set the port pin to output.
    *reinterpret_cast<volatile bval_type*>(pdir) |= bval;
  }

  void toggle() const
  {
    // Toggle the LED via direct memory access.
    *reinterpret_cast<volatile bval_type*>(port) ^= bval;
  }

private:
  // Private member variables of the class.
  const port_type port;
  const bval_type bval;
};

namespace
{
  // Create led_b5 on portb.5.
  const led led_b5
  {
    mcal::reg::portb,
    mcal::reg::bval5
  };
}

int main()
{
  // Toggle led_b5 in a loop forever.
  for(;;)
  {
    led_b5.toggle();
  }
}
