///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstddef>

extern "C"
{
  // Patched functions.
  void        __cxa_pure_virtual  (void);
  char*       __cxa_demangle      (const char*, char*, size_t*, int*);

  void        __cxa_pure_virtual  (void)                              { }
  char*       __cxa_demangle      (const char*, char*, size_t*, int*) { return nullptr; }
}

extern "C"
{
  // Patched labels.
  void* __dso_handle;
}
