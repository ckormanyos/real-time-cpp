///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2014_01_10_H_
  #define MCAL_PORT_2014_01_10_H_

  extern void mcal_port_pin_mode_out(const unsigned pin_index, const bool set_direction_to_output);
  extern void mcal_port_pin_set     (const unsigned pin_index, const bool set_value_to_high);
  extern bool mcal_port_pin_read    (const unsigned pin_index);

  namespace mcal
  {
    namespace port
    {
      typedef void config_type;

      inline void init(const config_type*) { }

      template<const unsigned PinIndex>
      class port_pin
      {
      public:
        static void set_direction_output() noexcept { ::mcal_port_pin_mode_out(PinIndex, true); }
        static void set_direction_input () noexcept { ::mcal_port_pin_mode_out(PinIndex, false); }
        static void set_pin_high        () noexcept { ::mcal_port_pin_set (PinIndex, true); }
        static void set_pin_low         () noexcept { ::mcal_port_pin_set (PinIndex, false);}
        static bool read_input_value    () noexcept { return ::mcal_port_pin_read(PinIndex); }
        static void toggle_pin          () noexcept { read_input_value() ? set_pin_low() : set_pin_high(); }
      };
    }
  }

#endif // MCAL_PORT_2014_01_10_H_
