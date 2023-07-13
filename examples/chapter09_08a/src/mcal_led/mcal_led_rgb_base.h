///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_RGB_BASE_2023_07_12_H
  #define MCAL_LED_RGB_BASE_2023_07_12_H

  #include <cstdint>

  #include <mcal_led/mcal_led_boolean_state_base.h>

  namespace mcal { namespace led {

  class led_rgb_base : public mcal::led::led_boolean_state_base
  {
  private:
    using base_class_type = mcal::led::led_boolean_state_base;

  public:
    led_rgb_base() : my_hue_r(0U),
                     my_hue_g(0U),
                     my_hue_b(0U) { }

    ~led_rgb_base() override = default;

    auto toggle() -> void override
    {
      // Toggle the LED state.
      base_class_type::state_is_on() ? my_off() : my_on();

      base_class_type::toggle();
    }

    void set_color(const std::uint32_t color)
    {
      my_hue_r = static_cast<std::uint8_t>(color >>  0U);
      my_hue_g = static_cast<std::uint8_t>(color >>  8U);
      my_hue_b = static_cast<std::uint8_t>(color >> 16U);

      apply_color();
    }

    void set_color(const std::uint_fast8_t hue_r,
                   const std::uint_fast8_t hue_g,
                   const std::uint_fast8_t hue_b)
    {
      my_hue_r = hue_r;
      my_hue_g = hue_g;
      my_hue_b = hue_b;

      apply_color();
    }

    std::uint32_t get_color() const
    {
      return std::uint32_t(  std::uint32_t(my_hue_r) <<  0U
                            | std::uint32_t(my_hue_g) <<  8U
                            | std::uint32_t(my_hue_b) << 16U);
    }

    std::uint_fast8_t get_hue_r() const { return my_hue_r; }
    std::uint_fast8_t get_hue_g() const { return my_hue_g; }
    std::uint_fast8_t get_hue_b() const { return my_hue_b; }

  private:
    std::uint_fast8_t my_hue_r;
    std::uint_fast8_t my_hue_g;
    std::uint_fast8_t my_hue_b;

    virtual void apply_color() = 0;

    auto my_on () -> void { set_color(255U, 255U, 255U); }
    auto my_off() -> void { set_color(  0U,   0U,   0U); }
  };

  } } // namespace mcal::led

#endif // MCAL_LED_RGB_BASE_2023_07_12_H
