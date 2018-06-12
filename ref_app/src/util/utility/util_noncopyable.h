///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_NONCOPYABLE_2008_12_16_H_
  #define UTIL_NONCOPYABLE_2008_12_16_H_

  // Taken (with slight modification) from boost::noncopyable.

  namespace util
  {
    namespace my_noncopyable_namespace
    {
      class noncopyable
      {
      protected:
        noncopyable() = default;
        ~noncopyable() = default;

      private:
        // Emphasize: The following members are private.
        noncopyable(const noncopyable&) = delete;
        noncopyable& operator=(const noncopyable&) = delete;
      };
    }

    using noncopyable = my_noncopyable_namespace::noncopyable;
  }

#endif // UTIL_NONCOPYABLE_2008_12_16_H_
