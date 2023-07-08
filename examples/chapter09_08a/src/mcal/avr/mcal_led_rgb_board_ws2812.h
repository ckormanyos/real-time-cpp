///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_RGB_BOARD_2017_11_12_H
  #define MCAL_LED_RGB_BOARD_2017_11_12_H

  #include <cstdint>

  #include <mcal_reg.h>
  #include <mcal_irq.h>
  #include <mcal_port.h>
  #include <mcal_led_rgb_board_ws2812_detail.h>
  #include <util/device/util_device_led_rgb.h>

  namespace mcal { namespace led {

  // The industry-standard RGB LED on the board is of type ws2812.

  template<const std::uint8_t port_addr,
           const std::uint8_t port_bpos>
  class led_rgb_board final : public util::device::led_rgb
  {
  private:
    using base_class_type = util::device::led_rgb;

  public:
    led_rgb_board()
    {
      port_pin_type::set_direction_output();
    }

    ~led_rgb_board() override = default;

  private:
    using port_pin_type =
      mcal::port::port_pin<std::uint8_t,
                           std::uint8_t,
                           port_addr,
                           port_bpos>;

    template<const std::uint8_t bit_number_param>
    static auto push_data(const std::uint8_t data_value) -> void
    {
      {
        if(std::uint8_t(data_value & (UINT8_C(0x80) >> bit_number_param)) == UINT8_C(0))
        {
          port_pin_type::set_pin_high();
          detail::nop_maker<UINT8_C(3)>::nops();

          port_pin_type::set_pin_low();
          detail::nop_maker<UINT8_C(8)>::nops();
        }
        else
        {
          port_pin_type::set_pin_high();
          detail::nop_maker<UINT8_C(7)>::nops();

          port_pin_type::set_pin_low();
          detail::nop_maker<UINT8_C(6)>::nops();
        }
      }
    }

    auto apply_color() -> void override
    {
      const std::uint8_t red   = base_class_type::get_hue_r();
      const std::uint8_t green = base_class_type::get_hue_g();
      const std::uint8_t blue  = base_class_type::get_hue_b();

      mcal::irq::disable_all();

      push_data<static_cast<std::uint8_t>(UINT8_C(0))>(green);
      push_data<static_cast<std::uint8_t>(UINT8_C(1))>(green);
      push_data<static_cast<std::uint8_t>(UINT8_C(2))>(green);
      push_data<static_cast<std::uint8_t>(UINT8_C(3))>(green);
      push_data<static_cast<std::uint8_t>(UINT8_C(4))>(green);
      push_data<static_cast<std::uint8_t>(UINT8_C(5))>(green);
      push_data<static_cast<std::uint8_t>(UINT8_C(6))>(green);
      push_data<static_cast<std::uint8_t>(UINT8_C(7))>(green);

      push_data<static_cast<std::uint8_t>(UINT8_C(0))>(red);
      push_data<static_cast<std::uint8_t>(UINT8_C(1))>(red);
      push_data<static_cast<std::uint8_t>(UINT8_C(2))>(red);
      push_data<static_cast<std::uint8_t>(UINT8_C(3))>(red);
      push_data<static_cast<std::uint8_t>(UINT8_C(4))>(red);
      push_data<static_cast<std::uint8_t>(UINT8_C(5))>(red);
      push_data<static_cast<std::uint8_t>(UINT8_C(6))>(red);
      push_data<static_cast<std::uint8_t>(UINT8_C(7))>(red);

      push_data<static_cast<std::uint8_t>(UINT8_C(0))>(blue);
      push_data<static_cast<std::uint8_t>(UINT8_C(1))>(blue);
      push_data<static_cast<std::uint8_t>(UINT8_C(2))>(blue);
      push_data<static_cast<std::uint8_t>(UINT8_C(3))>(blue);
      push_data<static_cast<std::uint8_t>(UINT8_C(4))>(blue);
      push_data<static_cast<std::uint8_t>(UINT8_C(5))>(blue);
      push_data<static_cast<std::uint8_t>(UINT8_C(6))>(blue);
      push_data<static_cast<std::uint8_t>(UINT8_C(7))>(blue);

      mcal::irq::enable_all();
    }
  };

  } } // namespace mcal::led

#endif // MCAL_LED_RGB_BOARD_2017_11_12_H
