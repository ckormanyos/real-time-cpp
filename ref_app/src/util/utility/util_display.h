///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_DISPLAY_2023_06_09_H
  #define UTIL_DISPLAY_2023_06_09_H

  #include <cstdint>

  #include <util/utility/util_noncopyable.h>
  #include <util/utility/util_time.h>

  namespace util {

  class display_multiline_base : private util::noncopyable
  {
  public:
    virtual ~display_multiline_base() = default;

    virtual auto init() noexcept -> bool = 0;

    virtual auto write(const char* pstr,
                       const std::uint_fast8_t length,
                       const std::uint_fast8_t line_index) -> bool = 0;

  protected:
    display_multiline_base() noexcept = default;

    virtual auto set_line_index(const std::uint8_t) noexcept -> bool { return true; }

    using timer_type = util::timer<std::uint32_t>;

    static void blocking_delay(const typename timer_type::tick_type blocking_delay_value)
    {
      timer_type::blocking_delay(blocking_delay_value);
    }
  };

  } // namespace util

#endif // UTIL_DISPLAY_2023_06_09_H
