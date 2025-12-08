///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_COMMUNICATION_2012_05_31_H
  #define UTIL_COMMUNICATION_2012_05_31_H

  #include <cstdint>

  namespace util
  {
    class communication_base
    {
    public:
      using buffer_value_type = std::uint8_t;

      using send_iterator_type = const buffer_value_type*;
    };
  }

#endif // UTIL_COMMUNICATION_2012_05_31_H
