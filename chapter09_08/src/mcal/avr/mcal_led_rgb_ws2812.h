///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_RGB_WS2812_2017_11_12_H_
  #define MCAL_LED_RGB_WS2812_2017_11_12_H_

  #include <cstdint>

  #include <mcal/mcal_reg_access_template.h>
  #include <mcal_irq.h>
  #include <mcal_led_rgb_ws2812_detail.h>
  #include <mcal_port.h>
  #include <util/device/util_device_led_rgb.h>

  namespace mcal { namespace led {

  template<const std::uint8_t port_addr,
           const std::uint8_t port_bpos>
  class led_rgb_ws2812 final : public util::device::led_rgb
  {
  public:
    led_rgb_ws2812()
    {
      port_pin_type::set_direction_output();
    }

    virtual ~led_rgb_ws2812() { }

  private:
    using port_pin_type =
      mcal::port::port_pin<std::uint8_t,
                           std::uint8_t,
                           port_addr,
                           port_bpos>;

    template<const std::uint8_t bit_number_param>
    static void push_data(const std::uint8_t data_value)
    {
      if(std::uint8_t(data_value & (UINT8_C(0x80) >> bit_number_param)) != UINT8_C(0))
      {
        port_pin_type::set_pin_high();
        detail::nop_maker<UINT8_C(8)>::nops();

        port_pin_type::set_pin_low();
        detail::nop_maker<UINT8_C(4)>::nops();
      }
      else
      {
        port_pin_type::set_pin_high();
        detail::nop_maker<UINT8_C(3)>::nops();

        port_pin_type::set_pin_low();
        detail::nop_maker<UINT8_C(10)>::nops();
      }
    }

    virtual void apply_color()
    {
      const std::uint8_t red  (get_hue_r());
      const std::uint8_t green(get_hue_g());
      const std::uint8_t blue (get_hue_b());

      mcal::irq::disable_all();

      push_data<UINT8_C(0)>(green);
      push_data<UINT8_C(1)>(green);
      push_data<UINT8_C(2)>(green);
      push_data<UINT8_C(3)>(green);
      push_data<UINT8_C(4)>(green);
      push_data<UINT8_C(5)>(green);
      push_data<UINT8_C(6)>(green);
      push_data<UINT8_C(7)>(green);

      push_data<UINT8_C(0)>(red);
      push_data<UINT8_C(1)>(red);
      push_data<UINT8_C(2)>(red);
      push_data<UINT8_C(3)>(red);
      push_data<UINT8_C(4)>(red);
      push_data<UINT8_C(5)>(red);
      push_data<UINT8_C(6)>(red);
      push_data<UINT8_C(7)>(red);

      push_data<UINT8_C(0)>(blue);
      push_data<UINT8_C(1)>(blue);
      push_data<UINT8_C(2)>(blue);
      push_data<UINT8_C(3)>(blue);
      push_data<UINT8_C(4)>(blue);
      push_data<UINT8_C(5)>(blue);
      push_data<UINT8_C(6)>(blue);
      push_data<UINT8_C(7)>(blue);

      mcal::irq::enable_all();
    }
  };

  } } // namespace mcal::led

#endif // MCAL_LED_RGB_WS2812_2017_11_12_H_
