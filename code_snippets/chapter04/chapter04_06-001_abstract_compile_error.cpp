///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter04_06-001_abstract_compile_error.cpp

#include <algorithm>
#include <cstdint>
#include <iostream>

class led_base
{
public:
  // Virtual default destructor.
  virtual ~led_base() = default;

  // Pure virtual.
  virtual auto toggle() noexcept -> void = 0;

  // Interface for querying the LED state.
  auto state_is_on() const noexcept
    -> bool { return is_on; }

protected:
  // A protected default constructor.
  led_base() = default;

  auto set_is_on(const bool val) noexcept
    -> void { is_on = val; }

private:
  bool is_on { };

  // Private non-implemented copy constructor.
  led_base(const led_base&) = delete;

  // Private non-implemented assignment operator.
  auto operator=(const led_base&)
    -> const led_base& = delete;
};

class led_no_toggle : public led_base
{
public:
  led_no_toggle()
  {
    // ...
  }

  // Does not have a toggle function.
  // Uncomment the toggle() function
  // to remove the compile error.

  #if 0
  auto toggle() noexcept -> void override
  {
    // Toggle the is_on indication flag.
    set_is_on(!led_base::state_is_on());

    // Show the PC simulated port LED.
    std::cout << "LED no toggle: ";

    std::cout << (led_base::state_is_on() ? "is on" : "is off") << std::endl;
  }
  #endif
};

namespace
{
  led_no_toggle led_no { }; // Compilation error!
}

auto do_something() -> void;

auto do_something() -> void
{
  led_no.toggle();
  led_no.toggle();
  led_no.toggle();
  led_no.toggle();
}

auto main() -> int;

auto main() -> int
{
  do_something();
}
