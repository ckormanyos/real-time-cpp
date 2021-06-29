///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LCD_2020_06_10_H_
  #define MCAL_LCD_2020_06_10_H_

  #include <mcal_lcd/mcal_lcd_base.h>

  namespace mcal { namespace lcd {

  typedef void config_type;

  void init(const config_type*);

  lcd_base& lcd0();
  lcd_base& lcd1();

  } } // namespace mcal::lcd

#endif // MCAL_LCD_2020_06_10_H_
