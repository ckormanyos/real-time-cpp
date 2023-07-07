///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_RGB_BASE_2017_11_12_H
  #define MCAL_LED_RGB_BASE_2017_11_12_H

  #include <cstdint>

  #include <util/utility/util_noncopyable.h>

  namespace mcal { namespace led {

  class led_rgb_base : private util::noncopyable
  {
  public:
    struct color_rgb
    {
      explicit color_rgb(const std::uint8_t r = static_cast<std::uint8_t>(UINT8_C(0)),
                         const std::uint8_t g = static_cast<std::uint8_t>(UINT8_C(0)),
                         const std::uint8_t b = static_cast<std::uint8_t>(UINT8_C(0)))
        : my_r(r),
          my_g(g),
          my_b(b) { }

      auto is_on() const -> bool
      {
        return
        (
             (my_r != static_cast<std::uint8_t>(UINT8_C(0)))
          || (my_g != static_cast<std::uint8_t>(UINT8_C(0)))
          || (my_b != static_cast<std::uint8_t>(UINT8_C(0)))
        );
      }

      auto get_r() const -> std::uint8_t { return my_r; }
      auto get_g() const -> std::uint8_t { return my_g; }
      auto get_b() const -> std::uint8_t { return my_b; }

    private:
      std::uint8_t my_r { };
      std::uint8_t my_g { };
      std::uint8_t my_b { };
    };

    virtual auto set(const color_rgb& color_rgb_new) -> bool
    {
      my_color_rgb = color_rgb_new;

      this->set_color_rgb();

      return true;
    }

    auto state_is_on() const -> bool
    {
      return my_color_rgb.is_on();
    }

    virtual ~led_rgb_base() = default;

    auto get_r() const -> std::uint8_t { return my_color_rgb.get_r(); }
    auto get_g() const -> std::uint8_t { return my_color_rgb.get_g(); }
    auto get_b() const -> std::uint8_t { return my_color_rgb.get_b(); }

  protected:
    led_rgb_base() = default;

    virtual auto set_color_rgb() -> void = 0;
            auto get_color_rgb() -> const color_rgb& { return my_color_rgb; }

  private:
    color_rgb my_color_rgb { };
  };

  } // namespace led
  } // namespace mcal

#endif // MCAL_LED_RGB_BASE_2017_11_12_H
