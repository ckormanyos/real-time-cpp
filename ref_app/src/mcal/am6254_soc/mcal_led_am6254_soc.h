///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_AM6254_SOC_2025_08_04_H
  #define MCAL_LED_AM6254_SOC_2025_08_04_H

  #include <mcal_led/mcal_led_boolean_state_base.h>

  #include <util/utility/util_time.h>

  #include <cstdint>

  #define PADCFG_CTRL0_CFG0_PADCONFIG3  UINT32_C(0x000F400C)
  #define PADCFG_CTRL0_CFG0_PADCONFIG4  UINT32_C(0x000F4010)
  #define PADCFG_CTRL0_CFG0_PADCONFIG5  UINT32_C(0x000F4014)
  #define PADCFG_CTRL0_CFG0_PADCONFIG6  UINT32_C(0x000F4018)

  #define GPIO_DIR01       UINT32_C(0x00600010)
  #define GPIO_OUT_DATA01  UINT32_C(0x00600014)
  #define GPIO_SET_DATA01  UINT32_C(0x00600018)
  #define GPIO_CLR_DATA01  UINT32_C(0x0060001C)

  #define LED_1   6
  #define LED_2   5
  #define LED_3   4
  #define LED_4   3

  #define LED_INIT()  do{                                                                            \
                      *(volatile uint32_t*)(PADCFG_CTRL0_CFG0_PADCONFIG3) &= ~((uint32_t)1ul <<21);  \
                      *(volatile uint32_t*)(PADCFG_CTRL0_CFG0_PADCONFIG4) &= ~((uint32_t)1ul <<21);  \
                      *(volatile uint32_t*)(PADCFG_CTRL0_CFG0_PADCONFIG5) &= ~((uint32_t)1ul <<21);  \
                      *(volatile uint32_t*)(PADCFG_CTRL0_CFG0_PADCONFIG6) &= ~((uint32_t)1ul <<21);  \
                      *(volatile uint32_t*)(GPIO_DIR01) &= ~((uint32_t)0x78ul);                      \
                      *(volatile uint32_t*)(GPIO_CLR_DATA01) |= 0x78;                                \
                      *(volatile uint32_t*)(GPIO_OUT_DATA01) &= ~((uint32_t)0x78ul);                 \
                      }while(0)

  #define LED_ON(x)      do{*(volatile uint32_t*)(GPIO_SET_DATA01) |= (1ul << x); *(volatile uint32_t*)(GPIO_OUT_DATA01) |= (1ul << x);}while(0)
  #define LED_OFF(x)     do{*(volatile uint32_t*)(GPIO_CLR_DATA01) |= (1ul << x); *(volatile uint32_t*)(GPIO_OUT_DATA01) &= (uint32_t)(~(uint32_t)(1ul << x));}while(0)

  #define LED_1_ON()   LED_ON(LED_1)
  #define LED_2_ON()   LED_ON(LED_2)
  #define LED_3_ON()   LED_ON(LED_3)
  #define LED_4_ON()   LED_ON(LED_4)

  #define LED_1_OFF()  LED_OFF(LED_1)
  #define LED_2_OFF()  LED_OFF(LED_2)
  #define LED_3_OFF()  LED_OFF(LED_3)
  #define LED_4_OFF()  LED_OFF(LED_4)

  namespace mcal
  {
    namespace led
    {
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

      private:
        static const bool is_init;
      };

      template<typename VoidClass>
      const bool led_am6254_soc_base<VoidClass>::is_init = []() { LED_INIT(); return true; }();

      template<const int LED_ID>
      class led_am6254_soc final : public mcal::led::led_am6254_soc_base<void>
      {
      public:
        led_am6254_soc() noexcept = default;

        ~led_am6254_soc() override = default;

        auto toggle() -> void override
        {
          using base_class_type = led_am6254_soc_base<void>;

          if(base_class_type::state_is_on())
          {
            LED_OFF(LED_ID);
          }
          else
          {
            LED_ON(LED_ID);
          }

          base_class_type::toggle();
        }
      };

      template<const int LED_ID>
      static void main_core_worker(void)
      {
        using timer_type = util::timer<std::uint64_t>;

        using led_type = led_am6254_soc<LED_ID>;

        led_type my_led;

        timer_type led_timer(timer_type::seconds(1U));

        my_led.toggle();

        for(;;)
        {
          while(!led_timer.timeout()) { asm volatile("nop"); }

          my_led.toggle();

          led_timer.start_interval(timer_type::seconds(1U));
        }
      }
    } // namespace led
  } // namespace mcal

#endif // MCAL_LED_AM6254_SOC_2025_08_04_H
