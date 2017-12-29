///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_NOTHING_2010_06_13_H_
  #define _UTIL_NOTHING_2010_06_13_H_

  namespace util
  {
    // This is a structure that is used to represent *nothing*.
    struct nothing final
    {
      nothing() { }
      nothing(const nothing&) { }
      ~nothing() { }
      nothing& operator=(const nothing&) { return *this; }
    };

    inline bool operator==(const nothing&, const nothing&) { return true; }
    inline bool operator!=(const nothing&, const nothing&) { return false; }
    inline bool operator< (const nothing&, const nothing&) { return false; }
    inline bool operator<=(const nothing&, const nothing&) { return false; }
    inline bool operator> (const nothing&, const nothing&) { return false; }
    inline bool operator>=(const nothing&, const nothing&) { return false; }
  }

#endif // _UTIL_NOTHING_2010_06_13_H_
