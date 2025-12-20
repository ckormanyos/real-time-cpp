///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LCD_2024_12_06_H
  #define MCAL_LCD_2024_12_06_H

  #include <cstddef>

  namespace mcal
  {
    namespace lcd
    {
      auto init() -> void;
      auto write_line(const char* StringToPrint, const std::size_t StringSize, const std::size_t LineIndex) -> void;
    } // namespace lcd
  } // namespace mcal

#endif // MCAL_LCD_2024_12_06_H
