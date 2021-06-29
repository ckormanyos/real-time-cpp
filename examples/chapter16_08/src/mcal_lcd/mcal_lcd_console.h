#ifndef MCAL_LCD_CONSOLE_2020_06_10_H_
  #define MCAL_LCD_CONSOLE_2020_06_10_H_

  #include <iostream>
  #include <string>

  #include <mcal_lcd/mcal_lcd_base.h>

  namespace mcal { namespace lcd {

  class lcd_console : public mcal::lcd::lcd_base
  {
  public:
    lcd_console() = default;

    virtual ~lcd_console() = default;

    virtual bool write(const char* pstr,
                       const std::uint_fast8_t length,
                       const std::uint_fast8_t line_index)
    {
      static_cast<void>(line_index);

      bool write_is_ok;

      if((pstr != nullptr) && (length > 0U))
      {
        const std::string str(pstr, pstr + length);

        std::cout << str << std::endl;

        write_is_ok = true;
      }
      else
      {
        write_is_ok = false;
      }

      return write_is_ok;
    }

    virtual bool init() { return true; }
  };

  } } // namespace mcal::lcd

#endif // MCAL_LCD_CONSOLE_2020_06_10_H_
