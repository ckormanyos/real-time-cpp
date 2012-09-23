#include <mcal/mcal.h>

namespace mcal
{
  namespace led
  {
    const led_type<std::uint32_t,
                   std::uint32_t,
                   mcal::reg::gpioc_odr,
                   8U> led0;
/*
    const led_type<std::uint32_t,
                   std::uint32_t,
                   mcal::reg::gpioa_odr,
                   2U> led0;
*/
  }
}
