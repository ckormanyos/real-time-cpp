///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_07-001_led_static_polymorphism.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

class pwm final // A placeholder pwm class used for exemplary purposes.
{
public:
  pwm(const std::uint8_t c) : channel(c) { }

  ~pwm() = default;

  std::uint8_t get_channel() const { return channel; }

private:
  pwm(const pwm&) = delete;
  pwm& operator=(const pwm&) = delete;

  const std::uint8_t channel;
};

class led_port // No base class.
{
public:
  led_port(const std::uint8_t p, const std::uint8_t b)
    : is_on(false),
      port (p),
      bval (b) { static_cast<void>(bval); }

  void toggle() const // Not virtual.
  {
    // Toggle the LED port in the PC simulation.
    is_on = (!is_on);

    // Show the PC simulated port LED.
    std::cout << "LED port(" << std::showbase << std::hex << unsigned(port) << "): ";

    std::cout << (is_on ? "is on" : "is off") << std::endl;
  }

private:
  mutable bool is_on;

  const std::uint8_t port;
  const std::uint8_t bval;
};

class led_pwm // No base class.
{
public:
  led_pwm(const pwm* p) : is_on (false),
                          my_pwm( p) { }

  void toggle() const // Not virtual.
  {
    // Toggle the LED PWM in the PC simulation.
    is_on = (!is_on);

    // Show the PC simulated pwm LED.
    std::cout << "LED pwm(" << std::dec << unsigned(my_pwm->get_channel()) << "): ";

    std::cout << (is_on ? "is on" : "is off") << std::endl;
  }

private:
  mutable bool is_on;
  const pwm* my_pwm;
};

template<typename led_type>
void led_toggler(led_type& led)
{
  // Toggle with static polymorphism.
  led.toggle();
}

namespace
{
  // Two simulated port LEDs.
  led_port led0 { 0x12U, 1U };
  led_port led1 { 0x34U, 2U };

  // Two simulated PWMs.
  pwm pwm0 { 0U };
  pwm pwm1 { 1U };

  // Two simulated pwm LEDs.
  led_pwm led2 { &pwm0 };
  led_pwm led3 { &pwm1 };
}

void toggle_all_leds()
{
  led_toggler(led0); // Uses led_port::toggle().
  led_toggler(led1); // Uses led_port::toggle().

  led_toggler(led2); // Uses led_pwm::toggle().
  led_toggler(led3); // Uses led_pwm::toggle().
}

int main()
{
  for(;;)
  {
    toggle_all_leds();
  }
}
