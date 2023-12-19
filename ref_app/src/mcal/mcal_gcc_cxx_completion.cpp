///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <chrono>
#include <cstddef>
#include <mcal_cpu.h>
#include <mcal_gpt.h>

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#endif

// Implement std::chrono::high_resolution_clock::now()
// for the standard library's high-resolution clock.
namespace std
{
  namespace chrono
  {
    high_resolution_clock::time_point high_resolution_clock::now() noexcept
    {
       // The source of the high-resolution clock is microseconds.
       using microsecond_time_point_type =
         std::chrono::time_point<high_resolution_clock,
                                 std::chrono::microseconds>;

       // Get the consistent system tick (having microsecond resolution).
       const mcal::gpt::value_type microsecond_tick =
         mcal::gpt::secure::get_time_elapsed();

       // Obtain a time-point with microsecond resolution.
       const auto time_point_in_microseconds =
         microsecond_time_point_type(std::chrono::microseconds(microsecond_tick));

       // And return the corresponding duration with microsecond resolution.
       return time_point_cast<duration>(time_point_in_microseconds);
    }
  }
}

void* operator new(std::size_t size) noexcept
{
  // This is a naive and not completely functional
  // implementation of operator new(). In particular, there is
  // no sensible momory management or reaction to buffer overflow.
  volatile static std::uint8_t  buffer[8U];
  volatile static std::uint8_t* get_ptr = buffer;

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

void operator delete(void*)              noexcept { }
#if (defined(__GNUC__) && (__GNUC__ >= 12))
#else
void operator delete(void*, void*)       noexcept { }
#endif
#if(__cplusplus >= 201400L)
void operator delete(void*, std::size_t) noexcept { }
#endif

extern "C"
{
  // Declarations of patched functions.

  // Provide stubbed copies of certain functions declared in <stdlib.h> and <cstdlib>.
  // Also provide stubbed copies of certain empirically found library functions
  // and objects.

  void        abort               (void)                    __attribute__((noreturn));
  int         atexit              (void (*)(void));
  int         at_quick_exit       (void (*)(void));
  void        _Exit               (int)                     __attribute__((noreturn));
  void        exit                (int)                     __attribute__((noreturn));
  void        quick_exit          (int)                     __attribute__((noreturn));
  void        _exit               (int)                     __attribute__((noreturn));
  int         _isatty             (int);
  int         _lseek              (int, int, int);
  int         _open               (const char*, int, int);
  int         _close              (int);
  int         _read               (int, char*, int);
  int         _write              (int, char*, int);
  int         _fstat              (int, void*);
  const void* _sbrk               (int);
  int         _getpid             (void);
  int         _kill               (int, int);
  void        __cxa_pure_virtual  (void);
  char*       __cxa_demangle      (const char*, char*, size_t*, int*);

  // Implementations of patched functions.

  void        abort               (void)                              { for(;;) { mcal::cpu::nop(); } }
  int         atexit              (void (*)())                        { return 0; }
  int         at_quick_exit       (void (*)())                        { return 0; }
  void        _Exit               (int)                               { for(;;) { mcal::cpu::nop(); } }
  void        exit                (int)                               { for(;;) { mcal::cpu::nop(); } }
  void        quick_exit          (int)                               { _Exit(0); }
  void        _exit               (int)                               { for(;;) { mcal::cpu::nop(); } }
  int         _isatty             (int)                               { return  1; }
  int         _lseek              (int, int, int)                     { return  0; }
  int         _open               (const char*, int, int)             { return -1; }
  int         _close              (int)                               { return -1; }
  int         _read               (int, char*, int)                   { return  0; }
  int         _write              (int, char*, int)                   { return  0; }
  int         _fstat              (int, void*)                        { return  0; }
  const void* _sbrk               (int)                               { return  nullptr; }
  int         _getpid             (void)                              { return  1; }
  int         _kill               (int, int)                          { return -1; }
  void        __cxa_pure_virtual  (void)                              { }
  char*       __cxa_demangle      (const char*, char*, size_t*, int*) { return nullptr; }

  #if defined(environ)
  #undef environ
  #endif

  // Provide some patched data values.
  const char*  const __env[1U] = { nullptr };
  const char** const environ   = { nullptr };

  #if (defined(__GNUC__) && defined(__v850__))
  #else
  int* __errno(void);
  int* __errno(void) { static int __my_errno; return &__my_errno; }
  #endif

  std::uint8_t __fdlib_version;
}

namespace std
{
  [[noreturn]]
  void __throw_out_of_range_fmt(char const*, ...)  { for(;;) { ; } }
}

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
