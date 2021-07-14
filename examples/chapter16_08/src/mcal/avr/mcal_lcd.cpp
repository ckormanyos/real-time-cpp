///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_lcd.h>
#include <mcal_lcd/mcal_lcd_generic_st7066.h>
#include <mcal_port.h>

namespace
{
  // LCD port pin expander configuration.
  using mcal_lcd_port_pin_expander_port_pin_rs__type = mcal::port::port_pin_expander< 5U>;
  using mcal_lcd_port_pin_expander_port_pin_rw__type = mcal::port::port_pin_expander< 6U>;
  using mcal_lcd_port_pin_expander_port_pin_e1__type = mcal::port::port_pin_expander< 7U>;
  using mcal_lcd_port_pin_expander_port_pin_e2__type = mcal::port::port_pin_expander< 3U>;
  using mcal_lcd_port_pin_expander_port_pin_db0_type = mcal::port::port_pin_expander< 8U>;
  using mcal_lcd_port_pin_expander_port_pin_db1_type = mcal::port::port_pin_expander< 9U>;
  using mcal_lcd_port_pin_expander_port_pin_db2_type = mcal::port::port_pin_expander<10U>;
  using mcal_lcd_port_pin_expander_port_pin_db3_type = mcal::port::port_pin_expander<11U>;
  using mcal_lcd_port_pin_expander_port_pin_db4_type = mcal::port::port_pin_expander<12U>;
  using mcal_lcd_port_pin_expander_port_pin_db5_type = mcal::port::port_pin_expander<13U>;
  using mcal_lcd_port_pin_expander_port_pin_db6_type = mcal::port::port_pin_expander<14U>;
  using mcal_lcd_port_pin_expander_port_pin_db7_type = mcal::port::port_pin_expander<15U>;

  using mcal_lcd0_type = mcal::lcd::lcd_generic_st7066<mcal_lcd_port_pin_expander_port_pin_rs__type,
                                                       mcal_lcd_port_pin_expander_port_pin_rw__type,
                                                       mcal_lcd_port_pin_expander_port_pin_e1__type,
                                                       mcal_lcd_port_pin_expander_port_pin_db0_type,
                                                       mcal_lcd_port_pin_expander_port_pin_db1_type,
                                                       mcal_lcd_port_pin_expander_port_pin_db2_type,
                                                       mcal_lcd_port_pin_expander_port_pin_db3_type,
                                                       mcal_lcd_port_pin_expander_port_pin_db4_type,
                                                       mcal_lcd_port_pin_expander_port_pin_db5_type,
                                                       mcal_lcd_port_pin_expander_port_pin_db6_type,
                                                       mcal_lcd_port_pin_expander_port_pin_db7_type,
                                                       40U>;

  using mcal_lcd1_type = mcal::lcd::lcd_generic_st7066<mcal_lcd_port_pin_expander_port_pin_rs__type,
                                                       mcal_lcd_port_pin_expander_port_pin_rw__type,
                                                       mcal_lcd_port_pin_expander_port_pin_e2__type,
                                                       mcal_lcd_port_pin_expander_port_pin_db0_type,
                                                       mcal_lcd_port_pin_expander_port_pin_db1_type,
                                                       mcal_lcd_port_pin_expander_port_pin_db2_type,
                                                       mcal_lcd_port_pin_expander_port_pin_db3_type,
                                                       mcal_lcd_port_pin_expander_port_pin_db4_type,
                                                       mcal_lcd_port_pin_expander_port_pin_db5_type,
                                                       mcal_lcd_port_pin_expander_port_pin_db6_type,
                                                       mcal_lcd_port_pin_expander_port_pin_db7_type,
                                                       40U>;
}

void mcal::lcd::init(const config_type*)
{
  static_cast<void>(lcd0().init());
  static_cast<void>(lcd1().init());
}

mcal::lcd::lcd_base& mcal::lcd::lcd0()
{
  static mcal_lcd0_type lc0;

  return lc0;
}

mcal::lcd::lcd_base& mcal::lcd::lcd1()
{
  static mcal_lcd1_type lc1;

  return lc1;
}
