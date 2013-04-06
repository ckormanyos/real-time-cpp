///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_LANGUAGE_2006_04_10_H_
  #define _UTIL_LANGUAGE_2006_04_10_H_

  #include <util/utility/util_compiler.h>

  #if defined(__GNUC__) && (GCC_VERSION < 40600)
    #include <util/utility/util_null_ptr_workaround.h>
  #endif

#endif // _UTIL_LANGUAGE_2006_04_10_H_
