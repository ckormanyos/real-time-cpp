#include <mcal_lcd.h>
#include <mcal_lcd/mcal_lcd_console.h>

void mcal::lcd::init(const config_type*)
{
  static_cast<void>(lcd0().init());
  static_cast<void>(lcd1().init());
}

mcal::lcd::lcd_base& mcal::lcd::lcd0()
{
  static mcal::lcd::lcd_console lc0;

  return lc0;
}

mcal::lcd::lcd_base& mcal::lcd::lcd1()
{
  static mcal::lcd::lcd_console lc1;

  return lc1;
}
