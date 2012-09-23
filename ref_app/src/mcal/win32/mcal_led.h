#ifndef _MCAL_LED_2010_09_14_H_
  #define _MCAL_LED_2010_09_14_H_

  #include <iostream>
  #include <util/utility/util_type.h>
  #include <util/utility/util_noncopyable.h>
  #include <mcal_reg_access.h>

  namespace mcal
  {
    namespace led
    {
      template<typename addr_type = unsigned,
               typename bval_type = unsigned,
               const addr_type port = 0U,
               const bval_type bval = 0U>
      class led_type : private util::noncopyable
      {
      public:
        led_type() : is_on(false) { }

        void toggle() const
        {
          is_on = !is_on;
          std::cout << (is_on ? "LED is on" : "LED is off") << std::endl;
        }

      private:
        mutable bool is_on;
      };

      extern const led_type<> led0;
    }
  }

#endif // _MCAL_LED_2010_09_14_H_
