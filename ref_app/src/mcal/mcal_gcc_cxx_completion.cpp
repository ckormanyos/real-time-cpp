///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <chrono>
#include <mcal_cpu.h>
#include <mcal_gpt.h>

// Implement std::chrono::high_resolution_clock::now()
// for the standard library high-resolution clock.
namespace std
{
  namespace chrono
  {
    high_resolution_clock::time_point high_resolution_clock::now()
    {
       // The source of the high-resolution clock is from microseconds.
       typedef std::chrono::time_point<high_resolution_clock, microseconds> from_type;

       // Get the consistent tick in units of microseconds.
       const auto microsecond_tick = consistent_microsecond_tick();

       // Now obtain a time-point in microseconds.
       auto from_micro = from_type(microseconds(microsecond_tick));

       // And return the corresponding duration in microseconds.
       return time_point_cast<duration>(from_micro);
/*
       // The source of the high-resolution clock is microseconds.
      typedef std::chrono::time_point<high_resolution_clock, microseconds> microseconds_type;

      // Obtain a time-point from the consistent tick in units of microseconds.
      microseconds_type my_now(std::chrono::microseconds(::consistent_microsecond_tick()));

      // Return the corresponding duration in microseconds.
      return std::chrono::high_resolution_clock::time_point(my_now);
*/
    }
  }
}

void operator delete(void*) { }

extern "C"
{
  void __cxa_pure_virtual();

  void __cxa_pure_virtual() { }

  int __errno;

  void exit(int) __attribute__((noreturn));

  void exit(int)
  {
    while(1) { mcal::cpu::nop(); }
  }
}
