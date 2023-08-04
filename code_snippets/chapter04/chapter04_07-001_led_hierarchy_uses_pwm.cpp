///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter04_07-001_led_hierarchy_uses_pwm.cpp

#include <algorithm>
#include <cstdint>
#include <iostream>

class led_base
{
public:
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

  void toggle()
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
  explicit led_pwm() { }

  virtual ~led_pwm() = default;

  // This led_pwm uses the use-a relationship
  // to toggle.
  void toggle(pwm* p)
  {
    // Toggle the duty cycle.
    const  std::uint8_t duty =
      (p->get_duty() > 0U) ? 0U : 100U;

    p->set_duty(duty);

    // Toggle the LED with the PWM signal.
    is_on = (p->get_duty() > 0U);

    // Show the PC simulated pwm LED.
    std::cout << "LED pwm(" << std::dec << unsigned(p->get_channel()) << "): ";

    std::cout << (is_on ? "is on" : "is off") << std::endl;
  }

  // This LED class also supports dimming.
  void dimming(const std::uint8_t duty, pwm* p)
  {
    p->set_duty(duty);

    is_on = (duty != 0U);
  }
};

namespace
{
  // Two simulated port LEDs.
  led_port led0 { 0x12, 1U };
  led_port led1 { 0x34, 2U };

  // Two simulated PWMs.
  pwm pwm0 { 0 };
  pwm pwm1 { 1 };

  // Two simulated pwm LEDs.
  led_pwm led2;
  led_pwm led3;
}

void do_something()
{
  // Toggle led0-led3.
  led0.toggle();
  led1.toggle();
  led2.toggle(&pwm0);
  led3.toggle(&pwm1);
}

int main()
{
  for(;;)
  {
    do_something();
  }
}
