///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <chrono>
#include <mcal_gpt.h>

extern mcal::gpt::value_type consistent_microsecond_tick();

// Implement std::chrono::high_resolution_clock::now()
// for the standard library high-resolution clock.
namespace std
{
  namespace chrono
  {
    high_resolution_clock::time_point high_resolution_clock::now()
    {
      // The source of the high-resolution clock is microseconds.
      typedef std::chrono::time_point<high_resolution_clock, microseconds> microseconds_type;

      // Obtain a time-point from the consistent tick in units of microseconds.
      const microseconds_type my_now(std::chrono::microseconds(::consistent_microsecond_tick()));

      // Return the corresponding duration in microseconds.
      return std::chrono::high_resolution_clock::time_point(my_now);
    }
  }
}

void operator delete(void*) { }

namespace std
{
  struct ios_base
  {
    struct Init { Init(); };
  };

  ios_base::Init::Init() { }
}

extern "C"
{
  void __cxa_pure_virtual() { }

  int __errno;

  void exit(int) __attribute__((noreturn));

  void exit(int)
  {
    while(1) { ; }
  }
}
