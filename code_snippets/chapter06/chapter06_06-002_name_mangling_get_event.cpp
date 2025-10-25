///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_06-002_name_mangling_get_event.cpp

#include <cstdint>
#include <iostream>

// This program basically has no real functionality of an OS.
// It is merely used to illustrate name (de)-mangling.

// Using GCC on x86_64-linux-gnu.

// The example in Sect. 6.6 of the book uses the following commands:
// g++ -Wall -Wextra -pedantic -O2 -std=c++20 chapter06_06-002_name_mangling_get_event.cpp -c -o chapter06_06-002_name_mangling_get_event.o
// g++ -Wall -Wextra -pedantic -O2 -std=c++20 chapter06_06-002_name_mangling_get_event.o -Wl,-Map,chapter06_06-002_name_mangling_get_event.map -o chapter06_06-002_name_mangling_get_event.elf
// nm --numeric-sort --print-size chapter06_06-002_name_mangling_get_event.elf
// nm --numeric-sort --print-size chapter06_06-002_name_mangling_get_event.elf | c++filt
// c++filt _ZN2os9get_eventENS_12task_id_typeE

namespace os
{
  enum task_id_type : std::uint_fast16_t
  {
    id0, id1, id2
  };

  using event_type = std::uint_fast16_t;

  // Simulate an event functionality for the PC.
  event_type simulated_event;

  auto get_event(const task_id_type id) -> event_type;

  auto set_event(const event_type evt) -> void;
  auto clr_event(const event_type evt) -> void;

  auto set_event(const event_type evt) -> void
  {
    simulated_event |= (1U << evt);
  }

  auto clr_event(const event_type evt) -> void
  {
    simulated_event &= event_type(~event_type(1U << evt));
  }
}

// We will examine the mangled name of this subroutine.
auto os::get_event(const os::task_id_type) -> os::event_type
{
  // Simulate an event functionality for the PC.
  return os::simulated_event;
}

auto do_something() -> void;

auto do_something() -> void
{
  os::set_event(os::id1);

  std::cout << "Result of os::simulated_event after set_event(): " << os::get_event(os::id1) << std::endl;

  os::clr_event(os::id1);

  std::cout << "Result of os::simulated_event after clr_event(): " << os::get_event(os::id1) << std::endl;
}

auto main() -> int;

auto main() -> int
{
  for(std::uint_fast8_t i = 0U; i < 10U; ++i)
  {
    do_something();
  }
}
