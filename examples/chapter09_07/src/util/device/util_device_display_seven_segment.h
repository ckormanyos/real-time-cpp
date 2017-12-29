///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_DEVICE_DISPLAY_SEVEN_SEGMENT_2017_12_27_H_
  #define UTIL_DEVICE_DISPLAY_SEVEN_SEGMENT_2017_12_27_H_

  #include <cstdint>
  #include <iterator>

  #include <util/device/util_device_display_base.h>

  namespace util
  {
    namespace device
    {
      class display_seven_segment : public display_base
      {
      public:
        virtual ~display_seven_segment() { }

        bool write_dp(const bool dp_on)
        {
          return do_write_dp(dp_on);
        }

        bool read_dp(bool& dp_on) const
        {
          return do_read_dp(dp_on);
        }

      protected:
        display_seven_segment() : my_dp_is_on() { }

        display_seven_segment(const std::uint8_t value_to_write, const bool dp_on)
          : display_base(value_to_write),
            my_dp_is_on()
        {
          const bool write_dp_is_ok = write_dp(dp_on);

          static_cast<void>(write_dp_is_ok);
        }

        void set_dp_is_on(const bool dp_on) { my_dp_is_on = dp_on; }

        bool get_dp_is_on() const { return my_dp_is_on; }

      private:
        bool my_dp_is_on;

        virtual bool do_write_dp(const bool dp_on)  = 0;
        virtual bool do_read_dp (bool& dp_on) const = 0;
      };
    }
  } // namespace util::device

#endif // UTIL_DEVICE_DISPLAY_SEVEN_SEGMENT_2017_12_27_H_
