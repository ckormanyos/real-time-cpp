///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _CTIME_IMPL_2012_06_01_H_
  #define _CTIME_IMPL_2012_06_01_H_

  // Implement std::time_t of <ctime> for compilers that do not yet support it.

  #include <time.h>

  namespace std
  {
    using ::time_t;
  }

#endif // _CTIME_IMPL_2012_06_01_H_
