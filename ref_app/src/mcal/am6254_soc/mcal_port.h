///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2014_01_10_H_
  #define MCAL_PORT_2014_01_10_H_

  namespace mcal
  {
    namespace port
    {
      using config_type = void;

      inline void init(const config_type*) { }

      template<const unsigned PORT_ID>
      class port_pin
      {
      public:
        static void set_direction_output()
        {
        }

        static void set_direction_input()
        {
        }

        static void set_pin_high()
        {
        }

        static void set_pin_low()
        {
        }

        static bool read_input_value()
        {
          return false;
        }

        static void toggle_pin()
        {
        }
      };
    }
  }

#endif // MCAL_PORT_2014_01_10_H
