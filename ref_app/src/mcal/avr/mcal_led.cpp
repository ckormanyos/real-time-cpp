#include <mcal/mcal.h>

namespace mcal
{
  namespace led
  {
    const led_type<std::uint8_t,
                   std::uint8_t,
                   mcal::reg::portb,
                   5U> led0;
  }
}
