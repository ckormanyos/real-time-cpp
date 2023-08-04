///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter04_04-002_dynamic_polymorphism_cast.cpp

#include <algorithm>
#include <cstdint>
#include <iostream>

class led_base
{
public:
  virtual void toggle() = 0; // Pure abstract.
  virtual ~led_base() { }    // Virtual destructor.

  // Interface for querying the LED state.
  bool state_is_on() const { return is_on; }

protected:
  bool is_on;

  // A protected default constructor.
  led_base() : is_on(false) { }

private:
  // Private non-implemented copy constructor.
  led_base(const led_base&) = delete;

  // Private non-implemented copy assignment operator.
  const led_base& operator=(const led_base&) = delete;
};

class led_port : public led_base
{
public:
  typedef std::uint8_t port_type;
  typedef std::uint8_t bval_type;

  led_port(const port_type p, const bval_type b)
    : port(p),
      bval(b) { static_cast<void>(bval); }

  virtual ~led_port() { }

  virtual void toggle()
  {
    // Toggle the is_on indication flag.
    is_on = (!is_on);

    // Show the PC simulated port LED.
    std::cout << "LED port(" << std::showbase << std::hex << unsigned(port) << "): ";

    std::cout << (is_on ? "is on" : "is off") << std::endl;
  }

private:
  const port_type port;
  const bval_type bval;
};

class pwm final // A placeholder pwm class used for exemplary purposes.
{
public:
  explicit pwm(const std::uint8_t c)
    : channel   (c),
      duty_cycle(0U) { }

  ~pwm() = default;

  void set_duty(const std::uint8_t duty)
  {
    // Limit the duty cycle to 0...100.
    duty_cycle = (std::min)(std::uint8_t(duty),
                            std::uint8_t(100U));

    // Set the duty cycle in the PWM hardware.
    // ...
  }

  std::uint8_t get_duty() const
  {
    return duty_cycle;
  }

  std::uint8_t get_channel() const { return channel; }

private:
  std::uint8_t channel;
  std::uint8_t duty_cycle;
};

class led_pwm : public led_base
{
public:
  explicit led_pwm(pwm* p) : my_pwm(p) { }

  virtual ~led_pwm() = default;

  virtual void toggle()
  {
    // Toggle the duty cycle.
    const  std::uint8_t duty =
      (my_pwm->get_duty() > 0U) ? 0U : 100U;

    my_pwm->set_duty(duty);

    // Toggle the LED with the PWM signal.
    is_on = (my_pwm->get_duty() > 0U);

    // Show the PC simulated pwm LED.
    std::cout << "LED pwm(" << std::dec << unsigned(my_pwm->get_channel()) << "): ";

    std::cout << (is_on ? "is on" : "is off") << std::endl;
  }

  // This LED class also supports dimming.
  void dimming(const std::uint8_t duty)
  {
    my_pwm->set_duty(duty);

    is_on = (duty != 0U);
  }

private:
  pwm* my_pwm;
};

namespace
{
  // Two simulated port LEDs.
  led_port led0 { 0x12, 1U };
  led_port led1 { 0x34, 2U };

  // Two simulated PWMs.
  pwm pwm0 { 0U };
  pwm pwm1 { 1U };

  // Two simulated pwm LEDs.
  led_pwm led2 { &pwm0 };
  led_pwm led3 { &pwm1 };
}

void led_toggler(led_base* led)
{
  // Use dynamic polymorphism to toggle
  // a base class pointer.
  led->toggle();
}

void do_something()
{
  // Toggle led0-led3.
  led_toggler(static_cast<led_base*>(&led0));
  led_toggler(static_cast<led_base*>(&led1));
  led_toggler(static_cast<led_base*>(&led2));
  led_toggler(static_cast<led_base*>(&led3));
}

int main()
{
  for(;;)
  {
    do_something();
  }
}
