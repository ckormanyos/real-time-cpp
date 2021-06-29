///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_lcd.h>
#include <mcal_lcd_st7066u_newhaven_0216k1z.h>
#include <mcal_port.h>

mcal::lcd::lcd_base& mcal::lcd::lcd0()
{
  // LCD port pin expander configuration.
  using mcal_lcd_port_pin_expander_port_pin_rs__type = mcal::port::port_pin_expander< 5U>;
  using mcal_lcd_port_pin_expander_port_pin_rw__type = mcal::port::port_pin_expander< 6U>;
  using mcal_lcd_port_pin_expander_port_pin_e___type = mcal::port::port_pin_expander< 7U>;
  using mcal_lcd_port_pin_expander_port_pin_db0_type = mcal::port::port_pin_expander< 8U>;
  using mcal_lcd_port_pin_expander_port_pin_db1_type = mcal::port::port_pin_expander< 9U>;
  using mcal_lcd_port_pin_expander_port_pin_db2_type = mcal::port::port_pin_expander<10U>;
  using mcal_lcd_port_pin_expander_port_pin_db3_type = mcal::port::port_pin_expander<11U>;
  using mcal_lcd_port_pin_expander_port_pin_db4_type = mcal::port::port_pin_expander<12U>;
  using mcal_lcd_port_pin_expander_port_pin_db5_type = mcal::port::port_pin_expander<13U>;
  using mcal_lcd_port_pin_expander_port_pin_db6_type = mcal::port::port_pin_expander<14U>;
  using mcal_lcd_port_pin_expander_port_pin_db7_type = mcal::port::port_pin_expander<15U>;

  using mcal_lcd0_type = mcal::lcd::lcd_st7066u_newhaven_0216k1z<mcal_lcd_port_pin_expander_port_pin_rs__type,
                                                                    mcal_lcd_port_pin_expander_port_pin_rw__type,
                                                                    mcal_lcd_port_pin_expander_port_pin_e___type,
                                                                    mcal_lcd_port_pin_expander_port_pin_db0_type,
                                                                    mcal_lcd_port_pin_expander_port_pin_db1_type,
                                                                    mcal_lcd_port_pin_expander_port_pin_db2_type,
                                                                    mcal_lcd_port_pin_expander_port_pin_db3_type,
                                                                    mcal_lcd_port_pin_expander_port_pin_db4_type,
                                                                    mcal_lcd_port_pin_expander_port_pin_db5_type,
                                                                    mcal_lcd_port_pin_expander_port_pin_db6_type,
                                                                    mcal_lcd_port_pin_expander_port_pin_db7_type>;

  static mcal_lcd0_type lc0;

  return lc0;
}
