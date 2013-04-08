///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// The Led Program (with timing)

#include <cstdint>
#include <util/utility/util_time.h>
#include <mcal/mcal.h>

class led
{
public:
  typedef std::uint8_t port_type;
  typedef std::uint8_t bval_type;

  led(const port_type p,
      const bval_type b) : port(p),
                           bval(b)
  {
    // Set the port pin to low.
    *reinterpret_cast<volatile bval_type*>(port) &= static_cast<bval_type>(~bval);

    // Set the port pin to output.
    *reinterpret_cast<volatile bval_type*>(port - 1U) |= bval;
  }

  void toggle(void) const
  {
    // Toggle the LED.
    *reinterpret_cast<volatile bval_type*>(port) ^= bval;
  }

private:
  const port_type port;
  const bval_type bval;
};

namespace
{
  // Define a convenient local 32-bit timer type.
  typedef util::timer<std::uint32_t> timer_type;

  // Create led_b5 at port B, bit position 5.
  const led led_b5(mcal::reg::portb, mcal::reg::bval5);
}

int main(void)
{
  // Enable all global interrupts.
  mcal::irq::enable_all();

  // Initialize the mcal.
  mcal::init();

  // Toggle led0 forever.
  for(;;)
  {
    led_b5.toggle();

    // Wait 1 second in a blocking delay.
    timer_type::blocking_delay(timer_type::seconds(1U));
  }
}
