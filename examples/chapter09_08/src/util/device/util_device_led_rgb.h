///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_DEVICE_LED_RGB_2017_11_12_H_
  #define UTIL_DEVICE_LED_RGB_2017_11_12_H_

  #include <cstdint>

  #include <util/device/util_device_led_base.h>

  namespace util
  {
    namespace device
    {
      class led_rgb : public  led_base
      {
      public:
        virtual ~led_rgb() { }

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

      protected:
        led_rgb() : my_hue_r(0U),
                    my_hue_g(0U),
                    my_hue_b(0U) { }

      private:
        std::uint_fast8_t my_hue_r;
        std::uint_fast8_t my_hue_g;
        std::uint_fast8_t my_hue_b;

        virtual void apply_color() = 0;

        virtual void my_on () { set_color(255U, 255U, 255U); }
        virtual void my_off() { set_color(  0U,   0U,   0U);
        }
      };
    }
  }

#endif // UTIL_DEVICE_LED_RGB_2017_11_12_H_
