///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_RGB_BASE_2023_07_12_H
  #define MCAL_LED_RGB_BASE_2023_07_12_H

  #include <mcal_led/mcal_led_boolean_state_base.h>

  #include <cstdint>

  namespace mcal { namespace led {

  class led_rgb_base : public mcal::led::led_boolean_state_base
  {
  public:
    ~led_rgb_base() override = default;

    auto toggle() noexcept -> void override
    {
      using base_class_type = mcal::led::led_boolean_state_base;

      // Toggle the LED state.
      (base_class_type::state_is_on() ? my_off() : my_on());

      base_class_type::toggle();
    }

    auto set_color(const std::uint_fast8_t hue_r,
                   const std::uint_fast8_t hue_g,
                   const std::uint_fast8_t hue_b) -> void
    {
      my_hue_r = hue_r;
      my_hue_g = hue_g;
      my_hue_b = hue_b;

      this->apply_color();
    }

    auto set_color(const std::uint32_t color) -> void
    {
      set_color
      (
        static_cast<std::uint8_t>(color >> static_cast<unsigned>(UINT8_C( 0))),
        static_cast<std::uint8_t>(color >> static_cast<unsigned>(UINT8_C( 8))),
        static_cast<std::uint8_t>(color >> static_cast<unsigned>(UINT8_C(16)))
      );
    }

    constexpr auto get_color() const noexcept -> std::uint32_t
    {
      return
        static_cast<std::uint32_t>
        (
            static_cast<std::uint32_t>(static_cast<std::uint32_t>(my_hue_r) << static_cast<unsigned>(UINT8_C( 0)))
          | static_cast<std::uint32_t>(static_cast<std::uint32_t>(my_hue_g) << static_cast<unsigned>(UINT8_C( 8)))
          | static_cast<std::uint32_t>(static_cast<std::uint32_t>(my_hue_b) << static_cast<unsigned>(UINT8_C(16)))
        );
    }

    constexpr auto get_hue_r() const noexcept -> std::uint_fast8_t { return my_hue_r; }
    constexpr auto get_hue_g() const noexcept -> std::uint_fast8_t { return my_hue_g; }
    constexpr auto get_hue_b() const noexcept -> std::uint_fast8_t { return my_hue_b; }

  protected:
    constexpr led_rgb_base() = default;

  private:
    std::uint_fast8_t my_hue_r { };
    std::uint_fast8_t my_hue_g { };
    std::uint_fast8_t my_hue_b { };

    virtual void apply_color() = 0;

    auto my_on () -> void
    {
      set_color
      (
        static_cast<std::uint8_t>(UINT8_C(255)),
        static_cast<std::uint8_t>(UINT8_C(255)),
        static_cast<std::uint8_t>(UINT8_C(255))
      );
    }

    auto my_off() -> void
    {
      set_color
      (
        static_cast<std::uint8_t>(UINT8_C(0)),
        static_cast<std::uint8_t>(UINT8_C(0)),
        static_cast<std::uint8_t>(UINT8_C(0))
      );
    }
  };

  } // namespace led
  } // namespace mcal

#endif // MCAL_LED_RGB_BASE_2023_07_12_H
