///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_ALIGNAS_2015_05_20_H_
  #define _UTIL_ALIGNAS_2015_05_20_H_

  #if defined(_MSC_VER)
    #define ALIGNAS(n)
  #else
    #define ALIGNAS(n) alignas(n)
  #endif

#endif // _UTIL_ALIGNAS_2015_05_20_H_
