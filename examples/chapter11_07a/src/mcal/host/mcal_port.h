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

      inline auto init(const config_type*) -> void { }

      class port_pin
      {
      public:
        static auto set_direction_output() -> void { }
        static auto set_direction_input () -> void { }
        static auto set_pin_high        () -> void { }
        static auto set_pin_low         () -> void { }
        static auto read_input_value    () -> bool { return false; }
        static auto toggle_pin          () -> void { }
      };
    }
  }

#endif // MCAL_PORT_2012_06_27_H
