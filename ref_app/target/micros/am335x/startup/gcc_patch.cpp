///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

extern "C" void __cxa_pure_virtual();

void __cxa_pure_virtual() { }

void operator delete(void*) { }

int __errno;

extern "C" void exit(int) __attribute__((noreturn));

void exit(int) { while(1) { ; } }

namespace std
{
  struct ios_base
  {
    struct Init { Init(); };
  };

  ios_base::Init::Init() { }
}
