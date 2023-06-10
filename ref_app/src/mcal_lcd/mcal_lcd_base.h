///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LCD_BASE_2020_06_10_H
  #define MCAL_LCD_BASE_2020_06_10_H

  #include <cstdint>

  #include <util/utility/util_display.h>

  namespace mcal { namespace lcd {

  class lcd_base : public util::display_multiline_base
  {
  public:
    ~lcd_base() override = default;

  protected:
    lcd_base() noexcept = default;
  };

  } } // namespace mcal::lcd

#endif // MCAL_LCD_BASE_2020_06_10_H
