///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef STL_LOCAL_CONSTEXPR_2014_12_04_H_
  #define STL_LOCAL_CONSTEXPR_2014_12_04_H_

  #if (defined(__cplusplus) && (__cplusplus >= 201402L))
    #if defined(__AVR__) && (!defined(__GNUC__) || (defined(__GNUC__) && (__GNUC__ > 7)))
    #define STL_LOCAL_CONSTEXPR_ALGORITHMS constexpr
    #elif (defined(__cpp_lib_constexpr_algorithms) && (__cpp_lib_constexpr_algorithms>=201806))
      #if defined(__clang__)
        #if (__clang_major__ > 9)
        #define STL_LOCAL_CONSTEXPR_ALGORITHMS constexpr
        #else
        #define STL_LOCAL_CONSTEXPR_ALGORITHMS
        #endif
      #else
      #define STL_LOCAL_CONSTEXPR_ALGORITHMS constexpr
      #endif
    #else
    #define STL_LOCAL_CONSTEXPR_ALGORITHMS
    #endif
  #else
    #define STL_LOCAL_CONSTEXPR_ALGORITHMS
  #endif

  #if defined(__GNUC__) || defined(__IAR_SYSTEMS_ICC__)
    #define STL_LOCAL_CONSTEXPR constexpr
  #else
    #define STL_LOCAL_CONSTEXPR const
  #endif

#endif // STL_LOCAL_CONSTEXPR_2014_12_04_H_
