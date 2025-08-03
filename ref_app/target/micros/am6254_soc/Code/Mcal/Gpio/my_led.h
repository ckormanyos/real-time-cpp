
#ifndef MY_LED_2025_08_03_H
#define MY_LED_2025_08_03_H

#include <mcal_led/mcal_led_boolean_state_base.h>

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

template<const int LED_ID>
class my_led final : public mcal::led::led_boolean_state_base
{
public:
    my_led() noexcept = default;

    ~my_led() override = default;

    auto toggle() -> void override
    {
      using base_class_type = led_boolean_state_base;

      if(base_class_type::state_is_on())
      {
        LED_ON(LED_ID);
      }
      else
      {
        LED_OFF(LED_ID);
      }

      base_class_type::toggle();
    }

private:
  static const bool is_init;
};

template<const int LED_ID>
const bool my_led<LED_ID>::is_init = []() { LED_INIT(); return true; }();

#endif // MY_LED_2025_08_03_H
