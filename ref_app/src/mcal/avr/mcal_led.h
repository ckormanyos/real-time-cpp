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
          // Set the port pin value to low.
          port_pin_type::bit_clr();

          // Set the port pin direction to output.
          pdir_pin_type::bit_set();
        }

        void toggle() const
        {
          // Toggle the LED.
          port_pin_type::bit_not();
        }

      private:
        static constexpr addr_type pdir = port - 1U;

        typedef mcal::reg::access<addr_type, reg_type, port, bpos> port_pin_type;
        typedef mcal::reg::access<addr_type, reg_type, pdir, bpos> pdir_pin_type;
      };

      extern const led_type<std::uint8_t,
                            std::uint8_t,
                            mcal::reg::portb,
                            5U> led0;
    }
  }

#endif // _MCAL_LED_2010_09_14_H_
