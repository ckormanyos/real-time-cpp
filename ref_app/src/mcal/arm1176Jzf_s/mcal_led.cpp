///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstddef>
#include <cstdint>
#include <mcal_led.h>

constexpr std::uint32_t GPIO_BASE      = UINT32_C(0x20200000);

constexpr std::size_t   GPIO_GPFSEL0   = std::size_t( 0U);
constexpr std::size_t   GPIO_GPFSEL1   = std::size_t( 1U);
constexpr std::size_t   GPIO_GPFSEL2   = std::size_t( 2U);
constexpr std::size_t   GPIO_GPFSEL3   = std::size_t( 3U);
constexpr std::size_t   GPIO_GPFSEL4   = std::size_t( 4U);
constexpr std::size_t   GPIO_GPFSEL5   = std::size_t( 5U);
constexpr std::size_t   GPIO_GPSET0    = std::size_t( 7U);
constexpr std::size_t   GPIO_GPSET1    = std::size_t( 8U);
constexpr std::size_t   GPIO_GPCLR0    = std::size_t(10U);
constexpr std::size_t   GPIO_GPCLR1    = std::size_t(11U);
constexpr std::size_t   GPIO_GPLEV0    = std::size_t(13U);
constexpr std::size_t   GPIO_GPLEV1    = std::size_t(14U);
constexpr std::size_t   GPIO_GPEDS0    = std::size_t(16U);
constexpr std::size_t   GPIO_GPEDS1    = std::size_t(17U);
constexpr std::size_t   GPIO_GPREN0    = std::size_t(19U);
constexpr std::size_t   GPIO_GPREN1    = std::size_t(20U);
constexpr std::size_t   GPIO_GPFEN0    = std::size_t(22U);
constexpr std::size_t   GPIO_GPFEN1    = std::size_t(23U);
constexpr std::size_t   GPIO_GPHEN0    = std::size_t(25U);
constexpr std::size_t   GPIO_GPHEN1    = std::size_t(26U);
constexpr std::size_t   GPIO_GPLEN0    = std::size_t(28U);
constexpr std::size_t   GPIO_GPLEN1    = std::size_t(29U);
constexpr std::size_t   GPIO_GPAREN0   = std::size_t(31U);
constexpr std::size_t   GPIO_GPAREN1   = std::size_t(32U);
constexpr std::size_t   GPIO_GPAFEN0   = std::size_t(34U);
constexpr std::size_t   GPIO_GPAFEN1   = std::size_t(35U);
constexpr std::size_t   GPIO_GPPUD     = std::size_t(37U);
constexpr std::size_t   GPIO_GPPUDCLK0 = std::size_t(38U);
constexpr std::size_t   GPIO_GPPUDCLK1 = std::size_t(39U);

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
