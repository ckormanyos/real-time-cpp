///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LCD_GENERIC_ST7066_2020_05_07_H // NOLINT(llvm-header-guard)
  #define MCAL_LCD_GENERIC_ST7066_2020_05_07_H

  #include <mcal_lcd/mcal_lcd_base.h>
  #include <mcal_wdg.h>

  #include <util/utility/util_time.h>

  #include <algorithm>
  #include <cstring>

  #if(__cplusplus >= 201703L)
  namespace mcal::lcd {
  #else
  namespace mcal { namespace lcd { // NOLINT(modernize-concat-nested-namespaces)
  #endif

  template<typename port_pin_rs__type,
           typename port_pin_rw__type,
           typename port_pin_e___type,
           typename port_pin_db0_type,
           typename port_pin_db1_type,
           typename port_pin_db2_type,
           typename port_pin_db3_type,
           typename port_pin_db4_type,
           typename port_pin_db5_type,
           typename port_pin_db6_type,
           typename port_pin_db7_type,
           const std::uint_fast8_t lcd_line_width = 16U>
  class lcd_generic_st7066 final : public mcal::lcd::lcd_base
  {
  private:
    using timer_type = util::timer<std::uint32_t>;

  public:
    lcd_generic_st7066() = default;

    ~lcd_generic_st7066() override = default;

    auto init(void) -> bool override
    {
      port_pin_rs__type::set_pin_low();
      port_pin_rw__type::set_pin_low();
      port_pin_e___type::set_pin_high();

      P1_set(UINT8_C(0));

      port_pin_rs__type::set_direction_output();
      port_pin_rw__type::set_direction_output();
      port_pin_e___type::set_direction_output();

      P1_set_direction_output();

      port_pin_e___type::set_pin_low();

      blocking_delay(timer_type::milliseconds(15U));    // Set a timer which is at least 15ms from system start.
      command(UINT8_C(0x30));                           // Command 0x30 = Wake up
      blocking_delay(timer_type::milliseconds(7U));     // Must wait 5ms, busy flag not available.
      command(UINT8_C(0x30));                           // Command 0x30 = Wake up 2
      blocking_delay(timer_type::microseconds(200U));   // Must wait 160us, busy flag not available
      command(UINT8_C(0x30));                           // Command 0x30 = Wake up 3
      blocking_delay(timer_type::microseconds(200U));   // Must wait 160us, busy flag not available
      command(UINT8_C(0x38));                           // Function set: 8-bit/2-line
      command(UINT8_C(0x10));                           // Set cursor
      command(UINT8_C(0x0C));                           // Display ON; Cursor ON
      command(UINT8_C(0x06));                           // Entry mode set

      const auto write_clear_lines_is_ok = (   write_n(nullptr, 0U, 0U)
                                            && write_n(nullptr, 0U, 1U));


      return write_clear_lines_is_ok;
    }

    auto write(const char* pstr,
               const std::size_t length,
               const std::uint_fast8_t line_index) -> bool override
    {
      std::uint_fast8_t char_index = 0U;

      command(std::uint8_t(0x80U + ((line_index == 0U) ? 0x00U : 0x40U)));

      if(pstr != nullptr)
      {
        // Write the line at line_index.
        for( ; char_index < (std::min)(lcd_line_width, length); ++char_index)
        {
          write(std::uint8_t { pstr[char_index] });
        }
      }

      for( ; char_index < lcd_line_width; ++char_index)
      {
        write(std::uint8_t { ' ' });
      }

      return true;
    }

  private:
    static void blocking_delay(const typename timer_type::tick_type blocking_delay_value)
    {
      timer_type::blocking_delay(blocking_delay_value);
    }

    auto write(const std::uint8_t i) -> void
    {
      P1_set(i);                                        // P1 = i;   // Put data on the output Port
      port_pin_rs__type::set_pin_high();                // D_I =1;   // D/I=HIGH : send data
      port_pin_rw__type::set_pin_low();                 // R_W =0;   // R/W=LOW : Write
      port_pin_e___type::set_pin_high();                // E = 1;
      blocking_delay(timer_type::microseconds(10U));    // Delay(1); // Enable pulse width >= 300ns
      port_pin_e___type::set_pin_low();                 // E = 0;    // Clock enable: falling edge
    }

    auto command(std::uint8_t i) -> void
    {
      P1_set(i);                                        // P1 = i;   // Put data on output Port
      port_pin_rs__type::set_pin_low();                 // D_I =0;   // D/I=LOW : send instruction
      port_pin_rw__type::set_pin_low();                 // R_W =0;   // R/W=LOW : Write
      port_pin_e___type::set_pin_high();                // E = 1;
      blocking_delay(timer_type::microseconds(10U));    // Delay(1); // Enable pulse width >= 300ns
      port_pin_e___type::set_pin_low();                 // E = 0;    // Clock enable: falling edge
      blocking_delay(timer_type::microseconds(40U));                 // Command execution delay
    }

    auto P1_set(const std::uint8_t c) -> void
    {
      (static_cast<std::uint_fast8_t>(c & UINT8_C(0x01)) != UINT8_C(0)) ? port_pin_db0_type::set_pin_high() : port_pin_db0_type::set_pin_low();
      (static_cast<std::uint_fast8_t>(c & UINT8_C(0x02)) != UINT8_C(0)) ? port_pin_db1_type::set_pin_high() : port_pin_db1_type::set_pin_low();
      (static_cast<std::uint_fast8_t>(c & UINT8_C(0x04)) != UINT8_C(0)) ? port_pin_db2_type::set_pin_high() : port_pin_db2_type::set_pin_low();
      (static_cast<std::uint_fast8_t>(c & UINT8_C(0x08)) != UINT8_C(0)) ? port_pin_db3_type::set_pin_high() : port_pin_db3_type::set_pin_low();
      (static_cast<std::uint_fast8_t>(c & UINT8_C(0x10)) != UINT8_C(0)) ? port_pin_db4_type::set_pin_high() : port_pin_db4_type::set_pin_low();
      (static_cast<std::uint_fast8_t>(c & UINT8_C(0x20)) != UINT8_C(0)) ? port_pin_db5_type::set_pin_high() : port_pin_db5_type::set_pin_low();
      (static_cast<std::uint_fast8_t>(c & UINT8_C(0x40)) != UINT8_C(0)) ? port_pin_db6_type::set_pin_high() : port_pin_db6_type::set_pin_low();
      (static_cast<std::uint_fast8_t>(c & UINT8_C(0x80)) != UINT8_C(0)) ? port_pin_db7_type::set_pin_high() : port_pin_db7_type::set_pin_low();
    }

    static auto P1_set_direction_output() -> void
    {
      port_pin_db0_type::set_direction_output();
      port_pin_db1_type::set_direction_output();
      port_pin_db2_type::set_direction_output();
      port_pin_db3_type::set_direction_output();
      port_pin_db4_type::set_direction_output();
      port_pin_db5_type::set_direction_output();
      port_pin_db6_type::set_direction_output();
      port_pin_db7_type::set_direction_output();
    }
  };

  #if(__cplusplus >= 201703L)
  } // namespace mcal::lcd
  #else
  } // namespace lcd
  } // namespace mcal
  #endif

#endif // MCAL_LCD_GENERIC_ST7066_2020_05_07_H
