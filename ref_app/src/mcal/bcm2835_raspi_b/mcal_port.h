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

  #define GPIO_PIN02_H03      (uint8_t) (0x02U)
  #define GPIO_PIN03_H05      (uint8_t) (0x03U)
  #define GPIO_PIN04_H07      (uint8_t) (0x04U)
  #define GPIO_PIN17_H11      (uint8_t) (0x17U)
  #define GPIO_PIN27_H13      (uint8_t) (0x27U)
  #define GPIO_PIN22_H15      (uint8_t) (0x22U)
  #define GPIO_PIN10_H19      (uint8_t) (0x10U)
  #define GPIO_PIN09_H21      (uint8_t) (0x09U)
  #define GPIO_PIN11_H23      (uint8_t) (0x11U)
  #define GPIO_PIN05_H29      (uint8_t) (0x05U)
  #define GPIO_PIN06_H31      (uint8_t) (0x06U)
  #define GPIO_PIN13_H33      (uint8_t) (0x13U)
  #define GPIO_PIN19_H35      (uint8_t) (0x19U)
  #define GPIO_PIN26_H37      (uint8_t) (0x26U)
  #define GPIO_PIN14_H08      (uint8_t) (0x14U)
  #define GPIO_PIN15_H10      (uint8_t) (0x15U)
  #define GPIO_PIN18_H12      (uint8_t) (0x18U)
  #define GPIO_PIN23_H16      (uint8_t) (0x23U)
  #define GPIO_PIN24_H18      (uint8_t) (0x24U)
  #define GPIO_PIN25_H22      (uint8_t) (0x25U)
  #define GPIO_PIN08_H24      (uint8_t) (0x08U)
  #define GPIO_PIN07_H26      (uint8_t) (0x07U)
  #define GPIO_PIN12_H32      (uint8_t) (0x12U)
  #define GPIO_PIN16_H36      (uint8_t) (0x16U)
  #define GPIO_PIN20_H38      (uint8_t) (0x20U)
  #define GPIO_PIN21_H40      (uint8_t) (0x21U)

  #define GPIO_STATUS_LED     (uint8_t) (0x47U)

  #if defined(__cplusplus)
  namespace mcal
  {
    namespace port
    {
      typedef void config_type;
      void init(const config_type*);

      class port_pin_base
      {
      protected:
        static constexpr std::uint32_t GPFSEL0_ADDR         = UINT32_C(0x20200000);

        static constexpr std::uint32_t GPIO_PIN_X_INPUT     = UINT32_C(0);
        static constexpr std::uint32_t GPIO_PIN_X_OUTPUT    = UINT32_C(1);

        static constexpr std::uint32_t GPCLR0_ADDR          = UINT32_C(0x20200028);
        static constexpr std::uint32_t GPCLR1_ADDR          = UINT32_C(0x2020002C);

        static constexpr std::uint32_t GPSET0_ADDR          = UINT32_C(0x2020001C);
        static constexpr std::uint32_t GPSET1_ADDR          = UINT32_C(0x20200020);

        static constexpr std::uint32_t GPIO_NO_EFFECT       = UINT32_C(0);
        static constexpr std::uint32_t GPIO_SET_GPIO_PIN_X  = UINT32_C(1);
      };

      template<const std::uint8_t PortPin>
      class port_pin : public port_pin_base
      {
      private:
        static bool pin_is_high;

        static constexpr std::uint32_t port    = (std::uint32_t) ((PortPin & 0xF0U) >> 4u);
        static constexpr std::uint32_t pin     = (std::uint32_t) (PortPin & 0x0FU);
        static constexpr std::uint32_t pos     = (std::uint32_t) ((port * 10U) + pin);
        static constexpr std::uint32_t addfsel = (std::uint32_t) (GPFSEL0_ADDR + (std::uint32_t) (4U * port));
        static constexpr std::uint32_t valfout = (std::uint32_t) GPIO_PIN_X_OUTPUT << (pin * 3U);

        static constexpr std::uint32_t addclr  = (std::uint32_t) ((PortPin < 0x32U) ? GPCLR0_ADDR : GPCLR1_ADDR);
        static constexpr std::uint32_t valclr  = (std::uint32_t) ((std::uint32_t) GPIO_SET_GPIO_PIN_X << ((pos < 32U) ? (pos) : (pos - 32U)));

        static constexpr std::uint32_t addset  = (std::uint32_t) ((PortPin < 0x32U) ? GPSET0_ADDR : GPSET1_ADDR);
        static constexpr std::uint32_t valset  = (std::uint32_t) ((std::uint32_t) GPIO_SET_GPIO_PIN_X << ((pos < 32u) ? (pos) : (pos - 32u)));

      public:
        static void set_direction_output()
        {
          mcal_reg_access32_reg_or(addfsel, valfout);
        }

        static void set_direction_input() { }

        static void set_pin_high()
        {
          mcal_reg_access32_reg_or(addset, valset);

          pin_is_high = true;
        }

        static void set_pin_low()
        {
          mcal_reg_access32_reg_or(addclr, valclr);

          pin_is_high = false;
        }

        static bool read_input_value() { return false; }

        static void toggle_pin()
        {
          (pin_is_high ? set_pin_low() : set_pin_high());
        }
      };

      template<const std::uint8_t PortPin>
      bool port_pin<PortPin>::pin_is_high;
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
