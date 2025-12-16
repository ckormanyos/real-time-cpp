///////////////////////////////////////////////////////////////////////////////
//  Copyright Iliass Mahjoub 2023 - 2025
//  Copyright Christopher Kormanyos 2024 - 2025
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_lcd.h>
#include <mcal_lcd/mcal_lcd_console.h>

namespace local_lcd
{
  auto lcd_host_console() -> mcal::lcd::lcd_base&;

  auto lcd_host_console() -> mcal::lcd::lcd_base&
  {
    static mcal::lcd::lcd_console my_lcd { };

    return my_lcd;
  }
} // namespace local_lcd;

auto mcal::lcd::init() -> void
{
  static const bool is_init { local_lcd::lcd_host_console().init() };

  static_cast<void>(is_init);
}

auto mcal::lcd::write_line(const char* StringToPrint, const size_t StringSize, const size_t LineIndex) -> void
{
  static_cast<void>
  (
    local_lcd::lcd_host_console().write(StringToPrint, StringSize, static_cast<std::uint_fast8_t>(LineIndex))
  );
}
