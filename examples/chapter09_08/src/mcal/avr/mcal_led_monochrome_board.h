///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_MONOCHROME_BOARD_2017_09_14_H
  #define MCAL_LED_MONOCHROME_BOARD_2017_09_14_H

  #include <mcal_port.h>
  #include <util/device/util_device_led_monochrome.h>

  #include <cstdint>

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

        ~led_momochrome_board() override = default;

        auto my_on() -> void override
        {
          port_pin_type::set_pin_high();
        }

        auto my_off()-> void override
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

#endif // MCAL_LED_MONOCHROME_BOARD_2017_09_14_H
