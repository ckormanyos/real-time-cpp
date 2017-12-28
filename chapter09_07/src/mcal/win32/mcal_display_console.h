///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_DISPLAY_CONSOLE_2017_12_27_H_
  #define MCAL_DISPLAY_CONSOLE_2017_12_27_H_

  #include <cstdint>

  #include <util/device/util_device_display_seven_segment.h>

  namespace mcal
  {
    namespace display
    {
      class display_console final : public util::device::display_seven_segment
      {
      public:
        display_console() { }

        display_console(const std::uint8_t value_to_write, const bool dp_on)
          : display_seven_segment(value_to_write, dp_on) { }

        virtual ~display_console() { }

      private:
        virtual bool do_write(const std::uint8_t value_to_write);

        virtual bool do_read(std::uint8_t& value_to_read) const
        {
          value_to_read = get_data();

          return true;
        }

        virtual bool do_write_dp(const bool dp_on)
        {
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
  } // namespace mcal::display

#endif // MCAL_DISPLAY_CONSOLE_2017_12_27_H_
