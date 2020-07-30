///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2012_06_27_H_
  #define MCAL_PORT_2012_06_27_H_

  #include <mcal_reg.h>

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
      private:
        using address_uintptr_type = addr_type;
        using register_value_type  = reg_type;

        static constexpr address_uintptr_type port_address = port;
        static constexpr address_uintptr_type pdir_address = port_address - address_uintptr_type(1U);
        static constexpr address_uintptr_type pinp_address = port_address - address_uintptr_type(2U);
        static constexpr register_value_type  bpos_value   = bpos;
        static constexpr address_uintptr_type sfr_offset   = address_uintptr_type(0x20U);

      public:
        static void set_direction_output()
        {
          // Set the port pin's direction to output.
          // C++:
          // mcal::reg::reg_access_static<address_uintptr_type,
          //                              register_value_type,
          //                              pdir_address,
          //                              bpos_value>::bit_set();
          asm volatile("sbi %[myport],%[mybit]" : : [myport]"I"(pdir_address - sfr_offset), [mybit]"I"(bpos_value));
        }

        static void set_direction_input()
        {
          // Set the port pin's direction to input.
          // C++:
          // mcal::reg::reg_access_static<address_uintptr_type,
          //                              register_value_type,
          //                              pdir_address,
          //                              bpos_value>::bit_clr();
          asm volatile("cbi %[myport],%[mybit]" : : [myport]"I"(pdir_address - sfr_offset), [mybit]"I"(bpos_value));
        }

        static void set_pin_high()
        {
          // Set the port output value to high.
          // C++:
          // mcal::reg::reg_access_static<address_uintptr_type,
          //                              register_value_type,
          //                              port_address,
          //                              bpos_value>::bit_set();
          asm volatile("sbi %[myport],%[mybit]" : : [myport]"I"(port_address - sfr_offset), [mybit]"I"(bpos_value));
        }

        static void set_pin_low()
        {
          // Set the port output value to low.
          // C++:
          // mcal::reg::reg_access_static<address_uintptr_type,
          //                              register_value_type,
          //                              port_address,
          //                              bpos_value>::bit_clr();
          asm volatile("cbi %[myport],%[mybit]" : : [myport]"I"(port_address - sfr_offset), [mybit]"I"(bpos_value));
        }

        static bool read_input_value()
        {
          // Read the port input value.
          return mcal::reg::reg_access_static<address_uintptr_type,
                                              register_value_type,
                                              pinp_address,
                                              bpos_value>::bit_get();
        }

        static void toggle_pin()
        {
          // Toggle the port output value.
          mcal::reg::reg_access_static<address_uintptr_type,
                                       register_value_type,
                                       port_address,
                                       bpos_value>::bit_not();
        }
      };
    }
  }

#endif // MCAL_PORT_2012_06_27_H_
