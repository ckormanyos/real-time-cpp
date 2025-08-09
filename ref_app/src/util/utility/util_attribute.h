///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_ATTRIBUTE_2025_08_09_H
  #define UTIL_ATTRIBUTE_2025_08_09_H

  #if defined(ATTRIBUTE)
  #undef ATTRIBUTE
  #endif

  #if defined(_MSC_VER)
    #define ATTRIBUTE(...)
  #else
    #define ATTRIBUTE(...) __attribute__((__VA_ARGS__))
  #endif

#endif // UTIL_ATTRIBUTE_2025_08_09_H
