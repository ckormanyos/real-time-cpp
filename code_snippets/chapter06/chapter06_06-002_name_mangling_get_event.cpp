///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter06_06-002_name_mangling_get_event.cpp

#include <cstdint>
#include <iostream>

// This program basically has no real functionality of an OS.
// It is merely used to illustrate name mangling.

// Using GCC 8.1.0 with target --target=x86_64-w64-mingw32.

// The example in Sect. 6.6 of the book uses the following commands:
// g++ -Wall -Wextra -pedantic -O2 -std=c++11 chapter06_06-002_name_mangling_get_event.cpp -c -o chapter06_06-002_name_mangling_get_event.o
// g++ -Wall -Wextra -pedantic -O2 -std=c++11 chapter06_06-002_name_mangling_get_event.o -Wl,-Map,chapter06_06-002_name_mangling_get_event.map -o chapter06_06-002_name_mangling_get_event.elf
// nm --numeric-sort --print-size chapter06_06-002_name_mangling_get_event.elf > chapter06_06-002_name_mangling_get_event.txt
// c++filt _ZN2os9get_eventENS_12task_id_typeE

namespace os
{
  typedef enum task_id_type
  {
    id0, id1, id2
  }
  task_id_type;

  using event_type   = std::uint_fast16_t;

  // Simulate an event functionality for the PC.
  event_type simulated_event;

  event_type get_event(const task_id_type id);

  void set_event(const event_type evt)
  {
    simulated_event |= (1U << evt);
  }

  void clr_event(const event_type evt)
  {
    simulated_event &= event_type(~event_type(1U << evt));
  }
}

// We will examine the mangled name of this subroutine.
os::event_type os::get_event(const os::task_id_type)
{
  // Simulate an event functionality for the PC.
  return os::simulated_event;
}

void do_something()
{
  os::set_event(os::id1);

  std::cout << "Result of os::simulated_event after set_event(): " << os::get_event(os::id1) << std::endl;

  os::clr_event(os::id1);

  std::cout << "Result of os::simulated_event after clr_event(): " << os::get_event(os::id1) << std::endl;
}

int main()
{
  for(std::uint_fast8_t i = 0U; i < 10U; ++i)
  {
    do_something();
  }
}
