///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_PORT_2012_06_27_H_
  #define _MCAL_PORT_2012_06_27_H_

  #include <mcal_reg_access.h>

  namespace mcal
  {
    namespace port
    {
      typedef void config_type;
      void init(const config_type*);

      template<typename addr_type,
               typename reg_type,
               const addr_type port,
               const reg_type bpos>
      class port_pin
      {
      public:
        static void set_direction_output() { }
        static void set_direction_input() { }
        static void set_pin_high() { }
        static void set_pin_low() { }
        static bool read_input_value() { return false; }
        static void toggle_pin() { }
      };

      typedef port_pin<std::uint32_t, std::uint32_t, 0U, 0U> port_rdm_type;
    }
  }

#endif // _MCAL_PORT_2012_06_27_H_
