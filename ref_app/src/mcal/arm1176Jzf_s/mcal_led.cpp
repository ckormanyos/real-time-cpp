///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <mcal_led.h>

constexpr std::uint32_t GPIO_BASE      = 0x20200000UL;

constexpr std::uint32_t GPIO_GPFSEL0   = 0;
constexpr std::uint32_t GPIO_GPFSEL1   = 1;
constexpr std::uint32_t GPIO_GPFSEL2   = 2;
constexpr std::uint32_t GPIO_GPFSEL3   = 3;
constexpr std::uint32_t GPIO_GPFSEL4   = 4;
constexpr std::uint32_t GPIO_GPFSEL5   = 5;

constexpr std::uint32_t GPIO_GPSET0    = 7;
constexpr std::uint32_t GPIO_GPSET1    = 8;

constexpr std::uint32_t GPIO_GPCLR0    = 10;
constexpr std::uint32_t GPIO_GPCLR1    = 11;

constexpr std::uint32_t GPIO_GPLEV0    = 13;
constexpr std::uint32_t GPIO_GPLEV1    = 14;

constexpr std::uint32_t GPIO_GPEDS0    = 16;
constexpr std::uint32_t GPIO_GPEDS1    = 17;

constexpr std::uint32_t GPIO_GPREN0    = 19;
constexpr std::uint32_t GPIO_GPREN1    = 20;

constexpr std::uint32_t GPIO_GPFEN0    = 22;
constexpr std::uint32_t GPIO_GPFEN1    = 23;

constexpr std::uint32_t GPIO_GPHEN0    = 25;
constexpr std::uint32_t GPIO_GPHEN1    = 26;

constexpr std::uint32_t GPIO_GPLEN0    = 28;
constexpr std::uint32_t GPIO_GPLEN1    = 29;

constexpr std::uint32_t GPIO_GPAREN0   = 31;
constexpr std::uint32_t GPIO_GPAREN1   = 32;

constexpr std::uint32_t GPIO_GPAFEN0   = 34;
constexpr std::uint32_t GPIO_GPAFEN1   = 35;

constexpr std::uint32_t GPIO_GPPUD     = 37;
constexpr std::uint32_t GPIO_GPPUDCLK0 = 38;
constexpr std::uint32_t GPIO_GPPUDCLK1 = 39;

mcal::led::led_type::led_type() : led_is_on(false)
{
  volatile std::uint32_t* gpio = reinterpret_cast<volatile std::uint32_t*>(GPIO_BASE);

  // Write 1 to the GPIO16 init nibble in the Function Select 1 GPIO
  // peripheral register to enable GPIO16 as an output.
  gpio[GPIO_GPFSEL1] |= (1 << 18);

  // Set the GPIO16 output high (turn the OK LED off).
  gpio[GPIO_GPSET0] = (1 << 16);
}

void mcal::led::led_type::toggle() const
{
  volatile std::uint32_t* gpio = reinterpret_cast<volatile std::uint32_t*>(GPIO_BASE);

  // Toggle the LED state.
  if(led_is_on)
  {
    // Set the GPIO16 output high (turn the OK LED off).
    gpio[GPIO_GPSET0] = (1 << 16);
  }
  else
  {
    // Set the GPIO16 output low (turn the OK LED on).
    gpio[GPIO_GPCLR0] = (1 << 16);
  }

  led_is_on = (!led_is_on);
}

namespace mcal
{
  namespace led
  {
    const led_type led0;
  }
}
