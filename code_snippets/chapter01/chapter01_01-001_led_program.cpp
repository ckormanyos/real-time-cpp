///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter01_01-001_led_program.cpp

// The LED program (PC simulation).
// See also: https://godbolt.org/z/8zhTn98ba

#include <cstdint>
#include <iostream>

class led final
{
public:
  // The led class default constructor.
  constexpr led() = default;

  ~led() = default;

  auto toggle() const -> void
  {
    // Toggle the LED in the PC simulation.
    is_on = (!is_on);

    std::cout << (is_on ? "LED is on" : "LED is off") << std::endl;
  }

  constexpr led(const led&) = delete;
  constexpr led(led&&) noexcept = delete;

  constexpr auto operator=(const led&) -> led& = delete;
  constexpr auto operator=(led&&) noexcept -> led& = delete;

private:
  // Private member variables of the class.
  mutable bool is_on { };
};

namespace
{
  // Create led_b5 (simulated on a PC).
  const led led_b5;
}

auto main() -> int;

auto main() -> int
{
  // Toggle led_b5 in a loop 4 times.
  // (The version(s) for the embedded systems toggle in a forever-loop.)

  for(auto i = static_cast<unsigned>(UINT8_C(0)); i < static_cast<unsigned>(UINT8_C(4)); ++i)
  {
    led_b5.toggle();
  }
}
