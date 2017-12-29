///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_LED_2010_09_14_H_
  #define _MCAL_LED_2010_09_14_H_

  #include <util/utility/util_noncopyable.h>

  namespace mcal
  {
    namespace led
    {
      class led final : private util::noncopyable
      {
      public:
        led() : is_on(false) { }

        void toggle() const;

      private:
        mutable bool is_on;
      };

      typedef led led_type;

      extern const led_type led0;
    }
  }

#endif // _MCAL_LED_2010_09_14_H_
