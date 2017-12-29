///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_NOEXCEPT_2017_11_06_H_
  #define UTIL_NOEXCEPT_2017_11_06_H_

  #if defined(_MSC_VER) && (_MSC_VER <= 1900)
    #define UTIL_NOEXCEPT throw()
  #else
    #define UTIL_NOEXCEPT noexcept
  #endif

#endif // UTIL_NOEXCEPT_2017_11_06_H_
