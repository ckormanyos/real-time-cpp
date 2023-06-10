///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LCD_CONSOLE_2020_06_10_H
  #define MCAL_LCD_CONSOLE_2020_06_10_H

  #include <iostream>
  #include <string>

  #include <mcal_lcd/mcal_lcd_base.h>

  namespace mcal { namespace lcd {

  class lcd_console : public mcal::lcd::lcd_base
  {
  public:
    lcd_console() noexcept = default;

    ~lcd_console() override = default;

    auto write(const char* pstr, const std::uint_fast8_t length, const std::uint_fast8_t line_index) noexcept -> bool override
    {
      static_cast<void>(line_index);

      auto result_write_is_ok = bool { };

      if((pstr != nullptr) && (length > 0U))
      {
        const auto str = std::string(pstr, pstr + length);

        std::cout << str << std::endl;

        result_write_is_ok = true;
      }
      else
      {
        result_write_is_ok = false;
      }

      return result_write_is_ok;
    }

    auto init() noexcept -> bool override { return true; }
  };

  } } // namespace mcal::lcd

#endif // MCAL_LCD_CONSOLE_2020_06_10_H
