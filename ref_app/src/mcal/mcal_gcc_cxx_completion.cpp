///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
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
       typedef std::chrono::time_point<high_resolution_clock, std::chrono::microseconds> microsecond_time_point_type;

       // Get the consistent system tick with microsecond resolution.
       const mcal::gpt::value_type microsecond_tick = mcal::gpt::secure::get_time_elapsed();

       // Now obtain a time-point with microsecond resolution.
       const microsecond_time_point_type time_point_in_microseconds = microsecond_time_point_type(std::chrono::microseconds(microsecond_tick));

       // And return the corresponding duration with microsecond resolution.
       return time_point_cast<duration>(time_point_in_microseconds);
    }
  }
}

void operator delete(void*) noexcept;

void operator delete(void*) { }

extern "C"
{
  int __errno;

  // Provide a user-supplied copy of __cxa_pure_virtual().
  void __cxa_pure_virtual();

  void __cxa_pure_virtual() { }

  // Provide user-supplied copies of certain functions declared in <stdlib.h> and <cstdlib>.
  void abort             ()               noexcept __attribute__((noreturn));
  int  atexit            (void (*)(void)) noexcept;
  int  at_quick_exit     (void (*)(void)) noexcept;
  void _Exit             (int)            noexcept __attribute__((noreturn));
  void exit              (int)                     __attribute__((noreturn));
  void quick_exit        (int)                     __attribute__((noreturn));

  void abort() { for(;;) { mcal::cpu::nop(); } }

  int atexit       (void (*)(void)) noexcept { return 0; }
  int at_quick_exit(void (*)(void)) noexcept { return 0; }

  void _Exit     (int) { for(;;) { mcal::cpu::nop(); } }
  void exit      (int) { for(;;) { mcal::cpu::nop(); } }
  void quick_exit(int) { _Exit(0); }

  // Patch a floating-point library version identification.
  unsigned char __fdlib_version;
}
