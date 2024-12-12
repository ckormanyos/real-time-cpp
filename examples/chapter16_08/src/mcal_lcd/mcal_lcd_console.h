///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LCD_CONSOLE_2020_06_10_H_
  #define MCAL_LCD_CONSOLE_2020_06_10_H_

  #include <mcal_lcd/mcal_lcd_base.h>

  #include <iostream>
  #include <string>

  namespace mcal { namespace lcd {

  class lcd_console : public mcal::lcd::lcd_base
  {
  public:
    lcd_console() = default;

    ~lcd_console() override = default;

    auto write(const char* pstr,
               const std::uint_fast16_t length,
               const std::uint_fast8_t line_index) -> bool override
    {
      static_cast<void>(line_index);

      bool write_is_ok;

      if((pstr != nullptr) && (length > 0U))
      {
        const std::string str { pstr, pstr + length };

        std::cout << str << std::endl;

        write_is_ok = true;
      }
      else
      {
        write_is_ok = false;
      }

      return write_is_ok;
    }

    auto init() -> bool override { return true; }
  };

  } } // namespace mcal::lcd

#endif // MCAL_LCD_CONSOLE_2020_06_10_H_
