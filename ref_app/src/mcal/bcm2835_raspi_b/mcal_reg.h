///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_2010_04_10_H_
  #define MCAL_REG_2010_04_10_H_

  #include <cstdint>

  namespace mcal
  {
    namespace reg
    {
      // Port registers.
      constexpr std::uint32_t gpio_base      = UINT32_C(0x20200000);

      constexpr std::uint32_t gpio_gpfsel0                      = gpio_base + (UINT32_C(4) *  0);
      constexpr std::uint32_t gpio_gpfsel1                      = gpio_base + (UINT32_C(4) *  1);
      constexpr std::uint32_t gpio_gpfsel2                      = gpio_base + (UINT32_C(4) *  2);
      constexpr std::uint32_t gpio_gpfsel3                      = gpio_base + (UINT32_C(4) *  3);
      constexpr std::uint32_t gpio_gpfsel4                      = gpio_base + (UINT32_C(4) *  4);
      constexpr std::uint32_t gpio_gpfsel5                      = gpio_base + (UINT32_C(4) *  5);
      constexpr std::uint32_t gpio_gpset0                       = gpio_base + (UINT32_C(4) *  7);
      constexpr std::uint32_t gpio_gpset1                       = gpio_base + (UINT32_C(4) *  8);
      constexpr std::uint32_t gpio_gpclr0                       = gpio_base + (UINT32_C(4) * 10);
      constexpr std::uint32_t gpio_gpclr1                       = gpio_base + (UINT32_C(4) * 11);
      constexpr std::uint32_t gpio_gplev0                       = gpio_base + (UINT32_C(4) * 13);
      constexpr std::uint32_t gpio_gplev1                       = gpio_base + (UINT32_C(4) * 14);
      constexpr std::uint32_t gpio_gpeds0                       = gpio_base + (UINT32_C(4) * 16);
      constexpr std::uint32_t gpio_gpeds1                       = gpio_base + (UINT32_C(4) * 17);
      constexpr std::uint32_t gpio_gpren0                       = gpio_base + (UINT32_C(4) * 19);
      constexpr std::uint32_t gpio_gpren1                       = gpio_base + (UINT32_C(4) * 20);
      constexpr std::uint32_t gpio_gpfen0                       = gpio_base + (UINT32_C(4) * 22);
      constexpr std::uint32_t gpio_gpfen1                       = gpio_base + (UINT32_C(4) * 23);
      constexpr std::uint32_t gpio_gphen0                       = gpio_base + (UINT32_C(4) * 25);
      constexpr std::uint32_t gpio_gphen1                       = gpio_base + (UINT32_C(4) * 26);
      constexpr std::uint32_t gpio_gplen0                       = gpio_base + (UINT32_C(4) * 28);
      constexpr std::uint32_t gpio_gplen1                       = gpio_base + (UINT32_C(4) * 29);
      constexpr std::uint32_t gpio_gparen0                      = gpio_base + (UINT32_C(4) * 31);
      constexpr std::uint32_t gpio_gparen1                      = gpio_base + (UINT32_C(4) * 32);
      constexpr std::uint32_t gpio_gpafen0                      = gpio_base + (UINT32_C(4) * 34);
      constexpr std::uint32_t gpio_gpafen1                      = gpio_base + (UINT32_C(4) * 35);
      constexpr std::uint32_t gpio_gppud                        = gpio_base + (UINT32_C(4) * 37);
      constexpr std::uint32_t gpio_gppudclk0                    = gpio_base + (UINT32_C(4) * 38);
      constexpr std::uint32_t gpio_gppudclk1                    = gpio_base + (UINT32_C(4) * 39);

      // ARM timer registers.
      constexpr std::uint32_t rpi_armtimer_base                 = UINT32_C(0x2000B400);

      constexpr std::uint32_t rpi_armtimer_load                 = rpi_armtimer_base + UINT32_C(0x00);
      constexpr std::uint32_t rpi_armtimer_value                = rpi_armtimer_base + UINT32_C(0x04);
      constexpr std::uint32_t rpi_armtimer_control              = rpi_armtimer_base + UINT32_C(0x08);
      constexpr std::uint32_t rpi_armtimer_irq_clear            = rpi_armtimer_base + UINT32_C(0x0C);
      constexpr std::uint32_t rpi_armtimer_raw_irq              = rpi_armtimer_base + UINT32_C(0x10);
      constexpr std::uint32_t rpi_armtimer_maskedirq            = rpi_armtimer_base + UINT32_C(0x14);
      constexpr std::uint32_t rpi_armtimer_reload               = rpi_armtimer_base + UINT32_C(0x18);
      constexpr std::uint32_t rpi_armtimer_pre_divider          = rpi_armtimer_base + UINT32_C(0x1C);
      constexpr std::uint32_t rpi_armtimer_free_running_counter = rpi_armtimer_base + UINT32_C(0x20);

      // Interrupt controller registers.
      constexpr std::uint32_t rpi_interrupt_controller_base     = UINT32_C(0x2000B200);

      constexpr std::uint32_t rpi_interrupt_irq_basic_pending   = rpi_interrupt_controller_base + UINT32_C(0x00);
      constexpr std::uint32_t rpi_interrupt_irq_pending_1       = rpi_interrupt_controller_base + UINT32_C(0x04);
      constexpr std::uint32_t rpi_interrupt_irq_pending_2       = rpi_interrupt_controller_base + UINT32_C(0x08);
      constexpr std::uint32_t rpi_interrupt_fiq_control         = rpi_interrupt_controller_base + UINT32_C(0x0C);
      constexpr std::uint32_t rpi_interrupt_enable_irqs_1       = rpi_interrupt_controller_base + UINT32_C(0x10);
      constexpr std::uint32_t rpi_interrupt_enable_irqs_2       = rpi_interrupt_controller_base + UINT32_C(0x14);
      constexpr std::uint32_t rpi_interrupt_enable_basic_irqs   = rpi_interrupt_controller_base + UINT32_C(0x18);
      constexpr std::uint32_t rpi_interrupt_disable_irqs_1      = rpi_interrupt_controller_base + UINT32_C(0x1C);
      constexpr std::uint32_t rpi_interrupt_disable_irqs_2      = rpi_interrupt_controller_base + UINT32_C(0x20);
      constexpr std::uint32_t rpi_interrupt_disable_basic_irqs  = rpi_interrupt_controller_base + UINT32_C(0x24);
    }
  }

  #include <mcal/mcal_reg_access_dynamic.h>
  #include <mcal/mcal_reg_access_static.h>

#endif // MCAL_REG_2010_04_10_H_
