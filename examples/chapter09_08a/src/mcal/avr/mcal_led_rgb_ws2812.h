///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_RGB_WS2812_2017_11_12_H
  #define MCAL_LED_RGB_WS2812_2017_11_12_H

  #include <cstdint>

  #include <mcal_cpu.h>
  #include <mcal_irq.h>
  #include <mcal_port.h>
  #include <mcal_led/mcal_led_rgb_base.h>

  namespace mcal { namespace led {

  // The industry-standard RGB LED on the board is of type ws2812.

  template<const std::uint8_t PortAddr,
           const std::uint8_t PortBpos,
           const unsigned LedCount = static_cast<unsigned>(UINT8_C(1))>
  class led_rgb_ws2812 final : public mcal::led::led_rgb_base
  {
  private:
    using base_class_type = mcal::led::led_rgb_base;

    static constexpr auto port_addr() noexcept -> std::uint8_t { return PortAddr; }
    static constexpr auto port_bpos() noexcept -> std::uint8_t { return PortBpos; }

    static constexpr auto led_count() noexcept -> unsigned { return LedCount; }

  public:
    led_rgb_ws2812()
    {
      port_pin_type::set_direction_output();
    }

    ~led_rgb_ws2812() override = default;

  private:
    using port_pin_type =
      mcal::port::port_pin<std::uint8_t,
                           std::uint8_t,
                           port_addr(),
                           port_bpos()>;

    auto push_color() -> void
    {
      std::uint8_t red   = base_class_type::get_hue_r();
      std::uint8_t green = base_class_type::get_hue_g();
      std::uint8_t blue  = base_class_type::get_hue_b();

      const auto push_data =
        [](const std::uint8_t data_value)
        {
          const auto next_bit_value = static_cast<std::uint8_t>(data_value & static_cast<std::uint8_t>(UINT8_C(0x80)));

          const auto next_bit_is_zero = (next_bit_value == static_cast<std::uint8_t>(UINT8_C(0)));

          port_pin_type::set_pin_high();

          if(next_bit_is_zero)
          {
            // Next bit is 0:
            //   T0H = 0.35us
            //   T0L = 0.80us
            mcal::cpu::nop(); mcal::cpu::nop();
            port_pin_type::set_pin_low();
            mcal::cpu::nop(); mcal::cpu::nop();
          }
          else
          {
            // Next bit is 1:
            //   T1H = 0.70us
            //   T1L = 0.60us
            mcal::cpu::nop(); mcal::cpu::nop();
            mcal::cpu::nop(); mcal::cpu::nop();
            mcal::cpu::nop(); mcal::cpu::nop();
            port_pin_type::set_pin_low();
          }
        };

      mcal::irq::disable_all();

      push_data(green); green = static_cast<std::uint8_t>(green << static_cast<unsigned>(UINT8_C(1)));
      push_data(green); green = static_cast<std::uint8_t>(green << static_cast<unsigned>(UINT8_C(1)));
      push_data(green); green = static_cast<std::uint8_t>(green << static_cast<unsigned>(UINT8_C(1)));
      push_data(green); green = static_cast<std::uint8_t>(green << static_cast<unsigned>(UINT8_C(1)));
      push_data(green); green = static_cast<std::uint8_t>(green << static_cast<unsigned>(UINT8_C(1)));
      push_data(green); green = static_cast<std::uint8_t>(green << static_cast<unsigned>(UINT8_C(1)));
      push_data(green); green = static_cast<std::uint8_t>(green << static_cast<unsigned>(UINT8_C(1)));
      push_data(green); green = static_cast<std::uint8_t>(green << static_cast<unsigned>(UINT8_C(1)));

      push_data(red);   red   = static_cast<std::uint8_t>(red   << static_cast<unsigned>(UINT8_C(1)));
      push_data(red);   red   = static_cast<std::uint8_t>(red   << static_cast<unsigned>(UINT8_C(1)));
      push_data(red);   red   = static_cast<std::uint8_t>(red   << static_cast<unsigned>(UINT8_C(1)));
      push_data(red);   red   = static_cast<std::uint8_t>(red   << static_cast<unsigned>(UINT8_C(1)));
      push_data(red);   red   = static_cast<std::uint8_t>(red   << static_cast<unsigned>(UINT8_C(1)));
      push_data(red);   red   = static_cast<std::uint8_t>(red   << static_cast<unsigned>(UINT8_C(1)));
      push_data(red);   red   = static_cast<std::uint8_t>(red   << static_cast<unsigned>(UINT8_C(1)));
      push_data(red);   red   = static_cast<std::uint8_t>(red   << static_cast<unsigned>(UINT8_C(1)));

      push_data(blue);  blue  = static_cast<std::uint8_t>(blue  << static_cast<unsigned>(UINT8_C(1)));
      push_data(blue);  blue  = static_cast<std::uint8_t>(blue  << static_cast<unsigned>(UINT8_C(1)));
      push_data(blue);  blue  = static_cast<std::uint8_t>(blue  << static_cast<unsigned>(UINT8_C(1)));
      push_data(blue);  blue  = static_cast<std::uint8_t>(blue  << static_cast<unsigned>(UINT8_C(1)));
      push_data(blue);  blue  = static_cast<std::uint8_t>(blue  << static_cast<unsigned>(UINT8_C(1)));
      push_data(blue);  blue  = static_cast<std::uint8_t>(blue  << static_cast<unsigned>(UINT8_C(1)));
      push_data(blue);  blue  = static_cast<std::uint8_t>(blue  << static_cast<unsigned>(UINT8_C(1)));
      push_data(blue);  blue  = static_cast<std::uint8_t>(blue  << static_cast<unsigned>(UINT8_C(1)));

      mcal::irq::enable_all();
    }

    auto apply_color() -> void override
    {
      for(auto i = static_cast<unsigned>(UINT8_C(0)); i < led_count(); ++i)
      {
        push_color();
      }
    }
  };

  } } // namespace mcal::led

#endif // MCAL_LED_RGB_WS2812_2017_11_12_H
