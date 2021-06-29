#ifndef MCAL_LCD_BASE_2020_06_10_H_
  #define MCAL_LCD_BASE_2020_06_10_H_

  #include <cstdint>

  namespace mcal { namespace lcd {

  class lcd_base
  {
  public:
    virtual ~lcd_base() = default;

    virtual bool init() = 0;

    virtual bool write(const char* pstr,
                       const std::uint_fast8_t length,
                       const std::uint_fast8_t line_index) = 0;

  protected:
    lcd_base() = default;

    virtual bool set_line_index(const std::uint8_t) { return true; }
  };

  } } // namespace mcal::lcd

#endif // MCAL_LCD_BASE_2020_06_10_H_
