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

    virtual bool write_n(const char* pstr,
                         const std::uint_fast8_t length,
                         const std::uint_fast8_t line_index,
                         const bool do_clear_line)
    {
      static_cast<void>(line_index);
      static_cast<void>(do_clear_line);

      bool write_is_ok;

      if((pstr != nullptr) && (length > 0U))
      {
        std::cout << std::string(pstr, pstr + length) << std::endl;

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
