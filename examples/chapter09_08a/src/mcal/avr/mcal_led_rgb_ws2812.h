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
    #if defined(__GNUC__)
    __attribute__((optimize(3)))
    #endif
    auto push_color() -> void;

  public:
    led_rgb_ws2812()
    {
      port_pin_type::set_direction_output();
    }

    ~led_rgb_ws2812() override = default;

    auto apply_color() -> void override
    {
      for(auto i = static_cast<unsigned>(UINT8_C(0)); i < led_count(); ++i)
      {
        push_color();
      }
    }

  private:
    using base_class_type = mcal::led::led_rgb_base;

    static constexpr auto port_addr() noexcept -> std::uint8_t { return PortAddr; }
    static constexpr auto port_bpos() noexcept -> std::uint8_t { return PortBpos; }

    static constexpr auto led_count() noexcept -> unsigned { return LedCount; }

    using port_pin_type = mcal::port::port_pin<std::uint8_t, std::uint8_t, port_addr(), port_bpos()>;
  };

  // Timing of WS2812.

  // Next bit is 0:
  //   T0H = 0.35us
  //   T0L = 0.80us

  // Next bit is 1:
  //   T1H = 0.70us
  //   T1L = 0.60us

  #define MCAL_LED_RGB_WS2812_NOPS_01() asm volatile("nop")
  #define MCAL_LED_RGB_WS2812_NOPS_02() MCAL_LED_RGB_WS2812_NOPS_01(); MCAL_LED_RGB_WS2812_NOPS_01()
  #define MCAL_LED_RGB_WS2812_NOPS_03() MCAL_LED_RGB_WS2812_NOPS_02(); MCAL_LED_RGB_WS2812_NOPS_01()
  #define MCAL_LED_RGB_WS2812_NOPS_05() MCAL_LED_RGB_WS2812_NOPS_03(); MCAL_LED_RGB_WS2812_NOPS_02();
  #define MCAL_LED_RGB_WS2812_NOPS_06() MCAL_LED_RGB_WS2812_NOPS_03(); MCAL_LED_RGB_WS2812_NOPS_03();
  #define MCAL_LED_RGB_WS2812_NOPS_11() MCAL_LED_RGB_WS2812_NOPS_06(); MCAL_LED_RGB_WS2812_NOPS_05()

  #define MCAL_LED_RGB_WS2812_PUSH_DATA(next_bit_is_zero) port_pin_type::set_pin_high(); \
  if   (next_bit_is_zero) { MCAL_LED_RGB_WS2812_NOPS_02(); port_pin_type::set_pin_low(); MCAL_LED_RGB_WS2812_NOPS_11(); } \
  else                    { MCAL_LED_RGB_WS2812_NOPS_06(); port_pin_type::set_pin_low(); MCAL_LED_RGB_WS2812_NOPS_06(); }

  template<const std::uint8_t PortAddr,
           const std::uint8_t PortBpos,
           const unsigned LedCount> auto led_rgb_ws2812<PortAddr, PortBpos, LedCount>::push_color() -> void
  {
    const auto red   = static_cast<std::uint8_t>(base_class_type::get_hue_r());
    const auto green = static_cast<std::uint8_t>(base_class_type::get_hue_g());
    const auto blue  = static_cast<std::uint8_t>(base_class_type::get_hue_b());

    mcal::irq::disable_all();

    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(green & static_cast<std::uint8_t>(UINT8_C(0x80))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(green & static_cast<std::uint8_t>(UINT8_C(0x40))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(green & static_cast<std::uint8_t>(UINT8_C(0x20))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(green & static_cast<std::uint8_t>(UINT8_C(0x10))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(green & static_cast<std::uint8_t>(UINT8_C(0x08))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(green & static_cast<std::uint8_t>(UINT8_C(0x04))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(green & static_cast<std::uint8_t>(UINT8_C(0x02))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(green & static_cast<std::uint8_t>(UINT8_C(0x01))) == static_cast<std::uint8_t>(UINT8_C(0)));

    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(red   & static_cast<std::uint8_t>(UINT8_C(0x80))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(red   & static_cast<std::uint8_t>(UINT8_C(0x40))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(red   & static_cast<std::uint8_t>(UINT8_C(0x20))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(red   & static_cast<std::uint8_t>(UINT8_C(0x10))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(red   & static_cast<std::uint8_t>(UINT8_C(0x08))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(red   & static_cast<std::uint8_t>(UINT8_C(0x04))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(red   & static_cast<std::uint8_t>(UINT8_C(0x02))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(red   & static_cast<std::uint8_t>(UINT8_C(0x01))) == static_cast<std::uint8_t>(UINT8_C(0)));

    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(blue  & static_cast<std::uint8_t>(UINT8_C(0x80))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(blue  & static_cast<std::uint8_t>(UINT8_C(0x40))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(blue  & static_cast<std::uint8_t>(UINT8_C(0x20))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(blue  & static_cast<std::uint8_t>(UINT8_C(0x10))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(blue  & static_cast<std::uint8_t>(UINT8_C(0x08))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(blue  & static_cast<std::uint8_t>(UINT8_C(0x04))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(blue  & static_cast<std::uint8_t>(UINT8_C(0x02))) == static_cast<std::uint8_t>(UINT8_C(0)));
    MCAL_LED_RGB_WS2812_PUSH_DATA(static_cast<std::uint8_t>(blue  & static_cast<std::uint8_t>(UINT8_C(0x01))) == static_cast<std::uint8_t>(UINT8_C(0)));

    mcal::irq::enable_all();
  }

  #if defined(MCAL_LED_RGB_WS2812_PUSH_DATA)
  #undef MCAL_LED_RGB_WS2812_PUSH_DATA
  #endif

  #if defined(MCAL_LED_RGB_WS2812_NOPS_01)
  #undef MCAL_LED_RGB_WS2812_NOPS_01
  #endif
  #if defined(MCAL_LED_RGB_WS2812_NOPS_02)
  #undef MCAL_LED_RGB_WS2812_NOPS_02
  #endif
  #if defined(MCAL_LED_RGB_WS2812_NOPS_03)
  #undef MCAL_LED_RGB_WS2812_NOPS_03
  #endif
  #if defined(MCAL_LED_RGB_WS2812_NOPS_05)
  #undef MCAL_LED_RGB_WS2812_NOPS_05
  #endif
  #if defined(MCAL_LED_RGB_WS2812_NOPS_06)
  #undef MCAL_LED_RGB_WS2812_NOPS_06
  #endif
  #if defined(MCAL_LED_RGB_WS2812_NOPS_11)
  #undef MCAL_LED_RGB_WS2812_NOPS_11
  #endif

  } } // namespace mcal::led

#endif // MCAL_LED_RGB_WS2812_2017_11_12_H
