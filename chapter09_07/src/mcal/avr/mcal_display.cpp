///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <mcal_port.h>
#include <mcal/mcal_display.h>

namespace
{
  template<typename segment_a_port,
           typename segment_b_port,
           typename segment_c_port,
           typename segment_d_port,
           typename segment_e_port,
           typename segment_f_port,
           typename segment_g_port,
           typename segment_dp_port>
  class display_fnd567 final : public mcal::display::display_seven_segment
  {
  public:
    display_fnd567()
    {
      port_init();
    }

    display_fnd567(const std::uint8_t value,
                   const bool dp_on)
      : display_seven_segment(value, dp_on)
    {
      port_init();

      do_write_dp(dp_on);

      do_write(value);
    }

    virtual ~display_fnd567() { }

    virtual bool write(const std::uint8_t value)
    {
      return do_write(value);
    }

    virtual bool read(std::uint8_t& byte_to_read) const
    {
      byte_to_read = data;

      return true;
    }

    virtual bool write_dp(const bool dp_on)
    {
      return do_write_dp(dp_on);
    }

    virtual bool read_dp(bool& dp_on) const
    {
      dp_on = dp_is_on;

      return true;
    }

  private:
    static void port_init()
    {
      segment_a_port::set_pin_high();
      segment_b_port::set_pin_high();
      segment_c_port::set_pin_high();
      segment_d_port::set_pin_high();
      segment_e_port::set_pin_high();
      segment_f_port::set_pin_high();
      segment_g_port::set_pin_high();
      segment_dp_port::set_pin_high();

      segment_a_port::set_direction_output();
      segment_b_port::set_direction_output();
      segment_c_port::set_direction_output();
      segment_d_port::set_direction_output();
      segment_e_port::set_direction_output();
      segment_f_port::set_direction_output();
      segment_g_port::set_direction_output();
      segment_dp_port::set_direction_output();
    }

    bool do_write(const std::uint8_t value)
    {
      const std::array<std::uint8_t, 16U>
      character_table =
      {{
        UINT8_C(0x3F), // '0'
        UINT8_C(0x06), // '1'
        UINT8_C(0x5B), // '2'
        UINT8_C(0x4F), // '3'
        UINT8_C(0x66), // '4'
        UINT8_C(0x6D), // '5'
        UINT8_C(0x7D), // '6'
        UINT8_C(0x07), // '7'
        UINT8_C(0x7F), // '8'
        UINT8_C(0x6F), // '9'
        UINT8_C(0x77), // 'A'
        UINT8_C(0x7C), // 'b'
        UINT8_C(0x39), // 'C'
        UINT8_C(0x5E), // 'd'
        UINT8_C(0x79), // 'E'
        UINT8_C(0x71)  // 'F'
      }};

      std::uint8_t table_index;
      bool write_is_ok;

      const bool byte_is_in_range =
        (value < std::uint8_t(character_table.size()));

      if(byte_is_in_range)
      {
        table_index = value;

        write_is_ok = true;
      }
      else
      {
        table_index =
          std::uint8_t(character_table.size() - 1U);

        write_is_ok = false;
      }

      const std::uint8_t segment_pattern =
        character_table[table_index];

      data = segment_pattern;

      ((std::uint8_t(segment_pattern & UINT8_C(0x01)) != UINT8_C(0)) ? segment_a_port::set_pin_low() : segment_a_port::set_pin_high());
      ((std::uint8_t(segment_pattern & UINT8_C(0x02)) != UINT8_C(0)) ? segment_b_port::set_pin_low() : segment_b_port::set_pin_high());
      ((std::uint8_t(segment_pattern & UINT8_C(0x04)) != UINT8_C(0)) ? segment_c_port::set_pin_low() : segment_c_port::set_pin_high());
      ((std::uint8_t(segment_pattern & UINT8_C(0x08)) != UINT8_C(0)) ? segment_d_port::set_pin_low() : segment_d_port::set_pin_high());
      ((std::uint8_t(segment_pattern & UINT8_C(0x10)) != UINT8_C(0)) ? segment_e_port::set_pin_low() : segment_e_port::set_pin_high());
      ((std::uint8_t(segment_pattern & UINT8_C(0x20)) != UINT8_C(0)) ? segment_f_port::set_pin_low() : segment_f_port::set_pin_high());
      ((std::uint8_t(segment_pattern & UINT8_C(0x40)) != UINT8_C(0)) ? segment_g_port::set_pin_low() : segment_g_port::set_pin_high());

      return write_is_ok;
    }

    bool do_write_dp(const bool dp_on)
    {
      (dp_on ? segment_dp_port::set_pin_low ()
             : segment_dp_port::set_pin_high());

      dp_is_on = dp_on;

      return true;
    }
  };
}

mcal::display::display_seven_segment& mcal::display::display0()
{
  typedef mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, UINT8_C(0)> portc0_type;
  typedef mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, UINT8_C(1)> portc1_type;
  typedef mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, UINT8_C(2)> portc2_type;
  typedef mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, UINT8_C(3)> portc3_type;
  typedef mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, UINT8_C(4)> portc4_type;
  typedef mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, UINT8_C(5)> portc5_type;
  typedef mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portd, UINT8_C(0)> portd0_type;
  typedef mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portd, UINT8_C(1)> portd1_type;

  typedef display_fnd567<portc4_type,
                         portc3_type,
                         portc1_type,
                         portc0_type,
                         portc5_type,
                         portd0_type,
                         portd1_type,
                         portc2_type> display_type;

  static display_type the_display;

  return the_display;
}
