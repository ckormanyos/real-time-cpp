///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
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
  // Virtual default destructor.
  virtual ~led_base() = default;

  // Pure virtual.
  virtual auto toggle() -> void = 0;

  // Interface for querying the LED state.
  auto state_is_on() const -> bool { return is_on; }

protected:
  // A protected default constructor.
  led_base() = default;

  auto set_is_on(const bool val) -> void { is_on = val; }

private:
  bool is_on { };

  // Private non-implemented copy constructor.
  led_base(const led_base&) = delete;

  // Private non-implemented assignment operator.
  auto operator=(const led_base&)
    -> const led_base& = delete;
};

class led_port : public led_base
{
public:
  using port_type = std::uintptr_t;
  using bval_type = std::uintptr_t;

  explicit led_port(const port_type p,
                    const bval_type b) : port(p),
                                         bval(b)
  {
    // ...
  }

  ~led_port() override = default;

  auto toggle() -> void override
  {
    // Toggle the LED.
    *reinterpret_cast<volatile bval_type*>(port)
      ^= bval;

    // Toggle the is_on indication flag.
    const bool val_on
      { (!led_base::state_is_on()) };

    led_base::set_is_on(val_on);
  }

private:
  const port_type port;
  const bval_type bval;
};

class pwm final // A placeholder pwm class used for exemplary purposes.
{
public:
  explicit constexpr pwm(const std::uint8_t c)
    : channel   (c),
      duty_cycle(static_cast<std::uint8_t>(UINT8_C(0))) { }

  constexpr auto set_duty(const std::uint8_t duty) -> void
  {
    // Limit the duty cycle to 0...100.
    duty_cycle = (std::min)(static_cast<std::uint8_t>(duty),
                            static_cast<std::uint8_t>(UINT8_C(100)));

    // Set the duty cycle in the PWM hardware.
    // ...
  }

  constexpr auto get_duty() const -> std::uint8_t
  {
    return duty_cycle;
  }

  constexpr auto get_channel() const -> std::uint8_t { return channel; }

private:
  std::uint8_t channel;
  std::uint8_t duty_cycle;
};

class led_pwm : public led_base
{
public:
  explicit led_pwm(pwm* p) : my_pwm(p) { }

  ~led_pwm() override = default;

  auto toggle() -> void override
  {
    // Toggle the duty cycle.
    const  std::uint8_t duty =
      (my_pwm->get_duty() > 0U) ? 0U : 100U;

    my_pwm->set_duty(duty);

    // Toggle the LED with the PWM signal.
    led_base::set_is_on(my_pwm->get_duty() > 0U);

    // Show the PC simulated pwm LED.
    std::cout << "LED pwm(" << unsigned(my_pwm->get_channel()) << "): ";

    std::cout << (led_base::state_is_on() ? "is on" : "is off") << std::endl;
  }

  // This LED class also supports dimming.
  auto dimming(const std::uint8_t duty) -> void
  {
    my_pwm->set_duty(duty);
    led_base::set_is_on(duty != 0U);
  }

private:
  pwm* my_pwm { };
};

namespace mcal
{
  namespace reg
  {
    // Simulate the transmit and receive hardware buffers on the PC.
    std::uint8_t dummy_register_port0 { };
    std::uint8_t dummy_register_port1 { };
  }
}

namespace
{
  // Two simulated port LEDs.
  led_port led0 { reinterpret_cast<std::uintptr_t>(&mcal::reg::dummy_register_port0), 1U };
  led_port led1 { reinterpret_cast<std::uintptr_t>(&mcal::reg::dummy_register_port1), 2U };

  // Two simulated PWMs.
  pwm pwm0 { 0 };
  pwm pwm1 { 1 };

  // Two simulated pwm LEDs.
  led_pwm led2 { &pwm0 };
  led_pwm led3 { &pwm1 };
}

auto do_something() -> void;

auto do_something() -> void
{
  // Toggle led0-led3.
  led0.toggle();
  led1.toggle();
  led2.toggle();
  led3.toggle();
}

auto main() -> int;

auto main() -> int
{
  do_something();
  do_something();
  do_something();
  do_something();
}
