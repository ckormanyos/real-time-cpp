///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <iostream>
#include <mcal/mcal_display.h>

namespace
{
  class display_console final : public mcal::display::display_seven_segment
  {
  public:
    display_console() { }

    virtual ~display_console() { }

    virtual bool write(const std::uint8_t byte_to_write)
    {
      const std::array<std::uint8_t, 16U> character_table =
      {{
        UINT8_C('0'),
        UINT8_C('1'),
        UINT8_C('2'),
        UINT8_C('3'),
        UINT8_C('4'),
        UINT8_C('5'),
        UINT8_C('6'),
        UINT8_C('7'),
        UINT8_C('8'),
        UINT8_C('9'),
        UINT8_C('A'),
        UINT8_C('b'),
        UINT8_C('c'),
        UINT8_C('d'),
        UINT8_C('E'),
        UINT8_C('F')
      }};

      std::uint8_t table_index;
      bool write_is_ok;

      const bool byte_is_in_range =
        (byte_to_write <
            std::uint8_t(character_table.size()));

      if(byte_is_in_range)
      {
        table_index = byte_to_write;

        write_is_ok = true;
      }
      else
      {
        table_index =
          std::uint8_t(character_table.size() - 1U);

        write_is_ok = false;
      }

      std::cout << char(character_table[table_index]);

      if(dp_is_on)
      {
        std::cout << char('.');
      }

      std::cout << std::endl;

      return write_is_ok;
    }

    virtual bool read(std::uint8_t& byte_to_read) const
    {
      byte_to_read = data;

      return true;
    }

    virtual bool write_dp(const bool dp_on)
    {
      dp_is_on = dp_on;

      return true;
    }

    virtual bool read_dp(bool& dp_on) const
    {
      dp_on = dp_is_on;

      return true;
    }
  };
}

mcal::display::display_seven_segment& mcal::display::display0()
{
  typedef display_console display_type;

  static display_type the_display;

  return the_display;
}
