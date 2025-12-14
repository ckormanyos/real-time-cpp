///////////////////////////////////////////////////////////////////////////////
//  Copyright Iliass Mahjoub 2023 - 2024
//  Copyright Christopher Kormanyos 2024
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LCD_SERLCD_SPARKFUN_2024_12_05_H // NOLINT(llvm-header-guard)
  #define MCAL_LCD_SERLCD_SPARKFUN_2024_12_05_H

  #include <mcal_lcd/mcal_lcd_generic_device.h>

  #include <util/utility/util_communication.h>
  #include <util/utility/util_time.h>

  #if(__cplusplus >= 201703L)
  namespace mcal::lcd {
  #else
  namespace mcal { namespace lcd { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  template<typename CommunicationType>
  class lcd_serlcd_sparkfun final : public mcal::lcd::lcd_generic_device
  {
  private:
    using communication_type = CommunicationType;

    static constexpr std::uint8_t serlcd_blue_backlight      { (uint8_t) UINT8_C(0xD9) };
    static constexpr std::uint8_t serlcd_green_backlight     { (uint8_t) UINT8_C(0xBB) };
    static constexpr std::uint8_t serlcd_primary_backlight   { (uint8_t) UINT8_C(0x9D) };

    static constexpr std::uint8_t serlcd_setting_mode        { (uint8_t) UINT8_C(0x7C) };
    static constexpr std::uint8_t serlcd_clear_display       { (uint8_t) UINT8_C(0x2D) };

    static constexpr std::uint8_t serlcd_size_width_20       { (uint8_t) UINT8_C(0x03) };
    static constexpr std::uint8_t serlcd_size_lines_04       { (uint8_t) UINT8_C(0x05) };
    static constexpr std::uint8_t serlcd_size_lines_02       { (uint8_t) UINT8_C(0x06) };
    static constexpr std::uint8_t serlcd_size_lines_01       { (uint8_t) UINT8_C(0x07) };

  public:
    lcd_serlcd_sparkfun() = default;

    ~lcd_serlcd_sparkfun() override = default;

    auto init(void) -> bool override
    {
      blocking_delay(timer_type::milliseconds(tick_type { UINT16_C(1250) }));

      communication_type::init();

      setting(serlcd_clear_display);
      setting(serlcd_green_backlight);
      setting(serlcd_size_lines_04);
      setting(serlcd_size_width_20);

      return true;
    }

    auto write(const char* pstr,
               const std::size_t length,
               const std::uint_fast8_t line_index) -> bool override
    {
      // Limit to the maximum count of the display lines.
      const size_t
        line_index_to_use
        {
          (line_index > std::size_t { UINT8_C(3) }) ? std::size_t { UINT8_C(3) } : line_index
        };

      // Limit to the maximum count of the display rows.
      const std::size_t
        size_to_write
        {
          (length > std::size_t { UINT8_C(20)}) ? std::size_t { UINT8_C(20) } : length
        };

      set_line_index(static_cast<std::uint8_t>(line_index_to_use));

      for(std::size_t idx { UINT8_C(0) }; idx < std::size_t { UINT8_C(20) }; ++idx)
      {
        const char char_to_write { (idx < size_to_write) ? pstr[idx] : ' ' };

        transfer(static_cast<std::uint8_t>(char_to_write));
      }

      return true;
    }

  private:
    void transfer(const std::uint8_t byte_to_send)
    {
      std::uint8_t dummy_byte_to_recv { };

      communication_type::select();
      static_cast<void>(communication_type::send(byte_to_send, dummy_byte_to_recv));
      communication_type::deselect();
      blocking_delay(timer_type::microseconds(tick_type { UINT8_C(150) }));
    }

    void setting(const std::uint8_t setting)
    {
      transfer(serlcd_setting_mode);
      transfer(setting);
    }

    auto set_line_index(const std::uint8_t index) -> bool override
    {
      // Set the active cursor position to the beginning of the line index.

      constexpr std::uint_fast8_t index_to_row_table[std::size_t { UINT8_C(4) }] =
      {
        std::uint_fast8_t { UINT8_C( 0) },
        std::uint_fast8_t { UINT8_C(64) },
        std::uint_fast8_t { UINT8_C(20) },
        std::uint_fast8_t { UINT8_C(84) }
      };

      transfer(std::uint8_t { UINT8_C(0xFE) });

      const std::uint_fast8_t
        by_row
        {
          static_cast<std::uint_fast8_t>
          (
              std::uint_fast8_t { UINT8_C(0x80) }
            + index_to_row_table[index]
            + std::uint_fast8_t { UINT8_C(0x00) }
          )
        };

      transfer(static_cast<std::uint8_t>(by_row));

      return true;
    }
  };

  #if(__cplusplus >= 201703L)
  } // namespace mcal::lcd
  #else
  } // namespace lcd
  } // namespace mcal
  #endif

#endif // MCAL_LCD_SERLCD_SPARKFUN_2024_12_05_H
