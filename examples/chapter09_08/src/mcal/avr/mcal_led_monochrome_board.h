///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_MONOCHROME_BOARD_2017_09_14_H_
  #define MCAL_LED_MONOCHROME_BOARD_2017_09_14_H_

  #include <cstdint>

  #include <mcal_port.h>
  #include <util/device/util_device_led_monochrome.h>

  namespace mcal
  {
    namespace led
    {
      template<const std::uint8_t port_addr,
               const std::uint8_t port_bpos>
      class led_momochrome_board final : public util::device::led_monochrome
      {
      public:
        led_momochrome_board()
        {
          // Set the port pin value to low.
          port_pin_type::set_pin_low();

          // Set the port pin direction to output.
          port_pin_type::set_direction_output();
        }

        virtual ~led_momochrome_board() { }

        virtual void my_on()
        {
          port_pin_type::set_pin_high();
        }

        virtual void my_off()
        {
          port_pin_type::set_pin_low();
        }

      private:
        using port_pin_type =
          mcal::port::port_pin<std::uint8_t,
                               std::uint8_t,
                               port_addr,
                               port_bpos>;
      };
    }
  }

#endif // MCAL_LED_MONOCHROME_BOARD_2017_09_14_H_
