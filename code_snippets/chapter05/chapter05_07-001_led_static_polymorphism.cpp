///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_07-001_led_static_polymorphism.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>

class pwm final // A placeholder pwm class used for exemplary purposes.
{
public:
  explicit pwm(const std::uint8_t c) : channel(c) { }

  ~pwm() = default;

  auto get_channel() const noexcept -> std::uint8_t { return channel; }

private:
  pwm(const pwm&) = delete;
  pwm& operator=(const pwm&) = delete;

  const std::uint8_t channel;
};

class led_port // No base class.
{
public:
  explicit led_port(const std::uint8_t p, const std::uint8_t b)
    : port { p },
      bval { b }
  {
    static_cast<void>(bval);
  }

  auto toggle() const -> void // Not virtual.
  {
    // Toggle the LED port in the PC simulation.
    is_on = (!is_on);

    std::stringstream strm { };

    // Show the PC simulated port LED.
    strm << "LED port(" << std::showbase << std::hex << unsigned(port) << "): ";

    strm << (is_on ? "is on" : "is off");

    std::cout << strm.str() << std::endl;
  }

private:
  mutable bool is_on { };

  const std::uint8_t port;
  const std::uint8_t bval;
};

class led_pwm // No base class.
{
public:
  led_pwm(const pwm* p) : is_on { false },
                          my_pwm{ p } { }

  auto toggle() const -> void // Not virtual.
  {
    // Toggle the LED PWM in the PC simulation.
    is_on = (!is_on);

    std::stringstream strm { };

    // Show the PC simulated pwm LED.
    strm << "LED pwm(" << std::dec << unsigned(my_pwm->get_channel()) << "): ";

    strm << (is_on ? "is on" : "is off");

    std::cout << strm.str() << std::endl;
  }

private:
  mutable bool is_on;
  const pwm* my_pwm;
};

template<typename led_type>
auto led_toggler(const led_type& led) -> void
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
