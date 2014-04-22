/////////////////////////////////////////////////////// 
//  Copyright 2013 Stephan Hage.
//  Copyright 2013 Christopher Kormanyos.
//  Distributed under the Boost 
//  Software License, Version 1.0. 
//  (See accompanying file LICENSE_1_0.txt 
//  or copy at http://www.boost.org/LICENSE_1_0.txt ) 
//

#ifndef _CSTDBOOL_IMPL_2012_12_10_H_
  #define _CSTDBOOL_IMPL_2012_12_10_H_

  #include <stdbool.h>

  #if !defined(__bool_true_false_are_defined)
    #define __bool_true_false_are_defined 1
  #endif

  namespace std
  {
    using ::bool;
  }

#endif // _CSTDBOOL_IMPL_2012_12_10_H_
