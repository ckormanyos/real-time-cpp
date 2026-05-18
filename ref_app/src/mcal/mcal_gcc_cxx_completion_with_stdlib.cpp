///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstddef>

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
  // Patched functions.
  int         atexit              (void (*)());
  int         atexit              (void (*)())                        { return 0; }

  void        __cxa_pure_virtual  ();
  char*       __cxa_demangle      (const char*, char*, size_t*, int*);

  void        __cxa_pure_virtual  ()                                  { }
  char*       __cxa_demangle      (const char*, char*, size_t*, int*) { return nullptr; }
}

extern "C"
{
  // Patched labels.
  void* __dso_handle;
}
