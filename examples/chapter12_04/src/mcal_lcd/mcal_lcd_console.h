///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LCD_CONSOLE_2020_06_10_H // NOLINT(llvm-header-guard)
  #define MCAL_LCD_CONSOLE_2020_06_10_H

  #include <mcal_lcd/mcal_lcd_base.h>

  #include <iostream>
  #include <string>

  #if(__cplusplus >= 201703L)
  namespace mcal::lcd {
  #else
  namespace mcal { namespace lcd { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  class lcd_console : public mcal::lcd::lcd_base // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    lcd_console() = default; // LCOV_EXCL_LINE

    ~lcd_console() override = default;

    auto write(const char* pstr,
               const std::size_t length, // NOLINT(bugprone-easily-swappable-parameters)
               const std::uint_fast8_t line_index) -> bool override
    {
      static_cast<void>(line_index);

      bool write_is_ok { };

      if((pstr != nullptr) && (length > 0U))
      {
        const std::string str(pstr, pstr + length); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

        std::cout << str << std::endl;

        write_is_ok = true;
      }
      else
      {
        write_is_ok = false;
      }

      return write_is_ok;
    }

    auto init() -> bool override { return true; } // LCOV_EXCL_LINE
  };

  #if(__cplusplus >= 201703L)
  } // namespace mcal::lcd
  #else
  } // namespace lcd
  } // namespace mcal
  #endif

#endif // MCAL_LCD_CONSOLE_2020_06_10_H
