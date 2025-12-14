///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LCD_2024_12_06_H
  #define MCAL_LCD_2024_12_06_H

  #include <stddef.h>

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  void mcal_lcd_init(void);
  void mcal_lcd_write_line(const char* StringToPrint, const size_t StringSize, const size_t LineIndex);

  #if defined(__cplusplus)
  }
  #endif

#endif // MCAL_LCD_2024_12_06_H
