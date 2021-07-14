///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PORT_PIN_DUMMY_2020_05_05_H_
  #define PORT_PIN_DUMMY_2020_05_05_H_

  namespace mcal { namespace port {

  class port_pin_dummy
  {
  public:
    static void init                () noexcept { }
    static void set_direction_output() noexcept { }
    static void set_direction_input () noexcept { }
    static void set_pin_high        () noexcept { }
    static void set_pin_low         () noexcept { }
    static bool read_input_value    () noexcept { return false; }
    static void toggle_pin          () noexcept { }
  };

  } } // namespace mcal::port

#endif // PORT_PIN_DUMMY_2020_05_05_H_
