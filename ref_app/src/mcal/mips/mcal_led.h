#ifndef _MCAL_LED_2010_09_14_H_
  #define _MCAL_LED_2010_09_14_H_

  #include <util/utility/util_noncopyable.h>

  namespace mcal
  {
    namespace led
    {
      class led_type : private util::noncopyable
      {
      public:
        led_type() : is_on(false) { }

        void toggle() const;

      private:
        mutable bool is_on;
      };

      extern const led_type led0;
    }
  }

#endif // _MCAL_LED_2010_09_14_H_
