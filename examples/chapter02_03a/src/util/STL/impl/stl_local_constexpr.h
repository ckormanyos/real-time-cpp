///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef STL_LOCAL_CONSTEXPR_2014_12_04_H_
  #define STL_LOCAL_CONSTEXPR_2014_12_04_H_

  #if defined(__GNUC__)
    #define STL_LOCAL_CONSTEXPR constexpr
  #else
    #define STL_LOCAL_CONSTEXPR const
  #endif

#endif // STL_LOCAL_CONSTEXPR_2014_12_04_H_
