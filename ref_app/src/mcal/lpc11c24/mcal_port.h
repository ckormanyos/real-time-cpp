///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Copyright Joel Winarske 2019.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2019_06_21_H_
  #define MCAL_PORT_2019_06_21_H_

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
      public:

        static void set_direction_output()
        {
          mcal::reg::reg_access_static<addr_type, reg_type,
                                       dir_reg, bpos>::bit_set();
        }

        static void set_direction_input()
        {
          mcal::reg::reg_access_static<addr_type, reg_type,
                                       dir_reg, bpos>::bit_clr();
        }

        static void set_pin_high()
        {
          // Set the port output value to high.
          mcal::reg::reg_access_static<addr_type, reg_type,
                                       data_reg, out_val_high>::reg_set();
        }

        static void set_pin_low()
        {
          // Set the port output value to low.
          mcal::reg::reg_access_static<addr_type, reg_type,
                                       data_reg, out_val_low>::reg_set();
        }

        static bool read_input_value()
        {
          // Read the port input value.
          return static_cast<bool>(
            (mcal::reg::reg_access_static<addr_type, reg_type,
                                          data_reg>::reg_get() >> bpos) & 1);
        }

        static void toggle_pin()
        {
          // Toggle the port output value.
          mcal::reg::reg_access_static<addr_type, reg_type,
                                       data_reg, bpos>::bit_not();
        }

      private:
        static constexpr std::uint32_t data_reg = port + (UINT32_C(4) * (1 << bpos));
        static constexpr std::uint32_t dir_reg = port + UINT32_C(0x8000);

        static constexpr std::uint32_t out_val_high = 1UL << bpos;
        static constexpr std::uint32_t out_val_low = 0UL << bpos;
      };
    }
  }

#endif // MCAL_PORT_2019_06_21_H_
