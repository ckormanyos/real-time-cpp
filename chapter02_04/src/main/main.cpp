// The Led Program (with timing)

#include <cstdint>
#include <util/utility/util_time.h>
#include "../mcal/mcal.h"

class led
{
public:
  typedef std::uint8_t port_type;
  typedef std::uint8_t bval_type;

  led(const port_type p,const bval_type b) : port(p),
                                             bval(b)
  {
    // Set the port pin to low.
    *reinterpret_cast<volatile bval_type*>(port)
      &= static_cast<bval_type>(~bval);

    // Set the port pin to output.
    *reinterpret_cast<volatile bval_type*>(port - 1u)
      |= bval;
  }

  void toggle(void) const
  {
    // Toggle the LED.
    *reinterpret_cast<volatile bval_type*>(port)
      ^= bval;
  }

private:
  const port_type port;
  const bval_type bval;
};

namespace
{
  // Define a convenient local 16-bit timer type.
  typedef util::timer<std::uint16_t> timer_type;

  // Create led_b5 at port B, bit position 5.
  constexpr led led_b5
  {
    mcal::registers::REG_PORTB,
    mcal::registers::BVAL5
  };
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
    timer_type::blocking_delay(timer_type::second(1U));
  }
}
