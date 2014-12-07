///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _XUTILS_IMPL_2010_02_23_H_
  #define _XUTILS_IMPL_2010_02_23_H_

  // Implement helper utilities for the partial STL.

  namespace xutils
  {
    struct xnothing
    {
      xnothing() { }
      xnothing(const xnothing&) { }
      ~xnothing() { }
      xnothing& operator=(const xnothing&) { return *this; }
    };

    inline bool operator==(const xnothing&, const xnothing&) { return true; }
    inline bool operator!=(const xnothing&, const xnothing&) { return false; }
    inline bool operator< (const xnothing&, const xnothing&) { return false; }
    inline bool operator<=(const xnothing&, const xnothing&) { return false; }
    inline bool operator> (const xnothing&, const xnothing&) { return false; }
    inline bool operator>=(const xnothing&, const xnothing&) { return false; }
  }

#endif // _XUTILS_IMPL_2010_02_23_H_
