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
        static constexpr std::uint32_t spi1_ss_n                   { UINT32_C( 1) };   // spi1_ss_n : spi1_ss_n
        static constexpr std::uint32_t uart1_rx                    { UINT32_C( 2) };   // uart1_rx  : uart1_rx
        static constexpr std::uint32_t i2c0_scl                    { UINT32_C( 3) };   // i2c0_scl  : i2c0_scl
        static constexpr std::uint32_t pwm_b_4                     { UINT32_C( 4) };   // pwm_b_4   : pwm_b_4
        static constexpr std::uint32_t sio_xx                      { UINT32_C( 5) };   // sio_xx    : sio_xx
        static constexpr std::uint32_t pio0_xx                     { UINT32_C( 6) };   // pio0_xx   : pio0_xx
        static constexpr std::uint32_t pio1_xx                     { UINT32_C( 7) };   // pio1_xx   : pio1_xx
        static constexpr std::uint32_t clocks_gpout_3              { UINT32_C( 8) };   // clocks_gpout_3 : clocks_gpout_3
        static constexpr std::uint32_t usb_muxing_vbus_detect      { UINT32_C( 9) };   // usb_muxing_vbus_detect : usb_muxing_vbus_detect
        static constexpr std::uint32_t null                        { UINT32_C(31) };   // null : null

        static constexpr std::uint32_t port_index                  { PortIndex };
        static constexpr std::uint32_t addr_io_bank0_gpio_pin_ctrl { mcal::reg::io_bank0_status_base + std::uint32_t { port_index * 8U + 4U } };

      public:
        static void set_direction_output()
        {
          // SIO->GPIO_OE_CLR.bit.GPIO_OE_CLR |= 1UL<<pin;
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       mcal::reg::sio_gpio_oe_clr,
                                       port_index>::bit_set();

          // SIO->GPIO_OUT_CLR.bit.GPIO_OUT_CLR |= 1UL<<pin;
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       mcal::reg::sio_gpio_out_clr,
                                       port_index>::bit_set();

          // IO_BANK0->GPIO##pin##_CTRL.bit.FUNCSEL = sio_xx;
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       addr_io_bank0_gpio_pin_ctrl,
                                       sio_xx << 0U>::template reg_msk<UINT32_C(0x1F) << 0U>();

          // SIO->GPIO_OE_SET.bit.GPIO_OE_SET |= 1UL<<pin
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       mcal::reg::sio_gpio_oe_set,
                                       port_index>::bit_set();
        }

        static void set_direction_input()
        {
        }

        static void set_pin_high()
        {
          // SIO->GPIO_OUT_SET.bit.GPIO_OUT_SET |= 1UL<<pin
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       mcal::reg::sio_gpio_out_set,
                                       port_index>::bit_set();
        }

        static void set_pin_low()
        {
          // SIO->GPIO_OUT_CLR.bit.GPIO_OUT_CLR |= 1UL<<pin
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       mcal::reg::sio_gpio_out_clr,
                                       port_index>::bit_set();
        }

        static bool read_input_value()
        {
          return false;
        }

        static void toggle_pin()
        {
          // SIO->GPIO_OUT_XOR.bit.GPIO_OUT_XOR |= 1UL<<pin
          mcal::reg::reg_access_static<std::uint32_t,
                                       std::uint32_t,
                                       mcal::reg::sio_gpio_out_xor,
                                       port_index>::bit_set();
        }
      };
    }
  }

#endif // MCAL_PORT_2012_06_27_H_
