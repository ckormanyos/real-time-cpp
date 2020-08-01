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

  #if defined(__cplusplus)
  namespace mcal
  {
    namespace port
    {
      typedef void config_type;
      void init(const config_type*);

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

  void mcal_port_pin_clr(uint8_t PortPin);
  void mcal_port_pin_set(uint8_t PortPin);

  #if defined(__cplusplus)
  }
  #endif

#endif // MCAL_PORT_2012_06_27_H_
