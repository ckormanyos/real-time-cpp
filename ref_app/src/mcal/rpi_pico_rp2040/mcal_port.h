///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2012_06_27_H
  #define MCAL_PORT_2012_06_27_H

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
        static constexpr std::uint32_t sio_xx                      { UINT32_C( 5) };   // sio_xx    : sio_xx
        static constexpr std::uint32_t pio0_xx                     { UINT32_C( 6) };   // pio0_xx   : pio0_xx
        static constexpr std::uint32_t pio1_xx                     { UINT32_C( 7) };   // pio1_xx   : pio1_xx
        static constexpr std::uint32_t port_index                  { PortIndex };
        static constexpr std::uint32_t addr_io_bank0_gpio_pin_ctrl { mcal::reg::io_bank0_status_base + std::uint32_t { port_index * 8U + 4U } };

      public:
        static void set_direction_output()
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sio_gpio_oe_clr, port_index>::bit_set();

          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sio_gpio_out_clr, port_index>::bit_set();

          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, addr_io_bank0_gpio_pin_ctrl, sio_xx << 0U>::template reg_msk<UINT32_C(0x1F) << 0U>();

          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sio_gpio_oe_set, port_index>::bit_set();
        }

        static void set_direction_input()
        {
        }

        static void set_pin_high()
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sio_gpio_out_set, port_index>::bit_set();
        }

        static void set_pin_low()
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sio_gpio_out_clr, port_index>::bit_set();
        }

        static bool read_input_value()
        {
          return false;
        }

        static void toggle_pin()
        {
          mcal::reg::reg_access_static<std::uint32_t, std::uint32_t, mcal::reg::sio_gpio_out_xor, port_index>::bit_set();
        }
      };
    }
  }

#endif // MCAL_PORT_2012_06_27_H
