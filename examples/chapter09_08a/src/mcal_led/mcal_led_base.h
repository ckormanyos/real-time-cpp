///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_BASE_2020_04_32_H_
  #define MCAL_LED_BASE_2020_04_32_H_

  #include <util/utility/util_noncopyable.h>

  namespace mcal { namespace led {

  class led_base : private util::noncopyable
  {
  public:
    virtual auto toggle() -> void = 0;
    virtual auto state_is_on() const -> bool = 0;

    virtual ~led_base() = default;

  protected:
    led_base() = default;
  };

  } // namespace led
  } // namespace mcal

#endif // MCAL_LED_BASE_2020_04_32_H_
