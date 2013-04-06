#ifndef _MCAL_LED_2010_09_14_H_
  #define _MCAL_LED_2010_09_14_H_

  #include <util/utility/util_type.h>
  #include <util/utility/util_noncopyable.h>
  #include <mcal_reg_access.h>

  namespace mcal
  {
    namespace led
    {
      template<typename addr_type,
               typename reg_type,
               const addr_type port,
               const reg_type bpos>
      class led_type : private util::noncopyable
      {
      public:
        led_type()
        {
          // The ports have already been initialized.
          // TBD: Implement the proper LED encapsulation.
        }

        void toggle() const
        {
          // Toggle the LED.
          mcal::reg::access<addr_type, reg_type, port, bpos>::bit_not();
        }
      };

      extern const led_type<std::uint32_t,
                            std::uint32_t,
                            mcal::reg::gpioc_odr,
                            8U> led0;
/*
      extern const led_type<std::uint32_t,
                            std::uint32_t,
                            mcal::reg::gpioa_odr,
                            2U> led0;
*/
    }
  }

#endif // _MCAL_LED_2010_09_14_H_
