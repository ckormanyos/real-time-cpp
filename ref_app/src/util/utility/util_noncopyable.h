///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _UTIL_NONCOPYABLE_2008_12_16_H_
  #define _UTIL_NONCOPYABLE_2008_12_16_H_

  // A non-copyable base class, taken from boost::noncopyable.

  namespace util
  {
    class noncopyable
    {
    protected:
      noncopyable() {}
      ~noncopyable() {}

   // Emphasize: The following members are private.
   private:
#if defined(_MSC_VER) //&& (_MSC_VER <= 1600)
      noncopyable(const noncopyable&);
      const noncopyable& operator=(const noncopyable&);
#else
      noncopyable(const noncopyable&) = delete;
      const noncopyable& operator=(const noncopyable&) = delete;
#endif
    };
  }

#endif // _UTIL_NONCOPYABLE_2008_12_16_H_
