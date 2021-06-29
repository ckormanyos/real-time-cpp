///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PORT_2012_06_27_H_
  #define MCAL_PORT_2012_06_27_H_

  #if defined(__cplusplus)
  #include <cstdint>
  #else
  #include <stdint.h>
  #endif

  #include <mcal_reg.h>

  #if defined(__cplusplus)

  void mcal_port_pin_expander_set_direction_output(const uint8_t bpos);
  void mcal_port_pin_expander_set_direction_input (const uint8_t bpos);
  void mcal_port_pin_expander_set_pin_high        (const uint8_t bpos);
  void mcal_port_pin_expander_set_pin_low         (const uint8_t bpos);
  bool mcal_port_pin_expander_read_input_value    (const uint8_t bpos);
  void mcal_port_pin_expander_toggle_pin          (const uint8_t bpos);

  namespace mcal
  {
    namespace port
    {
      typedef void config_type;

      void init(const config_type*);

      constexpr std::uint8_t gpio_pin02_h03 = UINT8_C(0x02U);
      constexpr std::uint8_t gpio_pin03_h05 = UINT8_C(0x03U);
      constexpr std::uint8_t gpio_pin04_h07 = UINT8_C(0x04U);
      constexpr std::uint8_t gpio_pin17_h11 = UINT8_C(0x17U);
      constexpr std::uint8_t gpio_pin27_h13 = UINT8_C(0x27U);
      constexpr std::uint8_t gpio_pin22_h15 = UINT8_C(0x22U);
      constexpr std::uint8_t gpio_pin10_h19 = UINT8_C(0x10U);
      constexpr std::uint8_t gpio_pin09_h21 = UINT8_C(0x09U);
      constexpr std::uint8_t gpio_pin11_h23 = UINT8_C(0x11U);
      constexpr std::uint8_t gpio_pin05_h29 = UINT8_C(0x05U);
      constexpr std::uint8_t gpio_pin06_h31 = UINT8_C(0x06U);
      constexpr std::uint8_t gpio_pin13_h33 = UINT8_C(0x13U);
      constexpr std::uint8_t gpio_pin19_h35 = UINT8_C(0x19U);
      constexpr std::uint8_t gpio_pin26_h37 = UINT8_C(0x26U);
      constexpr std::uint8_t gpio_pin14_h08 = UINT8_C(0x14U);
      constexpr std::uint8_t gpio_pin15_h10 = UINT8_C(0x15U);
      constexpr std::uint8_t gpio_pin18_h12 = UINT8_C(0x18U);
      constexpr std::uint8_t gpio_pin23_h16 = UINT8_C(0x23U);
      constexpr std::uint8_t gpio_pin24_h18 = UINT8_C(0x24U);
      constexpr std::uint8_t gpio_pin25_h22 = UINT8_C(0x25U);
      constexpr std::uint8_t gpio_pin08_h24 = UINT8_C(0x08U);
      constexpr std::uint8_t gpio_pin07_h26 = UINT8_C(0x07U);
      constexpr std::uint8_t gpio_pin12_h32 = UINT8_C(0x12U);
      constexpr std::uint8_t gpio_pin16_h36 = UINT8_C(0x16U);
      constexpr std::uint8_t gpio_pin20_h38 = UINT8_C(0x20U);
      constexpr std::uint8_t gpio_pin21_h40 = UINT8_C(0x21U);

      constexpr std::uint8_t gpio_status_led = UINT8_C(0x47U);

      class port_pin_base
      {
      protected:
        static constexpr std::uint32_t gpfsel0_addr         = UINT32_C(0x20200000);

        static constexpr std::uint32_t gpio_pin_x_input     = UINT32_C(0);
        static constexpr std::uint32_t gpio_pin_x_output    = UINT32_C(1);

        static constexpr std::uint32_t gpclr0_addr          = UINT32_C(0x20200028);
        static constexpr std::uint32_t gpclr1_addr          = UINT32_C(0x2020002C);

        static constexpr std::uint32_t gpset0_addr          = UINT32_C(0x2020001C);
        static constexpr std::uint32_t gpset1_addr          = UINT32_C(0x20200020);

        static constexpr std::uint32_t gpio_no_effect       = UINT32_C(0);
        static constexpr std::uint32_t gpio_set_gpio_pin_x  = UINT32_C(1);
      };

      template<const std::uint8_t GpioPin>
      class port_pin : public port_pin_base
      {
      private:
        static bool my_pin_is_high;

        static constexpr std::uint8_t  gpio_pin = GpioPin;

        static constexpr std::uint32_t port     = (std::uint32_t) ((gpio_pin & 0xF0U) >> 4U);
        static constexpr std::uint32_t pin      = (std::uint32_t)  (gpio_pin & 0x0FU);
        static constexpr std::uint32_t pos      = (std::uint32_t) ((port * 10U) + pin);
        static constexpr std::uint32_t addfsel  = (std::uint32_t)  (gpfsel0_addr + (std::uint32_t) (4U * port));
        static constexpr std::uint32_t valfout  = (std::uint32_t)   gpio_pin_x_output << (pin * 3U);

        static constexpr std::uint32_t addclr   = (std::uint32_t) ((gpio_pin < 0x32U) ? gpclr0_addr : gpclr1_addr);
        static constexpr std::uint32_t valclr   = (std::uint32_t) ((std::uint32_t) gpio_set_gpio_pin_x << ((pos < 32U) ? (pos) : (pos - 32U)));

        static constexpr std::uint32_t addset   = (std::uint32_t) ((gpio_pin < 0x32U) ? gpset0_addr : gpset1_addr);
        static constexpr std::uint32_t valset   = (std::uint32_t) ((std::uint32_t) gpio_set_gpio_pin_x << ((pos < 32U) ? (pos) : (pos - 32U)));

      public:
        static void set_direction_output()
        {
          mcal_reg_access32_reg_or(addfsel, valfout);
        }

        static void set_direction_input()
        {
          // TBD: Not yet implemented.
        }

        static void set_pin_high()
        {
          mcal_reg_access32_reg_or(addset, valset);

          my_pin_is_high = true;
        }

        static void set_pin_low()
        {
          mcal_reg_access32_reg_or(addclr, valclr);

          my_pin_is_high = false;
        }

        static bool read_input_value()
        {
          // TBD: Not yet implemented.
          return false;
        }

        static void toggle_pin()
        {
          (my_pin_is_high ? set_pin_low() : set_pin_high());
        }
      };

      template<const std::uint8_t PortPin>
      bool port_pin<PortPin>::my_pin_is_high;

      template<const std::uint8_t bpos>
      class port_pin_expander
      {
      public:
        static void set_direction_output() {        mcal_port_pin_expander_set_direction_output(bpos); }
        static void set_direction_input () {        mcal_port_pin_expander_set_direction_input (bpos); }
        static void set_pin_high        () {        mcal_port_pin_expander_set_pin_high        (bpos); }
        static void set_pin_low         () {        mcal_port_pin_expander_set_pin_low         (bpos); }
        static bool read_input_value    () { return mcal_port_pin_expander_read_input_value    (bpos); }
        static void toggle_pin          () {        mcal_port_pin_expander_toggle_pin          (bpos); }
      };
    }
  }
  #endif

  #if defined(__cplusplus)
  #include <cstdint>
  #else
  #include <stdint.h>
  #endif

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  void mcal_port_pin_clr(uint8_t PortPin);
  void mcal_port_pin_set(uint8_t PortPin);

  #if defined(__cplusplus)
  }
  #endif

#endif // MCAL_PORT_2012_06_27_H_
