#include <iostream>
#include <mcal_led.h>
#include <mcal_reg_access.h>

const led led_b5;

void led::toggle() const
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
