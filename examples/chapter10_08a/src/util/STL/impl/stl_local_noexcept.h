///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef STL_LOCAL_NOEXCEPT_2017_08_16_H_
  #define STL_LOCAL_NOEXCEPT_2017_08_16_H_

  #if defined(_MSC_VER)
    #define STL_LOCAL_NOEXCEPT throw()
  #else
    #define STL_LOCAL_NOEXCEPT noexcept
  #endif

#endif // STL_LOCAL_NOEXCEPT_2017_08_16_H_
