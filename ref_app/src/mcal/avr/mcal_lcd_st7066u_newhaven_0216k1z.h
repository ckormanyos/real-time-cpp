#ifndef MCAL_LCD_ST7066U_NEWHAVEN_0216K1Z_2020_05_07_H_
  #define MCAL_LCD_ST7066U_NEWHAVEN_0216K1Z_2020_05_07_H_

  #include <algorithm>
  #include <cstdint>
  #include <cstring>

  #include <mcal_lcd/mcal_lcd_base.h>
  #include <mcal_wdg.h>
  #include <util/utility/util_countof.h>
  #include <util/utility/util_time.h>

  namespace mcal { namespace lcd {

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
           typename port_pin_db7_type>
  class lcd_st7066u_newhaven_0216k1z final : public mcal::lcd::lcd_base
  {
  private:
    using timer_type = util::timer<std::uint32_t>;

    static void blocking_delay(const typename timer_type::tick_type blocking_delay_value)
    {
      timer_type::blocking_delay(blocking_delay_value);
    }

  public:
    virtual bool init(void)
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

      clear_line(3U);
      clear_line(2U);
      clear_line(1U);
      clear_line(0U);

      return true;
    }

    virtual bool write_n(const char* pstr,
                         const std::uint_fast8_t length,
                         const std::uint_fast8_t line_index,
                         const bool do_clear_line)
    {
      bool write_is_ok;

      if((pstr != nullptr) && (length > 0U))
      {
        // Clear the line and reset the address to the line.
        if(do_clear_line)
        {
          clear_line(line_index);
        }
        else
        {
          set_line_index(line_index);
        }

        // Write the line at line_index.
        for(std::uint_fast8_t i = 0U; i < (std::min)(std::uint_fast8_t(16U), length); ++i)
        {
          write(std::uint8_t(pstr[i]));
        }

        write_is_ok = true;
      }
      else
      {
        write_is_ok = false;
      }

      return write_is_ok;
    }

  private:
    virtual bool set_line_index(const std::uint8_t line_index)
    {
      bool set_line_index_is_ok;

      if(line_index < 4U)
      {
        command(0x80U | ((line_index * 0x40U) + ((line_index > 1U) ? 20U : 0U)));

        set_line_index_is_ok = true;
      }
      else
      {
        set_line_index_is_ok = false;
      }

      return set_line_index_is_ok;
    }

    void clear_line(const std::uint8_t line_index)
    {
      set_line_index(line_index);

      // Clear the line at line_index.
      for(std::uint_fast8_t i = 0U; i < 20U; ++i)
      {
        write(std::uint8_t(char(' ')));
      }

      set_line_index(line_index);
    }

    void write(const std::uint8_t i)
    {
      P1_set(i);                                        // P1 = i;   // Put data on the output Port
      port_pin_rs__type::set_pin_high();                // D_I =1;   // D/I=HIGH : send data
      port_pin_rw__type::set_pin_low();                 // R_W =0;   // R/W=LOW : Write
      port_pin_e___type::set_pin_high();                // E = 1;
      blocking_delay(timer_type::microseconds(10U));    // Delay(1); //enable pulse width >= 300ns
      port_pin_e___type::set_pin_low();                 // E = 0;    //Clock enable: falling edge
    }

    void command(std::uint8_t i)
    {
      P1_set(i);                                        // P1 = i;   //put data on output Port
      port_pin_rs__type::set_pin_low();                 // D_I =0;   //D/I=LOW : send instruction
      port_pin_rw__type::set_pin_low();                 // R_W =0;   //R/W=LOW : Write
      port_pin_e___type::set_pin_high();                // E = 1;
      blocking_delay(timer_type::microseconds(10U));    // Delay(1); //enable pulse width >= 300ns
      port_pin_e___type::set_pin_low();                 // E = 0;    //Clock enable: falling edge
      blocking_delay(timer_type::microseconds(40U));
    }

    void P1_set(const std::uint8_t c)
    {
      std::uint_fast8_t(c & UINT8_C(0x01)) != UINT8_C(0) ? port_pin_db0_type::set_pin_high() : port_pin_db0_type::set_pin_low();
      std::uint_fast8_t(c & UINT8_C(0x02)) != UINT8_C(0) ? port_pin_db1_type::set_pin_high() : port_pin_db1_type::set_pin_low();
      std::uint_fast8_t(c & UINT8_C(0x04)) != UINT8_C(0) ? port_pin_db2_type::set_pin_high() : port_pin_db2_type::set_pin_low();
      std::uint_fast8_t(c & UINT8_C(0x08)) != UINT8_C(0) ? port_pin_db3_type::set_pin_high() : port_pin_db3_type::set_pin_low();
      std::uint_fast8_t(c & UINT8_C(0x10)) != UINT8_C(0) ? port_pin_db4_type::set_pin_high() : port_pin_db4_type::set_pin_low();
      std::uint_fast8_t(c & UINT8_C(0x20)) != UINT8_C(0) ? port_pin_db5_type::set_pin_high() : port_pin_db5_type::set_pin_low();
      std::uint_fast8_t(c & UINT8_C(0x40)) != UINT8_C(0) ? port_pin_db6_type::set_pin_high() : port_pin_db6_type::set_pin_low();
      std::uint_fast8_t(c & UINT8_C(0x80)) != UINT8_C(0) ? port_pin_db7_type::set_pin_high() : port_pin_db7_type::set_pin_low();
    }

    static std::uint8_t P1_get(void)
    {
      const std::uint8_t u =   std::uint8_t(std::uint_fast8_t(port_pin_db0_type::read_input_value() ? 1U : 0U) << 0U)
                             | std::uint8_t(std::uint_fast8_t(port_pin_db1_type::read_input_value() ? 1U : 0U) << 1U)
                             | std::uint8_t(std::uint_fast8_t(port_pin_db2_type::read_input_value() ? 1U : 0U) << 2U)
                             | std::uint8_t(std::uint_fast8_t(port_pin_db3_type::read_input_value() ? 1U : 0U) << 3U)
                             | std::uint8_t(std::uint_fast8_t(port_pin_db4_type::read_input_value() ? 1U : 0U) << 4U)
                             | std::uint8_t(std::uint_fast8_t(port_pin_db5_type::read_input_value() ? 1U : 0U) << 5U)
                             | std::uint8_t(std::uint_fast8_t(port_pin_db6_type::read_input_value() ? 1U : 0U) << 6U)
                             | std::uint8_t(std::uint_fast8_t(port_pin_db7_type::read_input_value() ? 1U : 0U) << 7U);

      return u;
    }

    static void P1_set_direction_output()
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

    static void P1_set_direction_input()
    {
      port_pin_db0_type::set_direction_input();
      port_pin_db1_type::set_direction_input();
      port_pin_db2_type::set_direction_input();
      port_pin_db3_type::set_direction_input();
      port_pin_db4_type::set_direction_input();
      port_pin_db5_type::set_direction_input();
      port_pin_db6_type::set_direction_input();
      port_pin_db7_type::set_direction_input();
    }
  };

  } } // namespace mcal::lcd

#endif // MCAL_LCD_ST7066U_NEWHAVEN_0216K1Z_2020_05_07_H_
