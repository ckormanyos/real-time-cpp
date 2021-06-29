#include <mcal_lcd.h>
#include <mcal_lcd/mcal_lcd_console.h>

mcal::lcd::lcd_base& mcal::lcd::lcd0()
{
  static mcal::lcd::lcd_console lc0;

  return lc0;
}
