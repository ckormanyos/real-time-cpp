///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <chrono>
#include <cstddef>
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
       // The source of the high-resolution clock is microseconds.
       typedef std::chrono::time_point<high_resolution_clock, std::chrono::microseconds> microsecond_time_point_type;

       // Get the consistent system tick (having microsecond resolution).
       const mcal::gpt::value_type microsecond_tick = mcal::gpt::secure::get_time_elapsed();

       // Now obtain a time-point with microsecond resolution.
       const microsecond_time_point_type time_point_in_microseconds = microsecond_time_point_type(std::chrono::microseconds(microsecond_tick));

       // And return the corresponding duration with microsecond resolution.
       return time_point_cast<duration>(time_point_in_microseconds);
    }
  }
}

void* operator new(std::size_t size);
void  operator delete(void*) noexcept;

void* operator new(std::size_t size)
{
  volatile std::uint8_t  buffer[16U];
  volatile std::uint8_t* get_ptr = &buffer[0U];

  // Get the newly allocated pointer.
  volatile std::uint8_t* p = get_ptr;

  // Does this allocation overflow the top of the buffer?
  const bool is_overflow = ((get_ptr + size) >= (buffer + sizeof(buffer)));

  // Increment the pointer for next time.
  // But only do this if the buffer does *not* overflow.
  if(is_overflow)
  {
    // TBD: Is any sensible error reaction possible here?
  }
  else
  {
    get_ptr += size;
  }

  return static_cast<void*>(const_cast<std::uint8_t*>(p));
}

void operator delete(void*) { }

extern "C"
{
  // Declarations of patched functions.

  // Provide user-supplied copies of certain functions declared in <stdlib.h> and <cstdlib>.
  // Provide also user-supplied copies of certain empirically found library functions.

  typedef struct struct_unwind_exception_type { unsigned dummy; } _Unwind_Exception;

  void        abort               ()               noexcept __attribute__((noreturn));
  int         atexit              (void (*)(void)) noexcept;
  int         at_quick_exit       (void (*)(void)) noexcept;
  void        _Exit               (int)            noexcept __attribute__((noreturn));
  void        exit                (int)                     __attribute__((noreturn));
  void        quick_exit          (int)                     __attribute__((noreturn));
  int         _exit               (int);
  int         _isatty             (int);
  int         _lseek              (int, int, int);
  int         _open               (const char*, int, int);
  int         _close              (int);
  int         _read               (int, char*, int);
  int         _write              (int, char*, int);
  int         _fstat              (int, void*);
  const void* _sbrk               (int);
  int         _getpid             ();
  int         _kill               (int, int);
  void        __cxa_pure_virtual  ();
  char*       __cxa_demangle      (const char*, char*, size_t*, int*);
  void        __cxa_call_terminate(_Unwind_Exception*);

  // Implementations of patched functions.

  void        abort               ()                                  { for(;;) { mcal::cpu::nop(); } }
  int         atexit              (void (*)(void)) noexcept           { return 0; }
  int         at_quick_exit       (void (*)(void)) noexcept           { return 0; }
  void        _Exit               (int)                               { for(;;) { mcal::cpu::nop(); } }
  void        exit                (int)                               { for(;;) { mcal::cpu::nop(); } }
  void        quick_exit          (int)                               { _Exit(0); }
  int         _exit               (int)                               { return -1; }
  int         _isatty             (int)                               { return  1; }
  int         _lseek              (int, int, int)                     { return  0; }
  int         _open               (const char*, int, int)             { return -1; }
  int         _close              (int)                               { return -1; }
  int         _read               (int, char*, int)                   { return  0; }
  int         _write              (int, char*, int)                   { return  0; }
  int         _fstat              (int, void*)                        { return  0; }
  const void* _sbrk               (int)                               { return  nullptr; }
  int         _getpid             ()                                  { return  1; }
  int         _kill               (int, int)                          { return -1; }
  void        __cxa_pure_virtual  ()                                  { }
  char*       __cxa_demangle      (const char*, char*, size_t*, int*) { return nullptr; }
  void        __cxa_call_terminate(_Unwind_Exception*)                { }

  // Provide some patched data.
  char*         __env[1] = { nullptr };
  char**        environ  = __env;
  int           __errno;
  unsigned char __fdlib_version;
}
