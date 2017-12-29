///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_LED_2014_07_28_H_
  #define _MCAL_LED_2014_07_28_H_

  #include <cstdint>

  class led
  {
  public:
    led() : is_on(false) { }

    void toggle(void) const;

  private:
    mutable bool is_on;
  };

  extern const led led_b5;

#endif // _MCAL_LED_2014_07_28_H_
