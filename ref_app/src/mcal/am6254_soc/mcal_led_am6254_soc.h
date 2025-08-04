///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Parts of this file originate from the file Mcal/Gpio/led.h in:
// https://github.com/Chalandi/Baremetal_TI_AM6254_multicore_nosdk

#ifndef MCAL_LED_AM6254_SOC_2025_08_04_H
  #define MCAL_LED_AM6254_SOC_2025_08_04_H

  #include <mcal_led/mcal_led_boolean_state_base.h>

  #include <util/utility/util_time.h>

  #include <cstdint>
  #include <type_traits>

  namespace mcal
  {
    namespace led
    {
      constexpr unsigned LED_1 { UINT8_C(6) };
      constexpr unsigned LED_2 { UINT8_C(5) };
      constexpr unsigned LED_3 { UINT8_C(4) };
      constexpr unsigned LED_4 { UINT8_C(3) };

      template<typename VoidClass>
      class led_am6254_soc_base : public mcal::led::led_boolean_state_base
      {
      public:
        ~led_am6254_soc_base() override = default;

      protected:
        led_am6254_soc_base() noexcept = default;

        auto toggle() -> void override
        {
          using base_class_type = led_boolean_state_base;

          base_class_type::toggle();
        }

        static constexpr std::uint32_t PADCFG_CTRL0_CFG0_PADCONFIG3 { UINT32_C(0x000F400C) };
        static constexpr std::uint32_t PADCFG_CTRL0_CFG0_PADCONFIG4 { UINT32_C(0x000F4010) };
        static constexpr std::uint32_t PADCFG_CTRL0_CFG0_PADCONFIG5 { UINT32_C(0x000F4014) };
        static constexpr std::uint32_t PADCFG_CTRL0_CFG0_PADCONFIG6 { UINT32_C(0x000F4018) };

        static constexpr std::uint32_t GPIO_DIR01      { UINT32_C(0x00600010) };
        static constexpr std::uint32_t GPIO_OUT_DATA01 { UINT32_C(0x00600014) };
        static constexpr std::uint32_t GPIO_SET_DATA01 { UINT32_C(0x00600018) };
        static constexpr std::uint32_t GPIO_CLR_DATA01 { UINT32_C(0x0060001C) };

      private:
        static const volatile bool is_init;

        using local_void_class = VoidClass;

        static_assert(std::is_same<local_void_class, void>::value, "Error: The template parameter must be of type void.");

        #if defined(__GNUC__)
        __attribute__((noinline,used))
        #endif
        static auto LED_INIT() -> bool
        {
          *reinterpret_cast<volatile std::uint32_t*>(PADCFG_CTRL0_CFG0_PADCONFIG3) &= static_cast<std::uint32_t>(~(UINT32_C(1) << 21U));
          *reinterpret_cast<volatile std::uint32_t*>(PADCFG_CTRL0_CFG0_PADCONFIG4) &= static_cast<std::uint32_t>(~(UINT32_C(1) << 21U));
          *reinterpret_cast<volatile std::uint32_t*>(PADCFG_CTRL0_CFG0_PADCONFIG5) &= static_cast<std::uint32_t>(~(UINT32_C(1) << 21U));
          *reinterpret_cast<volatile std::uint32_t*>(PADCFG_CTRL0_CFG0_PADCONFIG6) &= static_cast<std::uint32_t>(~(UINT32_C(1) << 21U));
          *reinterpret_cast<volatile std::uint32_t*>(GPIO_CLR_DATA01)              |= UINT32_C(0x78);
          *reinterpret_cast<volatile std::uint32_t*>(GPIO_OUT_DATA01)              &= static_cast<std::uint32_t>(~(UINT32_C(0x78)));
          *reinterpret_cast<volatile std::uint32_t*>(GPIO_DIR01)                   &= static_cast<std::uint32_t>(~(UINT32_C(0x78)));

          return true;
        }
      };

      template<typename VoidClass>
      const volatile bool led_am6254_soc_base<VoidClass>::is_init { LED_INIT() };

      template<const unsigned LED_ID>
      class led_am6254_soc final : public mcal::led::led_am6254_soc_base<void>
      {
      private:
        using base_class_type = led_am6254_soc_base<void>;

        static constexpr auto local_led_id() noexcept -> unsigned { return LED_ID; }

      public:
        led_am6254_soc() noexcept = default;

        ~led_am6254_soc() override = default;

        auto toggle() -> void override
        {
          ((base_class_type::state_is_on()) ? LED_OFF() : LED_ON());

          base_class_type::toggle();
        }

        static auto main_core_worker() -> void
        {
          using local_timer_type = util::timer<std::uint64_t>;
          using local_tick_type = typename local_timer_type::tick_type;
          using local_led_type = led_am6254_soc<local_led_id()>;

          local_led_type my_led { };

          local_timer_type led_timer(local_timer_type::seconds(local_tick_type { UINT8_C(1) }));

          my_led.toggle();

          for(;;)
          {
            while(!led_timer.timeout()) { asm volatile("nop"); }

            my_led.toggle();

            led_timer.start_interval(local_timer_type::seconds(local_tick_type { UINT8_C(1) }));
          }
        }

      private:
        auto LED_ON () noexcept -> void { *reinterpret_cast<volatile std::uint32_t*>(base_class_type::GPIO_SET_DATA01) |= static_cast<std::uint32_t>(UINT32_C(1) << local_led_id()); *reinterpret_cast<volatile std::uint32_t*>(base_class_type::GPIO_OUT_DATA01) |= static_cast<std::uint32_t>(UINT32_C(1) << local_led_id()); }
        auto LED_OFF() noexcept -> void { *reinterpret_cast<volatile std::uint32_t*>(base_class_type::GPIO_CLR_DATA01) |= static_cast<std::uint32_t>(UINT32_C(1) << local_led_id()); *reinterpret_cast<volatile std::uint32_t*>(base_class_type::GPIO_OUT_DATA01) &= static_cast<std::uint32_t>(~static_cast<std::uint32_t>(UINT32_C(1) << local_led_id())); }
      };
    } // namespace led
  } // namespace mcal

#endif // MCAL_LED_AM6254_SOC_2025_08_04_H
