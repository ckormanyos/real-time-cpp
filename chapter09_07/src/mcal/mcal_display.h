///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_DISPLAY_2015_01_30_H_
  #define _MCAL_DISPLAY_2015_01_30_H_

  #include <cstdint>
  #include <util/utility/util_noncopyable.h>

  namespace mcal
  {
    namespace display
    {
      class display_base : private util::noncopyable
      {
      public:
        virtual ~display_base() { }

        virtual bool write(const std::uint8_t)  = 0;
        virtual bool read (std::uint8_t&) const = 0;

      protected:
        display_base() { }
      };

      class display_seven_segment : public display_base
      {
      public:
        virtual ~display_seven_segment() { }

        virtual bool write   (const std::uint8_t)  = 0;
        virtual bool read    (std::uint8_t&) const = 0;
        virtual bool write_dp(const bool)          = 0;
        virtual bool read_dp (bool&) const         = 0;

      protected:
        display_seven_segment() { }

        std::uint8_t data;
        bool dp_is_on;
      };

      display_seven_segment& display0();
    }
  }

#endif // _MCAL_DISPLAY_2015_01_30_H_
