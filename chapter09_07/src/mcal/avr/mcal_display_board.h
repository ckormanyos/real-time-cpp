///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_DISPLAY_BOARD_2017_12_27_H_
  #define MCAL_DISPLAY_BOARD_2017_12_27_H_

  #include <array>
  #include <cstdint>

  #include <mcal_port.h>
  #include <util/device/util_device_display_seven_segment.h>

  namespace mcal
  {
    namespace display
    {
      template<typename segment_a_port,
               typename segment_b_port,
               typename segment_c_port,
               typename segment_d_port,
               typename segment_e_port,
               typename segment_f_port,
               typename segment_g_port,
               typename segment_dp_port>
      class display_board final : public util::device::display_seven_segment
      {
      public:
        display_board() { }

        display_board(const std::uint8_t value_to_write, const bool dp_on)
          : display_seven_segment(value_to_write, dp_on) { }

        virtual ~display_board() { }

      private:
        static void set_ports_for_write()
        {
          static bool ports_are_set_for_write;

          if(ports_are_set_for_write == false)
          {
            ports_are_set_for_write = true;

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
        }

        virtual bool do_write(const std::uint8_t value)
        {
          set_ports_for_write();

          constexpr std::array<std::uint8_t, 16U> character_table =
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
          bool         write_is_ok;

          const bool byte_is_in_range =
            (value < std::uint8_t(character_table.size()));

          if(byte_is_in_range)
          {
            table_index = value;

            write_is_ok = true;
          }
          else
          {
            table_index = std::uint8_t(character_table.size() - 1U);

            write_is_ok = false;
          }

          const std::uint8_t segment_pattern = character_table[table_index];

          set_data(segment_pattern);

          ((std::uint8_t(segment_pattern & UINT8_C(0x01)) != UINT8_C(0)) ? segment_a_port::set_pin_low() : segment_a_port::set_pin_high());
          ((std::uint8_t(segment_pattern & UINT8_C(0x02)) != UINT8_C(0)) ? segment_b_port::set_pin_low() : segment_b_port::set_pin_high());
          ((std::uint8_t(segment_pattern & UINT8_C(0x04)) != UINT8_C(0)) ? segment_c_port::set_pin_low() : segment_c_port::set_pin_high());
          ((std::uint8_t(segment_pattern & UINT8_C(0x08)) != UINT8_C(0)) ? segment_d_port::set_pin_low() : segment_d_port::set_pin_high());
          ((std::uint8_t(segment_pattern & UINT8_C(0x10)) != UINT8_C(0)) ? segment_e_port::set_pin_low() : segment_e_port::set_pin_high());
          ((std::uint8_t(segment_pattern & UINT8_C(0x20)) != UINT8_C(0)) ? segment_f_port::set_pin_low() : segment_f_port::set_pin_high());
          ((std::uint8_t(segment_pattern & UINT8_C(0x40)) != UINT8_C(0)) ? segment_g_port::set_pin_low() : segment_g_port::set_pin_high());

          return write_is_ok;
        }

        virtual bool do_read(std::uint8_t& value_to_read) const
        {
          value_to_read = get_data();

          return true;
        }

        virtual bool do_write_dp(const bool dp_on)
        {
          set_ports_for_write();

          (dp_on ? segment_dp_port::set_pin_low ()
                 : segment_dp_port::set_pin_high());

          set_dp_is_on(dp_on);

          return true;
        }

        virtual bool do_read_dp(bool& dp_on) const
        {
          dp_on = get_dp_is_on();

          return true;
        }
      };
    }
  }

#endif // MCAL_DISPLAY_BOARD_2017_12_27_H_
