///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter04_01-001_led_hierarchy.cpp
// See also https://godbolt.org/z/7MzKGEevh

#include <algorithm>
#include <cstdint>
#include <iostream>

class led_base
{
public:
  virtual void toggle() = 0;     // Pure abstract.
  virtual ~led_base() = default; // Virtual destructor.

  // Interface for querying the LED state.
  constexpr auto state_is_on() const noexcept -> bool { return is_on; }

  // Non-implemented (deleted) copy constructors.
  led_base(const led_base&) = delete;
  led_base(led_base&&) noexcept = delete;

  // Non-implemented (deleted) assignment operators.
  constexpr auto operator=(const led_base&) -> led_base& = delete;
  constexpr auto operator=(led_base&&) noexcept -> led_base& = delete;

protected:
  bool is_on { };

  // A protected default constructor.
  constexpr led_base() = default;
};

class led_port : public led_base
{
public:
  using port_type = std::uint8_t;
  using bval_type = std::uint8_t;

  explicit constexpr led_port(const port_type p,
                              const bval_type b = static_cast<bval_type>(UINT8_C(0)))
    : port(p),
      bval(b) { static_cast<void>(bval); }

  ~led_port() override = default;

  auto toggle() -> void override
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

  constexpr auto get_channel() const noexcept -> std::uint8_t { return channel; }

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
    const auto duty =
      static_cast<std::uint8_t>
      (
        (my_pwm->get_duty() > static_cast<std::uint8_t>(UINT8_C(0)))
          ? static_cast<std::uint8_t>(UINT8_C(0))
          : static_cast<std::uint8_t>(UINT8_C(100))
      );

    my_pwm->set_duty(duty);

    // Toggle the LED with the PWM signal.
    is_on = (my_pwm->get_duty() > static_cast<std::uint8_t>(UINT8_C(0)));

    // Show the PC simulated pwm LED.
    std::cout << "LED pwm(" << std::dec << static_cast<unsigned>(my_pwm->get_channel()) << "): ";

    std::cout << (is_on ? "is on" : "is off") << std::endl;
  }

  // This LED class also supports dimming.
  auto dimming(const std::uint8_t duty) -> void
  {
    my_pwm->set_duty(duty);

    is_on = (duty != static_cast<std::uint8_t>(UINT8_C(0)));
  }

private:
  pwm* my_pwm { nullptr };
};

namespace
{
  // Two simulated port LEDs.
  led_port led0
  {
    static_cast<led_port::port_type>(UINT8_C(0x12)),
    static_cast<led_port::bval_type>(UINT8_C(1))
  };

  led_port led1
  {
    static_cast<led_port::port_type>(UINT8_C(0x34)),
    static_cast<led_port::bval_type>(UINT8_C(2))
  };

  // Two simulated PWMs.
  pwm pwm0 { static_cast<std::uint8_t>(UINT8_C(0)) };
  pwm pwm1 { static_cast<std::uint8_t>(UINT8_C(1)) };

  // Two simulated pwm LEDs.
  led_pwm led2(&pwm0);
  led_pwm led3(&pwm1);
}

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
  // Toggle all 4 LEDs in a loop 4 times times.
  // (The version(s) for the embedded systems toggle in a forever-loop.)

  for(auto i = static_cast<unsigned>(UINT8_C(0)); i < static_cast<unsigned>(UINT8_C(4)); ++i)
  {
    do_something();
  }
}
