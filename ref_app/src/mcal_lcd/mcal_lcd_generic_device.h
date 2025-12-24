///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024 - 2025
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LCD_GENERIC_DEVICE_2024_12_06_H // NOLINT(llvm-header-guard)
  #define MCAL_LCD_GENERIC_DEVICE_2024_12_06_H

  #include <mcal_lcd/mcal_lcd_base.h>
  #include <util/utility/util_time.h>

  #if(__cplusplus >= 201703L)
  namespace mcal::lcd {
  #else
  namespace mcal { namespace lcd { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  class lcd_generic_device : public mcal::lcd::lcd_base
  {
  public:
    ~lcd_generic_device() override = default;

  protected:
    using timer_type = util::timer<std::uint32_t>;
    using tick_type = typename timer_type::tick_type;

    lcd_generic_device() = default;

    static void blocking_delay(const tick_type blocking_delay_value)
    {
      timer_type::blocking_delay(blocking_delay_value);
    }
  };

  #if(__cplusplus >= 201703L)
  } // namespace mcal::lcd
  #else
  } // namespace lcd
  } // namespace mcal
  #endif

#endif // MCAL_LCD_GENERIC_DEVICE_2024_12_06_H
