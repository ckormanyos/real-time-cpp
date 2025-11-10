///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2012_06_27_H
  #define MCAL_PORT_2012_06_27_H

  namespace mcal
  {
    namespace port
    {
      using config_type = void;

      auto init(const config_type*) -> void;

      class port_pin
      {
      public:
        static constexpr auto set_direction_output() noexcept -> void { }
        static constexpr auto set_direction_input () noexcept -> void { }
        static constexpr auto set_pin_high        () noexcept -> void { }
        static constexpr auto set_pin_low         () noexcept -> void { }
        static constexpr auto read_input_value    () noexcept -> bool { return false; }
        static constexpr auto toggle_pin          () noexcept -> void { }
      };
    } // namespace port
  } // namespace mcal

#endif // MCAL_PORT_2012_06_27_H
