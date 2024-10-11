///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_BASE_2020_04_32_H
  #define MCAL_LED_BASE_2020_04_32_H

  #include <util/utility/util_noncopyable.h>

  namespace mcal { namespace led {

  class led_base : private util::noncopyable // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
  {
  public:
    virtual ~led_base() = default;

    virtual auto toggle() -> void = 0;

    virtual auto state_is_on() const -> bool = 0;

  protected:
    constexpr led_base() = default;
  };

  } // namespace led
  } // namespace mcal

#endif // MCAL_LED_BASE_2020_04_32_H
