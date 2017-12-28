///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_DEVICE_LED_BASE_2017_11_05_H_
  #define UTIL_DEVICE_LED_BASE_2017_11_05_H_

  #include <cstdint>

  #include <util/utility/util_noncopyable.h>

  namespace util
  {
    namespace device
    {
      class led_base : private util::noncopyable
      {
      public:
        virtual ~led_base() { }

        void on () { my_on (); is_on = true; }
        void off() { my_off(); is_on = false; }

        void toggle() { (is_on ? off() : on()); }

      protected:
        led_base() : is_on(false) { }

      private:
        bool is_on;

        virtual void my_on () = 0;
        virtual void my_off() = 0;
      };
    }
  }

#endif // UTIL_DEVICE_LED_BASE_2017_11_05_H_
