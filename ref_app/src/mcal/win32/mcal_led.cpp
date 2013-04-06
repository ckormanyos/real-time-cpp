#include <mcal_led.h>
#include <iostream>

namespace mcal
{
  namespace led
  {
    const led_type led0;
  }
}

void mcal::led::led_type::toggle() const
{
  // Toggle the LED state.
  is_on = (!is_on);

  // Print the LED state.
  if(is_on)
  {
    std::cout << "LED is on" << std::endl;
  }
  else
  {
    std::cout << "LED is off" << std::endl;
  }
}
