#ifndef MCAL_LCD_BASE_2020_06_10_H_
  #define MCAL_LCD_BASE_2020_06_10_H_

  #include <cstdint>

  namespace mcal { namespace lcd {

  class lcd_base
  {
  public:
    virtual ~lcd_base() = default;

    virtual bool write_n(const char* pstr,
                         const std::uint_fast8_t length,
                         const std::uint_fast8_t line_index = 0,
                         const bool do_clear_line = true) = 0;

  protected:
    lcd_base() = default;

    virtual bool set_line_index() { return true; }
  };

  } } // namespace mcal::lcd

#endif // MCAL_LCD_BASE_2020_06_10_H_
