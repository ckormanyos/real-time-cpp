///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2012_06_27_H_
  #define MCAL_PORT_2012_06_27_H_

  #include <mcal_reg.h>

  #include <cstdint>

  namespace mcal
  {
    namespace port
    {
      typedef void config_type;
      void init(const config_type*);

      template<const unsigned PortIndex>
      class port_pin
      {
      private:
        static constexpr std::uint32_t my_pin { PortIndex };

      public:
        static void set_direction_output()
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sio_gpio_oe_clr, my_pin>::bit_set();
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sio_gpio_oe_clr, my_pin>::bit_set();
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, std::uint32_t { mcal::reg::io_bank0_base + (8U * my_pin) + 4U }, std::uint32_t { UINT32_C(5) << 0U }>::template reg_msk<std::uint32_t { UINT32_C(0x1F) << 0U }>();
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sio_gpio_oe_set, my_pin>::bit_set();
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, std::uint32_t { mcal::reg::pads_bank0_base + (4U * my_pin) + 4U }, std::uint32_t { UINT32_C(8) }>::bit_clr();
        }

        static void set_direction_input()
        {
        }

        static void set_pin_high()
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sio_gpio_out_set, my_pin>::bit_set();
        }

        static void set_pin_low()
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sio_gpio_out_clr, my_pin>::bit_set();
        }

        static bool read_input_value()
        {
          return false;
        }

        static void toggle_pin()
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sio_gpio_out_xor, my_pin>::bit_set();
        }
      };
    }
  }

#endif // MCAL_PORT_2012_06_27_H_
