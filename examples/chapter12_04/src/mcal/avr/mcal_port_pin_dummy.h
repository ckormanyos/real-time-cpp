///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PORT_PIN_DUMMY_2020_05_05_H
  #define PORT_PIN_DUMMY_2020_05_05_H

  namespace mcal { namespace port {

  class port_pin_dummy
  {
  public:
    static auto init                () noexcept -> void { }
    static auto set_direction_output() noexcept -> void { }
    static auto set_direction_input () noexcept -> void { }
    static auto set_pin_high        () noexcept -> void { }
    static auto set_pin_low         () noexcept -> void { }
    static auto read_input_value    () noexcept -> bool { return false; }
    static auto toggle_pin          () noexcept -> void { }
  };

  } } // namespace mcal::port

#endif // PORT_PIN_DUMMY_2020_05_05_H
