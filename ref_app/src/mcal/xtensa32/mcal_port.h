///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2014_01_10_H_
  #define MCAL_PORT_2014_01_10_H_

  #include <mcal_reg.h>

  namespace mcal
  {
    namespace port
    {
      typedef void config_type;

      void init(const config_type*);

      class port_pin
      {
      public:
        static void set_direction_output() noexcept { }
        static void set_direction_input () noexcept { }
        static void set_pin_high        () noexcept { }
        static void set_pin_low         () noexcept { }
        static bool read_input_value    () noexcept { return false; }
        static void toggle_pin          () noexcept { }
      };
    }
  }

#endif // MCAL_PORT_2014_01_10_H_
